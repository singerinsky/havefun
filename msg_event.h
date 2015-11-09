#ifndef _MSG_EVENT_H_
#define _MSG_EVENT_H_

enum event_type
{
	EVENT_NONE,
	EVENT_NEW_CONNECTION,
	EVENT_READ,
	EVENT_WRITE,
        EVENT_CLOST,	
};

struct msg_base
{
	uint16_t _event_type;
};

struct new_con_msg:public msg_base
{
	uint32_t _socket_fd;
};

#endif
