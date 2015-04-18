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
		verts[i]->edge_ = edges[i];
		verts[i]->pos_ = vertices[i];

		edges[i]->vert_ = verts[i];
		edges[i]->pair_ = NULL;
		edges[i]->next_ = edges[(i + 1) % vCount];
		edges[i]->face_ = face;
	}

	HalfEdgeMesh::SolvePair(face);
	HalfEdgeMesh::AddFace(face);
}

};