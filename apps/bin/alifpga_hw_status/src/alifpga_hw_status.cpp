#include <gflags/gflags.h>
#include<iostream>
#include "define.h"
#include "csd_maintenance.h"

#define NONE                 "\e[0m"
#define RED                  "\e[0;31m"
#define GREEN                "\e[0;32m"
#define YELLOW               "\e[0;33m"


using namespace std;
using namespace csd;

#define VERSION "1.2.1"

void PrintBoardHealthInfo(struct MonitorInfo &monitor_info) {
	if (monitor_info.pcie_speed.speed) {
		if (strcmp(monitor_info.pcie_speed.speed, "8GT/s") == 0 && monitor_info.pcie_speed.lane && strcmp(monitor_info.pcie_speed.lane, "x16") == 0) {
        	fprintf(stdout, "\tDevice Speed:\t" GREEN "OK (%s %s)\n" NONE, monitor_info.pcie_speed.speed, monitor_info.pcie_speed.lane);
        } else {
            fprintf(stdout, "\tDevice Speed:\t" RED "Failed (%s %s)\n" NONE, monitor_info.pcie_speed.speed, monitor_info.pcie_speed.lane);
        } 
	} else {
		fprintf(stdout, "\tDevice Speed:\t" YELLOW "NO\n" NONE);
	}

	if (strlen(monitor_info.partnum) == 0) {
        fprintf(stdout, "\tDevice Partnum:" YELLOW "\tNO\n" NONE);
    } else {
        fprintf(stdout, "\tDevice Partnum:" GREEN "\t%s\n" NONE, monitor_info.partnum);
    }

	fprintf(stdout, "\tPCIE Channel Status:\n");
	fprintf(stdout, "\t\tRegister:\t");
	if (monitor_info.pcie_health != 0) {
        fprintf(stdout, RED "Failed\n" NONE);
    } else {
		fprintf(stdout, GREEN "OK\n" NONE);
	}

	for (int i = 0; i < DDR_NUM; ++i) {
        fprintf(stdout, "\tDDR%d Channel Status:\n", i);
        fprintf(stdout, "\t\t\tEnable:\t");

        if (monitor_info.ddr_health.ddr_exist & (0x01 << (i + 2))) {
            fprintf(stdout, GREEN "YES\n" NONE);
            fprintf(stdout, "\t\t\tInit:\t");

            if (monitor_info.ddr_health.ddr_init & (0x01 << i)) {
                fprintf(stdout, GREEN "OK\n" NONE);
            } else {
                fprintf(stdout, RED "Failed\n" NONE);
            }

            fprintf(stdout, "\t\t\tECC:\t");
			
            if ((monitor_info.ddr_health.ddr_crc[i] & 0x00ff) == 0x0) {
                fprintf(stdout, GREEN "Multi Bits OK\n" NONE);
            } else if ((monitor_info.ddr_health.ddr_crc[i] & 0x00ff) == 0xff) {
                fprintf(stdout, YELLOW "Multi Bits N/A\n" NONE);
            } else if ((monitor_info.ddr_health.ddr_crc[i] & 0x00ff) > 0){
                fprintf(stdout, RED "Multi Bits Failed(%d)\n" NONE, monitor_info.ddr_health.ddr_crc[i] & 0x00ff);
            } 
            if (((monitor_info.ddr_health.ddr_crc[i] >> 16) & 0x00ff) == 0x00) {
                fprintf(stdout, GREEN "\t\t\t\tSingle Bit OK\n" NONE);
            } else if (((monitor_info.ddr_health.ddr_crc[i] >> 16) & 0x00ff) == 0xff) {
                fprintf(stdout, YELLOW "\t\t\t\tSingle Bits N/A\n" NONE);
            } else if (((monitor_info.ddr_health.ddr_crc[i] >> 16) & 0x00ff) > 0) {
                fprintf(stdout, RED "\t\t\t\tSingle Bit Failed(%d)\n" NONE, (monitor_info.ddr_health.ddr_crc[i] >> 16) & 0x00ff);
            }
        } else {
            fprintf(stdout, YELLOW "NO\n" NONE);
        }
    }

	fprintf(stdout, "\tBoard PLL Status:\t");
	if (false == monitor_info.pll_health) {
        fprintf(stdout, RED "Failed\n" NONE);
    } else {
        fprintf(stdout, GREEN "OK\n" NONE);
    }

	fprintf(stdout, "\tBoard Temp Status:\t");
	if (monitor_info.temperature >= 100.0) {
        fprintf(stdout, RED "Failed (%.02f)\n" NONE, monitor_info.temperature);
    } else {
        fprintf(stdout, GREEN "OK (%.02f)\n" NONE, monitor_info.temperature);
    }


/*
	int count = monitor_info.vt_md.size();
	for (int i = 0; i < count; i++) {
		struct MetaData &md = monitor_info.vt_md[i];
		std::cout << md.name << " = " << md.value << std::endl;
	}
	*/
}

int main(int argc,char* argv[]) {
	
	gflags::SetVersionString(VERSION);//设置版本
	string usage_str = "Usage:";
	usage_str+=argv[0];
	gflags::SetUsageMessage(usage_str);
	gflags::ParseCommandLineFlags(&argc, &argv, true);
		
    fprintf(stdout, "\nAliFPGA Detection Tool Info\n\tVersion:\t%s\n", VERSION);

	struct BoardInfos *board_infos = (BoardInfos *)malloc(sizeof(BoardInfos));
    if (board_infos == NULL) {
        FATAL;
		return 0;
    }

	CsdMaintenance *cm = csd::GetMaintenanceObject();
	
	int ret = cm->PorcessCommand(CHECK_BOARD_NUM, NULL, (void *)board_infos);
    if (ret < 0 || board_infos->device_num == 0) {
        fprintf(stdout, RED "\nCheck_board_num: Failed (FPGA device list is empty)\n" NONE);
        return 0;
    }

	ret = cm->PorcessCommand(CHECK_DRIVER_EXIST, NULL, NULL);
    if (ret < 0) {
        fprintf(stdout, "\nCheck_driver_exist: Failed (please check fpga driver)\n");
        return 1;
    }

	ret = cm->PorcessCommand(CHECK_DEVICE_ID, NULL, (void *)board_infos);
    if (ret < 0) {
        fprintf(stdout, "\nCheck_dev_id: Failed (please check fpga driver)\n");
        return 1;
    }

	fprintf(stdout, "\nFPGA Device List:\n");
	
	for (int i = 0; i < board_infos->device_num; ++i) {
		struct BoardInfo *board_info = &(board_infos->board_info[i]);
        int board_id = board_info->dev_id;
	
        fprintf(stdout, "\n\tFPGA device id:" GREEN "\t%d" NONE, board_id);
        fprintf(stdout, "\n\tPCIE bus:" GREEN "\t%02x:%02x.%01x" NONE,
                board_info->slot_bus, board_info->slot_device, board_info->slot_function);
        fprintf(stdout, "\n\tDevice Name:" GREEN "\t%s\n" NONE, board_info->device_name);
	
        if (strcmp(board_info->device_name, "AliFPGA-X15(1ded:1000)") == 0 ||
            strcmp(board_info->device_name, "AliFPGA-X13(1ded:1010)") == 0 ||
            strcmp(board_info->device_name, "AliFPGA-X13(1ded:1020)") == 0) {

			struct MonitorInfo monitor_info;
		/*

			struct MetaData md1;
			md1.name = "md1";
			monitor_info.vt_md.push_back(md1);

			struct MetaData md2;
			md2.name = "md2";
			monitor_info.vt_md.push_back(md2);
		*/
            (void)cm->PorcessCommand(GET_MONITOR_INFO, (void *)board_info, (void *)&monitor_info);			
			PrintBoardHealthInfo(monitor_info);
        }
    }

	return 0;
}



