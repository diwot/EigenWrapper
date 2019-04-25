#pragma once

#include <Eigen/Sparse>
#include <vector>

typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

namespace EigenWrapper
{
	//TODO: Rename
	public ref class EigSolver
	{
	private:
		int _numRows;
		Eigen::SparseLU<SpMat>* _solver; //https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html
	
	public:
		EigSolver(int numRows, cli::array<double>^ values, cli::array<int>^ rows, cli::array<int>^ cols);
		void DisposeResources();
		void Solve(cli::array<double>^ rhs, cli::array<double>^ solution);

	public:
		static void SolveTriplet(cli::array<double>^ values, cli::array<int>^ rows, cli::array<int>^ cols, cli::array<double>^ rhs, cli::array<double>^ solution);
	};
}

