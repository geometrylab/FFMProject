#pragma once 

namespace FFMGeometry
{

struct HE_Edge;
    
struct HE_Vertex
{
	HE_Vertex() : edge(NULL)
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
	HE_Face() : edge(NULL)
	{
	}

	HE_Face(HE_Edge* _edge) : edge(_edge)
	{
	}

	HE_Edge* edge;
};
    
struct HE_Edge
{
	HE_Edge() : vert(NULL), pair(NULL), next(NULL)
    {
    }

	HE_Edge(HE_Vertex* _vert, HE_Edge* _pair, HE_Edge* _next, TSharedPtr<HE_Face> _face) :
		vert(_vert),
		pair(_pair),
		next(_next),
		face(_face)
	{
	}

    HE_Vertex* vert;
    HE_Edge* pair;
    HE_Edge* next;
	TSharedPtr<HE_Face> face;
};

void MakeVertexList(const TSharedPtr<HE_Face>& face, TArray<FVector>& outVertices);

class HalfEdgeMesh
{
public:

	void AddFace(const TSharedPtr<HE_Face>& pFace);

	int GetFaceCount() const { return m_pFaces.Num(); }
	const TSharedPtr<HE_Face>& GetFace(int idx) const { return m_pFaces[idx]; }

private:

	TArray<TSharedPtr<HE_Face>> m_pFaces;
};

typedef TSharedPtr<HalfEdgeMesh> HalfEdgeMeshPtr;

}