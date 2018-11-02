#ifndef mustak_math_matrix
#define mustak_math_matrix

#include<iostream>
#include<vector>
#include"..\exceptions\exception.hpp"
#include"..\debug\debug.hpp"
using namespace std;

namespace mustak{
	namespace math{
		template<class T>
		class matrix{
			public:
				vector<vector<T> > matric;
				int rowno;
				int colno;
				bool is_init;
				matrix(int c, int r, T val = 0){
					rowno = r;
					colno = c;
					for(int i = 0; i<r; i++){
						vector<T> temp;
						for(int j = 0; j<c; j++){
							temp.push_back(val);
						}
						matric.push_back(temp);
					}
					is_init = true;
				}
				
				matrix(){
					is_init = false;
				}
				
				void mat_init(int c, int r, T val = 0){
					if(!is_init){
						rowno = r;
						colno = c;
						for(int i = 0; i<r; i++){
							vector<T> temp;
							for(int j = 0; j<c; j++){
								temp.push_back(val);
							}
							matric.push_back(temp);
						}
						is_init = true;
					}
				}
				
				void set(T val, int x, int y){
					try{
						if(is_init){
							matric[x][y] = val;
						}
						else{
							exceptions::matrix_not_initialized e;
							throw e;
						}
					}
					catch(exception& e){
						cout<<e.what();
					}
				}
				
				T get(int x, int y){
					try{
						if(is_init)
						return matric[x][y];
						else{
							exceptions::matrix_not_initialized e;
							throw e;
						}
					}
					catch(exception& e){
						cout<<e.what();
					}
				}
				
				void incSize(int cols, int rows, int val = 0){
					colno += cols;
					rowno += rows;
					if(cols > 0){
						for(int i = 0; i<rowno; i++){
							for(int j = 0; j<cols; j++) matric[i].push_back(val);
						}
					}
					if(rows > 0){
						for(int i = 0; i<rows; i++){
							vector<double> temp;
							for(int j = 0; j<colno; j++) temp.push_back(val);
							matric.push_back(temp);
						}
					}
				}
				
				void reset(){
					if(is_init){
						matric.clear();
						colno = 0;
						rowno = 0;
						is_init = false;
					}
				}
		};
	}
}

#endif
