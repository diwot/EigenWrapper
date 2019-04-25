#pragma once

#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <GenEigsSolver.h>
#include <SymEigsSolver.h>
#include <SymEigsShiftSolver.h>
#include <MatOp/SparseGenMatProd.h>
#include <MatOp/SparseSymMatProd.h>
#include <MatOp/SparseSymShiftSolve.h>
#include "SparseMat.h"
#include "VectorXd.h"

using namespace Spectra;

namespace EigenWrapper
{
	public ref class Spectra 
	{
	private:		

	public:
		Spectra()
		{
			
		}		

		static VectorXd^ SymmetricMatrixLargestEigenvalues(SparseMatrix^ m)
		{
			return SymmetricMatrixLargestEigenvalues(m, 3, 6);
		}

		static VectorXd^ SymmetricMatrixLargestEigenvalues(SparseMatrix^ m, int nev, int ncv)
		{
			//https://github.com/yixuan/spectra
			// Construct matrix operation object using the wrapper class SparseGenMatProd
			SparseGenMatProd<double> op(m->GetData());

			// Construct eigen solver object, requesting the largest three eigenvalues
			SymEigsSolver< double, LARGEST_MAGN, SparseGenMatProd<double> > eigs(&op, nev, ncv);

			// Initialize and compute
			eigs.init();
			int nconv = eigs.compute();

			// Retrieve results
			Eigen::VectorXd evalues;
			if (eigs.info() == SUCCESSFUL)
				evalues = eigs.eigenvalues();

			return gcnew VectorXd(evalues);
		}	

		static VectorXd^ SymmetricMatrixSmallestEigenvalues(SparseMatrix^ m)
		{
			return SymmetricMatrixSmallestEigenvalues(m, 3, 6);
		}

		/*	op_	Pointer to the matrix operation object, which should implement the matrix - vector multiplication operation of A : calculating Av for any vector v.Users could either create the object from the wrapper class such as DenseSymMatProd, or define their own that impelements all the public member functions as in DenseSymMatProd.
		nev_	Number of eigenvalues requested.This should satisfy 1≤nev≤n−1, where n is the size of matrix.
		ncv_	Parameter that controls the convergence speed of the algorithm.Typically a larger ncv_ means faster convergence, but it may also result in greater memory use and more matrix operations in each iteration.This parameter must satisfy nev < ncv≤n, and is advised to take ncv≥2⋅nev.*/
		static VectorXd^ SymmetricMatrixSmallestEigenvalues(SparseMatrix^ m, int nev, int ncv)
		{
			////https://github.com/yixuan/spectra
			//// Construct matrix operation object using the wrapper class SparseGenMatProd
			//SparseGenMatProd<double> op(m->GetData());

			//// Construct eigen solver object, requesting the largest three eigenvalues
			//SymEigsSolver< double, SMALLEST_MAGN, SparseGenMatProd<double> > eigs(&op, nev, ncv);

			//// Initialize and compute
			//eigs.init();
			//int nconv = eigs.compute();

			//// Retrieve results
			//Eigen::VectorXd evalues;
			//if (eigs.info() == SUCCESSFUL)
			//	evalues = eigs.eigenvalues();

			//return gcnew VectorXd(evalues);


			//https://github.com/yixuan/spectra
			//https://spectralib.org/doc/classspectra_1_1symeigsshiftsolver
			//https://github.com/yixuan/spectra/issues/10
			// Construct matrix operation object using the wrapper class SparseGenMatProd
			SparseSymShiftSolve<double> op(m->GetData());

			// Construct eigen solver object, requesting the largest three eigenvalues
			SymEigsShiftSolver< double, LARGEST_MAGN, SparseSymShiftSolve<double> > eigs(&op, nev, ncv, 0.0);

			// Initialize and compute
			eigs.init();
			int nconv = eigs.compute();

			// Retrieve results
			Eigen::VectorXd evalues;
			if (eigs.info() == SUCCESSFUL)
				evalues = eigs.eigenvalues();

			return gcnew VectorXd(evalues);
		}
	};
}

