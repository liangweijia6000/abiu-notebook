#ifndef _server_common_h_
#define _server_common_h_

#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <map>

#define SINGLETON_DECLARATION(class_name) \
	public:		static class_name& getInstance();	\
	private:	static class_name* _instance;

#define SINGLETON_DEFINITION(class_name)				\
	class_name* class_name::_instance = NULL;			\
	class_name& class_name::getInstance()				\
	{													\
	if (class_name::_instance == NULL)				\
		{												\
		class_name::_instance = new class_name();	\
		}												\
		return *class_name::_instance;					\
	}

#endif //_server_common_h_