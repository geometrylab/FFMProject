#include "FFMProject.h"
#include "Polygon.h"

namespace FFMGeometry
{

Polygon::Polygon()
{
}

Polygon::Polygon(TArray<FVector>& vertices, TArray<Edge>& edges) : m_Vertices(vertices), m_Edges(edges)
{
}

Polygon::Polygon(TArray<FVector>& vertices) : m_Vertices(vertices)
{
	for( int i = 0, iCount(m_Vertices.Num()); i < iCount; ++i )
		m_Edges.Add(Edge(i, (i + 1) % iCount));
}

}
