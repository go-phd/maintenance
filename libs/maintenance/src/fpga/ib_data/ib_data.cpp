#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/ioctl.h>

#include "ib_data.h"

namespace csd {

int PcieHealthyGet(IbData *instance, union MetaDataValueU &value) {
    instance->map_base_ = nullptr;
    value.discrete.value = 0x99;
    return ECSD_OK;
}

// sofeware property
static vector<struct MetaDataSoftwareT> md_sw_array = {
    {
        .get = PcieHealthyGet,
        .md = {
            .name = "Pcie Health",
            .type = CSD_META_DATA_TYPE_DISCRETE,
            .value = {
                .defult = 0,
            }
        }
    },
    {
        .get = nullptr,
        .md = {
            .name = "test",
            .type = CSD_META_DATA_TYPE_DISCRETE,
            .value = {
                .defult = 0,
            }
        }
    }
};

IbData::IbData() {
    nsa_ctl_fd_ = -1;
}

IbData::~IbData() {
    if (nsa_ctl_fd_ > 0) {
        close(nsa_ctl_fd_);
        nsa_ctl_fd_ = -1;
    }
}

int IbData::Get(struct MetaDataControlT &mdc) {
    if (INVALID_ADDR == mdc.addr) {
        for (auto md_sw : md_sw_array) {
            if (0 == strncmp(md_sw.md.name, mdc.md.name, strlen(md_sw.md.name))) {
                if (nullptr == md_sw.get) {
                    return ECSD_NO_SUPPORT;
                }

                int ret = md_sw.get(this, md_sw.md.value);

                if (ECSD_OK == ret) {
                    mdc.md = md_sw.md;
                }

                return ret;
            }
        }
    } else {
        //get register value
        printf("%s(), %d, ECSD_NO_SUPPORT\n", __func__, __LINE__);
    }

    return ECSD_NO_SUPPORT;
}

int IbData::Set(struct MetaDataControlT &mdc) {
    if (INVALID_ADDR == mdc.addr) {
        printf("%s(), %d, ECSD_NO_SUPPORT\n", __func__, __LINE__);
        return ECSD_NO_SUPPORT;
    } else {
        //set register value
        printf("%s(), %d, ECSD_NO_SUPPORT\n", __func__, __LINE__);
        return ECSD_NO_SUPPORT;
    }

    return ECSD_OK;
}

int IbData::ctrl_board_lock(int dev_id, nsa_lock_mode_e lock_mode) {
    int ret = ECSD_OK;
    //int cmd_opt;
    ndd_ioctl_args_t args;
    nsa_lock_get_e  lock_get = INIT_LOCK_MAX;

    if ((lock_mode < 0) || (lock_mode >= LOCK_MODE_MAX)) {
        fprintf(stdout, "lock_mode[%d] is invalid!\n", lock_mode);
        return ECSD_INVALID;
    }

    if (nsa_ctl_fd_ < 0) {
        int fd = open("/dev/nsa_ctl", O_RDWR);

        if (fd < 0) {
            fprintf(stdout, "Open %s error!\n", "/dev/nsa_ctl");
            return ECSD_NO_EXIST;
        }

        nsa_ctl_fd_ = fd;
    }

    memset(&args, 0x0, sizeof(ndd_ioctl_args_t));
    args.board_id  = dev_id;
    args.bus_id    = NSA_COM_CMD_APP_INIT_LOCK;   //NSA_COM_CMD_APP_INIT_LOCK
    args.reg_addr  = (uint32_t)lock_mode;         //0:get,1:set
    args.lock_type = NSA_DATA_LOCK;               //NSA_DATA_LOCK

    if (0 != (ret = ioctl(nsa_ctl_fd_, NSA_CMD_COMMON_CTRL, &args))) {
        fprintf(stdout, "DDI: Board ID[%d] pcie ioctl operation error:%d!\n", dev_id, ret);
        return ECSD_OPERATION;
    }

    lock_get = (nsa_lock_get_e)args.reg_width;    //0:lock unuse,init success, 1:lock use,init fail

    if (lock_mode == LOCK_MODE_GET) {
        if ((lock_get < 0) || (lock_get >= INIT_LOCK_MAX)) {
            fprintf(stdout, "lock_get[%d] is invalid!\n", lock_get);
            ret = ECSD_OPERATION;
            return ret;
        }

        if (lock_get == INIT_LOCK_SUCCESS) {
            ret = ECSD_OK;
        } else {
            fprintf(stdout, "Board id[%d] get lock failed.\r\n", dev_id);
            ret = ECSD_OPERATION;
        }
    } else {
        ret = ECSD_OK;
    }

    return ret;
}

int IbData::get_board_lock(int dev_id) {
    int err_cnt = 5;
    int ret;

    while (err_cnt) {
        ret = ctrl_board_lock(dev_id, LOCK_MODE_GET);

        if (ret == 0) {
            return 0;
        } else {
            fprintf(stdout, "get_board_lock error, try again.\n");
            ret = -1;
            err_cnt--;
            sleep(6);
        }
    }

    if (ret == -1) {
        fprintf(stdout, "get_board_lock failed, force to set lock.\n");

        if (set_board_lock(dev_id) == 0) {
            return get_board_lock(dev_id);
        }
    }

    return ret;
}

int IbData::set_board_lock(int dev_id) {
    return ctrl_board_lock(dev_id, LOCK_MODE_SET);
}


uint32_t IbData::read_register(void *map_base, uint32_t target) {
    /* calculate the virtual address to be accessed */
    uint32_t read_result;
    void *virt_addr = (void *)((char *)map_base + target);
    read_result = *((uint32_t *) virt_addr);
    /* swap 32-bit endianess if host is not little-endian */
    read_result = ltohl(read_result);
    //    printf("Read 32-bit value at address 0x%08x (%p): 0x%08x\n", (unsigned int)target, virt_addr, (unsigned int)read_result);
    return read_result;
}

void IbData::write_register(void *map_base, uint32_t target, uint32_t writeval) {
    /* swap 32-bit endianess if host is not little-endian */
    void *virt_addr = (void *)((char *)map_base + target);
    //  printf("Write 32-bits value 0x%08x to 0x%08x (0x%p)\n", (unsigned int)writeval, (unsigned int)target, virt_addr);
    writeval = htoll(writeval);
    *((uint32_t *) virt_addr) = writeval;
}

int IbData::check_board_partnum(void *map_base, char *partnum) {
    int i;
    //char partnum[PARTNUM_LEN+1];

    for (i = 0; i < PARTNUM_LEN; ++i) {
        usleep(1000);
        write_register(map_base, PARTNUM_W_REG0, PARTNUM_W_VALUE0);
        usleep(1000);
        write_register(map_base, PARTNUM_W_REG1, PARTNUM_W_VALUE1 + 0x1 * i);
        usleep(1000);
        write_register(map_base, PARTNUM_W_REG2, PARTNUM_W_VALUE2);
        usleep(1000);
        write_register(map_base, PARTNUM_W_REG3, PARTNUM_W_VALUE3);
        usleep(1000);
        partnum[i] = read_register(map_base, PARTNUM_R_REG) & 0xff;
    }

    partnum[i] = '\0';
    /*
    if (strlen(partnum) == 0) {
        fprintf(stdout, "\tDevice Partnum:" YELLOW "\tNO\n" NONE);
    } else {
        fprintf(stdout, "\tDevice Partnum:" GREEN "\t%s\n" NONE, partnum);
    }
    */
    return ECSD_OK;
}

int IbData::check_pcie_healthy(void *map_base, bool &pcie_health) {
    const uint32_t test_value = 0x5a5a3c3c;
    uint32_t result;
    //fprintf(stdout, "\tPCIE Channel Status:\n");
    //fprintf(stdout, "\t\tRegister:\t");
    write_register(map_base, RW_REG, test_value);
    result = read_register(map_base, RW_REG);

    if (result != test_value) {
        //fprintf(stdout, RED "Failed\n" NONE);
        //return -1;
        pcie_health = false;
        return ECSD_OK;
    }

    write_register(map_base, RW_RV_REG, test_value);
    result = read_register(map_base, RW_RV_REG);

    if (result != ~test_value) {
        //fprintf(stdout, RED "Failed\n" NONE);
        //return -1;
        pcie_health = false;
        return ECSD_OK;
    }

    //fprintf(stdout, GREEN "OK\n" NONE);
    pcie_health = true;
    return ECSD_OK;
}

int IbData::check_ddr_healthy(void *map_base, struct DdrHealth *ddr_health) {
    //uint32_t ddr_crc = 0;
    int i;
    ddr_health->ddr_exist = read_register(map_base, DDR_EXIST_REG);
    ddr_health->ddr_init  = read_register(map_base, DDR_INIT_REG);

    for (i = 0; i < DDR_NUM; ++i) {
        ddr_health->ddr_crc[i] = read_register(map_base, DDR_CRC_REG + i * 0x4);
        /*
            fprintf(stdout, "\tDDR%d Channel Status:\n", i);
            fprintf(stdout, "\t\t\tEnable:\t");

            if (ddr_health->ddr_exist & (0x01 << (i + 2))) {
                fprintf(stdout, GREEN "YES\n" NONE);
                fprintf(stdout, "\t\t\tInit:\t");

                if (ddr_health->ddr_init & (0x01 << i)) {
                    fprintf(stdout, GREEN "OK\n" NONE);
                } else {
                    fprintf(stdout, RED "Failed\n" NONE);
                }

                fprintf(stdout, "\t\t\tECC:\t");
                ddr_crc = read_register(map_base, DDR_CRC_REG + i * 0x4);

                if ((ddr_crc & 0x00ff) == 0x0) {
                    fprintf(stdout, GREEN "Multi Bits OK\n" NONE);
                } else if ((ddr_crc & 0x00ff) == 0xff) {
                    fprintf(stdout, YELLOW "Multi Bits N/A\n" NONE);
                } else if ((ddr_crc & 0x00ff) > 0){
                    fprintf(stdout, RED "Multi Bits Failed(%d)\n" NONE, ddr_crc & 0x00ff);
                }
                if (((ddr_crc >> 16) & 0x00ff) == 0x00) {
                    fprintf(stdout, GREEN "\t\t\t\tSingle Bit OK\n" NONE);
                } else if (((ddr_crc >> 16) & 0x00ff) == 0xff) {
                    fprintf(stdout, YELLOW "\t\t\t\tSingle Bits N/A\n" NONE);
                } else if (((ddr_crc >> 16) & 0x00ff) > 0) {
                    fprintf(stdout, RED "\t\t\t\tSingle Bit Failed(%d)\n" NONE, (ddr_crc >> 16) & 0x00ff);
                }

        		ddr_health->ddr_crc[i] = ddr_crc;
            } else {
                fprintf(stdout, YELLOW "NO\n" NONE);
            }
            */
    }

    return ECSD_OK;
}

int IbData::check_board_pll(void *map_base, bool &pll_health) {
    //uint32_t result;
    //fprintf(stdout, "\tBoard PLL Status:\t");
    pll_health = read_register(map_base, PLL_REG);

    if (0 == (pll_health & 0x01)) {
        //fprintf(stdout, RED "Failed\n" NONE);
        //return ECSD_FUNCION_FAILED;
        pll_health = false;
    } else {
        //fprintf(stdout, GREEN "OK\n" NONE);
        //return ECSD_OK;
        pll_health = true;
    }

    return ECSD_OK;
}

int IbData::check_board_power(void *map_base,        uint32_t &power) {
    //uint32_t power;
    //fprintf(stdout, "\tBoard Power Status:\t");
    usleep(1000);
    write_register(map_base, POWER_W_REG0, POWER_W_VALUE0);
    usleep(1000);
    write_register(map_base, POWER_W_REG1, POWER_W_VALUE1);
    usleep(1000);
    write_register(map_base, POWER_W_REG2, POWER_W_VALUE2);
    usleep(1000);
    write_register(map_base, POWER_W_REG3, POWER_W_VALUE3);
    usleep(1000);
    power = read_register(map_base, POWER_R_REG);
    /*
    	    if (power == 0xffff) {
    	        fprintf(stdout, YELLOW "NO\n" NONE);
    	        return ECSD_OK;
    	    }*/
#if 0

    if (power > 90) {
        fprintf(stdout, RED "Failed (%d)\n" NONE, power);
    } else {
        fprintf(stdout, GREEN "OK (%d)\n" NONE, power);
    }

#else
    //fprintf(stdout, GREEN "%d\n" NONE, power);
#endif
    return ECSD_OK;
}

int IbData::check_board_temperature(void *map_base, float &temp) {
    uint32_t result;
    //float temp;
    //fprintf(stdout, "\tBoard Temp Status:\t");
    result = read_register(map_base, TMP_REG);
    temp = ((float)(result & 0x0ffff) * 501.3743 / 65536 - 273.6777);
    /*
    	    if (temp >= 100.0) {
    	        fprintf(stdout, RED "Failed (%.02f)\n" NONE, temp);
    	    } else {
    	        fprintf(stdout, GREEN "OK (%.02f)\n" NONE, temp);
    	    }
    */
    return ECSD_OK;
}

int IbData::check_board_healthy(int dev_id, struct MonitorInfo *monitor_info) {
    char dev_name[256];
    int fd;
    void *map_base;
    sprintf(dev_name, "/dev/xdma%d_user", dev_id);

    if ((fd = open(dev_name, O_RDWR | O_SYNC)) < 0) {
        fprintf(stdout, YELLOW "\nCheck_board_healthy Failed (%s)\n" NONE, strerror(errno));
        return ECSD_NO_EXIST;
    }

    /* map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map_base == (void *) - 1) {
        FATAL;
        return ECSD_OPERATION;
    }

    check_board_partnum(map_base, monitor_info->partnum);
    check_pcie_healthy(map_base, monitor_info->pcie_health);
    check_ddr_healthy(map_base, &monitor_info->ddr_health);
    check_board_pll(map_base, monitor_info->pll_health);
    check_board_temperature(map_base, monitor_info->temperature);
    //    check_board_power(map_base);

    if (munmap(map_base, MAP_SIZE) == -1) {
        return ECSD_OPERATION;
    }

    close(fd);
    return ECSD_OK;
}

}