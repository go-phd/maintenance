
#ifndef IB_DATA_BASE_H
#define IB_DATA_BASE_H

#include "csd_maintenance.h"
#include "define.h"


namespace csd {

	class IbDataBase {
	public:

		virtual ~IbDataBase(){}
		
		virtual int get_board_lock(int dev_id) {
			dev_id = dev_id;
			//printf("%s, %s(), %d not support\n", __FILE__, __func__, __LINE__);
			return ECSD_NO_SUPPORT;
		}

		virtual int set_board_lock(int dev_id) {
			dev_id = dev_id;
			//printf("%s, %s(), %d not support\n", __FILE__, __func__, __LINE__);
			return ECSD_NO_SUPPORT;
		}

		virtual int check_board_healthy(int dev_id, struct MonitorInfo *monitor_info) {
			dev_id = dev_id;
			monitor_info = monitor_info;
			//printf("%s, %s(), %d not support\n", __FILE__, __func__, __LINE__);
			return ECSD_NO_SUPPORT;
		}

		virtual int Get(struct MetaDataControlT &mdc){
			CSD_SET_USED(mdc);
			return ECSD_NO_SUPPORT;
		}
		
		virtual int Set(struct MetaDataControlT &mdc){
			CSD_SET_USED(mdc);
			return ECSD_NO_SUPPORT;
		}


	};

	extern "C" IbDataBase* GetIbDataObject();

}

#endif

