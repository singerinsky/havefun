#include "rst.h"

class BaseObject
{
	public:
	
};

class Car:public RstClass<Car,BaseObject>
{
	public:
		void Init(Car& car){}
		void Release(){
			printf("Release Object %lld",GetID());
		}
		
		const char* GetClassName(){return "Card";}

};
