#include "FFMProject.h"
#include "GeometryCommon.h"
#include "Model.h"

namespace FFMGeometry
{

void Model::AddFace(const TArray<FVector>& vertices)
{
	int32 vCount = vertices.Num();

	HE_Edge** edges = new HE_Edge*[vCount];
	HE_Vertex** verts = new HE_Vertex*[vCount];
	HE_FacePtr face = HE_FacePtr(new HE_Face(edges[0]));

	for (int32 i = 0; i < vCount; ++i)
	{
		*(verts[i]) = HE_Vertex(vertices[i], edges[i]);
		*(edges[i]) = HE_Edge(verts[i], NULL, edges[(i+1)%vCount], face);
	}

	HalfEdgeMesh::AddFace(face);
}

};