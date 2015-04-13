#include "FFMProject.h"
#include "GeometryCommon.h"
#include "Model.h"

namespace FFMGeometry
{

Model::Model()
{
    m_pHalfEdgeMesh = HalfEdgeMeshPtr(new HalfEdgeMesh);
}

void Model::AddPolygon(PolygonPtr pPolygon)
{
	m_Polygons.Add(pPolygon);
}

void Model::SetHalfEdgeMesh( HalfEdgeMeshPtr pHalfEdgeMesh )
{
    m_pHalfEdgeMesh = pHalfEdgeMesh;
    
    m_Polygons.RemoveAll([&](const PolygonPtr& polygon){return true;});
    
    for( int i = 0, iFaceCount(m_pHalfEdgeMesh->GetFaceCount()); i < iFaceCount; ++i )
    {
        const HE_Face& face = m_pHalfEdgeMesh->GetFace(i);
        PolygonPtr pPoly = new FFMGeometry::Polygon(m_pHalfEdgeMesh->MakeFace(face));
        pPoly->SetHalfEdgeMesh(m_pHalfEdgeMesh);
        pPoly->AddHEFace(m_pHalfEdgeMesh->GetFaceIndex(face));
        m_Polygons.Add(pPoly);
    }
}
    
};