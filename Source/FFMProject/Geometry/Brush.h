#pragma once

#include "ProceduralMeshComponent.h"

namespace FFMGeometry
{

class Brush
{

private:

    UProceduralMeshComponent* m_pMesh;
};
    
typedef TSharedPtr<Brush> BrushPtr;

}