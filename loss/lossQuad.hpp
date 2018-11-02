#ifndef mustak_quadreatic_loss_function
#define mustak_quadreatic_loss_function

#include"..\preReq.hpp"
#include<cmath>
using namespace std;

namespace mustak{
	namespace loss{
		double lossQuad(math::matrix<double> networkOutput, math::matrix<double> expectedOutput){
			//error check if these matrix are empty or not
			int noOfOutput = networkOutput.colno;
			double squaredSum = 0;
			while(noOfOutput != 0){
				squaredSum += pow(expectedOutput.get(0, noOfOutput-1) - networkOutput.get(0, noOfOutput-1), 2);
				noOfOutput--;
			}
			return squaredSum/2;
		}
	}
	
	namespace loss_der{
		math::matrix<double> lossQuad(math::matrix<double> networkOutput, math::matrix<double> expectedOutput){
			cout<<"in lossQuad der function"<<endl;
			int noOfOutput = networkOutput.colno;
			math::matrix<double> derivative(noOfOutput, 1);
			for(int i = 0; i<noOfOutput; i++){
				derivative.set(networkOutput.get(0, i)-expectedOutput.get(0, i), 0, i);
			}
			return derivative;
		}
	}
}

#endif
