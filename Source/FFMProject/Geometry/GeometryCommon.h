#pragma once

namespace FFMGeometry
{

struct Edge
{
	Edge(){}
	Edge(uint16 i0, uint16 i1)
	{
		idx[0] = i0;
		idx[1] = i1;
	}
	Edge(uint16 _idx[2])
	{
		idx[0] = _idx[0];
		idx[1] = _idx[1];
	}
	uint16 idx[2];
};

struct Plane : public FPlane
{
public:
	bool HitTest(const FVector& vSrc, const FVector& vDest, float* outT = NULL, FVector* pOutVertex = NULL);
};

struct Vertex
{
	FVector position;
	FVector normal;
};

struct Face
{
	int16 indices[3];
};

struct Mesh
{
	TArray<Vertex> m_Vertices;
	TArray<Face> m_Faces;
};

}