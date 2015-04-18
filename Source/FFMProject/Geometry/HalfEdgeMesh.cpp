#include "FFMProject.h"
#include "GeometryCommon.h"
#include "HalfEdgeMesh.h"

namespace FFMGeometry
{

void HE_Vertex::GetNeighboringVertices(TArray<HE_Vertex*>& outVertices)
{
	HE_Edge* edge = edge_;
	bool bMeetBoundary = false;
	do
	{
		outVertices.Add(edge->next_->vert_);
		if (!edge->pair_)
		{
			bMeetBoundary = true;
			break;
		}
		edge = edge->pair_->next_;
	} while (edge != edge_);

	HE_Edge* prev = edge_->PrevEdge();
	if (!bMeetBoundary || !prev->pair_)
		return;

	edge = prev->pair_->PrevEdge();
	while (edge->pair_ && edge != edge_)
	{
		outVertices.Add(edge->pair_->vert_);
		edge = edge->pair_->PrevEdge();
	}
}

HE_Face::~HE_Face()
{
	if (edge_)
	{
		HE_Edge* pEntryEdge = edge_;
		do
		{
			HE_Edge* pDeletedEdge = edge_;
			edge_ = edge_->next_;
			delete pDeletedEdge;
		} while (edge_ != pEntryEdge);
	}
}

void HE_Face::MakeVertexList(TArray<FVector>& outVertices)
{
	HE_Edge* edge = edge_;
	do
	{
		outVertices.Add(edge->vert_->pos_);
		edge = edge->next_;
	} while (edge != edge_);
}

HE_Edge* HE_Face::FindEdge(const FVector& v0, const FVector& v1, bool bExcludeEdgeWithPair)
{
	HE_Edge* edge = edge_;
	do
	{
		if(!bExcludeEdgeWithPair || !edge->pair_)
		{
			if (v0.Equals(edge->vert_->pos_) && v1.Equals(edge->next_->vert_->pos_))
				return edge;
		}
		edge = edge->next_;
	} while (edge != edge_);
	return NULL;
}

HE_Edge* HE_Edge::PrevEdge()
{
	HE_Edge* edge = this;

	do 
	{
		if (edge->next_ == this)
			return edge;
		edge = edge->next_;
	} while (edge != this);

	// The previous edge must be found all the time.
	return NULL;
}

void HalfEdgeMesh::SolvePair(const HE_FacePtr& pFace)
{
	HE_Edge* edge = pFace->edge_;
	do
	{
		for (int i = 0, iCount(m_pFaces.Num()); i < iCount; ++i)
		{
			HE_Edge* foundEdge = m_pFaces[i]->FindEdge(edge->next_->vert_->pos_, edge->vert_->pos_, true);
			if (foundEdge)
			{
				foundEdge->pair_ = edge;
				edge->pair_ = foundEdge;
				break;
			}
		}
		edge = edge->next_;
	} while (edge != pFace->edge_);
}

}