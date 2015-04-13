#pragma once 

namespace FFMGeometry
{
    
struct HE_Vertex
{
    HE_Vertex() : edge_idx(-1)
    {
    }
    FVector pos;
    int edge_idx;
};
    
struct HE_Edge
{
    HE_Edge() : vert_idx(-1), pair_idx(-1), face_idx(-1), next_idx(-1)
    {
    }
    int vert_idx;
    int pair_idx;
    int face_idx;
    int next_idx;
};
    
struct HE_Face
{
    HE_Face() : edge_idx(-1)
    {
    }
    int edge_idx;
};

class HalfEdgeMesh
{
public:
    
    const HE_Edge& GetNextEdge( const HE_Edge& edge ) const
    {
        return m_Edges[edge.next_idx];
    }
    
    const HE_Edge* GetPairEdge( const HE_Edge& edge ) const
    {
        if( edge.pair_idx == -1 )
            return nullptr;
        return &m_Edges[edge.pair_idx];
    }
    
    const HE_Face& GetFace( const HE_Edge& edge ) const
    {
        return m_Faces[edge.face_idx];
    }
    
    const FVector& GetPos( const HE_Edge& edge ) const
    {
        return m_Vertices[edge.vert_idx].pos;
    }
    
    const FVector& GetNextPos( const HE_Edge& edge ) const
    {
        return m_Vertices[m_Edges[edge.next_idx].vert_idx].pos;
    }
    
    TArray<FVector> MakeFace( const HE_Face& face ) const
    {
        TArray<FVector> vlist;
        
        int first_edge_idx = face.edge_idx;
        int edge_idx = first_edge_idx;
        
        do
        {
            vlist.Add(m_Vertices[m_Edges[edge_idx].vert_idx].pos);
            edge_idx = m_Edges[edge_idx].next_idx;
        } while( first_edge_idx != edge_idx);
        
        return vlist;
    }
    
    const HE_Face* GetAdjacentFace( const HE_Face& face ) const
    {
        int pair_idx = m_Edges[face.edge_idx].pair_idx;
        if( pair_idx == -1 )
            return NULL;
        return &m_Faces[m_Edges[pair_idx].face_idx];
    }
    
    int GetFaceCount() const
    {
        return m_Faces.Num();
    }
    
    const HE_Face& GetFace( int face_idx )
    {
        return m_Faces[face_idx];
    }
    
    int GetFaceIndex( const HE_Face& face )
    {
        return m_Edges[face.edge_idx].face_idx;
    }
    
private:
    
    TArray<HE_Edge> m_Edges;
    TArray<HE_Vertex> m_Vertices;
    TArray<HE_Face> m_Faces;
};

typedef TSharedPtr<HalfEdgeMesh> HalfEdgeMeshPtr;

}