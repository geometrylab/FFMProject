#include "FFMProject.h"
#include "DynamicMeshBuilder.h"
#include "BrushMesh.h"
#include "Runtime/Launch/Resources/Version.h"

class FBrushVertexBuffer : public FVertexBuffer
{
public:
	TArray<FDynamicMeshVertex> Vertices;

	virtual void InitRHI() override
	{
		FRHIResourceCreateInfo CreateInfo;
		VertexBufferRHI = RHICreateVertexBuffer(Vertices.Num() * sizeof(FDynamicMeshVertex), BUF_Static, CreateInfo);
		void* VertexBufferData = RHILockVertexBuffer(VertexBufferRHI, 0, Vertices.Num() * sizeof(FDynamicMeshVertex), RLM_WriteOnly);
		FMemory::Memcpy(VertexBufferData, Vertices.GetData(), Vertices.Num() * sizeof(FDynamicMeshVertex));
		RHIUnlockVertexBuffer(VertexBufferRHI);
	}
};

class FBrushIndexBuffer : public FIndexBuffer
{
public:
	TArray<int32> Indices;

	virtual void InitRHI() override
	{
		FRHIResourceCreateInfo CreateInfo;
		IndexBufferRHI = RHICreateIndexBuffer(sizeof(int32), Indices.Num() * sizeof(int32), BUF_Static, CreateInfo);
		void* Buffer = RHILockIndexBuffer(IndexBufferRHI, 0, Indices.Num() * sizeof(int32), RLM_WriteOnly);
		FMemory::Memcpy(Buffer, Indices.GetData(), Indices.Num() * sizeof(int32));
		RHIUnlockIndexBuffer(IndexBufferRHI);
	}
};

class FBrushVertexFactory : public FLocalVertexFactory
{
public:
	FBrushVertexFactory()
	{
	}

	void Init(const FBrushVertexBuffer* VertexBuffer)
	{
		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			InitProceduralMeshVertexFactory,
			FBrushVertexFactory*, VertexFactory, this,
			const FBrushVertexBuffer*, VertexBuffer, VertexBuffer,
			{
				DataType NewData;
				NewData.PositionComponent = STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FDynamicMeshVertex, Position, VET_Float3);
				NewData.TextureCoordinates.Add(
					FVertexStreamComponent(VertexBuffer, STRUCT_OFFSET(FDynamicMeshVertex, TextureCoordinate), sizeof(FDynamicMeshVertex), VET_Float2)
					);
				NewData.TangentBasisComponents[0] = STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FDynamicMeshVertex, TangentX, VET_PackedNormal);
				NewData.TangentBasisComponents[1] = STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FDynamicMeshVertex, TangentZ, VET_PackedNormal);
				NewData.ColorComponent = STRUCTMEMBER_VERTEXSTREAMCOMPONENT(VertexBuffer, FDynamicMeshVertex, Color, VET_Color);
				VertexFactory->SetData(NewData);
			});
	}
};

class FBrushSceneProxy : public FPrimitiveSceneProxy
{
public:

	FBrushSceneProxy(UBrushMesh* Component)
		: FPrimitiveSceneProxy(Component)
		, MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		for (int TriIdx = 0; TriIdx < Component->ProceduralMeshTris.Num(); TriIdx++)
		{
			FBrushTriangle& Tri = Component->ProceduralMeshTris[TriIdx];

			const FVector Edge01 = (Tri.v[1].Position - Tri.v[0].Position);
			const FVector Edge02 = (Tri.v[2].Position - Tri.v[0].Position);

			const FVector TangentX = Edge01.GetSafeNormal();
			const FVector TangentZ = (Edge02 ^ Edge01).GetSafeNormal();
			const FVector TangentY = (TangentX ^ TangentZ).GetSafeNormal();

			FDynamicMeshVertex Vert0;
			Vert0.Position = Tri.v[0].Position;
			Vert0.Color = Tri.v[0].Color;
			Vert0.SetTangents(TangentX, TangentY, TangentZ);
			Vert0.TextureCoordinate.Set(Tri.v[0].U, Tri.v[0].V);
			int32 VIndex = VertexBuffer.Vertices.Add(Vert0);
			IndexBuffer.Indices.Add(VIndex);

			FDynamicMeshVertex Vert1;
			Vert1.Position = Tri.v[1].Position;
			Vert1.Color = Tri.v[1].Color;
			Vert1.SetTangents(TangentX, TangentY, TangentZ);
			Vert1.TextureCoordinate.Set(Tri.v[1].U, Tri.v[1].V);
			VIndex = VertexBuffer.Vertices.Add(Vert1);
			IndexBuffer.Indices.Add(VIndex);

			FDynamicMeshVertex Vert2;
			Vert2.Position = Tri.v[2].Position;
			Vert2.Color = Tri.v[2].Color;
			Vert2.SetTangents(TangentX, TangentY, TangentZ);
			Vert2.TextureCoordinate.Set(Tri.v[2].U, Tri.v[2].V);
			VIndex = VertexBuffer.Vertices.Add(Vert2);
			IndexBuffer.Indices.Add(VIndex);
		}

		VertexFactory.Init(&VertexBuffer);

		BeginInitResource(&VertexBuffer);
		BeginInitResource(&IndexBuffer);
		BeginInitResource(&VertexFactory);

		Material = Component->GetMaterial(0);
		if (Material == NULL)
		{
			Material = UMaterial::GetDefaultMaterial(MD_Surface);
		}
	}

	virtual ~FBrushSceneProxy()
	{
		VertexBuffer.ReleaseResource();
		IndexBuffer.ReleaseResource();
		VertexFactory.ReleaseResource();
	}

	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_ProceduralMeshSceneProxy_GetDynamicMeshElements);

		const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

		auto WireframeMaterialInstance = new FColoredMaterialRenderProxy(
			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy(IsSelected()) : NULL,
			FLinearColor(0, 0.5f, 1.f)
			);

		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);

		FMaterialRenderProxy* MaterialProxy = NULL;
		if (bWireframe)
		{
			MaterialProxy = WireframeMaterialInstance;
		}
		else
		{
			MaterialProxy = Material->GetRenderProxy(IsSelected());
		}

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			if (VisibilityMap & (1 << ViewIndex))
			{
				const FSceneView* View = Views[ViewIndex];
				FMeshBatch& Mesh = Collector.AllocateMesh();
				FMeshBatchElement& BatchElement = Mesh.Elements[0];
				BatchElement.IndexBuffer = &IndexBuffer;
				Mesh.bWireframe = bWireframe;
				Mesh.VertexFactory = &VertexFactory;
				Mesh.MaterialRenderProxy = MaterialProxy;
				BatchElement.PrimitiveUniformBuffer = CreatePrimitiveUniformBufferImmediate(GetLocalToWorld(), GetBounds(), GetLocalBounds(), true, UseEditorDepthTest());
				BatchElement.FirstIndex = 0;
				BatchElement.NumPrimitives = IndexBuffer.Indices.Num() / 3;
				BatchElement.MinVertexIndex = 0;
				BatchElement.MaxVertexIndex = VertexBuffer.Vertices.Num() - 1;
				Mesh.ReverseCulling = IsLocalToWorldDeterminantNegative();
				Mesh.Type = PT_TriangleList;
				Mesh.DepthPriorityGroup = SDPG_World;
				Mesh.bCanApplyViewModeOverrides = false;
				Collector.AddMesh(ViewIndex, Mesh);
			}
		}
	}

	virtual void DrawDynamicElements(FPrimitiveDrawInterface* PDI, const FSceneView* View)
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_ProceduralMeshSceneProxy_DrawDynamicElements);

		const bool bWireframe = AllowDebugViewmodes() && View->Family->EngineShowFlags.Wireframe;

		FColoredMaterialRenderProxy WireframeMaterialInstance(
			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy(IsSelected()) : NULL,
			FLinearColor(0, 0.5f, 1.f)
			);

		FMaterialRenderProxy* MaterialProxy = NULL;
		if (bWireframe)
		{
			MaterialProxy = &WireframeMaterialInstance;
		}
		else
		{
			MaterialProxy = Material->GetRenderProxy(IsSelected());
		}

		// Draw the mesh.
		FMeshBatch Mesh;
		FMeshBatchElement& BatchElement = Mesh.Elements[0];
		BatchElement.IndexBuffer = &IndexBuffer;
		Mesh.bWireframe = bWireframe;
		Mesh.VertexFactory = &VertexFactory;
		Mesh.MaterialRenderProxy = MaterialProxy;
		BatchElement.PrimitiveUniformBuffer = CreatePrimitiveUniformBufferImmediate(GetLocalToWorld(), GetBounds(), GetLocalBounds(), true, UseEditorDepthTest());
		BatchElement.FirstIndex = 0;
		BatchElement.NumPrimitives = IndexBuffer.Indices.Num() / 3;
		BatchElement.MinVertexIndex = 0;
		BatchElement.MaxVertexIndex = VertexBuffer.Vertices.Num() - 1;
		Mesh.ReverseCulling = IsLocalToWorldDeterminantNegative();
		Mesh.Type = PT_TriangleList;
		Mesh.DepthPriorityGroup = SDPG_World;
		PDI->DrawMesh(Mesh);
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View)
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bDynamicRelevance = true;
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		return Result;
	}

	virtual bool CanBeOccluded() const override
	{
		return !MaterialRelevance.bDisableDepthTest;
	}

	virtual uint32 GetMemoryFootprint(void) const
	{
		return(sizeof(*this) + GetAllocatedSize());
	}

	uint32 GetAllocatedSize(void) const
	{
		return(FPrimitiveSceneProxy::GetAllocatedSize());
	}

private:

	UMaterialInterface* Material;
	FBrushVertexBuffer VertexBuffer;
	FBrushIndexBuffer IndexBuffer;
	FBrushVertexFactory VertexFactory;

	FMaterialRelevance MaterialRelevance;
};

UBrushMesh::UBrushMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

bool UBrushMesh::SetTriangles(const TArray<FBrushTriangle>& Triangles)
{
	ProceduralMeshTris = Triangles;

	UpdateCollision();
    MarkRenderStateDirty();

	return true;
}

void UBrushMesh::AddTriangles(const TArray<FBrushTriangle>& Triangles)
{
	ProceduralMeshTris.Append(Triangles);
	MarkRenderStateDirty();
}

void  UBrushMesh::ClearTriangles()
{
	ProceduralMeshTris.Reset();
	MarkRenderStateDirty();
}


FPrimitiveSceneProxy* UBrushMesh::CreateSceneProxy()
{
	FPrimitiveSceneProxy* Proxy = NULL;
	if (ProceduralMeshTris.Num() > 0)
	{
		Proxy = new FBrushSceneProxy(this);
	}
	return Proxy;
}

int32 UBrushMesh::GetNumMaterials() const
{
	return 1;
}


FBoxSphereBounds UBrushMesh::CalcBounds(const FTransform & LocalToWorld) const
{
	if (ProceduralMeshTris.Num() > 0)
	{
		FVector vecMin = ProceduralMeshTris[0].v[0].Position;
		FVector vecMax = ProceduralMeshTris[0].v[0].Position;
		for (int32 TriIdx = 0; TriIdx < ProceduralMeshTris.Num(); TriIdx++)
		{
			vecMin.X = (vecMin.X > ProceduralMeshTris[TriIdx].v[0].Position.X) ? ProceduralMeshTris[TriIdx].v[0].Position.X : vecMin.X;
			vecMin.X = (vecMin.X > ProceduralMeshTris[TriIdx].v[1].Position.X) ? ProceduralMeshTris[TriIdx].v[1].Position.X : vecMin.X;
			vecMin.X = (vecMin.X > ProceduralMeshTris[TriIdx].v[2].Position.X) ? ProceduralMeshTris[TriIdx].v[2].Position.X : vecMin.X;

			vecMin.Y = (vecMin.Y > ProceduralMeshTris[TriIdx].v[0].Position.Y) ? ProceduralMeshTris[TriIdx].v[0].Position.Y : vecMin.Y;
			vecMin.Y = (vecMin.Y > ProceduralMeshTris[TriIdx].v[1].Position.Y) ? ProceduralMeshTris[TriIdx].v[1].Position.Y : vecMin.Y;
			vecMin.Y = (vecMin.Y > ProceduralMeshTris[TriIdx].v[2].Position.Y) ? ProceduralMeshTris[TriIdx].v[2].Position.Y : vecMin.Y;

			vecMin.Z = (vecMin.Z > ProceduralMeshTris[TriIdx].v[0].Position.Z) ? ProceduralMeshTris[TriIdx].v[0].Position.Z : vecMin.Z;
			vecMin.Z = (vecMin.Z > ProceduralMeshTris[TriIdx].v[1].Position.Z) ? ProceduralMeshTris[TriIdx].v[1].Position.Z : vecMin.Z;
			vecMin.Z = (vecMin.Z > ProceduralMeshTris[TriIdx].v[2].Position.Z) ? ProceduralMeshTris[TriIdx].v[2].Position.Z : vecMin.Z;

			vecMax.X = (vecMax.X < ProceduralMeshTris[TriIdx].v[0].Position.X) ? ProceduralMeshTris[TriIdx].v[0].Position.X : vecMax.X;
			vecMax.X = (vecMax.X < ProceduralMeshTris[TriIdx].v[1].Position.X) ? ProceduralMeshTris[TriIdx].v[1].Position.X : vecMax.X;
			vecMax.X = (vecMax.X < ProceduralMeshTris[TriIdx].v[2].Position.X) ? ProceduralMeshTris[TriIdx].v[2].Position.X : vecMax.X;

			vecMax.Y = (vecMax.Y < ProceduralMeshTris[TriIdx].v[0].Position.Y) ? ProceduralMeshTris[TriIdx].v[0].Position.Y : vecMax.Y;
			vecMax.Y = (vecMax.Y < ProceduralMeshTris[TriIdx].v[1].Position.Y) ? ProceduralMeshTris[TriIdx].v[1].Position.Y : vecMax.Y;
			vecMax.Y = (vecMax.Y < ProceduralMeshTris[TriIdx].v[2].Position.Y) ? ProceduralMeshTris[TriIdx].v[2].Position.Y : vecMax.Y;

			vecMax.Z = (vecMax.Z < ProceduralMeshTris[TriIdx].v[0].Position.Z) ? ProceduralMeshTris[TriIdx].v[0].Position.Z : vecMax.Z;
			vecMax.Z = (vecMax.Z < ProceduralMeshTris[TriIdx].v[1].Position.Z) ? ProceduralMeshTris[TriIdx].v[1].Position.Z : vecMax.Z;
			vecMax.Z = (vecMax.Z < ProceduralMeshTris[TriIdx].v[2].Position.Z) ? ProceduralMeshTris[TriIdx].v[2].Position.Z : vecMax.Z;
		}

		FVector vecOrigin = ((vecMax - vecMin) / 2) + vecMin;
		FVector BoxPoint = vecMax - vecMin;
		return FBoxSphereBounds(vecOrigin, BoxPoint, BoxPoint.Size()).TransformBy(LocalToWorld);
	}
	else
	{
		return FBoxSphereBounds();
	}
}


bool UBrushMesh::GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	FTriIndices Triangle;

	for (int32 i = 0; i < ProceduralMeshTris.Num(); i++)
	{
		const FBrushTriangle& tri = ProceduralMeshTris[i];

		Triangle.v0 = CollisionData->Vertices.Add(tri.v[0].Position);
		Triangle.v1 = CollisionData->Vertices.Add(tri.v[1].Position);
		Triangle.v2 = CollisionData->Vertices.Add(tri.v[2].Position);

		CollisionData->Indices.Add(Triangle);
		CollisionData->MaterialIndices.Add(i);
	}

	CollisionData->bFlipNormals = true;

	return true;
}

bool UBrushMesh::ContainsPhysicsTriMeshData(bool InUseAllTriData) const
{
	return (ProceduralMeshTris.Num() > 0);
}

void UBrushMesh::UpdateBodySetup()
{
	if (ModelBodySetup == NULL)
	{
		ModelBodySetup = ConstructObject<UBodySetup>(UBodySetup::StaticClass(), this);
		ModelBodySetup->CollisionTraceFlag = CTF_UseComplexAsSimple;
		ModelBodySetup->bMeshCollideAll = true;
	}
}

void UBrushMesh::UpdateCollision()
{
	if (bPhysicsStateCreated)
	{
		DestroyPhysicsState();
		UpdateBodySetup();
		CreatePhysicsState();
        
		ModelBodySetup->InvalidatePhysicsData();
		ModelBodySetup->CreatePhysicsMeshes();
	}
}

UBodySetup* UBrushMesh::GetBodySetup()
{
	UpdateBodySetup();
	return ModelBodySetup;
}