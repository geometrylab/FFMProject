#pragma once 

namespace FFMGeometry
{

struct HE_Edge;
    
struct HE_Vertex
{
	HE_Vertex() : edge()
    {
    }

	HE_Vertex(const FVector& _pos, HE_Edge* _edge) : pos(_pos), edge(_edge)
	{
	}

    FVector pos;
    HE_Edge* edge;
};

struct HE_Face
{
	HE_Face() : edge()
	{
	}

	HE_Face(HE_Edge* _edge) : edge(_edge)
	{
	}

	HE_Edge* edge;
};

typedef TSharedPtr<HE_Face> HE_FacePtr;
    
struct HE_Edge
{
	HE_Edge() : vert(), pair(), next()
    {
    }

	HE_Edge(HE_Vertex* _vert, HE_Edge* _pair, HE_Edge* _next, const HE_FacePtr& _face) :
		vert(_vert),
		pair(_pair),
		next(_next),
		face(_face)
	{
	}

    HE_Vertex* vert;
    HE_Edge* pair;
    HE_Edge* next;
	HE_FacePtr face;
};

void MakeVertexList(const HE_FacePtr& face, TArray<FVector>& outVertices);

class HalfEdgeMesh
{
public:

	void AddFace(const HE_FacePtr& pFace);

	int GetFaceCount() const { return m_pFaces.Num(); }
	const HE_FacePtr& GetFace(int idx) const { return m_pFaces[idx]; }

private:

	TArray<HE_FacePtr> m_pFaces;
};

typedef TSharedPtr<HalfEdgeMesh> HalfEdgeMeshPtr;

}