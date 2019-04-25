#pragma once

#include <Eigen/Sparse>
#include "NativeData.h"

namespace EigenWrapper
{
	public ref class VectorXi
	{
	private:
		NativeData<Eigen::VectorXi>* data;

	public:
		VectorXi()
		{
			data = new NativeData<Eigen::VectorXi>(Eigen::VectorXi());
		}

		VectorXi(int dim)
		{
			data = new NativeData<Eigen::VectorXi>(Eigen::VectorXi(dim));
		}
		
		VectorXi(Eigen::VectorXi d)
		{
			data = new NativeData<Eigen::VectorXi>(d);
		}
		~VectorXi() { this->!VectorXi(); }
		!VectorXi() 
		{
			if (data) 
			{
				delete data;
				data = 0;
			}
		}

		static VectorXi^ Ones(int dim)
		{
			return gcnew VectorXi(Eigen::VectorXi::Ones(dim));
		}

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

		const Eigen::VectorXi& GetData() { return data->Data; }

		virtual System::String^ ToString() override
		{
			std::stringstream ss;
			ss << data->Data;
			return gcnew System::String(ss.str().c_str());
		}
	};
}

