#ifndef mustak_exceptions
#define mustak_exceptions

#include<exception>
using namespace std;
namespace mustak{
	namespace exceptions{
		class matrix_order_not_match : public exception {
		    public:
		        const char * what() const throw(){
		            return "matrix order do not match";
		        }
		};
		
		class input_vector_size_not_match : public exception{
			public:
				const char* what() const throw(){
					return "input feed to the network do not match the input layer size";
				}
		};
		
		class input_vector_for_layer_not_set : public exception{
			public:
				const char* what() const throw(){
					return "input vector for layer is not set ... use setLayerInput before setLayerOutput";
				}
		};
		
		class layer_output_vector_not_set : public exception{
			public:
				const char* what() const throw(){
					return "layer output vector not set ... use setLayerOutput before getLayerOutput";
				}
		};
		
		class no_derivative_exists : public exception{
			public:
				const char* what() const throw(){
					return "The network try to find derivative of ReLU at 0... which is not defined";
				}
		};
		
		class limit_out_of_range : public exception{
			public:
				const char* what() const throw(){
					return "Crop dimensions are not in the dimensions of matrix";
				}
		};
		
		class matrix_not_initialized : public exception{
			public:
				const char* what() const throw(){
					return "matrix is not initialized";
				}
		};
	}
}

#endif
