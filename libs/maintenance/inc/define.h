
#ifndef DEFINE_H
#define DEFINE_H

#include <string.h>
#include <syslog.h>

/*
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>


using namespace log4cplus;
using namespace log4cplus::helpers;
*/


//#define enable_syslog

#define CSD_SET_USED(x) (void)(x)

enum {
    MAINTENANCE_LOG_INFO = 0,
    MAINTENANCE_LOG_WARNING = 1,
    MAINTENANCE_LOG_ERROR = 2,
};


//#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)
#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno)); } while(0)

#ifdef enable_syslog

#define MAINTENANCE_LOG_INIT() do { \
	openlog("csd-maintenance", LOG_CONS | LOG_PID, LOG_USER); 	\
}while(0)

#define MAINTENANCE_LOG(level, fmt, args...) do {\
    if (level >= MAINTENANCE_LOG_ERROR) { \
        syslog(LOG_ERR, "<error> " fmt, ##args);\
    } else if(level >= MAINTENANCE_LOG_WARNING){ \
		syslog(LOG_WARNING, "<warning> " fmt, ##args);\
	} else { \
		syslog(LOG_INFO, "<info> " fmt, ##args);\
	}\
}while(0)

#else

#define MAINTENANCE_LOG_INIT() do { \
}while(0)

#define MAINTENANCE_LOG(level, fmt, args...) do {\
    if (level >= MAINTENANCE_LOG_ERROR) { \
        fprintf(stdout, "<error> " fmt "\n", ##args);\
    } else if(level >= MAINTENANCE_LOG_WARNING){ \
		fprintf(stdout, "<warning> " fmt "\n", ##args);\
	} else { \
		fprintf(stdout, "<info> " fmt "\n", ##args);\
	}\
}while(0)



#endif


#endif

