#ifndef mustak_debug
#define mustak_debug

#include<iostream>
#include <cstdarg>
using namespace std;

namespace mustak{
	namespace debug{
		class debuger{
			private:
				bool debugEnable;
			public:
				debuger(){
					debugEnable = true;
				}
				
				void enable(){
					if(debugEnable) debugEnable = true;
				}
				
				void disable(){
					if(debugEnable) debugEnable = false;
				}
				
				void setMsg(string msg){
					if(debugEnable == true){
						cout<<msg<<endl;
					}
				}
				
				void setVal(double data, ...){
					if(debugEnable == true){
						cout<<" "<<data;
						va_list list;
						va_start(list, data);
						while(1){
							double arg = va_arg(list, double);
							if(arg == -1)break;
							cout<<" "<<arg;
						}
						cout<<endl;
					}
				}
		};
	}
}

#endif
