#include "FFMProject.h"
#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

void HalfEdgeMesh::AddFace(const TSharedPtr<HE_Face>& pFace)
{
	m_pFaces.Add(pFace);
}

void MakeVertexList(const TSharedPtr<HE_Face>& face, TArray<FVector>& outVertices)
{
	HE_Edge* edge = face->edge;
	do
	{
		outVertices.Add(edge->vert->pos);
		edge = edge->next;
	} while (edge != face->edge);
}

}