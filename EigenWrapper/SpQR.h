#pragma once
#include <Eigen/Sparse>
#include "SparseMat.h"
#include "Mat.h"
#include "ISol.h"

typedef Eigen::SparseMatrix<double> SpMat;

namespace EigenWrapper
{
	public ref class SparseQR : public ISolver
	{
	private:
		Eigen::SparseQR<SpMat, Eigen::COLAMDOrdering<int>>* data;

	public:
		SparseQR()
		{
			data = new Eigen::SparseQR<SpMat, Eigen::COLAMDOrdering<int>>();
		}
		~SparseQR() { this->!SparseQR(); }
		!SparseQR()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		virtual void compute(SparseMatrix^ m)
		{
			data->compute(m->GetData());
		}

		virtual VectorXd^ solve(VectorXd^ rhs)
		{
			return gcnew VectorXd(data->solve(rhs->GetData()));
		}

		virtual Matrix^ solve(Matrix^ rhs)
		{
			return gcnew Matrix(data->solve(rhs->GetData()));
		}
	};
}