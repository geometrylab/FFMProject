#pragma once 

namespace FFMGeometry
{

struct HE_Edge;
    
struct HE_Vertex
{
	HE_Vertex() : edge_()
    {
    }

	HE_Vertex(const FVector& pos, HE_Edge* edge) : pos_(pos), edge_(edge)
	{
	}

	void GetNeighboringVertices(TArray<HE_Vertex*>& outVertices) const;

    FVector pos_;
    HE_Edge* edge_;
};

struct HE_Face
{
	HE_Face() : edge_(NULL)
	{
	}

	HE_Face(HE_Edge* edge) : edge_(edge)
	{
	}

	~HE_Face();

	void MakeVertexList(TArray<FVector>& outVertices) const;
	HE_Edge* FindEdge(const FVector& v0, const FVector& v1, bool bExcludeEdgeWithPair = false) const;

	HE_Edge* edge_;
};

typedef TSharedPtr<HE_Face> HE_FacePtr;
    
struct HE_Edge
{
	HE_Edge() : vert_(NULL), pair_(NULL), next_(NULL), prev_(NULL)
    {
    }

	HE_Edge(HE_Vertex* vert, HE_Edge* pair, HE_Edge* next, HE_Edge* prev, const HE_FacePtr& face) :
		vert_(vert),
		pair_(pair),
		next_(next),
		prev_(prev),
		face_(face)
	{
	}

	~HE_Edge()
	{
		if (vert_)
			delete vert_;
	}

    HE_Vertex* vert_;
    HE_Edge* pair_;
    HE_Edge* next_;
	HE_Edge* prev_;
	HE_FacePtr face_;
};

class HalfEdgeMesh
{
public:

	void AddFace(const HE_FacePtr& pFace) { m_pFaces.Add(pFace); }
	void SolvePair(const HE_FacePtr& pFace);

	int GetFaceCount() const { return m_pFaces.Num(); }
	const HE_FacePtr& GetFace(int idx) const { return m_pFaces[idx]; }

    void Clear() { m_pFaces.RemoveAll( [&](const HE_FacePtr&){return true;} ); }

private:

	TArray<HE_FacePtr> m_pFaces;
};

typedef TSharedPtr<HalfEdgeMesh> HalfEdgeMeshPtr;

}