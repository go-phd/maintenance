
#ifndef FPGAMAINTENANCE_H
#define FPGAMAINTENANCE_H

#include "csd_maintenance.h"
#include "ib_data/ib_data_base.h"
#include "oob_data/oob_data.h"
#include "../config/config_parse.h"



namespace csd {

	union FpgaConfigureU {
		struct MetaDataControlT control;
	};
	
	struct FpgaConfigureT {
		int cmd; 
		union FpgaConfigureU Config;
	};

	/// @brief
	class FpgaMaintenance : public CsdMaintenance {
	public:
		FpgaMaintenance();
		~FpgaMaintenance();

		static FpgaMaintenance* Instance();

		int PorcessCommand(int cmd, void* arg);

	private:
		static FpgaMaintenance* instance_;
		IbDataBase* pid_;
		OobData* pood_;
		ConfigParse *config_parse_;

/*
		int CheckBoardNum(struct BoardInfos* board_infos);
		int check_driver_exist();
		int check_dev_id(struct BoardInfos* board_infos);
		void check_pcie_speed(struct BoardInfo* board_info, struct PcieSpeed& pcie_speed);

		int GetAssetInfo(struct AssetInfo* asset_info);
		int GetMonitorInfo(struct BoardInfo *board_info, struct MonitorInfo* monitor_info);
			*/
			
		int SetMetaDataConfig(const char* file_name);
		int GetDeviceList(struct DeviceListT* device_list);
		int GetDeviceInfo(struct FpgaDeviceInfoT* dev_info);
		int GetCuInfo(struct FpgaCuInfoT* cu_info);

		int GetMetaDataValue(struct MetaDataControlT* metadata);
		int SetMetaDataValue(struct MetaDataControlT* metadata);
	};

}

#endif

