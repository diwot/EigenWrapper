#pragma once

#include <Eigen/SVD>
#include <Eigen/Sparse>
#include "NativeData.h"
#include "Mat.h"
#include "SparseMat.h"

//typedef Eigen::Matrix<double, 3, 3> M3;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> M;
typedef Eigen::SparseMatrix<double> SpMat;


namespace EigenWrapper
{
	//public ref class JacobiSVD3
	//{
	//private:
	//	//Matrix^ matrixU;
	//	//Matrix^ matrixV;
	//	NativeData<Eigen::JacobiSVD<M3>>* data;

	//public:
	//	JacobiSVD3(Matrix^ m, bool fullU, bool fullV)
	//	{
	//		int opt = 0;

	//		if (fullU)
	//			opt |= Eigen::ComputeFullU;
	//		if (fullV)
	//			opt |= Eigen::ComputeFullV;

	//		M3 m3;
	//		//m3.coeffRef(0, 0) = m[0, 0];
	//		data = new NativeData<Eigen::JacobiSVD<M3>>(Eigen::JacobiSVD<M3>(m, opt));
	//	}

	//	Matrix^ matrixU()
	//	{
	//		return gcnew Matrix(data->Data.matrixU());
	//	}

	//	Matrix^ matrixV()
	//	{
	//		return gcnew Matrix(data->Data.matrixV());
	//	}

	//	VectorXd^ singularValues()
	//	{
	//		return gcnew VectorXd(data->Data.singularValues());
	//	}

	//	/*void compute3x2(Matrix^ m)
	//	{
	//	Eigen::Matrix<double, 3, 2> F = Eigen::Map<Eigen::Matrix<double, 3, 2> >(m->GetData().data());
	//	Eigen::JacobiSVD<Eigen::Matrix<double, 3, 2> > svd(F, Eigen::ComputeFullU | Eigen::ComputeFullV);
	//	}*/
	//};

	public ref class DecompositionOpt
	{
		/** \internal Not used (meant for LDLT?). */
	public:
		static const int Pivoting = 0x01;
		/** \internal Not used (meant for LDLT?). */
		static const int NoPivoting = 0x02;
		/** Used in JacobiSVD to indicate that the square matrix U is to be computed. */
		static const int ComputeFullU = 0x04;
		/** Used in JacobiSVD to indicate that the thin matrix U is to be computed. */
		static const int ComputeThinU = 0x08;
		/** Used in JacobiSVD to indicate that the square matrix V is to be computed. */
		static const int ComputeFullV = 0x10;
		/** Used in JacobiSVD to indicate that the thin matrix V is to be computed. */
		static const int ComputeThinV = 0x20;
		/** Used in SelfAdjointEigenSolver and GeneralizedSelfAdjointEigenSolver to specify
		* that only the eigenvalues are to be computed and not the eigenvectors. */
		static const int EigenvaluesOnly = 0x40;
		/** Used in SelfAdjointEigenSolver and GeneralizedSelfAdjointEigenSolver to specify
		* that both the eigenvalues and the eigenvectors are to be computed. */
		static const int ComputeEigenvectors = 0x80;
		/** \internal */
		static const int EigVecMask = EigenvaluesOnly | ComputeEigenvectors;
		/** Used in GeneralizedSelfAdjointEigenSolver to indicate that it should
		* solve the generalized eigenproblem \f$ Ax = \lambda B x \f$. */
		static const int Ax_lBx = 0x100;
		/** Used in GeneralizedSelfAdjointEigenSolver to indicate that it should
		* solve the generalized eigenproblem \f$ ABx = \lambda x \f$. */
		static const int ABx_lx = 0x200;
		/** Used in GeneralizedSelfAdjointEigenSolver to indicate that it should
		* solve the generalized eigenproblem \f$ BAx = \lambda x \f$. */
		static const int BAx_lx = 0x400;
		/** \internal */
		static const int GenEigMask = Ax_lBx | ABx_lx | BAx_lx;
	};

	public ref class JacobiSVD
	{
	private:
		//Matrix^ matrixU;
		//Matrix^ matrixV;
		NativeData<Eigen::JacobiSVD<M>>* data;

	public:
		JacobiSVD(Matrix^ m, int opt)
		{
			/*int opt = 0;

			if (fullU)
			opt |= Eigen::ComputeFullU;
			if (fullV)
			opt |= Eigen::ComputeFullV;*/

			data = new NativeData<Eigen::JacobiSVD<M>>(Eigen::JacobiSVD<M>(m->GetData(), (Eigen::DecompositionOptions)opt));
		}
		~JacobiSVD() { this->!JacobiSVD(); }
		!JacobiSVD()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		Matrix^ solve(Matrix^ rhs)
		{
			return gcnew Matrix(data->Data.solve(rhs->GetData()));
		}

		VectorXd^ solve(VectorXd^ rhs)
		{
			return gcnew VectorXd(data->Data.solve(rhs->GetData()));
		}

		void setThreshold(double value)
		{
			data->Data.setThreshold(value);
		}

		Matrix^ matrixU()
		{
			return gcnew Matrix(data->Data.matrixU());
		}

		Matrix^ matrixV()
		{
			return gcnew Matrix(data->Data.matrixV());
		}

		VectorXd^ singularValues()
		{
			return gcnew VectorXd(data->Data.singularValues());
		}

		//http://nghiaho.com/?page_id=671
		static void extractRotationSVD3x3(double m11, double m12, double m13, 
			double m21, double m22, double m23,
			double m31, double m32, double m33, 
			[System::Runtime::InteropServices::Out] double% rot11, [System::Runtime::InteropServices::Out] double% rot12, [System::Runtime::InteropServices::Out] double% rot13,
			[System::Runtime::InteropServices::Out] double% rot21, [System::Runtime::InteropServices::Out] double% rot22, [System::Runtime::InteropServices::Out] double% rot23, 
			[System::Runtime::InteropServices::Out] double% rot31, [System::Runtime::InteropServices::Out] double% rot32, [System::Runtime::InteropServices::Out] double% rot33)
		{
			Eigen::Matrix3d F;
			F << m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33;
			const Eigen::JacobiSVD<Eigen::Matrix3d> svd(F, Eigen::ComputeFullU | Eigen::ComputeFullV);
			F = svd.matrixU() * svd.matrixV().transpose();
			
			rot11 = F(0, 0); rot12 = F(0, 1); rot13 = F(0, 2);
			rot21 = F(1, 0); rot22 = F(1, 1); rot23 = F(1, 2);
			
			const auto singularValues = svd.singularValues();
			if (singularValues[0] * singularValues[1] * singularValues[2] >= 0)
			{
				rot31 = F(2, 0); rot32 = F(2, 1); rot33 = F(2, 2);
			}
			else
			{
				rot31 = -F(2, 0); rot32 = -F(2, 1); rot33 = -F(2, 2);
			}
		}
	};

	//public ref class SparseJacobiSVD
	//{
	//private:
	//	//Matrix^ matrixU;
	//	//Matrix^ matrixV;
	//	NativeData<Eigen::JacobiSVD<SpMat>>* data;

	//public:
	//	SparseJacobiSVD(SparseMatrix^ m, bool fullU, bool fullV)
	//	{
	//		int opt = 0;

	//		if (fullU)
	//			opt |= Eigen::ComputeFullU;
	//		if (fullV)
	//			opt |= Eigen::ComputeFullV;

	//		data = new NativeData<Eigen::JacobiSVD<SpMat>>(Eigen::JacobiSVD<SpMat>(m->GetData(), opt));
	//	}
	//	~SparseJacobiSVD() { this->!SparseJacobiSVD(); }
	//	!SparseJacobiSVD()
	//	{
	//		if (data)
	//		{
	//			delete data;
	//			data = 0;
	//		}
	//	}


	//	Matrix^ matrixU()
	//	{
	//		return gcnew Matrix(data->Data.matrixU());
	//	}

	//	Matrix^ matrixV()
	//	{
	//		return gcnew Matrix(data->Data.matrixV());
	//	}

	//	VectorXd^ singularValues()
	//	{
	//		return gcnew VectorXd(data->Data.singularValues());
	//	}

	//	/*void compute3x2(Matrix^ m)
	//	{
	//	Eigen::Matrix<double, 3, 2> F = Eigen::Map<Eigen::Matrix<double, 3, 2> >(m->GetData().data());
	//	Eigen::JacobiSVD<Eigen::Matrix<double, 3, 2> > svd(F, Eigen::ComputeFullU | Eigen::ComputeFullV);
	//	}*/
	//};

	//public ref class SparseBDCSVD
	//{
	//private:
	//	//Matrix^ matrixU;
	//	//Matrix^ matrixV;
	//	NativeData<Eigen::BDCSVD<SpMat>>* data;

	//public:
	//	SparseBDCSVD(SparseMatrix^ m, bool fullU, bool fullV)
	//	{
	//		int opt = 0;

	//		if (fullU)
	//			opt |= Eigen::ComputeFullU;
	//		if (fullV)
	//			opt |= Eigen::ComputeFullV;

	//		data = new NativeData<Eigen::BDCSVD<SpMat>>(Eigen::BDCSVD<SpMat>(m->GetData(), opt));
	//	}
	//	~SparseBDCSVD() { this->!SparseBDCSVD(); }
	//	!SparseBDCSVD()
	//	{
	//		if (data)
	//		{
	//			delete data;
	//			data = 0;
	//		}
	//	}

	//	Matrix^ matrixU()
	//	{
	//		return gcnew Matrix(data->Data.matrixU());
	//	}

	//	Matrix^ matrixV()
	//	{
	//		return gcnew Matrix(data->Data.matrixV());
	//	}

	//	VectorXd^ singularValues()
	//	{
	//		return gcnew VectorXd(data->Data.singularValues());
	//	}

	//	/*void compute3x2(Matrix^ m)
	//	{
	//	Eigen::Matrix<double, 3, 2> F = Eigen::Map<Eigen::Matrix<double, 3, 2> >(m->GetData().data());
	//	Eigen::JacobiSVD<Eigen::Matrix<double, 3, 2> > svd(F, Eigen::ComputeFullU | Eigen::ComputeFullV);
	//	}*/
	//};
}

