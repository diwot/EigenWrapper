#pragma once

#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>
#include "SparseMat.h"
#include "Mat.h"
#include "ISol.h"

typedef Eigen::SparseMatrix<double> SpMat;

namespace EigenWrapper
{
	public ref class LeastSquaresConjugateGradient : public ISolver
	{
	private:
		Eigen::LeastSquaresConjugateGradient <SpMat>* data;

	public:
		LeastSquaresConjugateGradient()
		{
			data = new Eigen::LeastSquaresConjugateGradient<SpMat>();			
		}
		~LeastSquaresConjugateGradient() { this->!LeastSquaresConjugateGradient(); }
		!LeastSquaresConjugateGradient()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		void setTolerance(double tolerance)
		{
			data->setTolerance(tolerance);
		}
		void setMaxIterations(int maxIterations)
		{
			data->setMaxIterations(maxIterations);
		}
		/*double getTolerance()
		{ 
			double d = data->tolerance();
			return d;
		}*/
		property double Tolerance
		{
			double get()
			{
				return data->tolerance();
			}
			void set(double tolerance)
			{
				data->setTolerance(tolerance);
			}
		}
		property int MaxIterations
		{
			int get()
			{
				return data->maxIterations();
			}
			void set(int maxIterations)
			{
				data->setMaxIterations(maxIterations);
			}
		}
		property int Iterations
		{
			int get()
			{
				return data->iterations();
			}
		}
		property double Error
		{
			double get()
			{
				return data->error();
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