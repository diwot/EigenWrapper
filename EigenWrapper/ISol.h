#pragma once

#include "VectorXd.h"
#include "SparseMat.h"
#include "Mat.h"

namespace EigenWrapper
{
	public interface class ISolver
	{
		void compute(SparseMatrix^ m);
		VectorXd^ solve(VectorXd^ rhs);
		Matrix^ solve(Matrix^ rhs);
	};
}


