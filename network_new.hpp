#ifndef mustak_neural_network
#define mustak_neural_network

#include"preReq.hpp"
#include"layers/neuralLayer.hpp"

#include"math/matrixMul.hpp"
#include"math/hadamardPro.hpp"
#include"math/transpose.hpp"
#include"math/cropMat.hpp"

#include"loss/lossQuad.hpp"
#include"activation/activation.hpp"
#include"optimizers/gradient_descent.hpp"
#include<cstdlib>
using namespace std;

namespace mustak{
	debug::debuger bug;
	class network{
		private:
			vector<layers::layer*> networkLayer;
			vector<math::matrix<double> > layerWeight;
			layers::layer* inputLayer;
			layers::layer* outputLayer;
			int max_iterations;
			double learning_rate;
			double (*activationDerivative)(double);
			double (*lossFunction)(math::matrix<double>, math::matrix<double>);
			math::matrix<double> (*lossFunctionDer)(math::matrix<double>, math::matrix<double>);
			void (*optimizer) (vector<layers::layer*>&, vector<math::matrix<double> >&, vector<math::matrix<double> >&, int, double);

		public://for testing purpose only these methods are public	
			math::matrix<double> feed(math::matrix<double>);
			// math::matrix<double> backPropagate(math::matrix<double> expectedOutput);
			void backPropagate(math::matrix<double> expectedOutput);
			
		public:
			network(double (&activationDer)(double) = act_der::sigmoid, 
					double (&lossFunc)(math::matrix<double>, math::matrix<double>) = loss::lossQuad,
					math::matrix<double> (&lossFuncDer)(math::matrix<double>, math::matrix<double>) = loss_der::lossQuad,
					void (&optimizerFunc) (vector<layers::layer*>&, vector<math::matrix<double> >&, vector<math::matrix<double> >&, int, double) = optimizers::gradient_descent,
					int max_iter = 1000,
					double lRate = 0.001);

			void addLayer(layers::layer &layerObj);
	};
}

////////////////////////////////////////////////////////////////////////////////////////

mustak::network::network(double (&activationDer)(double),
						 double (&lossFunc)(math::matrix<double>, math::matrix<double>),
						 math::matrix<double> (&lossFuncDer)(math::matrix<double>, math::matrix<double>),
						 void (&optimizerFunc) (vector<layers::layer*>&, vector<math::matrix<double> >&, vector<math::matrix<double> >&, int, double),
						 int max_iter,
						 double lRate){
	inputLayer = NULL;
	outputLayer = NULL;
	activationDerivative = &activationDer;
	lossFunction = &lossFunc;
	lossFunctionDer = &lossFuncDer;
	optimizer = &optimizerFunc;
	max_iterations = max_iter;
	learning_rate = lRate;
}

void mustak::network::addLayer(layers::layer &layerObj){
	int preLayerNeurons = 0;
	int thisLayerNeurons = layerObj.noOfNeurons;
	if(networkLayer.empty()){
		networkLayer.push_back(&layerObj);
		inputLayer = networkLayer.back();
		outputLayer = networkLayer.back();
	}
	else{
		preLayerNeurons = outputLayer->noOfNeurons;
		networkLayer.push_back(&layerObj);
		outputLayer = networkLayer.back();
		math::matrix<double> weightMat(thisLayerNeurons, preLayerNeurons+1);
		cout<<thisLayerNeurons<<"\t"<<preLayerNeurons<<endl; //test
		for(int i=0; i<preLayerNeurons+1; i++){
			for(int j = 0; j<thisLayerNeurons; j++){
				cout<<"."; //test 
				weightMat.set((double) rand()/(RAND_MAX/2)-1, i, j);
			}
		}
		layerWeight.push_back(weightMat);
		
		// This code segment is only for testing purpose
		bug.setMsg("well this is weight matrix");
		for(int i=0; i<preLayerNeurons+1; i++){
			for(int j = 0; j<thisLayerNeurons; j++){
				cout<<weightMat.get(i, j);
			}
			cout<<endl;
		}
		cout<<endl;
		// till here
	}
}


mustak::math::matrix<double> mustak::network::feed(math::matrix<double> input){
	try{
		if(input.colno == inputLayer->noOfNeurons){
			int noOfLayers = networkLayer.size();
			int layerIterator = 0;
			networkLayer[layerIterator]->setLayerInput(input);
			networkLayer[layerIterator]->setLayerOutput();
			input = networkLayer[layerIterator]->getLayerOutput();
			layerIterator++;
			math::matrix<double> layerInput;
			while(layerIterator != noOfLayers){
				input.incSize(1, 0, 1);
				layerInput = math::matrixMulti(input, layerWeight[layerIterator-1]);
				networkLayer[layerIterator]->setLayerInput(layerInput);
				networkLayer[layerIterator]->setLayerOutput();
				input = networkLayer[layerIterator]->getLayerOutput();
				layerIterator++;
			}
			return input;
		}
		else{
			exceptions::input_vector_size_not_match e;
			throw e;
		}
	}
	catch(exception& e){
		cout<<e.what();
	}	
}

// mustak::math::matrix<double> mustak::network::backPropagate(math::matrix<double> expectedOutput){
void mustak::network::backPropagate(math::matrix<double> expectedOutput){
	vector<math::matrix<double> > errors;
	math::matrix<double> layerError;
//	layerNode *layerPointer = outputLayer;
	int layerIterator = networkLayer.size()-1;
	math::matrix<double> activationDer(networkLayer[layerIterator]->noOfNeurons, 1);
	cout<<"in backpropagation"<<endl; //test

	for(int i=0; i<networkLayer[layerIterator]->noOfNeurons; i++){
		cout<<"in actDer loop"<<endl; // test
		activationDer.set(activationDerivative(networkLayer[layerIterator]->layerVector.get(0, i)), 0, i);
	}
	
	layerError = math::hadamard(lossFunctionDer(networkLayer[layerIterator]->layerOutVector, expectedOutput), activationDer);
	cout<<"done hadamard"<<endl; //test
	errors.push_back(layerError);

	// Test segment
	cout<<"output layer error: ";
	for(int i=0; i<layerError.colno; i++){
		cout<<layerError.get(0, i);
	}
	cout<<endl;
	//end segment

	while(--layerIterator){
		cout<<"in while"<<endl; //test
		activationDer.reset();
		activationDer.mat_init(networkLayer[layerIterator]->noOfNeurons, 1);
		for(int i=0; i<networkLayer[layerIterator]->noOfNeurons; i++){
			cout<<"in actDer"<<endl; //test
			activationDer.set(activationDerivative(networkLayer[layerIterator]->layerVector.get(0, i)), 0, i);
		}
		
		layerError = math::hadamard(
						math::matrixMulti(
							math::cropMatrix(
								layerWeight[layerIterator],
								0, layerWeight[layerIterator].colno, 0, layerWeight[layerIterator].rowno-1),
							math::transpose(errors.back())),
						math::transpose(activationDer));
		cout<<"completed layer error task"<<endl;
		layerError.is_init = true;
		errors.push_back(math::transpose(layerError));
	}
	
	cout<<"bye backprop"<<endl; // test segment
	//test
	for(int i = 0; i<errors.size(); i++){
		errors[i].print();
	}
	//end

	optimizer(networkLayer, errors, layerWeight, max_iterations, learning_rate);
}

#endif
