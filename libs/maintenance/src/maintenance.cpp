#include <stdio.h>
#include "csd_maintenance.h"
#include "define.h"
#include "fpga/fpga_maintenance.h"
#include "logger/logger.h"


namespace csd {

	CsdMaintenance *GetMaintenanceObject() {
		//MAINTENANCE_LOG_INIT();

		//printf("%s, %d\n", __func__, __LINE__);
/*
		CsdLog cl;
		const char *g = "erererr";
		cl.Log(g);
	*/	
		/*CsdLog* singleton1 = CsdLog::getInstance();
		printf("%s, %d\n", __func__, __LINE__);
		const char *g = "erererr";
		singleton1->Log(g);
		printf("%s, %d\n", __func__, __LINE__);
*/

		return csd::FpgaMaintenance::Instance();
	}

}


/// @brief CsdPorcessCommand
///
/// @param arg
/// @param cmd
/// @returns
int CsdPorcessCommand(int cmd, void* arg) {

	csd::CsdMaintenance* cm = csd::GetMaintenanceObject();

	//printf("%s, %d, cm = %p\n", __func__, __LINE__, cm);

	return cm->PorcessCommand(cmd, arg);
}


