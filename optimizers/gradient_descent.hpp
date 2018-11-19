#ifndef mustak_optimizers_gradient_descent
#define mustak_optimizers_gradient_descent

#include"../preReq.hpp"
#include"../layers/neuralLayer.hpp"

namespace mustak{
    namespace optimizers{
        void gradient_descent(vector<layers::layer*> &network, 
                            vector<math::matrix<double> > &error,
                            vector<math::matrix<double> > &weights,
                            int max_iterations,
                            double learning_rate){
            vector<math::matrix<double>> weight_gradient_vector;
            int layerIterator = error.size();
            int error_vector_size = layerIterator;
            
            // //test segment
            cout<<"before while"<<endl;
            cout<<layerIterator<<endl;
            // //end segment

            while(--layerIterator){
                weight_gradient_vector.push_back(
                                        math::matrixMulti(
                                            math::transpose(
                                                network[layerIterator]->layerOutVector),
                                                error[error_vector_size - layerIterator - 1]));
            }
            weight_gradient_vector.push_back(
                                        math::matrixMulti(
                                            math::transpose(
                                                network[layerIterator]->layerOutVector),
                                                error[error_vector_size - layerIterator - 1]));
            cout<<"set weight gradients"<<endl;
            cout<<weight_gradient_vector.size()<<endl;
            // gradient descent loop

            cout<<weight_gradient_vector[1].rowno<<"\t"<<weight_gradient_vector[1].colno<<endl;
            cout<<weights[weights.size()-2].rowno<<"\t"<<weights[weights.size()-2].colno<<endl;

            // layerIterator = weight_gradient_vector.size()-1;
            // for(layerIterator; layerIterator >= 0; --layerIterator){

            //     for(int i = 0; i<multiPro2.rowno; i++){
            //         for(int j = 0; j<multiPro2.colno; j++){
            //             cout<<multiPro2.get(i, j);
            //         }
            //         cout<<endl;
            //     }
            // }
        }
    }
}
#endif