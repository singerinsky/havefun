#ifndef _IO_HANDLER_H_
#define _IO_HANDLER_H_

class io_handle
{
    public:
        virtual int recv_msg() = 0;
        virtual int process_msg() = 0;
};

#endif
