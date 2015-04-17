#include "FFMProject.h"
#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

void HalfEdgeMesh::AddFace(const HE_FacePtr& pFace)
{
	m_pFaces.Add(pFace);
}

void MakeVertexList(const HE_FacePtr& face, TArray<FVector>& outVertices)
{
	HE_Edge* edge = face->edge;
	do
	{
		outVertices.Add(edge->vert->pos);
		edge = edge->next;
	} while (edge != face->edge);
}

}