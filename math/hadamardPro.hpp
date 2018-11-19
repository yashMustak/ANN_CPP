#ifndef mustak_math_hadamard
#define mustak_math_hadamard

#include"../preReq.hpp"
using namespace std;

namespace mustak{
	namespace math{
		matrix<double> hadamard(matrix<double> mat1, matrix<double> mat2){
			cout<<"in hadamard pro"<<endl;
			try{
				int out1 = mat1.rowno;
				int in1 = mat1.colno;
				int out2 = mat2.rowno;
				int in2 = mat2.colno;
				matrix<double> hProduct(in1, out1);
				if(out1 == out2 && in1 == in2){
					for(int i = 0; i<out1; i++){
						for(int j = 0; j<in1; j++){
							hProduct.set(mat1.get(i, j)*mat2.get(i, j), i, j);
						}
					}
					cout<<"returning from hadamard";
					return hProduct;
				}
				else{
					exceptions::matrix_order_not_match e;
					throw e;
				}
			}
			catch(exception& e){
				cout<<e.what()<<endl;
			}
		}
	}
}

#endif
