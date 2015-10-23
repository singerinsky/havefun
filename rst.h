#ifndef _RST_LL_H_
#define _RST_LL_H_
#include <ctype.h>
#include <stdint.h>

template<class T,class BaseClass>
class RstClass:public BaseClass
{
public:
	RstClass()
	{
	 	_uid = _guid++;
	}
	virtual void Init(T& t) = 0;
	static T*   Create()
	{
		return new T;	
	}

	virtual void Release() = 0;

	virtual const char* GetClassName() = 0;

	int64_t GetID(){return _uid;}

private:
	static	int64_t	_guid;
	int64_t _uid;
};

template<class T,class BaseClass>
int64_t RstClass<T,BaseClass>::_guid = 0;


#endif
