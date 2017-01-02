#include "stdafx.h"
#include "TCPFunc.h"

#include <fstream>
#include <time.h>

TCPFunc::TCPFunc()
{
	m_pTCPClient = NULL;

	m_iCurSystemCode = 2;		// 전장가시화 코드값

	initNetwork();

	// 연결상태 체크
	//SetTimer(0, 1000, NULL);
	//SetTimer(1, 10, NULL);

	initBuf();
	m_ipreRcvSize = 0;
	m_ichBufIndex = 0;

	// 보간법 관련 버퍼 초기화
	initBufPool();

	m_dSimTime = 1.01;
}


TCPFunc::~TCPFunc()
{
}


void TCPFunc::initNetwork()
{
	readConfigure();
	char iip[20];
	sprintf(iip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	//m_pTCPClient = new CNetworkTCPClient(iip , port1);
	m_pTCPClient = new CNetworkTCPClient("127.0.0.1", 5100);
	m_pTCPClient->addCallback(getUpdateMsg, this);

	initBuf();
}

void TCPFunc::initBuf()
{
	m_ichBufIndex = 0;		// 받은정보중 데이터가 있는부분
	m_ipreRcvSize = 0;		// 다음 패킷 받을때 붙여야 할 부분

	memset(&m_chBuf, 0x00, NETWORK_MAXSIZE);
}

void TCPFunc::SendEventData(char* packetData, int packetDataSize)
{
	char sendBuf[NETWORK_MAXSIZE];

	CODE_HEADER header;
	memset(&header, 0x00, sizeof(CODE_HEADER));
	int headsize = sizeof(CODE_HEADER);
	int totsize = headsize + packetDataSize;

	//header.C_TimeStamp = GetTimeStamp();
	//header.C_Length = totsize / 4;
	//header.C_SenderCode = m_iCurSystemCode;

	//header.C_TImeHour = 7;
	//header.C_TImeMinute = 12;
	//header.C_TImeSec = 22;
	//header.C_TImeMSec = 111;

	memcpy(&sendBuf, (char*)&header, headsize);						// 헤더 붙이기 
	memcpy(&sendBuf[headsize], (char*)packetData, packetDataSize);		// 데이터 불이기

																		//	dhPrint("packet size => H:%d, D:%d => total:%d, time:%d\n", headsize, packetDataSize, totsize, sizeof(header.H_Timestamp));

	if (m_pTCPClient->getConnectionState() == true)
	{
		m_pTCPClient->sendData(sendBuf, totsize);
	}
	else
	{
		TRACE("not connect a TCP/IP, then not sending data!!\n");
	}
}

void TCPFunc::SendUpdateData(char* packetData, int packetDataSize)
{
	char sendBuf[NETWORK_MAXSIZE];

	CODE_HEADER header;
	memset(&header, 0x00, sizeof(CODE_HEADER));
	int headsize = sizeof(CODE_HEADER);
	int totsize = headsize + packetDataSize;

//	header.C_TimeStamp = GetTimeStamp();
//	header.C_Length = totsize;
//	header.C_SenderCode = m_iCurSystemCode;

	memcpy(&sendBuf, (char*)&header, headsize);						// 헤더 붙이기 
	memcpy(&sendBuf[headsize], (char*)packetData, packetDataSize);		// 데이터 불이기

																		//	dhPrint("packet size => H:%d, D:%d => total:%d, time:%d\n", headsize, packetDataSize, totsize, sizeof(header.H_Timestamp));

	if (this == NULL)
	{
		TRACE("error => !!\n");
		return;
	}

	else
	{
		TRACE("not connect a TCP/IP, then not sending data!!\n");
	}
}

void TCPFunc::getEventMsg(char *msg, void *param, int dataSize)
{
	TCPFunc *pMF = (TCPFunc *)param;

	if (dataSize < 0 || pMF == NULL)
	{
		return;
	}

	pMF->EventMsgParser(msg, dataSize);
}

void TCPFunc::getUpdateMsg(char *msg, void *param)
{
	TCPFunc *pMF = (TCPFunc *)param;

	pMF->UpdateMsgParser(msg);
}

void TCPFunc::EventMsgParser(char *msg, int dataSize)		// 네트워크정보 수신정보 처리
{
	CString cstmp;
	int bufIndex = 0;
	int iTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	//////////////////////////////////////////////////////////////////////////
	if (m_ichBufIndex != 0)
	{
		initBuf();
	}

	// 임시 버퍼에 저장
	memcpy(&m_chBuf[m_ichBufIndex], &msg[bufIndex], dataSize);
	dataSize += m_ipreRcvSize;


	while (bufIndex < dataSize)
	{
		CODE_HEADER header;

		memcpy(&header, &m_chBuf[bufIndex], sizeof(CODE_HEADER));
	//	iTimeStamp = header.C_TimeStamp;
		iLength = header.C_Length * 4;

		// 패킷 분석 완료여부 판단
		if (iLength >(dataSize - bufIndex))
		{
			initBuf();
			m_ichBufIndex = dataSize - bufIndex;		// 받은정보중 데이터가 있는부분
			m_ipreRcvSize = iLength - m_ichBufIndex;	// 다음 패킷 받을때 붙여야 할 부분
			memcpy(&m_chBuf[0], &msg[bufIndex], dataSize - bufIndex);
		}

		cstmp.Format("rcvdata Size timestamp[%d], length:[%d:%d]\n", iTimeStamp, iLength, dataSize);
		recordMsg(cstmp);

		bufIndex += sizeof(CODE_HEADER);

		unsigned char c, l;
		memcpy(&c, &m_chBuf[bufIndex], 1);
		memcpy(&l, &m_chBuf[bufIndex + 1], 1);

		type = c;
		length = l;

		//TRACE("evenet message 신호 수신 type:[%#x], length:[%d] realSize[%d]\n", type, length, dataSize);
		cstmp.Format("evenet message 신호 수신 type:[%#x], length:[%d] realSize[%d]\n", type, length, dataSize);
		recordMsg(cstmp);

		switch (type)
		{
			// 시뮬레이션 제어 
		case MSG_CODE_EVENT_SIMULATION_CONTROL_0x11:
		{
			EVENT_SIMULATION_CONTROL rcvData;
			memset(&rcvData, 0x00, sizeof(EVENT_SIMULATION_CONTROL));
			memcpy(&rcvData, &m_chBuf[bufIndex], sizeof(EVENT_SIMULATION_CONTROL));

			bufIndex += sizeof(EVENT_SIMULATION_CONTROL);
		}
		break;
		case MSG_CODE_EVENT_OBJECT_SETUP_0x12:
		{
			EVENT_OBJECT_CONTROL rcvData;
			memset(&rcvData, 0x00, sizeof(EVENT_OBJECT_CONTROL));
			memcpy(&rcvData, &m_chBuf[bufIndex], sizeof(EVENT_OBJECT_CONTROL));

			/*cstmp.Format("EVENT_OBJECT_CONTROL [%d] type:[%#x], length:[%d], name[%s], mode:%d, (%f,%f,%f), (%f,%f,%f)\n",
				iTimeStamp, type, length, rcvData.object_ID, rcvData.object_Mode, rcvData.object_Status, rcvData.latitude, rcvData.longitude,
				rcvData.pitch, rcvData.roll, rcvData.yaw, rcvData.x, rcvData.y, rcvData.z);
			recordMsg(cstmp);*/

			bufIndex += sizeof(EVENT_OBJECT_CONTROL);
		}
		break;
		case MSG_CODE_EVENT_TORPEDO_SETUP_0x13:
		{
			/*S2VDS_EVENT_SIMULATION_CONTROL rcvData;
			memset(&rcvData, 0x00, sizeof(S2VDS_EVENT_SIMULATION_CONTROL));
			memcpy(&rcvData, &m_chBuf[bufIndex], sizeof(S2VDS_EVENT_SIMULATION_CONTROL));

			cstmp.Format("_S2VDS_EVENT_SIMULATION_CONTROL_0x23 [%d] type:[%#x], length:[%d], msg[%s]\n", iTimeStamp, type, length, rcvData.userMsg);
			recordMsg(cstmp);

			bufIndex += sizeof(S2VDS_EVENT_SIMULATION_CONTROL);*/
		}
		break;
		case MSG_CODE_EVENT_DECOY_SETUP_0x14:
		{
			/*S2VDS_EVENT_GUIDEDMISSILE_OBJECT_CONTROL rcvData;
			memset(&rcvData, 0x00, sizeof(S2VDS_EVENT_GUIDEDMISSILE_OBJECT_CONTROL));
			memcpy(&rcvData, &m_chBuf[bufIndex], sizeof(S2VDS_EVENT_GUIDEDMISSILE_OBJECT_CONTROL));

			bufIndex += sizeof(S2VDS_EVENT_GUIDEDMISSILE_OBJECT_CONTROL);*/
		}
		break;
		default:
			//TRACE("unknown message 신호 수신 type:[%#x], length:[%d]\n", type, length);
			cstmp.Format("unknown message 신호 수신 type:[%#x], length:[%d]\n", type, length);
			recordMsg(cstmp);

			initBuf();
			return;

			break;
		}
	}

	//process();
}

void TCPFunc::UpdateMsgParser(char *msg)
{
	CString cstmp;
	int bufIndex = 0;
	int iTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	CODE_HEADER header;

	memcpy(&header, &msg[bufIndex], sizeof(CODE_HEADER));
//	iTimeStamp = header.C_TimeStamp;
	iLength = header.C_Length;


	bufIndex += sizeof(CODE_HEADER);

	unsigned char c, l;
	memcpy(&c, &msg[bufIndex], 1);
	memcpy(&l, &msg[bufIndex + 1], 1);

	type = c;
	length = l;

	//TRACE("update message 신호 수신 [%d] type:[%#x], length:[%d]\n",iTimeStamp, type, length);

/*	switch (type)
	{
		// bit 신호 
	case _S2VDS_EVENT_GUIDEDMISSILE_OBJECT_SETUP_0x22:
	{

	}
	break;
	case _S2VDS_EVENT_GENERAL_OBJECT_SETUP_0x21:
	{
		S2VDS_EVENT_GENERAL_OBJECT_SETUP rcvData;
		memset(&rcvData, 0x00, sizeof(S2VDS_EVENT_GENERAL_OBJECT_SETUP));
		memcpy(&rcvData, &msg[bufIndex], sizeof(S2VDS_EVENT_GENERAL_OBJECT_SETUP));

		PosData curPos;
		memset(&curPos, 0x00, sizeof(PosData));

		curPos.time = iTimeStamp;
		curPos.x = rcvData.latitude;

		updateBufPool(&curPos);
		//cstmp.Format("MSG_CODE_UPDATE_OBJECT_CONTROL_0x21 [%d] type:[%#x], length:[%d], name[%s]\n", iTimeStamp, type, length, rcvData.Object_Name);
		cstmp.Format("S2VDS_EVENT_GENERAL_OBJECT_SETUP [%d] deg[%f] sin[%3.1f]=%f\n", iTimeStamp, rcvData.latitude, rcvData.latitude, rcvData.longitude);
		recordMsg(cstmp);
	}
	break;
	default:
		cstmp.Format("unknown message 신호 수신 type:[%#x], length:[%d]\n", type, length);
		recordMsg(cstmp);
		break;
	}*/
}

void TCPFunc::close()
{

	// 타이머 종료
//	KillTimer(0);
//	KillTimer(1);

	if (m_pTCPClient)
	{
		delete m_pTCPClient;
	}
	m_pTCPClient = NULL;
}

void TCPFunc::recordMsg(CString cstmp)
{
	m_cvListMsg.InsertString(0, cstmp);
}

void TCPFunc::initBufPool()
{
	memset(m_stBufPool, 0x00, sizeof(PosData) * 5);
	memset(m_bBufPoolFlag, 0x00, sizeof(bool) * 5);
	m_iCurbufPoolsize = 0;


	m_vListData.clear();
}

int TCPFunc::getBufPoolSize()
{
	m_iCurbufPoolsize = 0;

	for (int i = 0; i<5; i++)
	{
		if (m_bBufPoolFlag[i] == 1)
		{
			m_iCurbufPoolsize++;
		}
	}
	return m_iCurbufPoolsize;
}

bool TCPFunc::getCheckTimeRange(double curTime)
{
	if (m_stBufPool[0].time < curTime && m_stBufPool[4].time > curTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TCPFunc::updateBufPool(PosData *curPos)
{
	int i;
	for (i = 0; i<4; i++)
	{
		m_bBufPoolFlag[i] = m_bBufPoolFlag[i + 1];
		m_stBufPool[i].time = m_stBufPool[i + 1].time;

		m_stBufPool[i].x = m_stBufPool[i + 1].x;
		m_stBufPool[i].y = m_stBufPool[i + 1].y;
		m_stBufPool[i].z = m_stBufPool[i + 1].z;
		m_stBufPool[i].h = m_stBufPool[i + 1].h;
		m_stBufPool[i].p = m_stBufPool[i + 1].p;
		m_stBufPool[i].r = m_stBufPool[i + 1].r;
	}

	m_bBufPoolFlag[4] = 1;
	m_stBufPool[4].time = curPos->time;

	m_stBufPool[4].x = curPos->x;
	m_stBufPool[4].y = curPos->y;
	m_stBufPool[4].z = curPos->z;
	m_stBufPool[4].h = curPos->h;
	m_stBufPool[4].p = curPos->p;
	m_stBufPool[4].r = curPos->r;

	m_vListData.push_back(*curPos);
}


int TCPFunc::getCurPos(double interTime, PosData *InterPos)
{
	CString cstmp;

	if (getBufPoolSize() < 5)
	{
		cstmp.Format("아직 버퍼가 차지않았다. [%d]\n", getBufPoolSize());
		recordMsg(cstmp);
		return 0;
	}

	if (getCheckTimeRange(interTime) == false)
	{
		cstmp.Format("보간범위를 벗어난다 [%f] => [%d ~ %d]\n", interTime, m_stBufPool[0].time, m_stBufPool[4].time);
		recordMsg(cstmp);
		return -1;
	}

	double eT[5], eX[5];
	double intpx, intpDx;

	for (int i = 0; i <5; i++)
	{
		eT[i] = m_stBufPool[i].time;
		eX[i] = m_stBufPool[i].x;
	}

	InterPos->time = interTime;

	InterPos->x = intpx;
	InterPos->y = 0;
	InterPos->z = 0;
	InterPos->h = 0;
	InterPos->p = 0;
	InterPos->r = 0;

	return 1;
}

void TCPFunc::readConfigure(void)
{
	FILE *fp = fopen("configa.cfg", "r");
	if (fp)
	{
		char str[255];
		int a, b, c, d;
		fscanf(fp, "%s %d %d %d %d", str, &a, &b, &c, &d);
		ip[0] = (unsigned char)a;
		ip[1] = (unsigned char)b;
		ip[2] = (unsigned char)c;
		ip[3] = (unsigned char)d;

		fscanf(fp, "%s %d", str, &a);
		port1 = a;
		/*fscanf(fp , "%s %d" , str , &a);
		port2 = a;*/

		fclose(fp);
	}
}