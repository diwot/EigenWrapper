#pragma once

#include <Eigen/Sparse>
#include "NativeData.h"
typedef Eigen::Triplet<double> T;

namespace EigenWrapper
{
	public ref class TripletDoubleList
	{
	private:
		NativeData<std::vector<T>>* data;

	public:
		TripletDoubleList() 
		{
			data = new NativeData<std::vector<T>>(std::vector<T>());			
		}
		~TripletDoubleList() { this->!TripletDoubleList(); }
		!TripletDoubleList()
		{
			if (data)
			{
				delete data;
				data = 0;
			}
		}

		void reserve(int capacity)
		{
			data->Data.reserve(capacity);
		}

		//https://eigen.tuxfamily.org/dox/group__TutorialSparse.html
		// A triplet is a simple object representing a non-zero entry as the triplet: row index, column index, value.
		void push_back(int row, int col, double value)
		{
			data->Data.push_back(T(row, col, value));
		}

		int size() { return data->Data.size(); }

		const std::vector<T>& GetData() { return data->Data; } 

		property int Count
		{
			int get()
			{
				return data->Data.size();
			}
		}
	};
}

