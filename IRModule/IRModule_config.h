#ifndef IRModule_config_H__
#define IRModule_config_H__

#define I2C_SLAVE_ADDRESS 0x4
enum TVCOMAND {
TVCOMAND_power,
TVCOMAND_changeinput,
TVCOMAND_set3d,
TVCOMAND_aspect,
TVCOMAND_sendcode,
};

#ifdef IS_IR_SLAVE

#define SENDFUNC(code) sendKoganCode(&irsend, code)

#define TVCODE_POWER 0x20B
#define TVCODE_INPUT 0x21C
#define TVCODE_UP 0x22B
#define TVCODE_DOWN 0x22C
#define TVCODE_LEFT 0x22D
#define TVCODE_RIGHT 0x22E
#define TVCODE_DTV 0x232
#define TVCODE_MENU 0x215
#define TVCODE_ENTER 0x22F
#define TVCODE_ASPECT 0x231
#define TVCODE_EXIT 0x230
#define TVCODE_3D 0x233

#endif//IS_IR_SLAVE

#endif // IRModule_config_H__
