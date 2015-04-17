// Fill out your copyright notice in the Description page of Project Settings.

#include "FFMProject.h"
#include "ModelObject.h"

using namespace FFMGeometry;

#define USING_HALFEDGEMESH

AModelObject::AModelObject() :
	 m_pModel(new FFMGeometry::Model)
{	
	PrimaryActorTick.bCanEverTick = true;

	m_pBrushMesh = CreateDefaultSubobject<UBrushMesh>(TEXT("BrushMesh"));

	{
#ifndef USING_HALFEDGEMESH
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, 0));
		vertices.Add(FVector(0, 0, 100.0f));
		vertices.Add(FVector(100.0f, 0, 100.0f));
		vertices.Add(FVector(100.0f, 0, 0));
		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] = 
		{
			new HE_Vertex(FVector(0, 0, 0), edges[0]),
			new HE_Vertex(FVector(0, 0, 100.0f), edges[1]),
			new HE_Vertex(FVector(100.0f, 0, 100.0f), edges[2]),
			new HE_Vertex(FVector(100.0f, 0, 0), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
	}

	{
#ifndef USING_HALFEDGEMESH
		TArray<FVector> vertices;
		vertices.Add(FVector(100.0f, 0, 0));
		vertices.Add(FVector(100.0f, 0, 100.0f));
		vertices.Add(FVector(100.0f, 100.0f, 100.0f));
		vertices.Add(FVector(100.0f, 100.0f, 0));
		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] =
		{
			new HE_Vertex(FVector(100.0f, 0, 0), edges[0]),
			new HE_Vertex(FVector(100.0f, 0, 100.0f), edges[1]),
			new HE_Vertex(FVector(100.0f, 100.0f, 100.0f), edges[2]),
			new HE_Vertex(FVector(100.0f, 100.0f, 0), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
	}

	{
#ifndef USING_HALFEDGEMESH
		TArray<FVector> vertices;
		vertices.Add(FVector(100.0f, 100.0f, 0));
		vertices.Add(FVector(100.0f, 100.0f, 100.0f));
		vertices.Add(FVector(0, 100.0f, 100.0f));
		vertices.Add(FVector(0, 100.0f, 0));
		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] =
		{
			new HE_Vertex(FVector(100.0f, 100.0f, 0), edges[0]),
			new HE_Vertex(FVector(100.0f, 100.0f, 100.0f), edges[1]),
			new HE_Vertex(FVector(0, 100.0f, 100.0f), edges[2]),
			new HE_Vertex(FVector(0, 100.0f, 0), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
	}

 	{
#ifndef USING_HALFEDGEMESH
 		TArray<FVector> vertices;
 		vertices.Add(FVector(0, 100.0f, 0));
 		vertices.Add(FVector(0, 100.0f, 100.0f));
 		vertices.Add(FVector(0, 0, 100.0f));
 		vertices.Add(FVector(0, 0, 0));
 		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] =
		{
			new HE_Vertex(FVector(0, 100.0f, 0), edges[0]),
			new HE_Vertex(FVector(0, 100.0f, 100.0f), edges[1]),
			new HE_Vertex(FVector(0, 0, 100.0f), edges[2]),
			new HE_Vertex(FVector(0, 0, 0), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
 	}

	{
#ifndef USING_HALFEDGEMESH
		TArray<FVector> vertices;
		vertices.Add(FVector(0, 0, 100.0f));
		vertices.Add(FVector(0, 100.0f, 100.0f));
		vertices.Add(FVector(100.0f, 100.0f, 100.0f));
		vertices.Add(FVector(100.0f, 0, 100.0f));
		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] =
		{
			new HE_Vertex(FVector(0, 0, 100.0f), edges[0]),
			new HE_Vertex(FVector(0, 100.0f, 100.0f), edges[1]),
			new HE_Vertex(FVector(100.0f, 100.0f, 100.0f), edges[2]),
			new HE_Vertex(FVector(100.0f, 0, 100.0f), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
	}

	{
#ifndef USING_HALFEDGEMESH
		TArray<FVector> vertices;
		vertices.Add(FVector(100.0f, 0, 0));
		vertices.Add(FVector(100.0f, 100.0f, 0));
		vertices.Add(FVector(0, 100.0f, 0));
		vertices.Add(FVector(0, 0, 0));
		m_pModel->AddPolygon(PolygonPtr(new FFMGeometry::Polygon(vertices)));
#else
		HE_Edge* edges[4] = { new HE_Edge, new HE_Edge, new HE_Edge, new HE_Edge };
		HE_Vertex* verts[4] =
		{
			new HE_Vertex(FVector(100.0f, 0, 0), edges[0]),
			new HE_Vertex(FVector(100.0f, 100.0f, 0), edges[1]),
			new HE_Vertex(FVector(0, 100.0f, 0), edges[2]),
			new HE_Vertex(FVector(0, 0, 0), edges[3])
		};
		TSharedPtr<HE_Face> face = TSharedPtr<HE_Face>(new HE_Face(edges[0]));
		edges[0]->vert = verts[0];
		edges[0]->next = edges[1];
		edges[0]->face = face;
		edges[1]->vert = verts[1];
		edges[1]->next = edges[2];
		edges[1]->face = face;
		edges[2]->vert = verts[2];
		edges[2]->next = edges[3];
		edges[2]->face = face;
		edges[3]->vert = verts[3];
		edges[3]->next = edges[0];
		edges[3]->face = face;
		m_pModel->AddFace(face);
#endif
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
		MakeVertexList(m_pModel->GetFace(i),vlist);
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