#include"../math/matrix.hpp"
using namespace mustak;
using namespace std;
int main(){
	math::matrix<double> mat(5, 3, 1.5);
	mat.print();
	return 0;
}
