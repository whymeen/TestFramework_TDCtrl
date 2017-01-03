#include "stdafx.h"
#include "TCPFunc.h"
#include "TestFramework_TDCtrlDlg.h"
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

	//pMF->UpdateMsgParser(msg);
	int bufIndex = 0;
	double dTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	_ICD_HEADER header;

	memcpy(&header, &msg[bufIndex], sizeof(_ICD_HEADER));
	dTimeStamp = header.H_Timestamp;
	iLength = header.H_Length;

	if (header.H_Sender_Equip_Code == pMF->m_iCurSystemCode)
	{
		//dhPrint("내가 보낸 정보를 수신하였다. !!\n");
		return;
	}

	//dhPrint("iTimeStamp:%lf, iLength:%d\n", dTimeStamp, iLength);

	bufIndex += sizeof(_ICD_HEADER);

	unsigned char c, l;
	memcpy(&c, &msg[bufIndex], 1);
	memcpy(&l, &msg[bufIndex + 1], 1);

	type = c;
	length = l;

	switch (type)
	{
		// 시뮬레이션 제어 [8/12/2010 boxface]
	case MSG_CODE_EVENT_SIMULATION_CONTROL_0x11:
	{
		//////////////////////////////////////////////////////////////////////////

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_SIMULATION_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_SIMULATION_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_SIMULATION_CONTROL));

		//pMF->onSimulationCtrl(&rcvData);

		bufIndex += sizeof(EVENT_SIMULATION_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, control_code:%d, simspeed:%d\n", rcvData.type, rcvData.length, rcvData.control_code, rcvData.simspeed);
	}
	break;
	// 객체설정 [8/12/2010 boxface]
	case MSG_CODE_EVENT_OBJECT_SETUP_0x12:
	{

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_OBJECT_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_OBJECT_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_OBJECT_CONTROL));

		pMF->onObjectCtrl(&rcvData);

		bufIndex += sizeof(EVENT_OBJECT_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, objectID:%d, objectType:%d\n", rcvData.type, rcvData.length, rcvData.objectID, rcvData.objectType);
		//dhPrint("x:%f, y:%f, z:%f, h:%f, p:%f, r:%f\n", rcvData.x, rcvData.y, rcvData.z, rcvData.h, rcvData.p, rcvData.r);
	}
	break;
	}

}

void TCPFunc::EventMsgParser(char *msg, int dataSize)		// 네트워크정보 수신정보 처리
{

	int bufIndex = 0;
	double dTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	_ICD_HEADER header;

	memcpy(&header, &msg[bufIndex], sizeof(_ICD_HEADER));
	dTimeStamp = header.H_Timestamp;
	iLength = header.H_Length;

	if (header.H_Sender_Equip_Code == m_iCurSystemCode)
	{
		//dhPrint("내가 보낸 정보를 수신하였다. !!\n");
		return;
	}

	//dhPrint("iTimeStamp:%lf, iLength:%d\n", dTimeStamp, iLength);

	bufIndex += sizeof(_ICD_HEADER);

	unsigned char c, l;
	memcpy(&c, &msg[bufIndex], 1);
	memcpy(&l, &msg[bufIndex + 1], 1);

	type = c;
	length = l;

	switch (type)
	{
		// 시뮬레이션 제어 [8/12/2010 boxface]
	case MSG_CODE_EVENT_SIMULATION_CONTROL_0x11:
	{
		//////////////////////////////////////////////////////////////////////////

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_SIMULATION_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_SIMULATION_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_SIMULATION_CONTROL));

		//pMF->onSimulationCtrl(&rcvData);

		bufIndex += sizeof(EVENT_SIMULATION_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, control_code:%d, simspeed:%d\n", rcvData.type, rcvData.length, rcvData.control_code, rcvData.simspeed);
	}
	break;
	// 객체설정 [8/12/2010 boxface]
	case MSG_CODE_EVENT_OBJECT_SETUP_0x12:
	{

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_OBJECT_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_OBJECT_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_OBJECT_CONTROL));

		onObjectCtrl(&rcvData);

		bufIndex += sizeof(EVENT_OBJECT_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, objectID:%d, objectType:%d\n", rcvData.type, rcvData.length, rcvData.objectID, rcvData.objectType);
		//dhPrint("x:%f, y:%f, z:%f, h:%f, p:%f, r:%f\n", rcvData.x, rcvData.y, rcvData.z, rcvData.h, rcvData.p, rcvData.r);
	}
	break;
	}
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


void TCPFunc::getNetworkMsg(char *msg, void *param)
{
	TCPFunc *pMF = (TCPFunc *)param;

	int bufIndex = 0;
	double dTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	_ICD_HEADER header;

	memcpy(&header, &msg[bufIndex], sizeof(_ICD_HEADER));
	dTimeStamp = header.H_Timestamp;
	iLength = header.H_Length;

	if (header.H_Sender_Equip_Code == pMF->m_iCurSystemCode)
	{
		//dhPrint("내가 보낸 정보를 수신하였다. !!\n");
		return;
	}

	//dhPrint("iTimeStamp:%lf, iLength:%d\n", dTimeStamp, iLength);

	bufIndex += sizeof(_ICD_HEADER);

	unsigned char c, l;
	memcpy(&c, &msg[bufIndex], 1);
	memcpy(&l, &msg[bufIndex + 1], 1);

	type = c;
	length = l;

	switch (type)
	{
		// 시뮬레이션 제어 [8/12/2010 boxface]
	case MSG_CODE_EVENT_SIMULATION_CONTROL_0x11:
	{
		//////////////////////////////////////////////////////////////////////////

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_SIMULATION_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_SIMULATION_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_SIMULATION_CONTROL));

		//pMF->onSimulationCtrl(&rcvData);

		bufIndex += sizeof(EVENT_SIMULATION_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, control_code:%d, simspeed:%d\n", rcvData.type, rcvData.length, rcvData.control_code, rcvData.simspeed);
	}
	break;
	// 객체설정 [8/12/2010 boxface]
	case MSG_CODE_EVENT_OBJECT_SETUP_0x12:
	{

		// 수신된 정보 처리 [7/6/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		EVENT_OBJECT_CONTROL rcvData;
		memset(&rcvData, 0x00, sizeof(EVENT_OBJECT_CONTROL));
		memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_OBJECT_CONTROL));

		pMF->onObjectCtrl(&rcvData);

		bufIndex += sizeof(EVENT_OBJECT_CONTROL);

		//////////////////////////////////////////////////////////////////////////
		//dhPrint("type:%#x, length:%d, objectID:%d, objectType:%d\n", rcvData.type, rcvData.length, rcvData.objectID, rcvData.objectType);
		//dhPrint("x:%f, y:%f, z:%f, h:%f, p:%f, r:%f\n", rcvData.x, rcvData.y, rcvData.z, rcvData.h, rcvData.p, rcvData.r);
	}
	break;
	// 어뢰무장설정 [8/12/2010 boxface]
	/*case MSG_CODE_EVENT_TORPEDO_SETUP_0x14:
	{
	// ack 신호 송신 [7/6/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	pMF->SendAckMsg(dTimeStamp);
	//////////////////////////////////////////////////////////////////////////

	// 수신된 정보 처리 [7/6/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_TORPEDO_SETUP rcvData;
	memset(&rcvData, 0x00, sizeof(EVENT_TORPEDO_SETUP));
	memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_TORPEDO_SETUP));

	SUB_OBJECT_INFO rcvData0;
	memset(&rcvData0, 0x00, sizeof(SUB_OBJECT_INFO));
	rcvData0.objectID = rcvData.objectID;
	rcvData0.imageType = rcvData.imageType;
	if (rcvData.torpedoType == 0)		rcvData0.objectType = OBJECT_TYPE_TORPEDO;
	else								rcvData0.objectType = OBJECT_TYPE_TORPEDO;

	pMF->onTorpedoAdd(rcvData.parentID, &rcvData0);

	bufIndex += sizeof(EVENT_TORPEDO_SETUP);

	//////////////////////////////////////////////////////////////////////////
	dhPrint("type:%#x, length:%d, objectID:%d \n", rcvData.type, rcvData.length, rcvData.objectID);
	//dhPrint("x:%f, y:%f, z:%f, h:%f, p:%f, r:%f\n", rcvData.x, rcvData.y, rcvData.z, rcvData.h, rcvData.p, rcvData.r);
	}
	break;
	// 기만기설정 [8/12/2010 boxface]
	case MSG_CODE_EVENT_DECOY_SETUP_0x15:
	{
	// ack 신호 송신 [7/6/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	pMF->SendAckMsg(dTimeStamp);
	//////////////////////////////////////////////////////////////////////////

	// 수신된 정보 처리 [7/6/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_DECOY_SETUP rcvData;
	memset(&rcvData, 0x00, sizeof(EVENT_DECOY_SETUP));
	memcpy(&rcvData, &msg[bufIndex], sizeof(EVENT_DECOY_SETUP));

	SUB_OBJECT_INFO rcvData0;
	memset(&rcvData0, 0x00, sizeof(SUB_OBJECT_INFO));
	rcvData0.objectID = rcvData.objectID;
	rcvData0.imageType = rcvData.imageType;
	if (rcvData.decoyType == 0)		rcvData0.objectType = OBJECT_TYPE_DECOY;
	else							rcvData0.objectType = OBJECT_TYPE_DECOY;

	pMF->onDecoyAdd(rcvData.parentID, &rcvData0);

	bufIndex += sizeof(EVENT_DECOY_SETUP);

	//////////////////////////////////////////////////////////////////////////
	dhPrint("type:%#x, length:%d, objectID:%d\n", rcvData.type, rcvData.length, rcvData.objectID);
	//dhPrint("x:%f, y:%f, z:%f, h:%f, p:%f, r:%f\n", rcvData.x, rcvData.y, rcvData.z, rcvData.h, rcvData.p, rcvData.r);
	}
	break;
	// 센서설정 [8/12/2010 boxface]
	default:
	dhPrint("unknown message 신호 수신 type[%d], length:[%d]\n", type, length);
	break;*/
	}
}





void TCPFunc::onObjectCtrl(EVENT_OBJECT_CONTROL* rcvData)
{
	CTestFramework_TDCtrlDlg* pMainDlg = (CTestFramework_TDCtrlDlg*)::AfxGetMainWnd();
	switch (rcvData->mode)
	{
	case OBJECT_CTRL_CREATE:
	{
		CObjectBase pObject;

		pObject.setObjectID(rcvData->objectID);
		pObject.setObjectType(rcvData->type);
		pObject.setObjectStatus(rcvData->status);
		pObject.setIFF(rcvData->IFF);

		double x, y, z, h, p, r;



		x = rcvData->x;
		y = rcvData->y;
		z = rcvData->z;
		h = rcvData->h;
		p = rcvData->p;
		r = rcvData->r;

		double speed, course, latitude, longitude, depth;
		speed = rcvData->speed;
		course = rcvData->course;
		latitude = rcvData->latitude;
		longitude = rcvData->longitude;
		depth = rcvData->depth;

		pObject.setInitPosition(x, y, z);
		pObject.setInitDirection(h, p, r);
		pObject.setTranslate(x, y, z);
		pObject.setRotate(h, p, r);

		// Object ID 중복 채크 [7/8/2010 boxface]
		if (m_pObjectManager.checkObjectID(rcvData->objectID) != true)
		{
			// 객체관리 클래스에 전달 [7/8/2010 boxface]
			m_pObjectManager.addObject(pObject);

			// GUI 정보 업데이트 [6/15/2010 boxface]
			//////////////////////////////////////////////////////////////////////////
			pMainDlg->addObject(rcvData->objectID);
		}
		else
		{
			//dhPrint("현재 수신받은 객체 정보는 이미 존재하는 ID[%d] 임!!!\n", rcvData->objectID);
		}
	}
	break;
	case OBJECT_CTRL_UPDATE:
	{
		CObjectBase pObject;

		pObject.setObjectID(rcvData->objectID);
		pObject.setObjectType(rcvData->type);
		pObject.setObjectStatus(rcvData->status);
		pObject.setIFF(rcvData->IFF);

		double x, y, z, h, p, r;

		x = 0.0;
		y = 0.0;
		z = 0.0;
		h = 0.0;
		p = 0.0;
		r = 0.0;

		//x = rcvData->x;
		//y = rcvData->y;
		//z = rcvData->z;
		//h = rcvData->h;
		//p = rcvData->p;
		//r = rcvData->r;

		double speed, course, latitude, longitude, depth;
		speed = rcvData->speed;
		course = rcvData->course;
		latitude = rcvData->latitude;
		longitude = rcvData->longitude;
		depth = rcvData->depth;

		pObject.setInitPosition(x, y, z);
		pObject.setInitDirection(h, p, r);
		pObject.setTranslate(x, y, z);
		pObject.setRotate(h, p, r);

		// 객체관리 클래스에 전달 [7/8/2010 boxface]
		m_pObjectManager.updateObject(pObject);
	}
	break;
	case OBJECT_CTRL_DELETE:
	{
		// 객체관리 클래스에 전달 [7/8/2010 boxface]
		m_pObjectManager.delObject(rcvData->objectID);

		// GUI 정보 업데이트 [6/15/2010 boxface]
		//////////////////////////////////////////////////////////////////////////
		//pMainDlg->deleteObject(rcvData->objectID);
	}
	break;
	default:
		//dhPrint("CMainFrame::onObjectCtrl invalid data !!!\n");
		break;
	}
}