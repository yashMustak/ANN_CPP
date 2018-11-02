#ifndef mustak_math_transpose
#define mustak_math_transpose

#include"..\preReq.hpp"
using namespace std;

namespace mustak{
	namespace math{
		matrix<double> transpose(matrix<double> mat){
			int out = mat.rowno;
			int in = mat.colno;
			matrix<double> trans(out, in);
			for(int i = 0; i<in; i++){
				for(int j = 0; j<out; j++){
					trans.set(mat.get(j, i), i, j);
				}
			}
			return trans;
		}
	}
}

#endif
