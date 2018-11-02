#ifndef mustak_neural_network
#define mustak_neural_network

#include"preReq.hpp"
#include"layers\neuralLayer.hpp"

#include"math\matrixMul.hpp"
#include"math\hadamardPro.hpp"
#include"math\transpose.hpp"
#include"math\cropMat.hpp"

#include"loss\lossQuad.hpp"
#include"activation\activation.hpp"
#include<cstdlib>
using namespace std;

namespace mustak{
	debug::debuger bug;
	class network{
		private:
			struct layerNode{
				layers::layer* neuralLayer;
				layerNode* nextLayer;
				layerNode* preLayer;
				math::matrix<double> weightMat;
			};
			layerNode* inputLayer;
			layerNode* outputLayer;
			double (*activationDerivative)(double);
			double (*lossFunction)(math::matrix<double>, math::matrix<double>);
			math::matrix<double> (*lossFunctionDer)(math::matrix<double>, math::matrix<double>);
		
		public://for testing purpose only these methods are public	
			math::matrix<double> feed(math::matrix<double>);
			math::matrix<double> backPropagate(math::matrix<double> expectedOutput);
			
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
	layerNode* temp = new layerNode;
	temp->neuralLayer = &layerObj;
	temp->nextLayer = NULL;
	int preLayerNeurons = 0;
	int thisLayerNeurons = layerObj.noOfNeurons;
	if(inputLayer == NULL){
		temp->preLayer = NULL;
		inputLayer = temp;
		outputLayer = temp;
	}
	else{
		preLayerNeurons = outputLayer->neuralLayer->noOfNeurons;
		temp->preLayer = outputLayer;
		outputLayer->nextLayer = temp;
		outputLayer = temp;
		temp->weightMat.mat_init(thisLayerNeurons, preLayerNeurons+1);
		cout<<thisLayerNeurons<<"\t"<<preLayerNeurons; //test
		for(int i=0; i<preLayerNeurons+1; i++){
			for(int j = 0; j<thisLayerNeurons; j++){
				cout<<"."; //test 
				temp->weightMat.set((double) rand()/(RAND_MAX/2)-1, i, j);
			}
		}
		
		// This code segment is only for testing purpose
		/*
		bug.setMsg("well this is weight matrix");
		for(int i=0; i<preLayerNeurons+1; i++){
			for(int j = 0; j<thisLayerNeurons; j++){
				cout<<temp->weightMat.get(i, j);
			}
			cout<<endl;
		}
		cout<<endl;
		*/
		// till here
	}
}

mustak::math::matrix<double> mustak::network::feed(math::matrix<double> input){
	try{
		if(input.colno == inputLayer->neuralLayer->noOfNeurons){
			layerNode*  feeder = inputLayer;
			feeder->neuralLayer->setLayerInput(input);
			feeder->neuralLayer->setLayerOutput();
			input = feeder->neuralLayer->getLayerOutput();
			feeder = feeder->nextLayer;
			math::matrix<double> layerInput;
			while(feeder != NULL){
				input.incSize(1, 0, 1);
				layerInput = math::matrixMulti(input, feeder->weightMat);
				feeder->neuralLayer->setLayerInput(layerInput);
				feeder->neuralLayer->setLayerOutput();
				input = feeder->neuralLayer->getLayerOutput();
				feeder = feeder->nextLayer;
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

mustak::math::matrix<double> mustak::network::backPropagate(math::matrix<double> expectedOutput){
	vector<math::matrix<double> > errors;
	math::matrix<double> layerError;
	layerNode *layerPointer = outputLayer;
	math::matrix<double> activationDer(layerPointer->neuralLayer->noOfNeurons, 1);
	cout<<"in backpropagation"<<endl; //test
	for(int i=0; i<layerPointer->neuralLayer->noOfNeurons; i++){
		cout<<"in actDer loop"<<endl; // test
		activationDer.set(activationDerivative(layerPointer->neuralLayer->layerVector.get(0, i)), 0, i);
	}
	
	
	layerError = math::hadamard(lossFunctionDer(layerPointer->neuralLayer->layerOutVector, expectedOutput), activationDer);
	cout<<"done hadamard"<<endl; //test
	errors.push_back(layerError);
	// Test segment
	/*
	cout<<"output layer error: ";
	for(int i=0; i<layerError.colno; i++){
		cout<<layerError.get(0, i);
	}
	cout<<endl;
	*/
	//end segment
	while(layerPointer->preLayer != NULL){
		cout<<"in while"<<endl; //test
		layerPointer = layerPointer->preLayer;
		activationDer.reset();
		activationDer.mat_init(layerPointer->neuralLayer->noOfNeurons, 1);
		for(int i=0; i<layerPointer->neuralLayer->noOfNeurons; i++){
			cout<<"in actDer"<<endl;
			activationDer.set(activationDerivative(layerPointer->neuralLayer->layerVector.get(0, i)), 0, i);
		}
		
		// test segment
		/*
		cout<<endl<<"weightMat"<<endl;
		for(int i = 0; i<layerPointer->nextLayer->weightMat.rowno; i++){
			for(int j = 0; j<layerPointer->nextLayer->weightMat.colno; j++){
				cout<<layerPointer->nextLayer->weightMat.get(i, j);
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
		cout<<layerPointer->nextLayer->weightMat.colno<<"\t"<<layerPointer->nextLayer->weightMat.rowno-1<<endl; 
		math::matrix<double> multiPro1 = math::cropMatrix(
								layerPointer->nextLayer->weightMat,
								0, layerPointer->nextLayer->weightMat.colno, 0, layerPointer->nextLayer->weightMat.rowno-1);
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
								layerPointer->nextLayer->weightMat,
								0, layerPointer->nextLayer->weightMat.colno, 0, layerPointer->nextLayer->weightMat.rowno-1),
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
		*/
		// end segment
		
		
		layerError = math::hadamard(
						math::matrixMulti(
							math::cropMatrix(
								layerPointer->nextLayer->weightMat,
								0, layerPointer->nextLayer->weightMat.colno, 0, layerPointer->nextLayer->weightMat.rowno-1),
							math::transpose(errors.back())),
						math::transpose(activationDer));
		cout<<"completed layer error task"<<endl;
		errors.push_back(math::transpose(layerError));
	}
	cout<<"bye backprop"<<endl;
}

#endif
