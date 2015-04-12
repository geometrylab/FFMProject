#pragma once

#include "Polygon.h"

namespace FFMGeometry
{

class Model
{
public:
	void AddPolygon(PolygonPtr pPolygon);
	PolygonPtr GetPolygon(int nIndex) const { return m_Polygons[nIndex]; }
	int32 GetPolygonCount() const { return m_Polygons.Num(); }

private:
	TArray<PolygonPtr> m_Polygons;
};

typedef TSharedPtr<Model> ModelPtr;

}