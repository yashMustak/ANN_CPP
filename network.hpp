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
			double (*activationDerivative)(double);
			double (*lossFunction)(math::matrix<double>, math::matrix<double>);
			math::matrix<double> (*lossFunctionDer)(math::matrix<double>, math::matrix<double>);
		
		public://for testing purpose only these methods are public	
			math::matrix<double> feed(math::matrix<double>);
			// math::matrix<double> backPropagate(math::matrix<double> expectedOutput);
			void backPropagate(math::matrix<double> expectedOutput);
			
		public:
			network(double (&activationDer)(double) = act_der::sigmoid, 
					double (&lossFunc)(math::matrix<double>, math::matrix<double>) = loss::lossQuad,
					math::matrix<double> (&lossFunctionDer)(math::matrix<double>, math::matrix<double>) = loss_der::lossQuad);

			void addLayer(layers::layer &layerObj);
	};
}

mustak::network::network(double (&activationDer)(double),
						 double (&lossFunc)(math::matrix<double>, math::matrix<double>),
						 math::matrix<double> (&lossFuncDer)(math::matrix<double>, math::matrix<double>)){
	inputLayer = NULL;
	outputLayer = NULL;
	activationDerivative = &activationDer;
	lossFunction = &lossFunc;
	lossFunctionDer = &lossFuncDer;
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
			cout<<"in actDer"<<endl;
			activationDer.set(activationDerivative(networkLayer[layerIterator]->layerVector.get(0, i)), 0, i);
		}

		/*
		// test segment
		cout<<endl<<"weightMat"<<endl;
		for(int i = 0; i<layerWeight[layerIterator].rowno; i++){
			for(int j = 0; j<layerWeight[layerIterator].colno; j++){
				cout<<layerWeight[layerIterator].get(i, j);
			}
			cout<<endl;
		}
		cout<<endl<<"errors.back()"<<endl;
		math::matrix<double> test = errors.back();
		for(int i = 0; i<test.rowno; i++){
			for(int j = 0; j<test.colno; j++){
				cout<<test.get(i, j);
			}
			cout<<endl;
		}
		
		cout<<endl<<"multiplication pro 1"<<endl;
		cout<<layerWeight[layerIterator].colno<<"\t"<<layerWeight[layerIterator].rowno-1<<endl; 
		math::matrix<double> multiPro1 = math::cropMatrix(
								layerWeight[layerIterator],
								0, layerWeight[layerIterator].colno, 0, layerWeight[layerIterator].rowno-1);
		for(int i = 0; i<multiPro1.rowno; i++){
			for(int j = 0; j<multiPro1.colno; j++){
				cout<<multiPro1.get(i, j);
			}
			cout<<endl;
		}
		
		cout<<endl<<"multiplication pro 2"<<endl;
		math::matrix<double> multiPro2 = math::transpose(errors.back());
		for(int i = 0; i<multiPro2.rowno; i++){
			for(int j = 0; j<multiPro2.colno; j++){
				cout<<multiPro2.get(i, j);
			}
			cout<<endl;
		}
		
		cout<<endl<<"hadamard pro 1"<<endl;
		math::matrix<double> hadaPro1 = math::matrixMulti(
							math::cropMatrix(
								layerWeight[layerIterator],
								0, layerWeight[layerIterator].colno, 0, layerWeight[layerIterator].rowno-1),
							math::transpose(errors.back()));
		for(int i = 0; i<hadaPro1.rowno; i++){
			for(int j = 0; j<hadaPro1.colno; j++){
				cout<<hadaPro1.get(i, j);
			}
			cout<<endl;
		}
		
		cout<<endl<<"hadamard Pro 2"<<endl;
		math::matrix<double> h2 = math::transpose(activationDer);
		for(int i = 0; i<h2.rowno; i++){
			for(int j = 0; j<h2.colno; j++){
				cout<<h2.get(i, j);
			}
			cout<<endl;
		}
		// end segment
		*/
		
		
		layerError = math::hadamard(
						math::matrixMulti(
							math::cropMatrix(
								layerWeight[layerIterator],
								0, layerWeight[layerIterator].colno, 0, layerWeight[layerIterator].rowno-1),
							math::transpose(errors.back())),
						math::transpose(activationDer));
		cout<<"completed layer error task"<<endl;
		errors.push_back(math::transpose(layerError));
	}
	cout<<"bye backprop"<<endl; // test segment
	
	
	// rate of change of cost wrt weights
	vector<math::matrix<double>> weight_gradient_vector;
	layerIterator = networkLayer.size();
	
	cout<<"before while"<<endl;

	while(--layerIterator){
		// math::matrix<double> weightGrad;
		//test segment
		cout<<"inside while of weight"<<endl;
		networkLayer[layerIterator-1]->layerOutVector.print();
		cout<<endl<<"multi matrix 2"<<endl;
		cout<<layerIterator<<endl;
		//end segment

		weight_gradient_vector.push_back(
								math::matrixMulti(
									math::transpose(
										networkLayer[layerIterator-1]->layerOutVector),
										errors[layerIterator]));
	}
}

#endif
