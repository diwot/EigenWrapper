#pragma once

#include <Eigen/Sparse>
#include "SparseMat.h"
#include "Mat.h"
#include "ISol.h"

typedef Eigen::SparseMatrix<double> SpMat;

namespace EigenWrapper
{
	public ref class SimplicialLDLT : public ISolver 
	{
	private:
		Eigen::SimplicialLDLT<SpMat>* data;

	public:
		SimplicialLDLT() 
		{
			data = new Eigen::SimplicialLDLT<SpMat>();
		}
		~SimplicialLDLT() { this->!SimplicialLDLT(); }
		!SimplicialLDLT()
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

