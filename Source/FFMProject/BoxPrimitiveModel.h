// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Geometry/BrushMesh.h"
#include "BoxPrimitiveModel.generated.h"

UCLASS()
class FFMPROJECT_API ABoxPrimitiveModel : public AActor
{
	GENERATED_BODY()

public:
	ABoxPrimitiveModel();

	// Allow viewing/changing the Material of the procedural Mesh in editor (if placed in a level at construction)
	UPROPERTY(VisibleAnywhere, Category = Materials)
    
    UBrushMesh* mesh;

	void GenerateCube(const float& InSize, TArray<FProceduralMeshTriangle>& OutTriangles);
};
