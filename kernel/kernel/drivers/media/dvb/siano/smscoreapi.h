

#ifndef __SMS_CORE_API_H__
#define __SMS_CORE_API_H__

#include <linux/version.h>
#include <linux/device.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/types.h>
#include <asm/page.h>
#include <linux/mutex.h>
#include "compat.h"

#ifdef SMS_DVB3_SUBSYS
#include "dmxdev.h"
#include "dvbdev.h"
#include "dvb_demux.h"
#include "dvb_frontend.h"
#endif

#define kmutex_init(_p_) mutex_init(_p_)
#define kmutex_lock(_p_) mutex_lock(_p_)
#define kmutex_trylock(_p_) mutex_trylock(_p_)
#define kmutex_unlock(_p_) mutex_unlock(_p_)

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define SMS_ALLOC_ALIGNMENT					128
#define SMS_DMA_ALIGNMENT					16
#define SMS_ALIGN_ADDRESS(addr) \
	((((uintptr_t)(addr)) + (SMS_DMA_ALIGNMENT-1)) & ~(SMS_DMA_ALIGNMENT-1))

#define SMS_DEVICE_FAMILY2					1
#define SMS_ROM_NO_RESPONSE					2
#define SMS_DEVICE_NOT_READY					0x8000000
#define SMS_HOSTLIB_SUBSYS                            1
#define SMS_SPI_PXA310_DRV                            1


enum sms_device_type_st {
	SMS_STELLAR = 0,
	SMS_NOVA_A0,
	SMS_NOVA_B0,
	SMS_VEGA,
	SMS_NUM_OF_DEVICE_TYPES
};

struct smscore_device_t;
struct smscore_client_t;
struct smscore_buffer_t;

typedef int (*hotplug_t) (struct smscore_device_t *coredev,
			  struct device *device, int arrival);

typedef int (*setmode_t) (void *context, int mode);
typedef void (*detectmode_t) (void *context, int *mode);
typedef int (*sendrequest_t) (void *context, void *buffer, size_t size);
typedef int (*loadfirmware_t) (void *context, void *buffer, size_t size);
typedef int (*preload_t) (void *context);
typedef int (*postload_t) (void *context);

typedef int (*onresponse_t) (void *context, struct smscore_buffer_t *cb);
typedef void (*onremove_t) (void *context);

struct smscore_buffer_t {

	struct list_head entry;
	int size;
	int offset;


	void *p;
	dma_addr_t phys;
	unsigned long offset_in_common;
};

struct smsdevice_params_t {
	struct device *device;

	int buffer_size;
	int num_buffers;

	char devpath[32];
	unsigned long flags;

	setmode_t setmode_handler;
	detectmode_t detectmode_handler;
	sendrequest_t sendrequest_handler;
	preload_t preload_handler;
	postload_t postload_handler;

	void *context;
	enum sms_device_type_st device_type;
};

struct smsclient_params_t {
	int initial_id;
	int data_type;
	onresponse_t onresponse_handler;
	onremove_t onremove_handler;

	void *context;
};


#define SMS_ANTENNA_GPIO_0				1
#define SMS_ANTENNA_GPIO_1				0

#define BW_8_MHZ					0
#define BW_7_MHZ					1
#define BW_6_MHZ					2
#define BW_5_MHZ					3
#define BW_ISDBT_1SEG					4
#define BW_ISDBT_3SEG					5

#define MSG_HDR_FLAG_SPLIT_MSG				4

#define MAX_GPIO_PIN_NUMBER				31

#define HIF_TASK					11
#define SMS_HOST_LIB					150
#define DVBT_BDA_CONTROL_MSG_ID				201

#define SMS_MAX_PAYLOAD_SIZE				240
#define SMS_TUNE_TIMEOUT				500

#define MSG_SMS_GPIO_CONFIG_REQ				507
#define MSG_SMS_GPIO_CONFIG_RES				508
#define MSG_SMS_GPIO_SET_LEVEL_REQ			509
#define MSG_SMS_GPIO_SET_LEVEL_RES			510
#define MSG_SMS_GPIO_GET_LEVEL_REQ			511
#define MSG_SMS_GPIO_GET_LEVEL_RES			512
#define MSG_SMS_RF_TUNE_REQ				561
#define MSG_SMS_RF_TUNE_RES				562
#define MSG_SMS_INIT_DEVICE_REQ				578
#define MSG_SMS_INIT_DEVICE_RES				579
#define MSG_SMS_ADD_PID_FILTER_REQ			601
#define MSG_SMS_ADD_PID_FILTER_RES			602
#define MSG_SMS_REMOVE_PID_FILTER_REQ			603
#define MSG_SMS_REMOVE_PID_FILTER_RES			604
#define MSG_SMS_DAB_CHANNEL				607
#define MSG_SMS_GET_PID_FILTER_LIST_REQ			608
#define MSG_SMS_GET_PID_FILTER_LIST_RES			609
#define MSG_SMS_GET_STATISTICS_REQ			615
#define MSG_SMS_GET_STATISTICS_RES			616
#define MSG_SMS_SET_ANTENNA_CONFIG_REQ			651
#define MSG_SMS_SET_ANTENNA_CONFIG_RES			652
#define MSG_SMS_GET_STATISTICS_EX_REQ			653
#define MSG_SMS_GET_STATISTICS_EX_RES			654
#define MSG_SMS_SLEEP_RESUME_COMP_IND			655

#define MSG_SMS_SET_PERIODIC_STATS_REQ     658
#define MSG_SMS_SET_PERIODIC_STATS_RES     659

#define MSG_SMS_DATA_DOWNLOAD_REQ			660
#define MSG_SMS_DATA_DOWNLOAD_RES			661
#define MSG_SMS_SWDOWNLOAD_TRIGGER_REQ			664
#define MSG_SMS_SWDOWNLOAD_TRIGGER_RES			665
#define MSG_SMS_SWDOWNLOAD_BACKDOOR_REQ			666
#define MSG_SMS_SWDOWNLOAD_BACKDOOR_RES			667
#define MSG_SMS_GET_VERSION_EX_REQ			668
#define MSG_SMS_GET_VERSION_EX_RES			669
#define MSG_SMS_SET_CLOCK_OUTPUT_REQ			670
#define MSG_SMS_I2C_SET_FREQ_REQ			685
#define MSG_SMS_GENERIC_I2C_REQ				687
#define MSG_SMS_GENERIC_I2C_RES				688
#define MSG_SMS_DVBT_BDA_DATA				693
#define MSG_SW_RELOAD_REQ				697
#define MSG_SMS_DATA_MSG				699
#define MSG_SW_RELOAD_START_REQ				702
#define MSG_SW_RELOAD_START_RES				703
#define MSG_SW_RELOAD_EXEC_REQ				704
#define MSG_SW_RELOAD_EXEC_RES				705
#define MSG_SMS_SPI_INT_LINE_SET_REQ		710
#define MSG_SMS_GPIO_CONFIG_EX_REQ			712
#define MSG_SMS_GPIO_CONFIG_EX_RES			713
#define MSG_SMS_ISDBT_TUNE_REQ				776
#define MSG_SMS_ISDBT_TUNE_RES				777

#define MSG_SMS_LOOPBACK_REQ				718
#define MSG_SMS_LOOPBACK_RES				719


#define SMS_INIT_MSG_EX(ptr, type, src, dst, len) do { \
	(ptr)->msgType = type; (ptr)->msgSrcId = src; (ptr)->msgDstId = dst; \
	(ptr)->msgLength = len; (ptr)->msgFlags = 0; \
} while (0)
#define SMS_INIT_MSG(ptr, type, len) \
	SMS_INIT_MSG_EX(ptr, type, 0, HIF_TASK, len)

enum SMS_DVB3_EVENTS {
	DVB3_EVENT_INIT = 0,
	DVB3_EVENT_SLEEP,
	DVB3_EVENT_HOTPLUG,
	DVB3_EVENT_FE_LOCK,
	DVB3_EVENT_FE_UNLOCK,
	DVB3_EVENT_UNC_OK,
	DVB3_EVENT_UNC_ERR
};

enum SMS_DEVICE_MODE {
	DEVICE_MODE_NONE = -1,
	DEVICE_MODE_DVBT = 0,
	DEVICE_MODE_DVBH,
	DEVICE_MODE_DAB_TDMB,
	DEVICE_MODE_DAB_TDMB_DABIP,
	DEVICE_MODE_DVBT_BDA,
	DEVICE_MODE_ISDBT,
	DEVICE_MODE_ISDBT_BDA,
	DEVICE_MODE_CMMB,
	DEVICE_MODE_RAW_TUNER,
	DEVICE_MODE_MAX,
};

struct SmsMsgHdr_ST {
	u16 msgType;
	u8 msgSrcId;
	u8 msgDstId;
	u16 msgLength;		
	u16 msgFlags;
};

struct SmsMsgData_ST {
	struct SmsMsgHdr_ST xMsgHeader;
	u32 msgData[1];
};

struct SmsDataDownload_ST {
	struct SmsMsgHdr_ST xMsgHeader;
	u32 MemAddr;
	u8 Payload[SMS_MAX_PAYLOAD_SIZE];
};

struct SmsVersionRes_ST {
	struct SmsMsgHdr_ST xMsgHeader;

	u16 ChipModel;		
	u8 Step;		
	u8 MetalFix;		

	u8 FirmwareId;		
				
				 
	u8 SupportedProtocols;	
				

	u8 VersionMajor;
	u8 VersionMinor;
	u8 VersionPatch;
	u8 VersionFieldPatch;

	u8 RomVersionMajor;
	u8 RomVersionMinor;
	u8 RomVersionPatch;
	u8 RomVersionFieldPatch;

	u8 TextLabel[34];
};

struct SmsFirmware_ST {
	u32 CheckSum;
	u32 Length;
	u32 StartAddress;
	u8 Payload[1];
};

struct SMSHOSTLIB_STATISTICS_ST {
	u32 Reserved;		

	
	u32 IsRfLocked;		
	u32 IsDemodLocked;	
	u32 IsExternalLNAOn;	

	
	s32 SNR;		
	u32 BER;		
	u32 FIB_CRC;		
	u32 TS_PER;		
	u32 MFER;		
				 
	s32 RSSI;		
	s32 InBandPwr;		
	s32 CarrierOffset;	

	
	u32 Frequency;		
	u32 Bandwidth;		
	u32 TransmissionMode;	
				 
	u32 ModemState;		
	u32 GuardInterval;	
	u32 CodeRate;		
	u32 LPCodeRate;		
				 
	u32 Hierarchy;		
	u32 Constellation;	

	
	u32 BurstSize;		
	u32 BurstDuration;	
	u32 BurstCycleTime;	
	u32 CalculatedBurstCycleTime;	
					 
	u32 NumOfRows;		
	u32 NumOfPaddCols;	
	u32 NumOfPunctCols;	
	
	u32 ErrorTSPackets;	
				
	u32 TotalTSPackets;	
	u32 NumOfValidMpeTlbs;	
				 
	u32 NumOfInvalidMpeTlbs;
				 
	u32 NumOfCorrectedMpeTlbs; 
				    

	
	u32 BERErrorCount;	
	u32 BERBitCount;	

	
	u32 SmsToHostTxErrors;	


	u32 PreBER;		


	u32 CellId;		
				

};

struct SmsMsgStatisticsInfo_ST {
	u32 RequestResult;

	struct SMSHOSTLIB_STATISTICS_ST Stat;


	u32 Signal;		
	u32 Noise;		

};

struct smscore_gpio_config {
#define SMS_GPIO_DIRECTION_INPUT  0
#define SMS_GPIO_DIRECTION_OUTPUT 1
	u8 Direction;

#define SMS_GPIO_PULLUPDOWN_NONE     0
#define SMS_GPIO_PULLUPDOWN_PULLDOWN 1
#define SMS_GPIO_PULLUPDOWN_PULLUP   2
#define SMS_GPIO_PULLUPDOWN_KEEPER   3
	u8 PullUpDown;

#define SMS_GPIO_INPUTCHARACTERISTICS_NORMAL  0
#define SMS_GPIO_INPUTCHARACTERISTICS_SCHMITT 1
	u8 InputCharacteristics;

#define SMS_GPIO_OUTPUTSLEWRATE_SLOW		0 
#define SMS_GPIO_OUTPUTSLEWRATE_FAST		1 

#define SMS_GPIO_OUTPUTSLEWRATE_0_45_V_NS	0 
#define SMS_GPIO_OUTPUTSLEWRATE_0_9_V_NS	1 
#define SMS_GPIO_OUTPUTSLEWRATE_1_7_V_NS	2 
#define SMS_GPIO_OUTPUTSLEWRATE_3_3_V_NS	3 
	u8 OutputSlewRate;

#define SMS_GPIO_OUTPUTDRIVING_S_4mA		0 
#define SMS_GPIO_OUTPUTDRIVING_S_8mA		1 
#define SMS_GPIO_OUTPUTDRIVING_S_12mA		2 
#define SMS_GPIO_OUTPUTDRIVING_S_16mA		3 

#define SMS_GPIO_OUTPUTDRIVING_1_5mA		0 
#define SMS_GPIO_OUTPUTDRIVING_2_8mA		1 
#define SMS_GPIO_OUTPUTDRIVING_4mA			2 
#define SMS_GPIO_OUTPUTDRIVING_7mA			3 
#define SMS_GPIO_OUTPUTDRIVING_10mA			4 
#define SMS_GPIO_OUTPUTDRIVING_11mA			5 
#define SMS_GPIO_OUTPUTDRIVING_14mA			6 
#define SMS_GPIO_OUTPUTDRIVING_16mA			7 
	u8 OutputDriving;
};

#ifdef SMS_DVB3_SUBSYS

struct smsdvb_client_t {
	struct list_head entry;

	struct smscore_device_t *coredev;
	struct smscore_client_t *smsclient;

	struct dvb_adapter adapter;
	struct dvb_demux demux;
	struct dmxdev dmxdev;
	struct dvb_frontend frontend;

	fe_status_t		fe_status;
	int			fe_ber, fe_snr, fe_unc, fe_signal_strength;

	struct completion tune_done, stat_done;


	struct dvb_frontend_parameters fe_params;

};
#endif 

extern void smsspi_poweron(void);
extern void smsspi_off(void);
extern void smscore_registry_setmode(char *devpath, int mode);
extern int smscore_registry_getmode(char *devpath);

extern int smscore_register_hotplug(hotplug_t hotplug);
extern void smscore_unregister_hotplug(hotplug_t hotplug);

extern int smscore_register_device(struct smsdevice_params_t *params,
				   struct smscore_device_t **coredev);
extern void smscore_unregister_device(struct smscore_device_t *coredev);

extern int smscore_start_device(struct smscore_device_t *coredev);
extern int smscore_load_firmware(struct smscore_device_t *coredev,
				 char *filename,
				 loadfirmware_t loadfirmware_handler);
extern int smscore_set_device_mode(struct smscore_device_t *coredev, int mode);
extern int smscore_get_device_mode(struct smscore_device_t *coredev);

extern int smscore_reset_device_drvs(struct smscore_device_t *coredev);
extern int smscore_get_fw_filename(struct smscore_device_t *coredev, int mode,
				   char *filename);
extern int smscore_send_fw_file(struct smscore_device_t *coredev, u8 *ufwbuf,
				int size);

extern int smscore_register_client(struct smscore_device_t *coredev,
				   struct smsclient_params_t *params,
				   struct smscore_client_t **client);
extern void smscore_unregister_client(struct smscore_client_t *client);

extern int smsclient_sendrequest(struct smscore_client_t *client,
				 void *buffer, size_t size);
extern void smscore_onresponse(struct smscore_device_t *coredev,
			       struct smscore_buffer_t *cb);

int smscore_get_common_buffer_size(struct smscore_device_t *coredev);
int smscore_map_common_buffer(struct smscore_device_t *coredev,
				     struct vm_area_struct *vma);

extern struct smscore_buffer_t *smscore_getbuffer(struct smscore_device_t
						  *coredev);
extern void smscore_putbuffer(struct smscore_device_t *coredev,
			      struct smscore_buffer_t *cb);

int smscore_gpio_configure(struct smscore_device_t *coredev, u8 PinNum,
		struct smscore_gpio_config *pGpioConfig);
int smscore_gpio_set_level(struct smscore_device_t *coredev, u8 PinNum,
		u8 NewLevel);
int smscore_gpio_get_level(struct smscore_device_t *coredev, u8 PinNum,
		u8 *level);

void smscore_set_board_id(struct smscore_device_t *core, int id);
int smscore_get_board_id(struct smscore_device_t *core);

#ifdef SMS_HOSTLIB_SUBSYS
extern int smschar_register(void);
extern void smschar_unregister(void);
#endif

#ifdef SMS_NET_SUBSYS
extern int smsnet_register(void);
extern void smsnet_unregister(void);
#endif

#ifdef SMS_DVB3_SUBSYS
extern int smsdvb_register(void);
extern void smsdvb_unregister(void);
#endif

#ifdef SMS_USB_DRV
extern int smsusb_register(void);
extern void smsusb_unregister(void);
#endif

#ifdef SMS_SDIO_DRV
extern int smssdio_register(void);
extern void smssdio_unregister(void);
#endif

#ifdef SMS_SPI_PXA310_DRV
extern int smsspi_register(void);
extern void smsspi_unregister(void);
#endif

/* ------------------------------------------------------------------------ */

extern int sms_debug;

#define DBG_INFO 1
#define DBG_ADV  2



#if defined(SMS_CMMB_DEBUG_SWITCH)

#define sms_printk(kern, fmt, arg...) \
	printk(kern "%s: " fmt "\n", __func__, ##arg)

#define dprintk(kern, lvl, fmt, arg...) do {\
	if (sms_debug & lvl) \
		sms_printk(kern, fmt, ##arg); } while (0)

#define sms_log(fmt, arg...) sms_printk(KERN_INFO, fmt, ##arg)
#define sms_err(fmt, arg...) \
	sms_printk(KERN_ERR, "line: %d: " fmt, __LINE__, ##arg)
#define sms_warn(fmt, arg...)  sms_printk(KERN_WARNING, fmt, ##arg)
#define sms_info(fmt, arg...) \
	dprintk(KERN_INFO, DBG_INFO, fmt, ##arg)
#define sms_debug(fmt, arg...) \
	dprintk(KERN_DEBUG, DBG_ADV, fmt, ##arg)

#else
#define sms_log(fmt, arg...) 
#define sms_err(fmt, arg...) 
#define sms_warn(fmt, arg...) 
#define sms_info(fmt, arg...) 
#define sms_debug(fmt, arg...) 
#endif	

#endif 
