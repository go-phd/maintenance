#include <string>
#include <dirent.h>
#include <regex.h>

#include "fpga_maintenance.h"
#include "ib_data/ib_data_base.h"


namespace csd {
	FpgaMaintenance* FpgaMaintenance::instance_ = new FpgaMaintenance;

	FpgaMaintenance* FpgaMaintenance::Instance() {
		return instance_;
	}

	FpgaMaintenance::FpgaMaintenance() {
		pid_ = GetIbDataObject();
		pood_ = new OobData();
		config_parse_= new ConfigParse();
	}

	FpgaMaintenance::~FpgaMaintenance() {
		//don't to delete
		//delete pood_;
	}

#if 0
	int FpgaMaintenance::CheckBoardNum(struct BoardInfos *board_infos) {
	    FILE *fp, *board_id_fp = nullptr;
	    int i;
	    char buffer[512];
	    char cmd[512]; 

	    if (board_infos == NULL) {
	        return 0;
	    }

	    fp = popen("lspci | grep '1ded:1' | wc -l", "r");
	    fgets(buffer, sizeof(buffer), fp);
	    pclose(fp);
	    int device_num = atoi(buffer);

	    if (device_num > 0) {
	        //fprintf(stdout, "\nFPGA Device List:\n");

	        for (i = 0; i < device_num; ++i) {
	            sprintf(cmd, "lspci | grep '1ded:1' |awk NR==%d | awk -F [:.\\ ] '{print $1 $2 $3}'", i+1);
	            fp = popen(cmd, "r");
	            fgets(buffer, sizeof(buffer), fp);
	            int slot_bdf = strtol(buffer, NULL, 16);
	            board_infos->board_info[i].slot_bus = (slot_bdf >> 12) & 0xff;
	            board_infos->board_info[i].slot_device = (slot_bdf >> 4) & 0xff;
	            board_infos->board_info[i].slot_function = (slot_bdf >> 0) & 0xf;

	            sprintf(cmd, "lspci | grep 1ded | grep %x | awk '{print $5}'", board_infos->board_info[i].slot_bus);
	            board_id_fp = popen(cmd, "r");
	            fgets(buffer, sizeof(buffer), board_id_fp);
	            //            printf("%s",buffer);
	            pclose(board_id_fp);

	            if (strcmp(buffer, "1ded:1000\n") == 0) {
	                sprintf(board_infos->board_info[i].device_name, "AliFPGA-X15(1ded:1000)");
	            } else if (strcmp(buffer, "1ded:1010\n") == 0) {
	                sprintf(board_infos->board_info[i].device_name, "AliFPGA-X13(1ded:1010)");
	            } else if (strcmp(buffer, "1ded:1020\n") == 0) {
	                sprintf(board_infos->board_info[i].device_name, "AliFPGA-X16DP(1ded:1020)");
	            } else {
	                sprintf(board_infos->board_info[i].device_name, "AliFPGA-Unknown-Board");
	            }
	        }

	        pclose(fp);
	    }

		board_infos->device_num = device_num;

	    return ECSD_OK;
	}

	int FpgaMaintenance::check_driver_exist() {
		FILE *fp = NULL;
		char buffer[512];

		fp = popen("lsmod |grep -i nsa_dma | wc -l", "r");
		if (fp) {
			fgets(buffer, sizeof(buffer), fp);
			pclose(fp);
			if (atoi(buffer) > 0) {
				return ECSD_OK;
			} else {
				return ECSD_NO_EXIST;
			}
		} else {
			fprintf(stderr, "check_driver_exist: cmd error\n");
			return ECSD_NO_EXIST;
		}

		return ECSD_OK;
	}

	int FpgaMaintenance::check_dev_id(struct BoardInfos *board_infos) {
	    DIR *dir {};
	    struct dirent *ptr {};
	    dir = opendir("/proc/alifpga");
	    if (dir == NULL) {
	        fprintf(stdout, "Check_dev_id failed: Dev ID is null.\n");
	        return ECSD_NO_EXIST;
	    }
	    regex_t reg; 
	    regmatch_t match[2];
	    size_t match_num = 2;
	    //int perfer_pos = -1;
	    regcomp(&reg, "^dev([0-9])", REG_EXTENDED);
		int dev_num = board_infos->device_num;
	    int dev_ids[MAX_DEVICE_NUM] = {0};
	    int i;

	    int num_devices = 0;
	    while ((ptr = readdir(dir)) != NULL) {
	        if (num_devices >= dev_num) break;
	        if ((regexec(&reg, ptr->d_name, match_num, match, 0)) == 0) {
	            dev_ids[num_devices] = ptr->d_name[match[1].rm_so] - '0';
	            num_devices = num_devices + 1;
	        }
	    }
	    regfree(&reg);
	    closedir(dir);
#if 0
	    if (num_devices != dev_num) {
	        fprintf(stdout, "Check_dev_id failed: The num of Dev ID is beyond device_num.\n");
	        return -1;
	    }
#endif

	    if (num_devices == 1 && dev_num == 1) {
	        board_infos->board_info[0].dev_id = dev_ids[0];
	     } else if (num_devices == 1 && dev_num == 2) {
	        board_infos->board_info[0].dev_id = dev_ids[0];
	        board_infos->board_info[1].dev_id = dev_ids[0];
	    } else if (num_devices == 2 && dev_num == 2) {
	        for (i = 0; i < num_devices; ++i) {
	            if (board_infos->board_info[i].slot_bus < 0x80) {
	                board_infos->board_info[i].dev_id = 0;
	            } else {
	                board_infos->board_info[i].dev_id = 1;
	            }
	        }
	    }
	    return 0; 
	 
	}

	void FpgaMaintenance::check_pcie_speed(struct BoardInfo *board_info, struct PcieSpeed &pcie_speed) {
	    /*if (board_info == NULL) {
	        fprintf(stderr, "Error at check_pcie_speed, invalid params\n");
	        return;
	    }*/
	    FILE *fp;
	    char buffer[512];
	    char cmd[512]; 

	    buffer[0]='\0';
	    sprintf(cmd, "lspci -s %02x:%02x.%01x -vv | grep 'LnkSta:' | awk -F '[ ,]' '{print $2\" \"$5}'",
	            board_info->slot_bus, board_info->slot_device, board_info->slot_function);
	    fp = popen(cmd, "r");
	    fgets(buffer, sizeof(buffer), fp);
	    if (strlen(buffer) > 0) {
	        char *speed = NULL, *lane = NULL;
	        speed = strtok(buffer, " ");
		
	        if (speed != NULL) {
	            lane = strtok(NULL, "\n");
	        }
			
			/*
	        if (strcmp(speed, "8GT/s") == 0 && lane && strcmp(lane, "x16") == 0) {
            	fprintf(stdout, "\tDevice Speed:\t" GREEN "OK (%s %s)\n" NONE, speed, lane);
	        } else {
	            fprintf(stdout, "\tDevice Speed:\t" RED "Failed (%s %s)\n" NONE, speed, lane);
	        }
			*/
			
			pcie_speed.speed = speed;
			pcie_speed.lane = lane;
			
	    } else {
	        //fprintf(stdout, "\tDevice Speed:\t" YELLOW "NO\n" NONE);
			
			pcie_speed.speed = NULL;
			pcie_speed.lane = NULL;
	    }
		
	    pclose(fp);
	}

	int FpgaMaintenance::GetAssetInfo(struct AssetInfo *asset_info) {
		int ret = pood_->GetPartnumber(asset_info->partnumber);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetManufacture(asset_info->manufacture);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetProductSn(asset_info->sn);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetHwVersion(asset_info->hw_version);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetFpgaVersion(asset_info->fpga_version);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetCpldVersionTime(asset_info->cpld_version_time);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetCpldVersion(asset_info->cpld_version);
		if (ret < ECSD_OK) {
			/////log
		}

		ret = pood_->GetPartnumber(asset_info->partnumber);
		if (ret < ECSD_OK) {
			/////log
		}

		return ret;
	}

	int FpgaMaintenance::GetMonitorInfo(struct BoardInfo *board_info, struct MonitorInfo *monitor_info) {
		int ret = ECSD_OK;
		
		ret = pid_->get_board_lock(board_info->dev_id);
		if (ECSD_OK == ret) {
			ret = pid_->check_board_healthy(board_info->dev_id, monitor_info);
			if (ret < ECSD_OK) {
				/////log
			}

			ret = pid_->set_board_lock(board_info->dev_id);
		}
		
		ret = pood_->GetPowerDissipation(monitor_info->power_dissipation);
		if (ret < ECSD_OK) {
			/////log
		}

		check_pcie_speed(board_info, monitor_info->pcie_speed);

/*
		int count = monitor_info->vt_md.size();
		for (int i = 0; i < count; i++) {
			struct MetaData &md = monitor_info->vt_md[i];
			std::cout << md.name << std::endl;
			md.value = 11 + i;
		}
*/
		return ret;
	}
#endif
	int FpgaMaintenance::SetMetaDataConfig(const char* file_name) {
		CSD_SET_USED(file_name);
	
		return ECSD_OK;
	}

	int FpgaMaintenance::GetDeviceList(struct DeviceListT* device_list) {
		//printf("%s, %d\n", __func__, __LINE__);

		device_list->dev_type = CSD_DEVICE_TYPE_FPGA;
			
		device_list->dl.fdl.dev_num = 2;

		device_list->dl.fdl.dev_info[0].dev_id = 1;
		device_list->dl.fdl.dev_info[0].cu_num = 3;
		device_list->dl.fdl.dev_info[0].cu_info[0].cu_id = 1;
		device_list->dl.fdl.dev_info[0].cu_info[0].mds_num = 4;
		device_list->dl.fdl.dev_info[0].cu_info[1].cu_id = 1;
		device_list->dl.fdl.dev_info[0].cu_info[1].mds_num = 4;
		device_list->dl.fdl.dev_info[0].cu_info[2].cu_id = 1;
		device_list->dl.fdl.dev_info[0].cu_info[2].mds_num = 4;

		device_list->dl.fdl.dev_info[1].dev_id = 1;
		device_list->dl.fdl.dev_info[1].cu_num = 3;
		device_list->dl.fdl.dev_info[1].cu_info[0].cu_id = 1;
		device_list->dl.fdl.dev_info[1].cu_info[0].mds_num = 4;
		device_list->dl.fdl.dev_info[1].cu_info[1].cu_id = 1;
		device_list->dl.fdl.dev_info[1].cu_info[1].mds_num = 4;
		device_list->dl.fdl.dev_info[1].cu_info[2].cu_id = 1;
		device_list->dl.fdl.dev_info[1].cu_info[2].mds_num = 4;

		return ECSD_OK;
	}


	int FpgaMaintenance::GetDeviceInfo(struct FpgaDeviceInfoT* dev_info) {
		int dev_id = dev_info->dev_id;

		CSD_SET_USED(dev_id);
		
		//get metadata info by dev id
		printf("%s, %d\n", __func__, __LINE__);

		return ECSD_OK;
	}

	int FpgaMaintenance::GetCuInfo(struct FpgaCuInfoT* cu_info) {
		int dev_id = cu_info->dev_id;
		int cu_id = cu_info->cu_id;

		CSD_SET_USED(dev_id);
		CSD_SET_USED(cu_id);

		//get metadata info by dev id and cu id
		printf("%s, %d\n", __func__, __LINE__);

		return ECSD_OK;
	}

	int FpgaMaintenance::GetMetaDataValue(struct MetaDataControlT* metadata) {
		return pid_->Get(*metadata);
	}

	int FpgaMaintenance::SetMetaDataValue(struct MetaDataControlT* metadata) {
		printf("%s, %d\n", __func__, __LINE__);

		return pid_->Set(*metadata);
	}

	//Process user commond
	int FpgaMaintenance::PorcessCommand(int cmd, void* arg) {
		int ret = ECSD_OK;
		
		switch(cmd) {
			case SET_METADATA_CONFIG: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				//return GetDeviceList((struct FpgaDeviceListT*)parg);
				break;
			}
			case GET_DEVICE_LIST: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				return GetDeviceList((struct DeviceListT*)parg);
				break;
			}
			case GET_FPGA_DEVICE_INFO: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				
				return GetDeviceInfo((struct FpgaDeviceInfoT*)parg);
				break;	
			}
			case GET_FPGA_CU_INFO: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				
				return GetCuInfo((struct FpgaCuInfoT*)parg);
				break;	
			}
			case GET_FPGA_METADATA_VALUE: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				
				return GetMetaDataValue((struct MetaDataControlT*)parg);
				break;	
			}
			case SET_FPGA_METADATA_VALUE: {
				if (NULL == parg) {
					return ECSD_INVALID;
				}
				
				return SetMetaDataValue((struct MetaDataControlT*)parg);
				break;	
			}
			default :
				ret = ECSD_INVALID;
		}

		return ret;
	}
}

