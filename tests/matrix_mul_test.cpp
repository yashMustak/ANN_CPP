#include<iostream>
#include"../math/matrix.hpp"
#include"../math/matrixMul.hpp"
using namespace std;
using namespace mustak;
int main(){
	math::matrix<double> mat1(3, 3);
	math::matrix<double> mat2(1, 3);
	mat1.set(7.0, 0, 0);
	mat1.set(3.0, 0, 1);
	mat1.set(5.0, 0, 2);
	mat1.set(9.0, 1, 0);
	mat1.set(1.0, 1, 1);
	mat1.set(4.0, 1, 2);
	mat1.set(4.0, 2, 0);
	mat1.set(8.0, 2, 1);
	mat1.set(9.0, 2, 2);
	
	mat2.set(3.0, 0, 0);
//	mat1.matric[0][1] = 3.0;
//	mat1.matric[0][2] = 5.0;
	mat2.set(5.0, 1, 0);
//	mat1.matric[1][1] = 1.0;
//	mat1.matric[1][2] = 4.0;
	mat2.set(6.0, 2, 0);
//	mat1.matric[2][1] = 8.0;
//	mat1.matric[2][2] = 9.0;
	
//	for(int i = 0; i<mat1.size(); i++){
//		for(int j = 0; j<mat1[0].size(); j++){
//			cout<<mat1[i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;
//	for(int i = 0; i<mat2.size(); i++){
//		for(int j = 0; j<mat2[0].size(); j++){
//			cout<<mat2[i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	cout<<endl;

//	math::matrix<double> result(1, 3);
	math::matrix<double> result = math::matrixMulti(mat1, mat2);
	int size1 = result.colno;
	int size2 = result.rowno;
	for(int i = 0; i<size2; i++){
		for(int j = 0; j<size1; j++){
			cout<<result.get(i, j)<<" ";
		}
		cout<<endl;
	}
	return 0;
}
