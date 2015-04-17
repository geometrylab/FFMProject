#include "FFMProject.h"
#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

HE_Face::~HE_Face()
{
	if (edge)
	{
		HE_Edge* pEntryEdge = edge;
		do
		{
			HE_Edge* pDeletedEdge = edge;
			edge = edge->next;
			delete pDeletedEdge;
		} while (edge != pEntryEdge);
	}
}

void HE_Face::MakeVertexList(TArray<FVector>& outVertices)
{
	HE_Edge* _edge = edge;
	do
	{
		outVertices.Add(_edge->vert->pos);
		_edge = _edge->next;
	} while (_edge != edge);
}

HE_Edge* HE_Face::FindEdge(const FVector& v0, const FVector& v1, bool bExcludeEdgeWithPair)
{
	HE_Edge* _edge = edge;
	do
	{	
		if(!bExcludeEdgeWithPair || !_edge->pair)
		{
			if (v0.Equals(_edge->vert->pos) && v1.Equals(_edge->next->vert->pos))
				return _edge;
		}
		_edge = _edge->next;
	} while (_edge != edge);
	return NULL;
}

void HalfEdgeMesh::SolvePair(const HE_FacePtr& pFace)
{
	HE_Edge* edge = pFace->edge;
	do
	{
		for (int i = 0, iCount(m_pFaces.Num()); i < iCount; ++i)
		{
			HE_Edge* foundEdge = m_pFaces[i]->FindEdge(edge->next->vert->pos, edge->vert->pos, true);
			if (foundEdge)
			{
				foundEdge->pair = edge;
				edge->pair = foundEdge;
				break;
			}
		}
		edge = edge->next;
	} while (edge != pFace->edge);
}

}