#include"..\math\matrix.hpp"
using namespace mustak;
using namespace std;
int main(){
	math::matrix<double> mat(5, 3, 1.5);
	for(int i = 0; i<mat.rowno; i++){
		for(int j = 0; j<mat.colno; j++){
			cout<<mat.get(i, j);
		}
		cout<<endl;
	}
	return 0;
}
