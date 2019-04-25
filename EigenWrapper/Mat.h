#pragma once

#include "NativeData.h"
#include <Eigen/Sparse>
#include "VectorXd.h"
#include "DiagonalMat.h"
#include <Eigen/LU>




typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> M;

namespace EigenWrapper
{
	public ref class Matrix
	{
	private:
		NativeData<M>* data;

	public:
		Matrix()
		{
			data = new NativeData<M>(M());
		}

		Matrix(int numCols, ... array<double>^ values)
		{
			int l = values->Length;
			if (l%numCols != 0)
				throw gcnew System::Exception("Number of values provides must be a multiple of numCols");

			int numRows = l / numCols;
			data = new NativeData<M>(M(numRows, numCols));
			int indexer = 0;
			for (int i = 0; i < numRows; ++i)
				for (int j = 0; j < numCols; ++j)
					data->Data.coeffRef(i, j) = values[indexer++];
		}

		Matrix(int numCols, int numRows, array<double>^ values)
		{
			data = new NativeData<M>(M(numRows, numCols));
			int indexer = 0;
			for (int i = 0; i < numRows; ++i)
				for (int j = 0; j < numCols; ++j)
					data->Data.coeffRef(i, j) = values[indexer++];
		}

		Matrix(int rows, int cols)
		{
			data = new NativeData<M>(M(rows, cols));
		}
		Matrix(M d)
		{
			data = new NativeData<M>(d);
		}
		~Matrix() { this->!Matrix(); }
		!Matrix()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}
		const M& GetData() { return data->Data; }

		void resize(int rows, int cols) { data->Data.resize(rows, cols); }


		//VectorXd^ solve(VectorXd^ rhs)
		//{
		//	//https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
		//	return gcnew VectorXd(data->Data.colPivHouseholderQr().solve(rhs->GetData()));
		//}

		property int ColCount
		{
			int get()
			{
				return data->Data.cols();
			}
		}
		property int RowCount
		{
			int get()
			{
				return data->Data.rows();
			}
		}
		property System::String^ DebugString
		{
			System::String^ get()
			{
				return ToString();
			}
		}

		//Matrix^ inverse() { return gcnew Matrix(data->Data.inverse()); }

		Matrix^ transpose() { return gcnew Matrix(data->Data.transpose()); }

		void transposeInPlace() { data->Data.transposeInPlace(); }

		//double determinant() { return data->Data.determinant(); }

		static Matrix^ Zero(int rows, int cols)
		{
			return gcnew Matrix(M::Zero(rows, cols));
		}

		static Matrix^ Ones(int rows, int cols)
		{
			return gcnew Matrix(M::Ones(rows, cols));
		}

		static Matrix^ Identity(int dim)
		{
			return gcnew Matrix(M::Identity(dim, dim));
		}

		/*static Matrix^ Zero(int dim)
		{
			return gcnew Matrix(M::Zero(dim));
		}*/

		double norm() { return data->Data.norm(); }
		double squaredNorm() { return data->Data.squaredNorm(); }

		void setIdentity()
		{
			data->Data.setIdentity();
		}

		double determinant()
		{
			return data->Data.determinant();
		}

		Matrix^ inverse()
		{
			return gcnew Matrix(data->Data.inverse());
		}

		/*property double default[int]
		{
			inline double get(int i)
			{
				return data->Data(i);
			}
			inline void set(int i, double value)
			{
				data->Data(i) = value;
			}
		}*/

		property double default[int, int]
		{
			inline double get(int r, int c)
			{
				return data->Data.coeffRef(r, c);
			}
			inline void set(int r, int c, double value)
			{
				data->Data.coeffRef(r, c) = value;
			}
		}



		static VectorXd^ operator* (Matrix^ lhs, VectorXd^ rhs)
		{
			//if (lhs->cols() != rhs->rows())
			//	throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");

			return gcnew VectorXd(lhs->data->Data * rhs->GetData());
		}

		static Matrix^ operator* (const double lhs, const Matrix^ rhs)
		{
			return gcnew Matrix(lhs * rhs->data->Data);
		}

		static Matrix^ operator* (const Matrix^ lhs, const double rhs)
		{
			return gcnew Matrix(lhs->data->Data * rhs);
		}

		static Matrix^ operator+ (Matrix^ lhs, Matrix^ rhs)
		{
			/*if (lhs->rows() != rhs->rows())
				throw gcnew System::Exception("Both operands must have the same number of rows");

			if (lhs->cols() != rhs->cols())
				throw gcnew System::Exception("Both operands must have the same number of columns");*/

			return gcnew Matrix(lhs->data->Data + rhs->data->Data);
		}

		static Matrix^ operator- (Matrix^ lhs, Matrix^ rhs)
		{
			//if (lhs->rows() != rhs->rows())
			//	throw gcnew System::Exception("Both operands must have the same number of rows");

			//if (lhs->cols() != rhs->cols())
			//	throw gcnew System::Exception("Both operands must have the same number of columns");

			return gcnew Matrix(lhs->data->Data - rhs->data->Data);
		}

		static Matrix^ operator* (Matrix^ lhs, Matrix^ rhs)
		{
			//if (lhs->cols() != rhs->rows())
			//	throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");

			return gcnew Matrix(lhs->data->Data * rhs->data->Data);
		}

		static Matrix^ operator* (Matrix^ lhs, DiagonalMatrix^ rhs)
		{
			//if (lhs->cols() != rhs->rows())
			//	throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");

			return gcnew Matrix(lhs->data->Data * rhs->GetData());
		}

		static Matrix^ operator* (DiagonalMatrix^ lhs, Matrix^ rhs)
		{
			//if (lhs->cols() != rhs->rows())
			//	throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");

			return gcnew Matrix(lhs->GetData() * rhs->data->Data);
		}


		VectorXd^ col(int index)
		{
			return gcnew VectorXd(data->Data.col(index));
		}

		Matrix^ rightCols(int index)
		{
			return gcnew Matrix(data->Data.rightCols(index));
		}
		Matrix^ leftCols(int index)
		{
			return gcnew Matrix(data->Data.leftCols(index));
		}

		void rightCols(int index, VectorXd^ value)
		{
			data->Data.rightCols(index) = value->GetData();
		}
		void leftCols(int index, VectorXd^ value)
		{
			data->Data.leftCols(index) = value->GetData();
		}
		void rightCols(int index, Matrix^ value)
		{
			data->Data.rightCols(index) = value->GetData();
		}
		void leftCols(int index, Matrix^ value)
		{
			data->Data.leftCols(index) = value->GetData();
		}

		void col(int index, VectorXd^ col)
		{
			data->Data.col(index) = col->GetData();
		}

		int rows()
		{
			return data->Data.rows();
		}
		int cols()
		{
			return data->Data.cols();
		}

		void setZero()
		{
			data->Data.setZero();
		}

		Matrix^ eval()
		{
			return gcnew Matrix(data->Data.eval());
		}



		virtual System::String^ ToString() override
		{
			std::stringstream ss;
			ss << data->Data;
			return "[" + rows().ToString() + ", " + cols().ToString() + "]   " + gcnew System::String(ss.str().c_str());
		}
	};
}

