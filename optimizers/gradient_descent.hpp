#ifndef mustak_optimizers_gradient_descent
#define mustak_optimizers_gradient_descent

#include"../preReq.hpp"
#include"../layers/neuralLayer.hpp"
#include"../math/matrixMul.hpp"
#include"../math/transpose.hpp"

#include<cstdlib>

namespace mustak{
    namespace optimizers{
        bool gradient_descent(vector<layers::layer*> &network, 
                            vector<math::matrix<double> > &error,
                            vector<math::matrix<double> > &weights,
                            double threshold,
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

            cout<<weight_gradient_vector[1].rowno<<"\t"<<weight_gradient_vector[1].colno<<endl; //test
            cout<<weights[weights.size()-2].rowno<<"\t"<<weights[weights.size()-2].colno<<endl; //test

            int weight_size = weight_gradient_vector.size();

            //test segment
            // vector<math::matrix<double> >::iterator it;
            // for(it = weights.begin(); it!=weights.end(); ++it){
            //     it->print();
            // }
            //end segment

            bool end_point = true;
            double pre_weight;

            layerIterator = weight_gradient_vector.size()-1;
            for(layerIterator; layerIterator >= 0; --layerIterator){
                for(int i = 0; i<weight_gradient_vector[weight_size - layerIterator - 1].rowno; i++){
                    for(int j = 0; j<weight_gradient_vector[weight_size - layerIterator - 1].colno; j++){
                        pre_weight = weights[layerIterator].get(i,j);
                        weights[layerIterator].set((weights[layerIterator].get(i,j) - learning_rate * weight_gradient_vector[weight_size - layerIterator - 1].get(i, j)), i, j);
                        if(abs(weights[layerIterator].get(i,j)-pre_weight) > threshold) end_point = false;
                    }
                    cout<<endl;
                }
            }
            cout<<"end gradient descent once"<<endl;

            return end_point;

            // for(it = weights.begin(); it!=weights.end(); ++it){
            //     it->print();
            // }

            // error checking

        }
    }
}
#endif