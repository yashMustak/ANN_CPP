#ifndef mustak_activations
#define mustak_activations

#include"..\preReq.hpp"
#include<cmath>
using namespace std;

namespace mustak{
	namespace act{
		double sigmoid(double input){
			return 1/(1+exp(-input));
		}
		
		double ReLU(double input){
			return max(0.0, input);
		}
		
		double tanh(double input){
			return (2/(1+exp(-2*input)))-1;
		}
	}
	
	//derivative part of all functions
	namespace act_der{
		double sigmoid(double input){
			double temp = act::sigmoid(input);
			return temp*(1-temp);
		}
		
		double ReLU(double input){
			try{
				if(input < 0) return 0;
				if(input > 0) return 1;
				else{
					exceptions::no_derivative_exists e;
					throw e;
				}
			}
			catch(exception& e){
				cout<<e.what();
			}
		}
		
		double tanh(double input){
			double temp = act::tanh(input);
			return 1-temp*temp;
		}
	}
}

#endif
