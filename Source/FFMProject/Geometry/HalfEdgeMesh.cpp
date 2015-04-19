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
		outVertices.Add(edge->vert_->pos_);
		edge = edge->next_;
	} while (edge != edge_);
}

HE_Edge* HE_Face::FindEdge(const FVector& v0, const FVector& v1, bool bExcludeEdgeWithPair) const
{
	HE_Edge* edge = edge_;
	do
	{
		if(!bExcludeEdgeWithPair || !edge->pair_)
		{
			if (v0.Equals(edge->vert_->pos_) && v1.Equals(edge->next_->vert_->pos_))
				return edge;
		}
		edge = edge->next_;
	} while (edge != edge_);
	return NULL;
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
					pair->pair_ = edge;
					edge->pair_ = pair;
					break;
				}
			}
		}
		edge = edge->next_;
	} while (edge != pFace->edge_);
}

}