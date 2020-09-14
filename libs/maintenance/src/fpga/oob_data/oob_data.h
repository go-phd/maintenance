
#ifndef OOB_DATA_H
#define OOB_DATA_H


#include <string>
#include "csd_maintenance.h"
#include "define.h"
#include "ipmi_intf.h"

namespace csd {

	struct HwVersion {
		uint8_t fpga_id;
		uint8_t sub_cmd;
		uint8_t reserve[2];
	};

	class OobData {
	public:
		OobData();
		~OobData();

		
		int GetInfo(struct OobInfo *oob_info);
		
		int GetTemperature(int &temperature);
		int GetPowerDissipation(int &power_dissipation);
		int GetCpldVersionTime(char *time);
		int GetCpldVersion(char *version);
		int GetManufacture(char *manufacture);
		int GetPartnumber(char *partnumber);
		int GetHwVersion(char *version);
		int GetFpgaVersion(char *version);
		int GetProductSn(char *sn);
				
		int ReloadFpga();

	private:	
		int Init();
		void Cleanup();

		
		IpmiIntf *ipmi_;
	};

}

#endif

