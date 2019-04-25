#include "EigSolver.h"
#include <Eigen/Sparse>
#include <vector>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

namespace EigenWrapper
{
	EigSolver::EigSolver(int numRows, cli::array<double>^ values, cli::array<int>^ rows, cli::array<int>^ cols)
	{
		int l = values->Length;
		std::vector<T> buffer(l);
		for (int i = 0; i < l; ++i)
		{
			int r = rows[i];
			int c = cols[i];
			double v = values[i];
			buffer[i] = (T(r, c, v));
		}

		SpMat A(numRows, numRows);
		A.setFromTriplets(buffer.begin(), buffer.end());
		// Solving:
		_solver = new Eigen::SparseLU<SpMat>();
		_solver->compute(A);
		_numRows = numRows;

		if (_solver->info() != Eigen::ComputationInfo::Success)
		{
			throw gcnew System::Exception("Decomposition failed");
		}
	}

	void EigSolver::DisposeResources()
	{
		delete _solver;
	}

	void EigSolver::Solve(cli::array<double>^ rhs, cli::array<double>^ solution)
	{
		int numRows = _numRows;
		Eigen::VectorXd b(numRows);
		for (int i = 0; i < numRows; ++i)
			b[i] = rhs[i];

		Eigen::VectorXd x = _solver->solve(b);

		for (int i = 0; i < numRows; ++i)
			solution[i] = x[i];
	}

	void EigSolver::SolveTriplet(cli::array<double>^ values, cli::array<int>^ rows, cli::array<int>^ cols, 
		cli::array<double>^ rhs, cli::array<double>^ solution)
	{		
		int numRows = rhs->Length;
		int l = values->Length;
		std::vector<T> buffer(l);
		for (int i = 0; i < l; ++i) 
		{
			int r = rows[i];
			int c = cols[i];
			double v = values[i];
			buffer[i] = (T(r, c, v));
		}

		Eigen::VectorXd b(numRows);
		for (int i = 0; i < numRows; ++i)
			b[i] = rhs[i];

		SpMat A(numRows, numRows);
		A.setFromTriplets(buffer.begin(), buffer.end());
		// Solving:
		//https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html
		Eigen::SparseLU<SpMat> chol(A);  // performs a factorization of A
		Eigen::VectorXd x = chol.solve(b);         // use the factorization to solve for the given right hand side

		for (int i = 0; i < numRows; ++i)
			solution[i] = x[i];
	}
}
