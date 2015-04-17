#include "FFMProject.h"
#include "GeometryCommon.h"
#include "Model.h"

namespace FFMGeometry
{

void Model::AddFace(const TArray<FVector>& vertices)
{
	int32 vCount = vertices.Num();

	TArray<HE_Edge*> edges;
	TArray<HE_Vertex*> verts;

	for (int32 i = 0; i < vCount; ++i)
	{
		verts.Add(new HE_Vertex);
		edges.Add(new HE_Edge);
	}

	HE_FacePtr face = HE_FacePtr(new HE_Face(edges[0]));

	for (int32 i = 0; i < vCount; ++i)
	{
		verts[i]->edge = edges[i];
		verts[i]->pos = vertices[i];

		edges[i]->vert = verts[i];
		edges[i]->pair = NULL;
		edges[i]->next = edges[(i + 1) % vCount];
		edges[i]->face = face;
	}

	HalfEdgeMesh::SolvePair(face);
	HalfEdgeMesh::AddFace(face);
}

};