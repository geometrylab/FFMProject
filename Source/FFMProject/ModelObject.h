#pragma once

#include "GameFramework/Actor.h"
#include "Geometry/Model.h"
#include "Geometry/BrushMesh.h"
#include "ModelObject.generated.h"

UCLASS()
class FFMPROJECT_API AModelObject : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AModelObject();
	void BeginPlay() override;	
	void Tick( float DeltaSeconds ) override;

private:

	void UpdateBrushMesh();
    
    FFMGeometry::ModelPtr m_pModel;
    UBrushMesh* m_pBrushMesh;
};
