#include"..\preReq.hpp"
#include"..\math\transpose.hpp"
using namespace std;
using namespace mustak;
int main(){
	math::matrix<double> mat(3, 2);
	mat.set(2.0, 0, 0);
	mat.set(1.0, 0, 1);
	mat.set(9.0, 0, 2);
	mat.set(3.0, 1, 0);
	mat.set(8.0, 1, 1);
	mat.set(6.0, 1, 2);
	math::matrix<double> trans = math::transpose(mat);
	for(int i = 0; i<trans.rowno; i++){
		for(int j = 0; j<trans.colno; j++){
			cout<<trans.get(i, j)<<" ";
		}
		cout<<endl;
	}
}
