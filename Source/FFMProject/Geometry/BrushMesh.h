// UE4 Procedural Mesh Generation from the Epic Wiki (https://wiki.unrealengine.com/Procedural_Mesh_Generation)
//
// forked from "Engine/Plugins/Runtime/CustomMeshComponent/Source/CustomMeshComponent/Classes/CustomMeshComponent.h"

#pragma once

#include "BrushMesh.generated.h"

USTRUCT(BlueprintType)
struct FBrushVertex
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Triangle)
	FVector Position;

	UPROPERTY(EditAnywhere, Category = Triangle)
	FColor Color;

	UPROPERTY(EditAnywhere, Category = Triangle)
	float U;

	UPROPERTY(EditAnywhere, Category = Triangle)
	float V;
};

USTRUCT(BlueprintType)
struct FBrushTriangle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Triangle)
	FBrushVertex Vertex0;

	UPROPERTY(EditAnywhere, Category = Triangle)
	FBrushVertex Vertex1;

	UPROPERTY(EditAnywhere, Category = Triangle)
	FBrushVertex Vertex2;
};

/** Component that allows you to specify custom triangle mesh geometry */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class UBrushMesh : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_UCLASS_BODY()

public:
	/** Set the geometry to use on this triangle mesh */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	bool SetProceduralMeshTriangles(const TArray<FBrushTriangle>& Triangles);


	/** Add to the geometry to use on this triangle mesh.  This may cause an allocation.  Use SetCustomMeshTriangles() instead when possible to reduce allocations. */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void AddProceduralMeshTriangles(const TArray<FBrushTriangle>& Triangles);

	/** Removes all geometry from this triangle mesh.  Does not deallocate memory, allowing new geometry to reuse the existing allocation. */
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void ClearProceduralMeshTriangles();

	/** Description of collision */
	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	class UBodySetup* ModelBodySetup;

	// Begin Interface_CollisionDataProvider Interface
	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	virtual bool WantsNegXTriMesh() override{ return false; }
	// End Interface_CollisionDataProvider Interface

	// Begin UPrimitiveComponent interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual class UBodySetup* GetBodySetup() override;
	// End UPrimitiveComponent interface.

	// Begin UMeshComponent interface.
	virtual int32 GetNumMaterials() const override;
	// End UMeshComponent interface.

	void UpdateBodySetup();
	void UpdateCollision();

private:
	// Begin USceneComponent interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;
	// Begin USceneComponent interface.

	/** */
	TArray<FBrushTriangle> ProceduralMeshTris;

	friend class FProceduralMeshSceneProxy;
};
