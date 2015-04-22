#include "FFMProject.h"
#include "GeometryCommon.h"
#include "Model.h"

namespace FFMGeometry
{

void Model::AddFace(const TArray<FVector>& vertices, TArray<HE_Edge*>* outEdges)
{
	int32 vCount = vertices.Num();

    TArray<HE_Edge*> edges;
    TArray<HE_Edge*>* chosen_edges = outEdges ? outEdges : &edges;
	TArray<HE_Vertex*> verts;

	for (int32 i = 0; i < vCount; ++i)
	{
		verts.Add(new HE_Vertex);
		chosen_edges->Add(new HE_Edge);
	}

	HE_FacePtr face = HE_FacePtr(new HE_Face((*chosen_edges)[0]));

	for (int32 i = 0; i < vCount; ++i)
	{
		verts[i]->edge_ = (*chosen_edges)[i];
        verts[i]->pos_  = FindPos(vertices[i]);
        
        verts[i]->pos_->vs_.Add(verts[i]);

		(*chosen_edges)[i]->vert_ = verts[i];
		(*chosen_edges)[i]->pair_ = NULL;
		(*chosen_edges)[i]->next_ = (*chosen_edges)[(i + 1) % vCount];
		(*chosen_edges)[i]->next_->prev_ = (*chosen_edges)[i];
		(*chosen_edges)[i]->face_ = face;
    }
	
	HalfEdgeMesh::AddFace(face);
}

void Model::SolveAllEdgePairs()
{
	for (int i = 0, iCount(GetFaceCount()); i < iCount; ++i)
		SolvePair(GetFace(i));
}

};