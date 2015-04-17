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

void HalfEdgeMesh::AddFace(const HE_FacePtr& pFace)
{
	m_pFaces.Add(pFace);
}

}