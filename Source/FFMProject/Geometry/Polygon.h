#pragma once

#include "GeometryCommon.h"

namespace FFMGeometry
{

class Polygon
{
public:
	typedef TSharedPtr<Polygon> PolygonPtr;

public:

	Polygon();
	Polygon(TArray<FVector>& vertices, TArray<FFMGeometry::Edge>& edges);
	Polygon(TArray<FVector>& vertices);

private:

	TArray<FVector> m_Vertices;
	TArray<Edge> m_Edges;
	Plane m_Plane;
};

typedef Polygon::PolygonPtr PolygonPtr;

}