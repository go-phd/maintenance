#include <stdio.h>
#include "ib_data.h"
#include "ib_data_v2.h"


namespace csd {

	IbDataBase* GetIbDataObject() {
	
		//Only support v1
		return new IbData();
		
		//return new IbDataV2();
	}

}

