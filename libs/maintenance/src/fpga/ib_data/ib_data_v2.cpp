#include <stdio.h>
#include "ib_data_v2.h"

namespace csd {

	IbDataV2::IbDataV2() {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
	}

	IbDataV2::~IbDataV2() {
		printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
	}

}

