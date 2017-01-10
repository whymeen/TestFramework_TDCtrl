#include "dhTCP/networktcpclient.h"
#include <afxmt.h>
#include <vector>
#include "afxwin.h"
#include "afxcmn.h"
#include "objectBase.h"
#include "ObjectMananger.h"
#include "ThreadFunc.h"

//#define NETWORK_MAXSIZE			40000
#define FRAME_30HZ				33

#pragma once

struct PosData
{
	int time;

	double x;
	double y;
	double z;

	double h;
	double p;
	double r;
};

class TCPFunc
{
public:
	TCPFunc();
	~TCPFunc();


public:
	void initNetwork();		// 네트워크 초기화
	void initBuf();


	void SendEventData(char* packetData, int packetDataSize);
	void SendUpdateData(char* packetData, int packetDataSize);

	void close();

	int GetTimeStamp() { return m_iTimeStamp; }

	static void getUpdateMsg(char *msg, void *param);	// 네트워크정보 수신 함수

	void readConfigure(void);

	static TCPFunc* getinstance() { return m_instance; }	// MainFrame 인스턴스 반환함수

public:
	ThreadFunc m_Thread;
	static TCPFunc*	m_instance;
	CObjectMananger m_pObjectManager;
	CNetworkTCPClient *m_pTCPClient;
	int m_iCurSystemCode;
	unsigned int m_iTimeStamp;
	CString m_cstmp;

	CStatic m_cvTxtConnStatus;
	
	char m_chBuf[NETWORK_MAXSIZE + 10000];
	int m_ichBufIndex;
	int m_ipreRcvSize;

	PosData	oldPos;
	bool m_bBufPoolFlag[5];
	PosData m_stBufPool[5];
	double m_dSimTime;

	// read config value
	unsigned char ip[4];
	unsigned short port1, port2;

	std::vector<PosData> m_vListData;

	void initBufPool();
	void updateBufPool(PosData *curPos);



	bool getCheckTimeRange(double curTime);

	int m_iCurbufPoolsize;
	int getBufPoolSize();

	void onObjectCtrl(EVENT_OBJECT_CONTROL* rcvData);

	void onTorpedoAdd(int parentID, SUB_OBJECT_INFO* rcvData);
	void onDecoyAdd(int parentID, SUB_OBJECT_INFO* rcvData);

	void onSimulationCtrl(EVENT_SIMULATION_CONTROL* rcvData);
};

