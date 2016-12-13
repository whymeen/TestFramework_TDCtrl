
//#include "common.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 4267)	//'�μ�' : 'size_t'���� 'DWORD'(��)�� ��ȯ�ϸ鼭 �����Ͱ� �սǵ� �� �ֽ��ϴ�.
#pragma warning (disable: 4800)	// 'BOOL' : 'true' �Ǵ� 'false'�� bool ���� �����ϰ� �ֽ��ϴ�(���� ���).

#include <string>

//#include "dhutil/dhTextFileIO.h"
//#include "dhutil/dhXMLParser.h"
//#include "dhutil/dhException.h"
//#include "dhutil/dhPrinter.h"

//#include "EASPrinter.h"
//#include "EASDefBase.h"

#define NETWORK_MAXSIZE		3000

#define THE_NUMBER_OF_TIMES_ABOUT_SENDING_MESSAGE	5

#define CONFIGFILE_NAME		"../data/config.xml"

#define FRAME_3_75HZ			266
#define FRAME_7_5HZ				133
#define FRAME_15HZ				66
#define FRAME_30HZ				33
#define FRAME_60HZ				16
#define FRAME_120HZ				8
#define FRAME_240HZ				4

#define SURFACESHIP_ID			1000
#define SUBMARINE_ID			2000
#define TORPEDO_ID				3000
#define DECOY_ID				4000


enum SIMSPEED_MODE
{
	SPMODE_0_8,
	SPMODE_0_4,
	SPMODE_0_2,
	SPMODE_1,
	SPMODE_2,
	SPMODE_4,
	SPMODE_8,

	SPMODE_NUM
};

enum SIMCTRL_MODE
{
	SIMCTRL_STANDBY,
	SIMCTRL_START,
	SIMCTRL_PAUSE,
	SIMCTRL_STOP,
	SIMCTRL_MODE_SIMSPEED,

	SIMCTRL_NUM
};

enum OBJECT_STATUS_MODE
{
	OBJECT_STATUS_STANDBY,
	OBJECT_STATUS_ENABLE,
	OBJECT_STATUS_DISABLE,

	OBJECT_STATUS_NUM
};

enum OBJECT_CTRL_MODE
{
	OBJECT_CTRL_CREATE,
	OBJECT_CTRL_UPDATE,
	OBJECT_CTRL_DELETE,

	OBJECT_CTRL_NUM
};


enum OBJECT_TYPE
{
	OBJECT_TYPE_INIT,
	OBJECT_TYPE_SURFACESHIP,
	OBJECT_TYPE_SUBMARINE,
	OBJECT_TYPE_TORPEDO,
	OBJECT_TYPE_DECOY,

	OBJECT_TYPE_NUM
};

enum EQUIP_CODE
{
	EQUIP_CODE_ALL,
	EQUIP_CODE_OPERATION_CONTROL,
	EQUIP_CODE_BATTLEFIELD_DISPLAY,
	EQUIP_CODE_OWNSHIP,
	EQUIP_CODE_NEW_HEAVY_TORPEDO,
	EQUIP_CODE_TARGETSHIP,
	EQUIP_CODE_TACTICAL_OBJECT,

	EQUIP_CODE_NUM
};

enum IFF_CODE
{
	IFF_FRIEND,
	IFF_ENEMY,

	IFF__CODE
};



class Common
{
public:
	Common(void);
	~Common(void);

	// ���ڿ� ��ȯ �Լ� [3/31/2007 boxface]
//	static CString		stdToCString(std::string s)	{return s.c_str();}
//	static std::string		CStringTostd(CString c)	{return (LPCTSTR)c;}

//	static char*		CStringTochar(CString c)	{return (LPSTR)(LPCSTR)c;}
//	static char*		stdTochar(std::string s)	{CString cst = s.c_str();		return (LPSTR)(LPCSTR)cst;}

	static int			sizeOfCString(CString c)		{return c.GetLength();}
	static int			sizeOfstdString(std::string s)		{return (int)s.size();}

	// ���� ��ȯ [8/20/2007 boxface]
	static CString		SetNamedColor(COLORREF col);
	static char*		SetNamedColorToChar(COLORREF col);		
	static COLORREF		GetColorCSName(const CString &csCol);
	static COLORREF		GetColorStdName(const std::string &sCol);

	static CString	GetSystemName(int systemCode)
	{
		CString SystemName;
		switch(systemCode)
		{
		case EQUIP_CODE_OPERATION_CONTROL:			SystemName="���������";			break;
		case EQUIP_CODE_BATTLEFIELD_DISPLAY:		SystemName="���尡��ȭ";			break;
		case EQUIP_CODE_OWNSHIP:					SystemName="����� ���Ǳ�";			break;
		case EQUIP_CODE_NEW_HEAVY_TORPEDO:		    SystemName="�����߾�� ���Ǳ�";		break;
		case EQUIP_CODE_TARGETSHIP:					SystemName="ǥ���� ���Ǳ�";			break;
		case EQUIP_CODE_TACTICAL_OBJECT:			SystemName="������ü ���Ǳ�";		break;
		default:								    SystemName="unknown system Code";	break;
		}
		return SystemName;
	}

	static double DegreetoDMS(double Degree, double Minute, double Second)
	{
		double tempMin;
		double tempDegree;
		
		if (Second != 0)		tempMin = Minute + (Second / 60);
		else					tempMin = Minute;

		if (tempMin != 0)		tempDegree = Degree + (tempMin / 60);
		else					tempDegree = Degree;

		return tempDegree;
	}

	static double CutDegreet(char *temp)
	{
		double de, mi, se;
		char *p;
		p = strtok(temp, "-");
		de = atof(p);
		p = strtok(NULL, "-");
		mi = atof(p);
		p = strtok(NULL, "-");
		se = atof(p);

		return DegreetoDMS(de, mi, se);
	}

	static void DegreetoDMS(double dDegree, int &iDeg, int &iMin, int &iSec)
	{
		double dMin;

		iDeg = (int)dDegree;
		dMin = (dDegree - iDeg)*60.0;
		iMin = (int)dMin;
		iSec = (int)((dMin - iMin)*60.0);
	}
};
