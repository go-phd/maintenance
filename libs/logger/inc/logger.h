
#ifndef CSDLOG_H
#define CSDLOG_H

#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/loggingmacros.h>


#include <stdint.h>
#include <string>
#include <algorithm>

using namespace log4cplus;

namespace csd {

	class CsdLog {
	public:
		static CsdLog* getInstance();
		void Log(const char *fmt);

	private:
		CsdLog(void);
		~CsdLog(void);

		static CsdLog* instance;
		
		Logger logger;

	};

}

#endif

