#include "FFMProject.h"
#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

void HE_Vertex::GetNeighboringVertices(TArray<HE_Vertex*>& outVertices) const
{
	HE_Edge* edge = edge_;
	bool bCircular = true;
	do
	{
		outVertices.Add(edge->next_->vert_);
		if (!edge->pair_)
		{
			bCircular = false;
			break;
		}
		edge = edge->pair_->next_;
	} while (edge != edge_);

	if (bCircular)
		return;
	
	edge = edge_->prev_;
	do
	{
		outVertices.Add(edge->vert_);
		if (!edge->pair_)
			break;
		edge = edge->pair_->prev_;
	} while (edge != edge_);
}

HE_Face::~HE_Face()
{
	if (edge_)
	{
		HE_Edge* edge = edge_;
		do
		{
			HE_Edge* prev = edge;
			edge = edge->next_;
			delete prev;
		} while (edge != edge_);
	}
}

void HE_Face::MakeVertexList(TArray<FVector>& outVertices) const
{
	HE_Edge* edge = edge_;
	do
	{
		outVertices.Add(edge->vert_->pos_->p_);
		edge = edge->next_;
	} while (edge != edge_);
}

HE_Edge* HE_Face::FindEdge(const HE_Pos* v0, const HE_Pos* v1, bool bExcludeEdgeWithPair) const
{
	HE_Edge* edge = edge_;
	do
	{
		if(!bExcludeEdgeWithPair || !edge->pair_)
		{
			if ( v0 == edge->vert_->pos_ && v1 == edge->next_->vert_->pos_ )
				return edge;
		}
		edge = edge->next_;
	} while (edge != edge_);
	return NULL;
}
    
HalfEdgeMesh::~HalfEdgeMesh()
{
    Clear();
}
    
void HalfEdgeMesh::Clear()
{
    m_pFaces.RemoveAll( [&](const HE_FacePtr&){return true;} );

    for( int i = 0, iCount(m_pPosList.Num()); i < iCount; ++i )
        delete m_pPosList[i];
    m_pPosList.RemoveAll( [&](HE_Pos*&){return true;} );
}

void HalfEdgeMesh::SolvePair(const HE_FacePtr& pFace)
{
	HE_Edge* edge = pFace->edge_;
	do
	{
		if (!edge->pair_)
		{
			for (int i = 0, iCount(m_pFaces.Num()); i < iCount; ++i)
			{
				if (m_pFaces[i] == pFace)
					continue;
				HE_Edge* pair = m_pFaces[i]->FindEdge(edge->next_->vert_->pos_, edge->vert_->pos_, true);
				if (pair)
				{
					edge->SetPair(pair);
					break;
				}
			}
		}
		edge = edge->next_;
	} while (edge != pFace->edge_);
}
    
HE_Pos* HalfEdgeMesh::FindPos( const FVector& pos )
{
    for( int i = 0, iCount(m_pPosList.Num()); i < iCount; ++i )
    {
        if ( m_pPosList[i]->p_.Equals(pos) )
            return m_pPosList[i];
    }
    
    HE_Pos* pNewPos = new HE_Pos(pos);
    m_pPosList.Add(pNewPos);
    
    return pNewPos;
}

}