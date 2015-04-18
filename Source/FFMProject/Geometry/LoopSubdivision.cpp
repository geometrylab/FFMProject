#include "FFMProject.h"
#include "LoopSubdivision.h"

namespace FFMGeometry
{

ModelPtr LoopSubdivision::Subdivide(ModelPtr pModel)
{
	ModelPtr pNextModel = ModelPtr(new Model);

	for (int i = 0, iFaceCount(pModel->GetFaceCount()); i < iFaceCount; ++i)
	{
		const HE_FacePtr& face = pModel->GetFace(i);

		FVector next_edge_positions[3];
		FVector next_vert_positions[3];

		// Calculates the next positions
		{
			int count = 0;
			HE_Edge* edge = face->edge_;
			do
			{
				if (edge->pair_)
				{
					next_edge_positions[count] =
						edge->vert_->pos_ * 0.375f +
						edge->PrevEdge()->vert_->pos_ * 0.375f +
						edge->next_->vert_->pos_ * 0.125f +
						edge->pair_->next_->next_->vert_->pos_ * 0.125f;
				}
				else
				{
					next_edge_positions[count] =
						edge->vert_->pos_ * 0.5f +
						edge->next_->next_->vert_->pos_ * 0.5f;
				}

				{
					TArray<HE_Vertex*> neighbors;
					edge->vert_->GetNeighboringVertices(neighbors);
					int n = neighbors.Num();
					float beta = 3.0f / (n*(n + 2.0f));
					next_vert_positions[count] = FVector::ZeroVector;
					for (int k = 0; k < n; ++k)
						next_vert_positions[count] += neighbors[k]->pos_;
					next_vert_positions[count] *= beta;
					next_vert_positions[count] += (1 - n*beta)*edge->vert_->pos_;
				}

				++count;
				edge = edge->next_;

			} while (edge != face->edge_ && count < 3);
		}

		// Makes next level faces based on new position calculated above
		{
			TArray<FVector> next_face;
			for (int k = 0; k < 3; ++k)
			{
				int prev_k = (k + 2) % 3;

				next_face.Add(next_vert_positions[k]);
				next_face.Add(next_edge_positions[prev_k]);
				next_face.Add(next_edge_positions[k]);

				pNextModel->AddFace(next_face);
			}
		}
	}

	return pNextModel;
}

}