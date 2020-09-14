#include <gflags/gflags.h>
#include<iostream>
#include<string>

#include "csd_maintenance.h"


using namespace std;
using namespace csd;

#define VERSION "1.0.0"

int main(int argc,char* argv[]) {
	
	gflags::SetVersionString(VERSION);//设置版本
	string usage_str = "Usage:";
	usage_str+=argv[0];
	gflags::SetUsageMessage(usage_str);
	gflags::ParseCommandLineFlags(&argc, &argv, true);
		
    fprintf(stdout, "\nAliFPGA Detection Tool Info\n\tVersion:\t%s\n", VERSION);

	struct BoardInfos *board_infos = (BoardInfos *)malloc(sizeof(BoardInfos));
    if (board_infos == NULL) {
		return 0;
    }

	CsdMaintenance *cm = csd::GetMaintenanceObject();

//	(void)cm->PorcessCommand(RELOAD_FPGA, NULL, NULL);

	struct AssetInfo AssetInfo;
	(void)cm->PorcessCommand(GET_ASSET_INFO, NULL, (void *)&AssetInfo);
	//std::cout << AssetInfo.cpld_version << AssetInfo.cpld_version_time << AssetInfo.fpga_version << AssetInfo.hw_version << AssetInfo.manufacture << AssetInfo.partnumber << AssetInfo.sn << std::endl;
	
	//(void)cm->PorcessCommand(RELOAD_FPGA, NULL, NULL);
	
	return 0;
}



