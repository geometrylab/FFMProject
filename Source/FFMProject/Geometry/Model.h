#pragma once

#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

class Model : public HalfEdgeMesh
{
public:	

	void AddFace(const TArray<FVector>& vertices, TArray<HE_Edge*>* outEdges = NULL);
	void SolveAllEdgePairs();
    
};

typedef TSharedPtr<Model> ModelPtr;

}