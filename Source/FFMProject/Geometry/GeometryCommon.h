#pragma once

namespace FFMGeometry
{

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