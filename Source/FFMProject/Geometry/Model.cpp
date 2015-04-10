#include "FFMProject.h"
#include "GeometryCommon.h"
#include "Model.h"

namespace FFMGeometry
{

void Model::AddPolygon(PolygonPtr pPolygon)
{
	m_Polygons.Add(pPolygon);
}

};