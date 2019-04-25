//#pragma once
//
//#include "NativeData.h"
//#include "VectorXd.h"
//#include "cppoptlib\problem.h"
//#include "cppoptlib/solver/lbfgssolver.h"
//
//typedef cppoptlib::Problem<double> BaseProblem;
//
//namespace EigenWrapper
//{
//	class ProblemWrapper : public BaseProblem
//	{
//	public:
//		double(*_value)(const Eigen::VectorXd &x);
//
//		ProblemWrapper(/*double(*value_)(const Eigen::VectorXd &x)*/)
//		{
//			//_value = value_;
//		}
//
//		double value(const Eigen::VectorXd &x)
//		{
//			return _value(x);
//		}
//		void gradient(const Eigen::VectorXd &x, Eigen::VectorXd &grad)
//		{
//			BaseProblem::gradient(x, grad);
//		}
//	};
//
//
//	public ref class Problem
//	{
//	private:
//		NativeData<ProblemWrapper>* data;
//		VectorXd^ _x;
//
//		double valueNative(const Eigen::VectorXd &x)
//		{
//			_x->SetData(x);
//			return value(_x);
//		};
//
//	public:
//		Problem()
//		{
//			_x = gcnew VectorXd();
//			data = new NativeData<ProblemWrapper>(ProblemWrapper(/*&valueNative*/));
//		}
//
//		virtual double value(VectorXd^ x)
//		{
//			return 0;
//		};
//	};
//}
//
