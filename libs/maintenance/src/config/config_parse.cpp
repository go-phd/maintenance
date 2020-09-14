#include "config_parse.h"
#include "csd_maintenance.h"


namespace csd {
	ConfigParse::ConfigParse(){
	}
	 
	ConfigParse::~ConfigParse(){
	}

	int ConfigParse::LoadFromFile() {
		return ECSD_OK;
	}

	/*ConfigParse *ConfigParse::instance = new ConfigParse();
	
	ConfigParse* ConfigParse::getInstance(){
		return instance;
	}*/
	
}


