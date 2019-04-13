#ifndef Neural_network_layer
#define Neural_network_layer

#include"../preReq.hpp"
#include<cstdlib>

//Including the optimizer functions
#include"../activation/activation.hpp"
using namespace std;

namespace mustak{
	namespace layers{
		
		/*
		* Layer class generates layer with perticular optimizer
		*/
		class layer{
			public:
				/*
				* layerVector is a vector containing the values as received by the layer
				* layerOutVector is a vector containing the values after applying optimizer to the layerVector
				*/
				math::matrix<double> layerVector;
				math::matrix<double> layerOutVector;
				
				bool layerVectorSet;
				bool layerOutVectorSet;
				
				/*
				* noOfNeurons tell the number of neurons in the perticular layer
				*/
				int noOfNeurons;
				
				/*
				* activation is a function pointer to the function which has been choosen as activation function by the user
				*/
				double (*activation)(double);
				
				/*
				*constructor with parameters
				* neurons: telling the number of neurons to set noOfNeurons
				* init_activation: this is a function reference to set activation function. default set to sigmoid
				*/
				layer(int neurons, double (&init_activation)(double) = act::sigmoid);
				
				/*
				* setLayerOutput method set the layerOutVector value after applying activation function
				*/
				void setLayerOutput();
				
				/*
				* setLayerOutput function initialize layerVector
				*/
				void setLayerInput(math::matrix<double> &inputVector);
				
				math::matrix<double> getLayerOutput() const;
		};
	}
}

#include"neuralLayer_impl.hpp"

#endif
