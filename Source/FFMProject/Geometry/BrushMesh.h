#pragma once

#include "BrushMesh.generated.h"

struct FBrushVertex
{
	FVector Position;
	FColor Color;
	float U;
	float V;
};

struct FBrushTriangle
{
	FBrushVertex Vertex0;
	FBrushVertex Vertex1;
	FBrushVertex Vertex2;
};

UCLASS()
class UBrushMesh : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_UCLASS_BODY()

public:
	bool SetTriangles(const TArray<FBrushTriangle>& Triangles);
	void AddTriangles(const TArray<FBrushTriangle>& Triangles);
	void ClearTriangles();
	class UBodySetup* ModelBodySetup;

    bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	bool WantsNegXTriMesh() override{ return false; }
	FPrimitiveSceneProxy* CreateSceneProxy() override;
	class UBodySetup* GetBodySetup() override;
	int32 GetNumMaterials() const override;

	void UpdateBodySetup();
	void UpdateCollision();

private:

	FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;
	TArray<FBrushTriangle> ProceduralMeshTris;

	friend class FBrushSceneProxy;
};
