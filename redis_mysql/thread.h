#ifndef _THREAD_H_01_
#define _THREAD_H_01_

#include <thread>

namespace rstll
{
	class RstThread:public std::thread
	{
		private:
			void* _data;
	};


};


#endif
