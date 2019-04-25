#pragma once

#include <Eigen/Sparse>
#include "NativeData.h"

namespace EigenWrapper
{
	public ref class DiagonalMatrix
	{
	private:
		NativeData<Eigen::DiagonalMatrix<double, Eigen::Dynamic>>* data;

	public:
		DiagonalMatrix(Eigen::DiagonalMatrix<double, Eigen::Dynamic> d)
		{
			data = new NativeData<Eigen::DiagonalMatrix<double, Eigen::Dynamic>>(d);
		}
		~DiagonalMatrix() { this->!DiagonalMatrix(); }
		!DiagonalMatrix()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		const Eigen::DiagonalMatrix<double, Eigen::Dynamic>& GetData() { return data->Data; }

		int cols() { return data->Data.cols(); }
		int rows() { return data->Data.rows(); }

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


		static DiagonalMatrix^ operator* (const double lhs, const DiagonalMatrix^ rhs)
		{
			return gcnew DiagonalMatrix(lhs * rhs->data->Data);
		}

		static DiagonalMatrix^ operator* (const DiagonalMatrix^ lhs, const double rhs)
		{
			return gcnew DiagonalMatrix(lhs->data->Data * rhs);
		}

		/*static Matrix^ operator* (const DiagonalMatrix^ lhs, const Matrix^ rhs)
		{
			return gcnew Matrix(lhs->data->Data * rhs->GetData());
		}*/


		virtual System::String^ ToString() override
		{
			std::stringstream ss;
			ss << data->Data.diagonal();
			return gcnew System::String(ss.str().c_str());
		}
	};
}

