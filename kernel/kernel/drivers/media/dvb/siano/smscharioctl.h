
#ifndef __SMS_CHAR_IOCTL_H__
#define __SMS_CHAR_IOCTL_H__

#include <linux/ioctl.h>

struct smschar_buffer_t {
	unsigned long offset;	
	int size;
};

struct smschar_get_fw_filename_ioctl_t {
	int mode;
	char filename[200];
};

struct smschar_send_fw_file_ioctl_t {
	char *fw_buf;
	int fw_size;
};

#define SMSCHAR_SET_DEVICE_MODE		_IOW('K', 0, int)
#define SMSCHAR_GET_DEVICE_MODE		_IOR('K', 1, int)
#define SMSCHAR_GET_BUFFER_SIZE		_IOR('K', 2, int)
#define SMSCHAR_WAIT_GET_BUFFER		_IOR('K', 3, struct smschar_buffer_t)
#define SMSCHAR_IS_DEVICE_PNP_EVENT 	_IOR('K', 4, int)
#define SMSCHAR_GET_FW_FILE_NAME	\
	_IOWR('K', 5, struct smschar_get_fw_filename_ioctl_t)
#define SMSCHAR_SEND_FW_FILE		\
	_IOW('K', 6, struct smschar_send_fw_file_ioctl_t)
#define SMSCHAR_CANCEL_WAIT_BUFFER	_IO('K', 7)
#define SMSCHAR_RESET_DEVICE_DRVS	_IO('K', 8)
#define SMSCHAR_STARTUP	                _IO('K', 9)
#define SMSCHAR_GET_RESUME_FLAG     _IO('K', 10)
#define SMSCHAR_SET_RESUME_FLAG     _IO('K', 11)
#endif 
