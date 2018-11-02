#include<iostream>
#include"..\network_new.hpp"
using namespace std;
using namespace mustak;

int main(){
	network mynn;
	layers::layer l1(2);
	layers::layer l2(3);
	layers::layer l3(2);
//	layers::layer l4(3);
	mynn.addLayer(l1);
	mynn.addLayer(l2);
	mynn.addLayer(l3);
//	mynn.addLayer(l4);
	math::matrix<double> input(2, 1);
	input.set(3.0, 0, 0);
	input.set(1.0, 0, 1);
	math::matrix<double> output = mynn.feed(input);
	for(int i = 0; i<output.colno; i++){
		cout<<output.get(0, i)<<", ";
	}
	math::matrix<double> out(1, 2);
	out.set(1.0, 0, 0);
	out.set(0.0, 0, 1);
	mynn.backPropagate(out);
	cout<<"finish !!!"<<endl;
	return 0;
}
