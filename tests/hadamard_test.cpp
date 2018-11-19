#include<iostream>
#include"../math/hadamardPro.hpp"
#include"../preReq.hpp"
using namespace std;
using namespace mustak;

int main(){
	math::matrix<double> mat1(3, 2);
	math::matrix<double> mat2(3, 2);
	mat1.set(2.0, 0, 0);
	mat1.set(5.0, 0, 1);
	mat1.set(1.0, 0, 2);
	mat1.set(3.0, 1, 0);
	mat1.set(8.0, 1, 1);
	mat1.set(6.0, 1, 2);
	
	mat2.set(0.0, 0, 0);
	mat2.set(4.0, 0, 1);
	mat2.set(7.0, 0, 2);
	mat2.set(8.0, 1, 0);
	mat2.set(1.0, 1, 1);
	mat2.set(5.0, 1, 2);
	math::matrix<double> ans;
	ans = math::hadamard(mat1, mat2);
	for(int i = 0; i<ans.rowno; i++){
		for(int j = 0; j<ans.colno; j++){
			cout<<ans.get(i, j)<<"\t";
		}
		cout<<endl;
	}
	// 2 5 1	0 4 7	0 20 7
	// 3 8 6	8 1 5	24 8 30 
}
