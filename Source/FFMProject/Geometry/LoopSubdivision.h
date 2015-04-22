#pragma once

#include "Model.h"

namespace FFMGeometry
{

class LoopSubdivision
{
public:
    
	ModelPtr Subdivide(ModelPtr pHalfEdgeMesh);
    void Subdivide_2(ModelPtr pHalfEdgeMesh);

private:
	
};

}