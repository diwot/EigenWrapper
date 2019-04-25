#pragma once

#include "DiagonalMat.h"
#include <Eigen/Sparse>
#include "NativeData.h"

namespace EigenWrapper
{
	public ref class VectorXd 
	{
	private:
		NativeData<Eigen::VectorXd>* data;
		
	public:
		VectorXd()
		{
			data = new NativeData<Eigen::VectorXd>(Eigen::VectorXd());
		}

		VectorXd(... array<double>^ values)
		{
			int l = values->Length;
			data = new NativeData<Eigen::VectorXd>(Eigen::VectorXd(l));
			for (int i = 0; i < l; ++i)
				data->Data.coeffRef(i) = values[i];
		}

		VectorXd(int dim) 
		{
			data = new NativeData<Eigen::VectorXd>(Eigen::VectorXd(dim));
		}

		VectorXd(Eigen::VectorXd d)
		{
			data = new NativeData<Eigen::VectorXd>(d);
		}
		~VectorXd() { this->!VectorXd(); }
		!VectorXd()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		double maxCoeff()
		{
			return data->Data.maxCoeff();
		}

		double minCoeff()
		{
			return data->Data.minCoeff();
		}

		static VectorXd^ Zero(int dim)
		{
			return gcnew VectorXd(Eigen::VectorXd::Zero(dim));
		}

		void fill(double value)
		{
			data->Data.fill(value);
		}

		/*double squaredNorm()
		{
			data->Data.squaredNorm();
		}*/
		double squaredNorm()
		{
			double sum = 0;
			int l = data->Data.size();
			for (int i = 0; i < l; ++i)
				sum += data->Data.coeffRef(i) * data->Data.coeffRef(i);
			return sum;
		}

		double norm() { return data->Data.norm(); }

		VectorXd^ transpose()
		{
			return gcnew VectorXd(data->Data.transpose());
		}

		const Eigen::VectorXd& GetData() { return data->Data; }

		void SetData(const Eigen::VectorXd& d) { data->Data = d; }
		
		int size() { return data->Data.size(); }
		int cols() { return data->Data.cols(); }
		int rows() { return data->Data.rows(); }

		property int ElementCount
		{
			int get()
			{
				return data->Data.size();
			}
		}
		property int RowCount
		{
			int get()
			{
				return data->Data.rows();
			}
		}
		property int ColCount
		{
			int get()
			{
				return data->Data.cols();
			}
		}
		property System::String^ DebugString
		{
			System::String^ get()
			{
				return ToString();
			}
		}

		void setZero() { data->Data.setZero(); }

		void resize(int size) {	data->Data.resize(size); }

		static VectorXd^ Ones(int dim)
		{
			return gcnew VectorXd(Eigen::VectorXd::Ones(dim));
		}

		//void map(cli::array<double>^ values) 
		//{
		//	//*data = Eigen::Map<Eigen::VectorXd>(&values[0], values->Length);
		//	int l = values->Length;
		//	resize(l);
		//	for (int i = 0; i < l; ++i)
		//		data->Data.coeffRef(i) = values[i];
		//}


		void map(System::Collections::Generic::IList<double>^ values)
		{
			int l = values->Count;
			resize(l);
			for (int i = 0; i < l; ++i)
				data->Data.coeffRef(i) = values[i];
		}

		void conservativeResize(int size) { data->Data.conservativeResize(size); }
		
		DiagonalMatrix^ asDiagonal()
		{
			return gcnew DiagonalMatrix(data->Data.asDiagonal());
		}

		property double default[int]
		{
			inline double get(int index)
			{
				return data->Data.coeffRef(index);
			}
			inline void set(int index, double value)
			{
				data->Data.coeffRef(index) = value;
			}
		}

		static VectorXd^ operator* (DiagonalMatrix^ lhs, VectorXd^ rhs)
		{
			/*if (lhs->cols() != rhs->rows())
				throw gcnew System::Exception("lhs.cols() must be equal to rhs.rows()");*/

			return gcnew VectorXd(lhs->GetData() * rhs->data->Data);
		}

		static VectorXd^ operator* (const double lhs, const VectorXd^ rhs)
		{			
			return gcnew VectorXd(lhs * rhs->data->Data);			
		}
		static VectorXd^ operator* (const VectorXd^ lhs, const double rhs)
		{
			return gcnew VectorXd(lhs->data->Data * rhs);
		}

		static VectorXd^ operator+ (VectorXd^ lhs, VectorXd^ rhs)
		{
			/*if (lhs->size() != rhs->size())
				throw gcnew System::Exception("vectors must have the same number of elements");*/

			return gcnew VectorXd(lhs->data->Data + rhs->data->Data);
		}
		static VectorXd^ operator- (VectorXd^ lhs, VectorXd^ rhs)
		{
			/*if (lhs->size() != rhs->size())
				throw gcnew System::Exception("vectors must have the same number of elements");*/

			return gcnew VectorXd(lhs->data->Data - rhs->data->Data);
		}
		static VectorXd^ operator- (const VectorXd^ v)
		{
			return gcnew VectorXd(-v->data->Data);
		}

		void noalias(const VectorXd^ v)
		{
			data->Data.noalias() = v->data->Data;
		}


		double dot (const VectorXd^ rhs)
		{
			return data->Data.dot(rhs->data->Data);
		}
		VectorXd^ eval()
		{
		   return gcnew VectorXd(data->Data.eval());
		}

		double infinityNorm()
		{
			return data->Data.template lpNorm<Eigen::Infinity>();
		}

		virtual System::String^ ToString() override
		{
			std::stringstream ss;
			ss << data->Data;
			return gcnew System::String(ss.str().c_str());
		}
	};
}

