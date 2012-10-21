


#include <linux/types.h>
#include <linux/input.h>

#include "smscoreapi.h"
#include "smsir.h"
#include "sms-cards.h"



static struct keyboard_layout_map_t keyboard_layout_maps[] = {
		[SMS_IR_KB_DEFAULT_TV] = {
			.ir_protocol = IR_RC5,
			.rc5_kbd_address = KEYBOARD_ADDRESS_TV1,
			.keyboard_layout_map = {
					KEY_0, KEY_1, KEY_2,
					KEY_3, KEY_4, KEY_5,
					KEY_6, KEY_7, KEY_8,
					KEY_9, 0, 0, KEY_POWER,
					KEY_MUTE, 0, 0,
					KEY_VOLUMEUP, KEY_VOLUMEDOWN,
					KEY_BRIGHTNESSUP,
					KEY_BRIGHTNESSDOWN, KEY_CHANNELUP,
					KEY_CHANNELDOWN,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		},
		[SMS_IR_KB_HCW_SILVER] = {
			.ir_protocol = IR_RC5,
			.rc5_kbd_address = KEYBOARD_ADDRESS_LIGHTING1,
			.keyboard_layout_map = {
					KEY_0, KEY_1, KEY_2,
					KEY_3, KEY_4, KEY_5,
					KEY_6, KEY_7, KEY_8,
					KEY_9, KEY_TEXT, KEY_RED,
					KEY_RADIO, KEY_MENU,
					KEY_SUBTITLE,
					KEY_MUTE, KEY_VOLUMEUP,
					KEY_VOLUMEDOWN, KEY_PREVIOUS, 0,
					KEY_UP, KEY_DOWN, KEY_LEFT,
					KEY_RIGHT, KEY_VIDEO, KEY_AUDIO,
					KEY_MHP, KEY_EPG, KEY_TV,
					0, KEY_NEXTSONG, KEY_EXIT,
					KEY_CHANNELUP, 	KEY_CHANNELDOWN,
					KEY_CHANNEL, 0,
					KEY_PREVIOUSSONG, KEY_ENTER,
					KEY_SLEEP, 0, 0, KEY_BLUE,
					0, 0, 0, 0, KEY_GREEN, 0,
					KEY_PAUSE, 0, KEY_REWIND,
					0, KEY_FASTFORWARD, KEY_PLAY,
					KEY_STOP, KEY_RECORD,
					KEY_YELLOW, 0, 0, KEY_SELECT,
					KEY_ZOOM, KEY_POWER, 0, 0
			}
		},
		{ } 
};

u32 ir_pos;
u32	ir_word;
u32 ir_toggle;

#define RC5_PUSH_BIT(dst, bit, pos)	\
	{ dst <<= 1; dst |= bit; pos++; }


static void sms_ir_rc5_event(struct smscore_device_t *coredev,
				u32 toggle, u32 addr, u32 cmd)
{
	bool toggle_changed;
	u16 keycode;

	sms_log("IR RC5 word: address %d, command %d, toggle %d",
				addr, cmd, toggle);

	toggle_changed = ir_toggle != toggle;
	
	ir_toggle = toggle;

	if (addr !=
		keyboard_layout_maps[coredev->ir.ir_kb_type].rc5_kbd_address)
		return; 

	keycode =
		keyboard_layout_maps
		[coredev->ir.ir_kb_type].keyboard_layout_map[cmd];

	if (!toggle_changed &&
			(keycode != KEY_VOLUMEUP && keycode != KEY_VOLUMEDOWN))
		return; 
	sms_log("kernel input keycode (from ir) %d", keycode);
	input_report_key(coredev->ir.input_dev, keycode, 1);
	input_sync(coredev->ir.input_dev);

}


static u32 ir_rc5_decode(unsigned int code)
{

	unsigned int pair;
	unsigned int rc5 = 0;
	int i;

	for (i = 0; i < 14; ++i) {
		pair = code & 0x3;
		code >>= 2;

		rc5 <<= 1;
		switch (pair) {
		case 0:
		case 2:
			break;
		case 1:
			rc5 |= 1;
			break;
		case 3:

			sms_log("bad code");
			return 0;
		}
	}

	return rc5;
}

static void sms_rc5_parse_word(struct smscore_device_t *coredev)
{
	#define RC5_START(x)    (((x)>>12)&3)
	#define RC5_TOGGLE(x)   (((x)>>11)&1)
	#define RC5_ADDR(x)     (((x)>>6)&0x1F)
	#define RC5_INSTR(x)    ((x)&0x3F)

	int i, j;
	u32 rc5_word = 0;


	for (i = 0 ; i < 28 ; i++)
		RC5_PUSH_BIT(rc5_word, (ir_word>>i)&1, j)

	rc5_word = ir_rc5_decode(rc5_word);
	

	sms_ir_rc5_event(coredev,
				RC5_TOGGLE(rc5_word),
				RC5_ADDR(rc5_word),
				RC5_INSTR(rc5_word));
}


static void sms_rc5_accumulate_bits(struct smscore_device_t *coredev,
		s32 ir_sample)
{
	#define RC5_TIME_GRANULARITY	200
	#define RC5_DEF_BIT_TIME		889
	#define RC5_MAX_SAME_BIT_CONT	4
	#define RC5_WORD_LEN			27 

	u32 i, j;
	s32 delta_time;
	u32 time = (ir_sample > 0) ? ir_sample : (0-ir_sample);
	u32 level = (ir_sample < 0) ? 0 : 1;

	for (i = RC5_MAX_SAME_BIT_CONT; i > 0; i--) {
		delta_time = time - (i*RC5_DEF_BIT_TIME) + RC5_TIME_GRANULARITY;
		if (delta_time < 0)
			continue; 
		if (delta_time > (2 * RC5_TIME_GRANULARITY)) {
			
			if (ir_pos == (RC5_WORD_LEN-1))
				
				RC5_PUSH_BIT(ir_word, level, ir_pos)

			if (ir_pos == RC5_WORD_LEN)
				sms_rc5_parse_word(coredev);
			else if (ir_pos) 
				sms_log("IR error parsing a word");

			ir_pos = 0;
			ir_word = 0;
		
			break;
		}
		
		for (j = 0 ; j < i ; j++)
			RC5_PUSH_BIT(ir_word, level, ir_pos)

		break;
	}
}

void sms_ir_event(struct smscore_device_t *coredev, const char *buf, int len)
{
	#define IR_DATA_RECEIVE_MAX_LEN	520 
	u32 i;
	enum ir_protocol ir_protocol =
			keyboard_layout_maps[coredev->ir.ir_kb_type]
					     .ir_protocol;
	s32 *samples;
	int count = len>>2;

	samples = (s32 *)buf;


	for (i = 0; i < count; i++)
		if (ir_protocol == IR_RC5)
			sms_rc5_accumulate_bits(coredev, samples[i]);
	
}

int sms_ir_init(struct smscore_device_t *coredev)
{
	struct input_dev *input_dev;

	sms_log("Allocating input device");
	input_dev = input_allocate_device();
	if (!input_dev)	{
		sms_err("Not enough memory");
		return -ENOMEM;
	}

	coredev->ir.input_dev = input_dev;
	coredev->ir.ir_kb_type =
		sms_get_board(smscore_get_board_id(coredev))->ir_kb_type;
	coredev->ir.keyboard_layout_map =
		keyboard_layout_maps[coredev->ir.ir_kb_type].
				keyboard_layout_map;
	sms_log("IR remote keyboard type is %d", coredev->ir.ir_kb_type);

	coredev->ir.controller = 0;	
	coredev->ir.timeout = IR_DEFAULT_TIMEOUT;
	sms_log("IR port %d, timeout %d ms",
			coredev->ir.controller, coredev->ir.timeout);

	snprintf(coredev->ir.name,
				IR_DEV_NAME_MAX_LEN,
				"SMS IR w/kbd type %d",
				coredev->ir.ir_kb_type);
	input_dev->name = coredev->ir.name;
	input_dev->phys = coredev->ir.name;
	input_dev->dev.parent = coredev->device;


	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	input_dev->keybit[BIT_WORD(BTN_0)] = BIT_MASK(BTN_0);

	sms_log("Input device (IR) %s is set for key events", input_dev->name);

	if (input_register_device(input_dev)) {
		sms_err("Failed to register device");
		input_free_device(input_dev);
		return -EACCES;
	}

	return 0;
}

void sms_ir_exit(struct smscore_device_t *coredev)
{
	if (coredev->ir.input_dev)
		input_unregister_device(coredev->ir.input_dev);

	sms_log("");
}
