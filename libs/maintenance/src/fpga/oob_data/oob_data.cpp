#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h> 
#include "oob_data.h"

namespace csd {
	OobData::OobData() {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);

		ipmi_ = new IpmiIntf();
	}

	OobData::~OobData() {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);

		delete ipmi_;
	}

	int OobData::GetTemperature(int &temperature) {
		temperature = 15;
/*
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);

		unsigned char buf[64] = {0};
		
		ipmi_->RequestData(6, 1, NULL, 0, buf, 64);

		printf("------------------------\n");
		for (int i = 0; i < 64; i++) {
			printf("0x%x ", buf[i]);
		}
		printf("------------------------\n");
		*/
		return ECSD_OK;
	}

	int OobData::GetPowerDissipation(int &power_dissipation) {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		power_dissipation = 100;
		
		return ECSD_OK;
	}

	int OobData::GetCpldVersionTime(char *time) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		time = time;//"cpld time 3";
		
		return ECSD_OK;
	}
	
	int OobData::GetCpldVersion(char *version) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		version = version;//"cpld version 1.1";
		
		return ECSD_OK;
	}

	int OobData::GetManufacture(char *manufacture) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		manufacture = manufacture;//"manufacture";
		
		return ECSD_OK;
	}

	int OobData::GetPartnumber(char *partnumber) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		partnumber = partnumber;//"partnumber";
		
		return ECSD_OK;
	}

	int OobData::GetHwVersion(char *version) {
		struct HwVersion hw_version;
		unsigned char buf[64] = {0};
		
		int ret = ipmi_->RequestData(0x3e, 0x52, (unsigned char *)&hw_version, sizeof(struct HwVersion), buf, 64);
		if (ret < 0) {
			printf("ret = %d\n", ret);

			return ECSD_FUNCION_FAILED;
		}
		
		//version = version;//"HW 1.2.0";
		CSD_SET_USED(version);
		
		return ECSD_OK;
	}

	int OobData::GetFpgaVersion(char *version) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		version = version;//"fpga 1.3";
		
		return ECSD_OK;
	}

	int OobData::GetProductSn(char *sn) {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		sn = sn;//"sn234677u";
		
		return ECSD_OK;
	}

	int OobData::ReloadFpga()     {
		MAINTENANCE_LOG(MAINTENANCE_LOG_INFO, "Start to reload FPGA, = %d.", 11);
		
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);		

		MAINTENANCE_LOG(MAINTENANCE_LOG_INFO, "Reload FPGA completed.");
		
		MAINTENANCE_LOG(MAINTENANCE_LOG_WARNING, "Start to reload FPGA, = %d.", 12);
		MAINTENANCE_LOG(MAINTENANCE_LOG_ERROR, "Start to reload FPGA, = %d.", 14);

		
		return ECSD_OK;
	}
}

