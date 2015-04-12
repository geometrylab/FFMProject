// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "BoxPrimitiveModel.h"

ABoxPrimitiveModel::ABoxPrimitiveModel()
{
	mesh = CreateDefaultSubobject<UBrushMesh>(TEXT("CubeMesh"));

	// Generate a cube
	TArray<FBrushTriangle> triangles;
	GenerateCube(60.0f, triangles);
	mesh->SetTriangles(triangles);

	RootComponent = mesh;
}

// Generate a full cube
void ABoxPrimitiveModel::GenerateCube(const float& InSize, TArray<FBrushTriangle>& OutTriangles)
{
	// The 8 vertices of the cube
	FVector p0 = FVector(0.f, 0.f, 0.f);
	FVector p1 = FVector(0.f, 0.f, InSize);
	FVector p2 = FVector(InSize, 0.f, InSize);
	FVector p3 = FVector(InSize, 0.f, 0.f);
	FVector p4 = FVector(InSize, InSize, 0.f);
	FVector p5 = FVector(InSize, InSize, InSize);
	FVector p6 = FVector(0.f, InSize, InSize);
	FVector p7 = FVector(0.f, InSize, 0.f);

	FBrushVertex v0;
	FBrushVertex v1;
	FBrushVertex v2;
	FBrushVertex v3;
	v0.U = 0.f; v0.V = 0.f;
	v1.U = 0.f; v1.V = 1.f;
	v2.U = 1.f; v2.V = 1.f;
	v3.U = 1.f; v3.V = 0.f;

	FBrushTriangle t1;
	FBrushTriangle t2;

	// front face
	v0.Position = p0;
	v1.Position = p1;
	v2.Position = p2;
	v3.Position = p3;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);

	// back face
	v0.Position = p4;
	v1.Position = p5;
	v2.Position = p6;
	v3.Position = p7;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);

	// left face
	v0.Position = p7;
	v1.Position = p6;
	v2.Position = p1;
	v3.Position = p0;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);

	// right face
	v0.Position = p3;
	v1.Position = p2;
	v2.Position = p5;
	v3.Position = p4;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);

	// top face
	v0.Position = p1;
	v1.Position = p6;
	v2.Position = p5;
	v3.Position = p2;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);

	// bottom face
	v0.Position = p3;
	v1.Position = p4;
	v2.Position = p7;
	v3.Position = p0;
	t1.Vertex0 = v0;
	t1.Vertex1 = v1;
	t1.Vertex2 = v2;
	t2.Vertex0 = v0;
	t2.Vertex1 = v2;
	t2.Vertex2 = v3;
	OutTriangles.Add(t1);
	OutTriangles.Add(t2);
}
