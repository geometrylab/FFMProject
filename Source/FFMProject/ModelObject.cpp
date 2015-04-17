// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "ModelObject.h"

using namespace FFMGeometry;

AModelObject::AModelObject() :
	 m_pModel(new FFMGeometry::Model)
{	
	PrimaryActorTick.bCanEverTick = true;

	m_pBrushMesh = CreateDefaultSubobject<UBrushMesh>(TEXT("BrushMesh"));


//    BuildBox();
    BuildTetrahedron();
    
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
    m_pModel->Clear();
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(0, 0, 0));
        vertices.Add(FVector(0, 0, 100.0f));
        vertices.Add(FVector(100.0f, 0, 100.0f));
        vertices.Add(FVector(100.0f, 0, 0));
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f, 0, 0));
        vertices.Add(FVector(100.0f, 0, 100.0f));
        vertices.Add(FVector(100.0f, 100.0f, 100.0f));
        vertices.Add(FVector(100.0f, 100.0f, 0));
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f, 100.0f, 0));
        vertices.Add(FVector(100.0f, 100.0f, 100.0f));
        vertices.Add(FVector(0, 100.0f, 100.0f));
        vertices.Add(FVector(0, 100.0f, 0));
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(0, 100.0f, 0));
        vertices.Add(FVector(0, 100.0f, 100.0f));
        vertices.Add(FVector(0, 0, 100.0f));
        vertices.Add(FVector(0, 0, 0));
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(0, 0, 100.0f));
        vertices.Add(FVector(0, 100.0f, 100.0f));
        vertices.Add(FVector(100.0f, 100.0f, 100.0f));
        vertices.Add(FVector(100.0f, 0, 100.0f));
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f, 0, 0));
        vertices.Add(FVector(100.0f, 100.0f, 0));
        vertices.Add(FVector(0, 100.0f, 0));
        vertices.Add(FVector(0, 0, 0));
        m_pModel->AddFace(vertices);
    }
}

void AModelObject::BuildTetrahedron()
{
    m_pModel->Clear();
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f, 0, 0));
        vertices.Add(FVector(100.0f, 100.0f, 0));
        vertices.Add(FVector(0, 100.0f, 0));
        vertices.Add(FVector(0, 0, 0));
        m_pModel->AddFace(vertices);
    }
    
    const FVector apex(50.0f,50.0f,100.0f);
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(0,0,0));
        vertices.Add(FVector(0,100.0f,0));
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(0,100.0f,0));
        vertices.Add(FVector(100.0f,100.0f,0));
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f,100.0f,0));
        vertices.Add(FVector(100.0f,0,0));
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
    
    {
        TArray<FVector> vertices;
        vertices.Add(FVector(100.0f,0,0));
        vertices.Add(FVector(0,0,0));
        vertices.Add(apex);
        m_pModel->AddFace(vertices);
    }
}
