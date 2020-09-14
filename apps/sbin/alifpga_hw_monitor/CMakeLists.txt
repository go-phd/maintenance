cmake_minimum_required(VERSION 2.8)

PROJECT(alifpga_hw_monitor)

MESSAGE (STATUS "Start cmake " ${PROJECT_NAME} )

INCLUDE_DIRECTORIES(
inc
${CSD_MAINTENANCE_SOURCE}/libs/maintenance/inc
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wfatal-errors -Wextra -Wshadow -Wpointer-arith -Wformat-security -Werror -Wcast-qual -Waggregate-return -Winline -Wunreachable-code -Wcast-align -Wundef -Wredundant-decls")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wchar-subscripts -Wcomment -Wmissing-braces -Wparentheses -Wsequence-point -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-function -Wunused-label -Wunused-variable -Wmaybe-uninitialized -Wfloat-equal -Wreturn-type -Wsign-compare -Wconversion-null -Wsizeof-pointer-memaccess -Wreorder -Woverflow")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE -pipe -fstack-protector -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D_LARGE_FILE_SOURCE ")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O ")

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

LINK_DIRECTORIES(${CSD_MAINTENANCE_BINARY_DIR}/libs/maintenance)

ADD_EXECUTABLE( ${PROJECT_NAME} ${DIR_SRCS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} libcsd_maintenance.a gflags pthread) #liblog4cplus.a 

INSTALL(TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION bin)
