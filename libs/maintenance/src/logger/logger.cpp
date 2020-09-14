#include "logger.h"


namespace csd {
	CsdLog::CsdLog(){
		/*
		//printf("%s, %d\n", __func__, __LINE__);
		log4cplus::initialize ();
	    //helpers::LogLog::getLogLog()->setInternalDebugging(true);	//屏蔽log4cplus的调试信息
		//printf("%s, %d\n", __func__, __LINE__);
	    SharedFileAppenderPtr _append(
	        new RollingFileAppender(LOG4CPLUS_TEXT("log/alifpga_hw_status.log"), 500*1024, 2,
	            true, true));
	    _append->setName(LOG4CPLUS_TEXT("csdlog"));
	    _append->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
	    _append->getloc();
	    
	    logger = Logger::getInstance(LOG4CPLUS_TEXT("csd"));
		//printf("%s, %d\n", __func__, __LINE__);
		logger.addAppender(SharedAppenderPtr(_append.get()));
		//printf("%s, %d\n", __func__, __LINE__);*/
	}
	 
	CsdLog::~CsdLog(){
		//log4cplus::Logger::shutdown();
	}

	void CsdLog::Log(const char *fmt) {
		fmt = fmt;
		//LOG4CPLUS_DEBUG_FMT(subTest, ap);
		/*
		NDCContextCreator _context(LOG4CPLUS_TEXT("alifpga_hw_status"));
		LOG4CPLUS_DEBUG_FMT(logger, fmt);
		*/
	}

	CsdLog *CsdLog::instance = new CsdLog();
	
	CsdLog* CsdLog::getInstance(){
		return instance;
	}
	
}


