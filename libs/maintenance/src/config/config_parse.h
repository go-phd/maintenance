
#ifndef CINFIG_PARSE_H
#define CINFIG_PARSE_H


#include <stdint.h>
#include <string>
#include <algorithm>


namespace csd {

	class ConfigParse {
	public:
		ConfigParse(void);
		~ConfigParse(void);
		//static ConfigParse* getInstance();
		int LoadFromFile();

	private:
		//static ConfigParse *instance;

	};

}

#endif


