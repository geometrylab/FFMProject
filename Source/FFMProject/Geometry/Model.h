#pragma once

#include "Polygon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

class Model
{
public:
    Model();
    
	void AddPolygon(PolygonPtr pPolygon);
	PolygonPtr GetPolygon(int nIndex) const { return m_Polygons[nIndex]; }
	int32 GetPolygonCount() const { return m_Polygons.Num(); }
    
    void SetHalfEdgeMesh( HalfEdgeMeshPtr pHalfEdgeMesh );

private:
	TArray<PolygonPtr> m_Polygons;
	HalfEdgeMeshPtr m_pHalfEdgeMesh;
};

typedef TSharedPtr<Model> ModelPtr;

}