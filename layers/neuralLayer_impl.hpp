mustak::layers::layer::layer(int neurons, double (&init_activation)(double)) : noOfNeurons(neurons){
	activation = &init_activation;
	layerVector.mat_init(noOfNeurons, 1);
	layerOutVector.mat_init(noOfNeurons, 1);
//	layerVector(noOfNeurons, 1);
//	layerOutVector(noOfNeurons, 1);
	layerVectorSet = false;
	layerOutVectorSet = false;
}

void mustak::layers::layer::setLayerOutput(){
	try{
		if(layerVectorSet){
			for(int i = 0; i<noOfNeurons; i++) layerOutVector.set(activation(layerVector.get(0, i)), 0, i);
			layerOutVectorSet = true;
		}
		else{
			exceptions::input_vector_for_layer_not_set e;
			throw e;
		}
	}
	catch(exception& e){
		cout<<e.what();
	}
}

void mustak::layers::layer::setLayerInput(math::matrix<double> &inputVector){
	layerVector = inputVector;
	layerVectorSet = true;
}

mustak::math::matrix<double> mustak::layers::layer::getLayerOutput() const{
	try{
		if(layerOutVectorSet) return layerOutVector;
		else{
			exceptions::layer_output_vector_not_set e;
			throw e;
		}
	}
	catch(exception& e){
		cout<<e.what();
	}
}
