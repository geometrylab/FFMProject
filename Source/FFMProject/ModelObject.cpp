// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "ModelObject.h"
#include "Geometry/LoopSubdivision.h"

using namespace FFMGeometry;

AModelObject::AModelObject() :
	 m_pModel(new FFMGeometry::Model)
{	
	PrimaryActorTick.bCanEverTick = true;

	m_pBrushMesh = CreateDefaultSubobject<UBrushMesh>(TEXT("BrushMesh"));

    BuildBox();
    //BuildTetrahedron();

	m_pModel->SolveAllEdgePairs();

	int nSubdivisionCount = rand() % 5;

	for (int i = 0; i < nSubdivisionCount; ++i)
	{
		FFMGeometry::LoopSubdivision ls;
		m_pModel = ls.Subdivide(m_pModel);
	}
    
	UpdateBrushMesh();

    RootComponent = m_pBrushMesh;
}

void AModelObject::BeginPlay()
{
	Super::BeginPlay();
}

void AModelObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AModelObject::UpdateBrushMesh()
{	
	TArray<FBrushTriangle> mesh;

	for (int i = 0, iCount(m_pModel->GetFaceCount()); i < iCount; ++i)
	{
		TArray<FVector> vlist;
		m_pModel->GetFace(i)->MakeVertexList(vlist);
		int iVertexCount = vlist.Num();

		for (int k = 0; k < iVertexCount - 2; ++k )
		{
			FBrushTriangle triangle;

			triangle.v[0].Position = vlist[0];
			triangle.v[1].Position = vlist[k+1];
			triangle.v[2].Position = vlist[k+2];

			for (int a = 0; a < 3; ++a)
			{
				triangle.v[a].Color = FColor(255, 255, 255, 255);
				triangle.v[a].U = 1.0;
				triangle.v[a].V = 1.0;
			}

			mesh.Add(triangle);
		}
	}

	m_pBrushMesh->SetTriangles(mesh);
}

void AModelObject::BuildBox()
{
	const float size = 100.0f;

	m_pModel->Clear();

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, 0));
		vertices.Add(FVector(0, 0, size));
		vertices.Add(FVector(size, 0, size));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, 0));
		vertices.Add(FVector(size, 0, size));
        vertices.Add(FVector(size, 0, 0));
		m_pModel->AddFace(vertices);
        
    }
    
	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, 0, 0));
		vertices.Add(FVector(size, 0, size));
		vertices.Add(FVector(size, size, size));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, 0, 0));
		vertices.Add(FVector(size, size, size));
        vertices.Add(FVector(size, size, 0));
        m_pModel->AddFace(vertices);
    }
    
	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, size, 0));
		vertices.Add(FVector(size, size, size));
		vertices.Add(FVector(0, size, size));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, size, 0));
		vertices.Add(FVector(0, size, size));
        vertices.Add(FVector(0, size, 0));
        m_pModel->AddFace(vertices);
    }
    
	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, size, 0));
		vertices.Add(FVector(0, size, size));
		vertices.Add(FVector(0, 0, size));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, size, 0));
		vertices.Add(FVector(0, 0, size));
        vertices.Add(FVector(0, 0, 0));
        m_pModel->AddFace(vertices);
    }
    
	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, size));
		vertices.Add(FVector(0, size, size));
		vertices.Add(FVector(size, size, size));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, size));
		vertices.Add(FVector(size, size, size));
        vertices.Add(FVector(size, 0, size));
        m_pModel->AddFace(vertices);
    }
    
	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, 0, 0));
		vertices.Add(FVector(size, size, 0));
		vertices.Add(FVector(0, size, 0));
		m_pModel->AddFace(vertices);
	}

	{
		TArray<FVector> vertices;
		vertices.Add(FVector(size, 0, 0));
		vertices.Add(FVector(0, size, 0));
        vertices.Add(FVector(0, 0, 0));
        m_pModel->AddFace(vertices);
    }
}

void AModelObject::BuildTetrahedron()
{
	const float size = 230.0f;
    m_pModel->Clear();
    
	TArray<FVector> bottom_vertices;
    {        
		bottom_vertices.Add(FVector(0.86602f*size, 0.5f*size, 0));
		bottom_vertices.Add(FVector(0, size, 0));
		bottom_vertices.Add(FVector(0, 0, 0));
		m_pModel->AddFace(bottom_vertices);
    }
    
	FVector apex = (bottom_vertices[0] + bottom_vertices[1] + bottom_vertices[2]) / 3.0f;
	apex.Z = 0.4f*size;

    {
        TArray<FVector> vertices;
		vertices.Add(bottom_vertices[2]);
		vertices.Add(bottom_vertices[1]);
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
		vertices.Add(bottom_vertices[1]);
		vertices.Add(bottom_vertices[0]);
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
		vertices.Add(bottom_vertices[0]);
		vertices.Add(bottom_vertices[2]);
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }    
}
