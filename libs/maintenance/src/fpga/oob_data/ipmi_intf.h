
#ifndef IPMI_H
#define IPMI_H

#include <sys/ioctl.h>

/* When the address is not used, the type will be set to this value.
   The channel is the BMC's channel number for the channel (usually
   0), or IPMC_BMC_CHANNEL if communicating directly with the BMC. */
#define IPMI_SYSTEM_INTERFACE_ADDR_TYPE	0xc

#define IPMI_RESPONSE_RECV_TYPE		1 /* A response to a command */

#define MAX_IPMI_DATA_SIZE 256


struct IpmiSystemInterfaceAddr {
	int           addr_type;
	short         channel;
	unsigned char lun;
}; 

/*
 * This is an overlay for all the address types, so it's easy to
 * determine the actual address type.  This is kind of like addresses
 * work for sockets.
 */
#define IPMI_MAX_ADDR_SIZE 32
struct IpmiAddr {
	 /* Try to take these from the "Channel Medium Type" table
	    in section 6.5 of the IPMI 1.5 manual. */
	int   addr_type;
	short channel;
	char  data[IPMI_MAX_ADDR_SIZE];
};


struct IpmiMsg {
    unsigned char  netfn;
    unsigned char  cmd;
    unsigned short data_len;
    unsigned char  *data;
} ;

/* Messages sent to the interface are this format. */
struct IpmiReq {
	unsigned char *addr; /* Address to send the message to. */
	unsigned int  addr_len;

	long    msgid; /* The sequence number for the message.  This
			  exact value will be reported back in the
			  response to this request if it is a command.
			  If it is a response, this will be used as
			  the sequence value for the response.  */

	struct IpmiMsg msg;
};


/* Messages received from the interface are this format. */
struct IpmiRecv {
	int     recv_type; /* Is this a command, response or an
			      asyncronous event. */

	unsigned char *addr;    /* Address the message was from is put
				   here.  The caller must supply the
				   memory. */
	unsigned int  addr_len; /* The size of the address buffer.
				   The caller supplies the full buffer
				   length, this value is updated to
				   the actual message length when the
				   message is received. */

	long    msgid; /* The sequence number specified in the request
			  if this is a response.  If this is a command,
			  this will be the sequence number from the
			  command. */

	struct IpmiMsg msg; /* The data field must point to a buffer.
				The data_size field must be set to the
				size of the message buffer.  The
				caller supplies the full buffer
				length, this value is updated to the
				actual message length when the message
				is received. */
};

/* The magic IOCTL value for this interface. */
#define IPMI_IOC_MAGIC 'i'

/*
 * Send a message to the interfaces.  error values are:
 *   - EFAULT - an address supplied was invalid.
 *   - EINVAL - The address supplied was not valid, or the command
 *              was not allowed.
 *   - EMSGSIZE - The message to was too large.
 *   - ENOMEM - Buffers could not be allocated for the command.
 */
#define IPMICTL_SEND_COMMAND		_IOR(IPMI_IOC_MAGIC, 13,	\
					     struct IpmiReq)
					     
/*
 * Receive a message.  error values:
 *  - EAGAIN - no messages in the queue.
 *  - EFAULT - an address supplied was invalid.
 *  - EINVAL - The address supplied was not valid.
 *  - EMSGSIZE - The message to was too large to fit into the message buffer,
 *               the message will be left in the buffer. */
#define IPMICTL_RECEIVE_MSG		_IOWR(IPMI_IOC_MAGIC, 12,	\
					      struct IpmiRecv)

/*
 * Like RECEIVE_MSG, but if the message won't fit in the buffer, it
 * will truncate the contents instead of leaving the data in the
 * buffer.
 */
#define IPMICTL_RECEIVE_MSG_TRUNC	_IOWR(IPMI_IOC_MAGIC, 11,	\
					      struct IpmiRecv)


namespace csd {
	class IpmiIntf {
	public:
		IpmiIntf();
		~IpmiIntf();

		int RequestData(unsigned char     netfn, 
										unsigned char cmd, 
										unsigned char *in_data, 
										unsigned short in_data_len, 
										unsigned char *out_data, 
										unsigned short out_data_len);
		
	private:	
		int Init();
		void Cleanup();
		int SendCommand(unsigned char *in_data, unsigned short in_data_len);
		int RecvResponse(unsigned char *out_data, unsigned short out_data_len);

		int ipmi_fd_;
		unsigned char netfn_;
		unsigned char cmd_;
		long msg_id_;
		unsigned char recv_data_[MAX_IPMI_DATA_SIZE];
	};

}

#endif

