#ifndef mustak_math_matrixCrop
#define mustak_math_matrixCrop

#include"../preReq.hpp"
using namespace std;
namespace mustak{
	namespace math{
		matrix<double> cropMatrix(matrix<double> mat, int fromcol, int tocol, int fromrow, int torow){
			try{
				if(fromcol <= tocol && fromrow <= torow && fromcol >= 0 && fromrow >= 0 && tocol <= mat.colno && torow <= mat.rowno){
					matrix<double> croped(tocol-fromcol, torow-fromrow);
					for(int i=fromrow; i<torow; i++){
						for(int j=fromcol; j<=tocol; j++){
							croped.set(mat.get(i, j), i-fromrow, j-fromcol);
						}
					}
					return croped;	
				}
				else{
					exceptions::limit_out_of_range e;
					throw e;
				}
			}
			catch(exception& e){
				cout<<e.what()<<endl;
			}
		}
	}
}

#endif
