
// �޽��� �ڵ� [8/31/2010 boxface]
//////////////////////////////////////////////////////////////////////////////////
// V 0.9 
//  ������ : 2010. 09. 05 , �ۼ��� : ��������
//  - #define MSG_CODE_EVENT_SIM_CONTROL_0xA7		0xA7
//      => #define MSG_CODE_EVENT_SIM_CONTROL_0x93		0x93
//  - #define MSG_CODE_EVENT_SIM_CONTROL_REPLY_0xA8	0xA8
//      => #define MSG_CODE_EVENT_SIM_CONTROL_REPLY_0xA7	0xA7
//////////////////////////////////////////////////////////////////////////



// ������� -> ��ü �ý���
#define MSG_CODE_EVENT_SIMULATION_CONTROL_0x11				0x11
#define MSG_CODE_EVENT_SCENARIO_SETUP_0x12					0x12
#define MSG_CODE_EVENT_OBJECT_CONTROL_0x13					0x13
#define MSG_CODE_EVENT_TORPEDO_SETUP_0x14					0x14
#define MSG_CODE_EVENT_DECOY_SETUP_0x15						0x15
#define MSG_CODE_EVENT_SENSOR_SETUP_0x16					0x16
#define MSG_CODE_EVENT_ENV_SETUP_0x17						0x17
#define MSG_CODE_EVENT_LOGIN_0x18							0x18

// ��ü �ý��� -> �������
#define MSG_CODE_UPDATE_BIT_0x21							0x21
#define MSG_CODE_EVENT_SCENARIO_SETUP_REPLY_0x22			0x22
#define MSG_CODE_UPDATE_OBJECT_CONTROL_0x23					0x23
#define MSG_CODE_EVENT_LOGIN_REPLY_0x24						0x24
#define MSG_CODE_EVENT_ACK_0x2F								0x2F

// ���尡��ȭ -> ������ü���Ǳ�
#define MSG_CODE_EVENT_TORPEDO_IMPACT_0x31					0x31

// ����� ����ü�� -> �����߾�� & ������ü����
#define MSG_CODE_EVENT_TORPEDO_PRESET_0x51					0x51
//#define MSG_CODE_EVENT_TORPEDO_FIRE_0x52					0x52	// ������ [9/13/2010 boxface]
//#define MSG_CODE_EVENT_TORPEDO_CONTROL_0x53				0x53	// ������ [8/20/2010 boxface]

// �����߾�� & ������ü���� -> ����� ����ü��
#define MSG_CODE_EVENT_TORPEDO_PRESET_REPLY_0x61			0x61
#define MSG_CODE_UPDATE_TORPEDO_STATUS_0x62					0x62
#define MSG_CODE_UPDATE_TORPEDO_TACTICAL_DISPLAY_0x63				0x63
#define MSG_CODE_UPDATE_TORPEDO_TACTICAL_WPA_DISPLAY_0x64			0x64


// ǥ���� ����ü�� -> ������ü����
#define MSG_CODE_EVENT_DECOY_PRESET_0x71					0x71
#define MSG_CODE_EVENT_DECOY_FIRE_0x72						0x72
#define MSG_CODE_EVENT_DECOY_CONTROL_0x73					0x73

// ������ü���� -> ǥ���� ����ü��
#define MSG_CODE_EVENT_DECOY_PRESET_REPLY_0x81				0x81

// ����� ����ü����Ǳ�(����) -> ����� ����ü����Ǳ�(��)
#define MSG_CODE_EVENT_TUBE_ASSIGNMENT_0x91				0x91
#define MSG_CODE_EVENT_TORPEDO_SIM_PRESET_0x92				0x92
#define MSG_CODE_EVENT_SIM_CONTROL_0x93					0x93
#define MSG_CODE_EVENT_ONWSHIP_CONTROL_0x94				0x94
#define MSG_CODE_EVENT_TOUCH_PANEL_CONTROL_0x95				0x95


// ����� ����ü����Ǳ�(��) -> ����� ����ü����Ǳ�(����)
#define MSG_CODE_EVENT_TUBE_ASSIGNMENT_REPLY_0xA1		0xA1
#define MSG_CODE_UPDATE_TUBE_STATUS_0xA2					0xA2
#define MSG_CODE_EVENT_TORPEDO_SIM_PRESET_REPLY_0xA3		0xA3
#define MSG_CODE_UPDATE_TORPEDO_SIM_STATUS_0xA4				0xA4
#define MSG_CODE_UPDATE_OWNSHIP_STATUS_0xA5					0xA5
#define MSG_CODE_UPDATE_TARGETSHIP_STATUS_0xA6				0xA6
#define MSG_CODE_EVENT_SIM_CONTROL_REPLY_0xA7				0xA7
#define MSG_CODE_EVENT_OWNSHIP_CONTROL_REPLY_0xA8				0xA8
#define MSG_CODE_UPDATE_TORPEDO_TARGET_0xA9				0xA9
#define MSG_CODE_UPDATE_TORPEDO_SONAR_0xAA				0xAA
#define MSG_CODE_UPDATE_OWNSHIP_SONAR_0xAB				0xAB
#define MSG_CODE_UPDATE_TORPEDO_SIM_TACTICAL_DISPLAY_0xAC				0xAC
#define MSG_CODE_UPDATE_TORPEDO_SIM_TACTICAL_WPA_DISPLAY_0xAD				0xAD
//////////////////////////////////////////////////////////////////////////