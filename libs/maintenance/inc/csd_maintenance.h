//
/// Copyright (c) 2018 Alibaba-inc.
/// 
/// All rights reserved.
/// @file    csd_maintenance.h
/// @brief
/// @author  chenyan
/// @version 1.0
/// @date    2018-11-27


#ifndef CSDMAINTENANCE_H
#define CSDMAINTENANCE_H

#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <string>
#include <algorithm>

// errno
#define ECSD_OK	0
#define ECSD_NO_SUPPORT -1
#define ECSD_INVALID -2
#define ECSD_NO_EXIST -3
#define ECSD_OPERATION -4
#define ECSD_FUNCION_FAILED	-5


// PorcessCommand cmd
#define SET_METADATA_CONFIG					1		//select specific metadata file

#define GET_DEVICE_LIST						2
#define GET_FPGA_DEVICE_INFO 		3
#define GET_FPGA_CU_INFO 		4

#define GET_FPGA_METADATA_VALUE				5
#define SET_FPGA_METADATA_VALUE				6



		
#define MAX_DEVICE_NUM 16
struct BoardInfo {
	int dev_id;
	int slot_bus;
	int slot_device;
	int slot_function;
	char device_name[512];
};

struct BoardInfos {
	int device_num;
	struct BoardInfo board_info[MAX_DEVICE_NUM];
};

#define ASSET_INFO_STRING_SIZE	128
struct AssetInfo {
	char manufacture[ASSET_INFO_STRING_SIZE];
	char sn[ASSET_INFO_STRING_SIZE];
	char hw_version[ASSET_INFO_STRING_SIZE];
	char fpga_version[ASSET_INFO_STRING_SIZE];
	char cpld_version_time[ASSET_INFO_STRING_SIZE];
	char cpld_version[ASSET_INFO_STRING_SIZE];
	char partnumber[ASSET_INFO_STRING_SIZE];
};

	
#define DDR_NUM	4
struct DdrHealth{
	uint32_t ddr_exist;
	uint32_t ddr_init;
	uint32_t ddr_crc[DDR_NUM];
};

struct PcieSpeed {
	char *speed;
	char *lane;
};


/*
struct CuInfo {
	//common
	uint32_t req_ack;	
	// ...
	
	//extend
	//std::vector<struct MetaData> vt_md;
	int mds_len;
	struct MetaData mds[0];
};
*/

#define PARTNUM_LEN 18
struct MonitorInfo {
	char partnum[PARTNUM_LEN + 1];	
	bool pcie_health; 
	bool pll_health;
	float temperature;
	int power_dissipation;	
	struct DdrHealth ddr_health;
	struct PcieSpeed pcie_speed;

	//cu info
	//std::vector<struct CuInfo> vt_cu;
	int cu_len;
	//struct CuInfo cus[0];
};
















enum MetaDataTypeE{
	CSD_META_DATA_TYPE_DISCRETE = 0x00,
	CSD_META_DATA_TYPE_THRESHOLD = 0x01,
	CSD_META_DATA_TYPE_STRING = 0X02,
	CSD_META_DATA_TYPE_BUFFER = 0X03,
	CSD_META_DATA_TYPE_MAX = 0X04
};

struct MetaDataValueDiscreteT {
	uint32_t value;
};

struct MetaDataThresholdsT {
	uint32_t low_critical;      /* Lower Critical Threshold */
	uint32_t low_major;         /* Lower Major Threshold */
	uint32_t low_minor;         /* Lower Minor Threshold */
	uint32_t up_critical;       /* Upper critical Threshold */
	uint32_t up_major;          /* Upper major Threshold */
	uint32_t up_minor;          /* Upper minor Threshold */
	uint32_t pos_thd_hysteresis; /* Positive Threshold Hysteresis */
	uint32_t neg_thd_hysteresis; /* Negative Threshold Hysteresis */
};

struct MetaDataValueThresholdT {
	uint32_t value;
	struct MetaDataThresholdsT thresholds;
};


#define META_DATA_VALUE_STRING_MAX_LEN	32
struct MetaDataValueStringT {
	char string[META_DATA_VALUE_STRING_MAX_LEN];
};


#define META_DATA_VALUE_BUFFER_MAX_LEN	32
struct MetaDataValueBufferT {
	uint32_t data_len;
	char data[META_DATA_VALUE_BUFFER_MAX_LEN];
};

union MetaDataValueU{
	uint32_t defult;
	struct MetaDataValueDiscreteT discrete;
	struct MetaDataValueThresholdT threshold;
	struct MetaDataValueStringT string;
	struct MetaDataValueBufferT buffer;
};

//#define MATEDATA_NAME_MAX_LEN	16
struct MetaDataT {
	//char name[MATEDATA_NAME_MAX_LEN];
	const char *name;
	enum MetaDataTypeE type;
	union MetaDataValueU value;
};

//
struct MetaDataControlT {
	int dev_id;
	int cu_id;
#define INVALID_ADDR -1
	int32_t addr;	//if addr is INVALID_ADDR, the MetaData is the software value
	int32_t mask;
	struct MetaDataT md;
};


// get cu info 
struct FpgaCuInfoT {
	int dev_id;
	int cu_id;
	char name[16];
		
	int mds_num;		
	struct MetaDataT mds[0];
};


// get device info 
struct FpgaDeviceInfoT {
	int dev_id;
	char name[16];
		
	int mds_num;		
	struct MetaDataT mds[0];
};


struct FpgaCuBaseInfoT {
	int cu_id;	
	int mds_num;

	//init 
	//FpgaCuBaseInfoT(){cu_id = 0; mds_num = 0;}
};

struct FpgaDeviceBaseInfoT {
	int dev_id;
	int cu_num;
	struct FpgaCuBaseInfoT cu_info[16];
};

struct FpgaDeviceListT {
	int dev_num;		
	struct FpgaDeviceBaseInfoT dev_info[8];
};

union DeviceListU{
	struct FpgaDeviceListT fdl;
};

enum DeviceTypeE{
	CSD_DEVICE_TYPE_FPGA = 0x00,
	CSD_DEVICE_TYPE_MAX = 0x01
};

struct DeviceListT {
	enum DeviceTypeE dev_type;
	union DeviceListU dl;
};



namespace csd {
	class CsdMaintenance {
	public:

		virtual ~CsdMaintenance(){}

		virtual int PorcessCommand(int cmd, void* arg) = 0;
	};

  	extern "C" CsdMaintenance *GetMaintenanceObject();
}

extern "C" int CsdPorcessCommand(int cmd, void* arg);

#endif

