#pragma once

#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

class LoopSubdivision
{
public:
    
    HalfEdgeMeshPtr Subdivide( HalfEdgeMeshPtr pHalfEdgeMesh);
};

}