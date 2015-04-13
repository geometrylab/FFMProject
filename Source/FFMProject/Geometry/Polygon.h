#pragma once

#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

class Polygon
{
public:
	typedef TSharedPtr<Polygon> PolygonPtr;

public:
	Polygon();
	Polygon(TArray<FVector>& vertices, TArray<Edge>& edges);
	Polygon(TArray<FVector>& vertices);
    
    void SetHalfEdgeMesh( HalfEdgeMeshPtr pHalfEdgeMesh )
    {
        m_pHalfEdgeMesh = pHalfEdgeMesh;
    }
    
    void AddHEFace( int he_face_idx )
    {
        m_HEFaceIndices.Add(he_face_idx);
    }

private:
    TArray<FVector> m_Vertices;
    TArray<Edge> m_Edges;
	Plane m_Plane;
    
    TArray<int> m_HEFaceIndices;

    HalfEdgeMeshPtr m_pHalfEdgeMesh;
};

typedef Polygon::PolygonPtr PolygonPtr;

}