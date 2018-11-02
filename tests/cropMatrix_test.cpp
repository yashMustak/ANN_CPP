#include"..\math\cropMat.hpp"
#include"..\math\matrix.hpp"
using namespace std;
using namespace mustak;

int main(){
	math::matrix<double> mat(3, 4);
	mat.set(2.0, 0, 0);
	mat.set(5.0, 0, 1);
	mat.set(1.0, 0, 2);
	mat.set(3.0, 1, 0);
	mat.set(8.0, 1, 1);
	mat.set(6.0, 1, 2);
	mat.set(0.0, 2, 0);
	mat.set(4.0, 2, 1);
	mat.set(5.0, 2, 2);
	mat.set(7.0, 3, 0);
	mat.set(2.0, 3, 1);
	mat.set(7.0, 3, 2);
	math::matrix<double> ans = math::cropMatrix(mat, 0, 3, 0, 3);
	for(int i = 0; i<ans.rowno; i++){
		for(int j = 0; j<ans.colno; j++){
			cout<<ans.get(i, j);
		}
		cout<<endl;
	}
}
