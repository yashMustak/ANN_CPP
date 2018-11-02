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
	class network{
		private:
			struct layerNode{
				layers::layer* neuralLayer;
				layerNode* nextLayer;
				layerNode* preLayer;
				matrix weightMat;
			};
			layerNode* inputLayer;
			layerNode* outputLayer;
			double (*activationDerivative)(double);
			double (*lossFunction)(matrix, matrix);
			matrix (*lossFunctionDer)(matrix, matrix);
		
		public://for testing purpose only these methods are public	
			matrix feed(matrix);
			matrix backPropagate(matrix expectedOutput);
			
		public:
			network(double (&activationDer)(double) = act_der::sigmoid, 
					double (&lossFunc)(matrix, matrix) = loss::lossQuad,
					matrix (&lossFunctionDer)(matrix, matrix) = loss_der::lossQuad);

			void addLayer(layers::layer &layerObj);
	};
}

mustak::network::network(double (&activationDer)(double),
						 double (&lossFunc)(matrix, matrix),
						 matrix (&lossFuncDer)(matrix, matrix)){
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
	int thisLayerNeurons = temp->neuralLayer->noOfNeurons;
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
		for(int i=0; i<preLayerNeurons+1; i++){
			vector<double> tempo;
			for(int j = 0; j<thisLayerNeurons; j++){
				tempo.push_back((double) rand()/(RAND_MAX/2)-1);
			}
			temp->weightMat.push_back(tempo);
		}
		
		// This code segment is only for testing purpose
		for(int i=0; i<preLayerNeurons+1; i++){
			for(int j = 0; j<thisLayerNeurons; j++){
				cout<<temp->weightMat[i][j];
			}
			cout<<endl;
		}
		cout<<endl;
		// till here
	}
}

matrix mustak::network::feed(matrix input){
	try{
		if(input[0].size() == inputLayer->neuralLayer->noOfNeurons){
			layerNode*  feeder = inputLayer;
			feeder->neuralLayer->setLayerInput(input);
			feeder->neuralLayer->setLayerOutput();
			input = feeder->neuralLayer->getLayerOutput();
			feeder = feeder->nextLayer;
			matrix layerInput;
			while(feeder != NULL){
				input[0].push_back(1);
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

matrix mustak::network::backPropagate(matrix expectedOutput){
	vector<matrix> errors;
	matrix layerError;
	layerNode *layerPointer = outputLayer;
	matrix activationDer;
	vector<double> tempActDer;
	cout<<"in backpropagation"<<endl;
	for(int i=0; i<layerPointer->neuralLayer->layerOutVector[0].size(); i++){
		tempActDer.push_back(activationDerivative(layerPointer->neuralLayer->layerVector[0][i]));
	}
	activationDer.push_back(tempActDer);
	layerError = math::hadamard(lossFunctionDer(layerPointer->neuralLayer->layerOutVector, expectedOutput), activationDer);
	errors.push_back(layerError);
	// Test segment
	cout<<"output layer error: ";
	for(int i=0; i<layerError[0].size(); i++){
		cout<<layerError[0][i];
	}
	cout<<endl;
	//end segment
	while(layerPointer->preLayer != NULL){
		cout<<"in while"<<endl;
		layerPointer = layerPointer->preLayer;
		activationDer.clear();
		tempActDer.clear();
		for(int i=0; i<layerPointer->neuralLayer->layerOutVector[0].size(); i++){
			tempActDer.push_back(activationDerivative(layerPointer->neuralLayer->layerVector[0][i]));
		}
		activationDer.push_back(tempActDer);
		// test segment
		cout<<endl<<"weightMat"<<endl;
		for(int i = 0; i<layerPointer->nextLayer->weightMat.size(); i++){
			for(int j = 0; j<layerPointer->nextLayer->weightMat[0].size(); j++){
				cout<<layerPointer->nextLayer->weightMat[i][j];
			}
			cout<<endl;
		}
		cout<<endl<<"errors.back()"<<endl;
		matrix test = errors.back();
		for(int i = 0; i<test.size(); i++){
			for(int j = 0; j<test[0].size(); j++){
				cout<<test[i][j];
			}
			cout<<endl;
		}
		
		cout<<endl<<"multiplication pro 1"<<endl;
		matrix multiPro1 = math::cropMatrix(
								layerPointer->nextLayer->weightMat,
								1, layerPointer->nextLayer->weightMat[0].size()-1, 1, layerPointer->nextLayer->weightMat.size()-2);
		for(int i = 0; i<multiPro1.size(); i++){
			for(int j = 0; j<multiPro1[0].size(); j++){
				cout<<multiPro1[i][j];
			}
			cout<<endl;
		}
		
		cout<<endl<<"multiplication pro 2"<<endl;
		matrix multiPro2 = math::transpose(errors.back());
		for(int i = 0; i<multiPro2.size(); i++){
			for(int j = 0; j<multiPro2[0].size(); j++){
				cout<<multiPro2[i][j];
			}
			cout<<endl;
		}
		
		cout<<endl<<"hadamard pro 1"<<endl;
		matrix hadaPro1 = math::matrixMulti(
							math::cropMatrix(
								layerPointer->nextLayer->weightMat,
								1, layerPointer->nextLayer->weightMat[0].size()-1, 1, layerPointer->nextLayer->weightMat.size()-2),
							math::transpose(errors.back()));
		for(int i = 0; i<hadaPro1.size(); i++){
			for(int j = 0; j<hadaPro1[0].size(); j++){
				cout<<hadaPro1[i][j];
			}
			cout<<endl;
		}
		
		cout<<endl<<"hadamard Pro 2"<<endl;
		for(int i = 0; i<activationDer.size(); i++){
			for(int j = 0; j<activationDer[0].size(); j++){
				cout<<activationDer[i][j];
			}
			cout<<endl;
		}
		// end segment
		
		layerError = math::hadamard(
						math::matrixMulti(
							math::cropMatrix(
								layerPointer->nextLayer->weightMat,
								1, layerPointer->nextLayer->weightMat[0].size()-1, 1, layerPointer->nextLayer->weightMat.size()-2),
							math::transpose(errors.back())),
						math::transpose(activationDer));
		errors.push_back(layerError);
	}
}

#endif
