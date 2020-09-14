
#ifndef IB_DATA_H
#define IB_DATA_H

#include <string>
#include <vector>
#include "ib_data_base.h"

#define NONE                 "\e[0m"
#define RED                  "\e[0;31m"
#define GREEN                "\e[0;32m"
#define YELLOW               "\e[0;33m"

using namespace std; 


namespace csd {

#define PARTNUM_LEN 18


/* ltoh: little to host */
/* htol: little to host */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define ltohl(x)       (x)
#  define ltohs(x)       (x)
#  define htoll(x)       (x)
#  define htols(x)       (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#  define ltohl(x)     __bswap_32(x)
#  define ltohs(x)     __bswap_16(x)
#  define htoll(x)     __bswap_32(x)
#  define htols(x)     __bswap_16(x)
#endif
	
#define TMP_REG       0x130000
#define PLL_REG       0x110004
#define DDR_EXIST_REG 0x100020
#define DDR_INIT_REG  0x11000C
#define DDR_CRC_REG   0x110018
#define RW_REG        0x120000
#define RW_RV_REG     0x120004
			
//#define PARTNUM_LEN       18
#define PARTNUM_W_REG0    0x00400010
#define PARTNUM_W_VALUE0  0x57
#define PARTNUM_W_REG1    0x00400004
#define PARTNUM_W_VALUE1  0x800001c4
#define PARTNUM_W_REG2    0x00400008
#define PARTNUM_W_VALUE2  0x1
#define PARTNUM_W_REG3    0x00400000
#define PARTNUM_W_VALUE3  0xc0000000
#define PARTNUM_R_REG     0x0040000c
			
#define POWER_W_REG0      0x500004
#define POWER_W_VALUE0    0x4000000e
#define POWER_W_REG1      0x500008
#define POWER_W_VALUE1    0x2
#define POWER_W_REG2      0x500010
#define POWER_W_VALUE2    0x10
#define POWER_W_REG3      0x500000
#define POWER_W_VALUE3    0xc0000000
#define POWER_R_REG       0x50000c
		
//#define DDR_NUM       4

#define MAP_SIZE (256*1024*1024UL)
#define MAP_MASK (MAP_SIZE - 1)

#define NSA_COM_CMD_APP_INIT_LOCK (0x434f4d09)
#define NSA_CMD_COMMON_CTRL       (0x6e73610c)

	typedef enum {
	    NSA_CTRL_LOCK = 0,
	    NSA_DATA_LOCK,
	    NSA_MAX_LOCK
	}nsa_lock_type_e;

	typedef enum {
	    FPGA_IP_NOT_EXIST = 0,
	    FPAG_IP_EXIST,
	    FPGA_IP_MAX_EXIST
	}fpga_ip_status_e;
	
	/*ioctl operation */
	typedef struct {
	    int        board_id;            /* PCIE device index in PDE*/
	    int        bus_id;              /*bus num*/
	    int        dev_addr;            /* Address for operation */
	    unsigned int  reg_addr;         /* device register */
	    int        reg_width;           /* register width */
	    unsigned long long int   data;  /* read/write data */
	    int        data_len;            /*read/write data length */
	    nsa_lock_type_e lock_type;      /*lock type: 0-Control lock, 1-data lock*/
	    fpga_ip_status_e fpga_ip_status; /*status flag for modues of fpga ip*/
	} ndd_ioctl_args_t;

	typedef enum {
	    INIT_LOCK_SUCCESS = 0,
	    INIT_LOCK_FAILURE,
	    INIT_LOCK_MAX
	} nsa_lock_get_e;
	
	typedef enum {
		LOCK_MODE_GET = 0,
		LOCK_MODE_SET,
		LOCK_MODE_MAX
	} nsa_lock_mode_e;
		
	class IbData : public IbDataBase {
	public:
		IbData();
		~IbData();

		int get_board_lock(int dev_id);
		int set_board_lock(int dev_id);

		int check_board_healthy(int dev_id, struct MonitorInfo *monitor_info);


		friend int PcieHealthyGet(IbData* instance, union MetaDataValueU &value);
		int Get(struct MetaDataControlT &mdc);
		int Set(struct MetaDataControlT &mdc);

		
		
	private:
		int ctrl_board_lock(int dev_id, nsa_lock_mode_e lock_mode);
		uint32_t read_register(void *map_base, uint32_t target);
		void write_register(void *map_base, uint32_t target, uint32_t writeval);
		int check_board_partnum(void *map_base, char *partnum);
		int check_pcie_healthy(void *map_base, bool &pcie_health);
		int check_ddr_healthy(void *map_base, struct DdrHealth* ddr_health);
		int check_board_pll(void *map_base, bool &pll_health);
		int check_board_power(void *map_base,        uint32_t &power);
		int check_board_temperature(void *map_base, float &temp);
		
		int nsa_ctl_fd_;
		void *map_base_;
	};


	struct MetaDataSoftwareT {
		int (*get)(IbData* instance, union MetaDataValueU &value);
		struct MetaDataT md;
	};

}

#endif

