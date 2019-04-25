#pragma once

#include <Eigen/Sparse>
#include "NativeData.h"
#include "TripletDoubleList.h"
#include "VectorXd.h"
#include "VectorXi.h"
#include "DiagonalMat.h"
#include "Mat.h"


namespace EigenWrapper
{
	public value class SparseMatrixEntry
	{
	public:
		int Row;
		int Col;
		double Value;

		SparseMatrixEntry(int row, int col, double value)
		{
			Row = row;
			Col = col;
			Value = value;
		}

		virtual System::String^ ToString() override
		{
			return Value.ToString() + " (" + Row.ToString() + ", " + Col.ToString() + ")";
		}
	};

	public ref class SparseMatrix
	{
	private:
		NativeData<Eigen::SparseMatrix<double>>* data;

	public:
		SparseMatrix() 
		{
			data = new NativeData<Eigen::SparseMatrix<double>>(Eigen::SparseMatrix<double>());
		}

		SparseMatrix(int rows, int cols)
		{
			data = new NativeData<Eigen::SparseMatrix<double>>(Eigen::SparseMatrix<double>(rows, cols));
		}

		SparseMatrix(Eigen::SparseMatrix<double> d)
		{
			data = new NativeData<Eigen::SparseMatrix<double>>(d);
		}
		~SparseMatrix() { this->!SparseMatrix(); }
		!SparseMatrix()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		
		System::Collections::Generic::List<SparseMatrixEntry>^ GetListOfNonzeroEntries()
		{
			System::Collections::Generic::List<SparseMatrixEntry>^ result = gcnew System::Collections::Generic::List<SparseMatrixEntry>();
			for (int k = 0; k < data->Data.outerSize(); ++k) 
			{
				for (Eigen::SparseMatrix<double>::InnerIterator it(data->Data, k); it; ++it)
				{
					/*cout << it.row() << "\t";
					cout << it.col() << "\t";
					cout << it.value() << endl;*/
					result->Add(SparseMatrixEntry(it.row(), it.col(), it.value()));
				}
			}
			return result;
		}

		const Eigen::SparseMatrix<double>& GetData() { return data->Data; }

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

		property bool IsRowMajor
		{
			bool get()
			{
				return data->Data.IsRowMajor; 
			}
		}

		void resize(int rows, int cols) { data->Data.resize(rows, cols); }

		void reserve(VectorXi^ v) { data->Data.reserve(v->GetData()); }

		SparseMatrix^ transpose()
		{
			SparseMatrix^ m = gcnew SparseMatrix();
			m->data->Data = data->Data.transpose();
			return m;
		}

		void setFromTriplets(System::Collections::Generic::IList<SparseMatrixEntry>^ triplets)
		{
			int l = triplets->Count;
			std::vector<T> buffer(l);
			for (int i = 0; i < l; ++i)
			{
				SparseMatrixEntry t = triplets[i];
				buffer[i] = (T(t.Row, t.Col, t.Value));
			}
			
			//data = new Eigen::SparseMatrix<double>(numRows, numRows);
			data->Data.setFromTriplets(buffer.begin(), buffer.end());
		}

		void setFromTriplets(TripletDoubleList^ triplets) 
		{
			auto t = triplets->GetData();
			data->Data.setFromTriplets(t.begin(), t.end());
		}
		void setFromTriplets(int numRows, System::Collections::Generic::IList<double>^ values, 
			System::Collections::Generic::IList<int>^ rows, System::Collections::Generic::IList<int>^ cols)
		{
			//https://msdn.microsoft.com/en-us/library/1dz8byfh.aspx

			int l = values->Count;
			std::vector<T> buffer(l);
			for (int i = 0; i < l; ++i)
			{
				int r = rows[i];
				int c = cols[i];
				double v = values[i];
				buffer[i] = (T(r, c, v));
			}

			//data = new Eigen::SparseMatrix<double>(numRows, numRows);
			data->Data.setFromTriplets(buffer.begin(), buffer.end());
		}	

		static SparseMatrix^ operator* (SparseMatrix^ lhs, SparseMatrix^ rhs)
		{
			/*if (lhs->cols() != rhs->rows())
				throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");*/

			//https://msdn.microsoft.com/en-us/library/ms235240.aspx
			return gcnew SparseMatrix(lhs->data->Data * rhs->data->Data);			
		}
		static VectorXd^ operator* (SparseMatrix^ lhs, VectorXd^ rhs)
		{
			/*if (lhs->cols() != rhs->rows())
				throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");*/

			return gcnew VectorXd(lhs->data->Data * rhs->GetData());
		}
		static SparseMatrix^ operator* (double lhs, SparseMatrix^ rhs)
		{
			return gcnew SparseMatrix(lhs * rhs->data->Data);
		}
		static SparseMatrix^ operator* (SparseMatrix^ lhs, DiagonalMatrix^ rhs)
		{
			/*if (lhs->cols() != rhs->rows())
				throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");*/

			return gcnew SparseMatrix(lhs->data->Data * rhs->GetData());
		}
		static Matrix^ operator* (SparseMatrix^ lhs, Matrix^ rhs)
		{
			/*if (lhs->cols() != rhs->rows())
				throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");*/

			return gcnew Matrix(lhs->data->Data * rhs->GetData());
		}
		static SparseMatrix^ operator+ (SparseMatrix^ lhs, SparseMatrix^ rhs)
		{
			/*if (lhs->rows() != rhs->rows())
				throw gcnew System::Exception("Both operands must have the same number of rows");

			if (lhs->cols() != rhs->cols())
				throw gcnew System::Exception("Both operands must have the same number of columns");*/

			return gcnew SparseMatrix(lhs->data->Data + rhs->data->Data);
		}
		static SparseMatrix^ operator- (SparseMatrix^ lhs, SparseMatrix^ rhs)
		{
			/*if (lhs->rows() != rhs->rows())
				throw gcnew System::Exception("Both operands must have the same number of rows");

			if (lhs->cols() != rhs->cols())
				throw gcnew System::Exception("Both operands must have the same number of columns");*/

			return gcnew SparseMatrix(lhs->data->Data - rhs->data->Data);
		}

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

		//https://eigen.tuxfamily.org/dox/group__TutorialSparse.html#title7
		SparseMatrix^ GetBlock(const int startRow, const int startCol, const int blockRows, const int blockCols)
		{
			return gcnew SparseMatrix(data->Data.block(startRow, startCol, blockRows, blockCols));
		}
		/*SparseMatrix^ SetBlock(SparseMatrix block, const int startRow, const int startCol)
		{
			data->Data.block(startRow, startCol) = block;
		}*/

		virtual System::String^ ToString() override
		{
			std::stringstream ss;
			ss << data->Data; 
			return "[" + rows().ToString() + ", " + cols().ToString() + "]   " + gcnew System::String(ss.str().c_str());
		}


		/*void GraphColoringExperiment()
		{
			std::map<int, std::map<int, std::vector<int>>> colorTable;
			int colorIndexer = 0;

			auto& m = data->Data;
			for (int k = 0; k < m.outerSize(); ++k)
				for (Eigen::SparseMatrix<double>::InnerIterator it(m, k); it; ++it)
				{
					//it.value();
					it.row();   // row index
					it.col();   // col index (here it is equal to k)
					//it.index(); // inner index, here it is equal to it.row()


				}
		}*/
	};
}

