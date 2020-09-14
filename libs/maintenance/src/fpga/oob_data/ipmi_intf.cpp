#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h> 
#include <unistd.h> 
#include "ipmi_intf.h"

namespace csd {
	IpmiIntf::IpmiIntf() {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		ipmi_fd_ = -1;
	}

	IpmiIntf::~IpmiIntf() {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
		Cleanup();
	}

	int IpmiIntf::Init() {
	    char devname[30] = {0};
	    int fd = 0;
	    int ret = 0;

		if (ipmi_fd_ > 0) {
			return ret;
		}

	    sprintf(devname, "/dev/ipmidev/0");
	    fd = open(devname, O_RDWR);
	    if (fd == -1) {
			ret = errno;
			sprintf(devname, "/dev/ipmi/0");
			fd = open(devname, O_RDWR);
			if (fd == -1) {
			    if (errno != ENOENT)
					ret = errno;
				
			    sprintf(devname, "/dev/ipmi0");
			    fd = open(devname, O_RDWR);
				//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);
			    if (fd == -1) {
					if (errno != ENOENT)
					    ret = errno;
			    }
			}
	    }

	    ipmi_fd_ = fd;
		msg_id_ = 0;
		return ret;
	}

	void IpmiIntf::Cleanup() {
		if (ipmi_fd_ > 0) {
			close(ipmi_fd_);
			ipmi_fd_ = -1;
		}
	}

	int IpmiIntf::SendCommand(unsigned char *in_data, unsigned short in_data_len) {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);

		//send to ipmi driver
		struct IpmiSystemInterfaceAddr si_addr;
		si_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	    si_addr.channel = 0xf;	//system channel
	    si_addr.lun = 0;

		struct IpmiReq req;	
		req.addr = (unsigned char *)&si_addr;
		req.addr_len = sizeof(si_addr);
		req.msgid = msg_id_;
		req.msg.netfn = netfn_;
		req.msg.cmd = cmd_;
		req.msg.data = in_data;
		req.msg.data_len = in_data_len;

		int ret = ioctl(ipmi_fd_, IPMICTL_SEND_COMMAND, &req);
		if (ret < -1)
			ret = errno;
		
		return ret;
	}

	int IpmiIntf::RecvResponse(unsigned char *out_data, unsigned short out_data_len) {
		//printf("%s, %s(), %d\n", __FILE__, __func__, __LINE__);

		int ret = 0;
		fd_set readfds;
		

		/* Wait for something. */
		struct timeval wait_time; 
		wait_time.tv_sec = 3;	//wait for 3 second3
		wait_time.tv_usec = 0;
		
		FD_ZERO(&readfds);
		FD_SET(ipmi_fd_, &readfds);
		ret = select(ipmi_fd_ + 1, &readfds, NULL, NULL, &wait_time);
		if (ret < 0) {
		    fprintf(stdout, "Error from select: %s\n", strerror(errno));
		    return ret;
		} else if (0 == ret) {
			fprintf(stdout, "select time out!\n");
			return -1;
		} else {
			;
		}

		/* Receive the message. */
		struct IpmiRecv recv;
		struct IpmiAddr addr;
		
		recv.addr = (unsigned char *) &addr;
		recv.addr_len = sizeof(addr);
		recv.msg.data = recv_data_;
		recv.msg.data_len = MAX_IPMI_DATA_SIZE;
		ret = ioctl(ipmi_fd_, IPMICTL_RECEIVE_MSG_TRUNC, &recv);
		if (ret == -1) {
			if (errno == EMSGSIZE) {
			    /* The message was truncated, handle it as such. */
			    //data[0] = IPMI_REQUESTED_DATA_LENGTH_EXCEEDED_CC;
			    ret = EMSGSIZE;
			} else
			    return ret;
	    }

		if ((IPMI_RESPONSE_RECV_TYPE == recv.recv_type) && 
			(netfn_ == (recv.msg.netfn & 0xfe)) && 
			(cmd_ == recv.msg.cmd) && 
			(msg_id_ == recv.msgid) && 
			(recv.msg.data_len <= out_data_len)) {
				memcpy(out_data, recv.msg.data, recv.msg.data_len);
				
				printf("\n---------------------===========---\n");
				for (int i = 0; i < recv.msg.data_len; i++) {
					printf("0x%x ", recv.msg.data[i]);
				}
				printf("\n-------------------=========-----\n");
				
			} else {
				return -1;
			}
		
		return 0;
	}

	int IpmiIntf::RequestData(unsigned char     netfn, 
									unsigned char cmd, 
									unsigned char *in_data, 
									unsigned short in_data_len, 
									unsigned char *out_data, 
									unsigned short out_data_len) {

		netfn_ = netfn;
		cmd_ = cmd;

		// init ipmi device
		int ret = Init();
		if (ret < 0) {
			return ret;
		}

		ret = SendCommand(in_data, in_data_len);
		if (0 == ret) {
			ret = RecvResponse(out_data, out_data_len);
			if (ret < 0) {
				goto end;
			}
		}

	end:
		msg_id_++;
		return ret;
		
	}						
}

