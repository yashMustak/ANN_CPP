#ifndef math_matrix_mul
#define math_matrix_mul

#include<iostream>
#include"../math/matrix.hpp"
#include"../exceptions/exception.hpp"
#include<vector>
using namespace std;
//better to apply dynamic programming
namespace mustak{
	namespace math{
		template<class T>
		matrix<T> matrixMulti(matrix<T> matrix1, matrix<T> matrix2){
			try{
				if(matrix1.colno == matrix2.rowno){
					matrix<T> resultMat(matrix2.colno, matrix1.rowno);
					int outer = matrix1.rowno;
					int middle = matrix2.colno;
					int inner = matrix2.rowno;
					for(int i = 0; i<outer; i++){
						for(int j = 0; j<middle; j++){
							for(int k = 0; k<inner; k++){
								resultMat.set(matrix1.get(i, k) * matrix2.get(k, j), i, j);
							}
						}
					}
					return resultMat;
				}
				
				else{
					exceptions::matrix_order_not_match e;
					throw e;		
				}
			}
			catch(exception& e){
				cout<<e.what();
			}
		}
	}
}

#endif
