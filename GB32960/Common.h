#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sstream>     // std::stringstream
#include "Log.h"
using namespace std;

typedef char                CHAR;
typedef signed char         INT8;
typedef unsigned char       UCHAR;
typedef unsigned char       UINT8;
typedef unsigned char       BYTE;
typedef short               SHORT;
typedef signed short        INT16;
typedef unsigned short      USHORT;
typedef unsigned short      UINT16;
typedef unsigned short      WORD;
typedef int                 INT;
typedef signed int          INT32;
typedef unsigned int        UINT;
typedef unsigned int        UINT32;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef unsigned long       DWORD;
typedef __int64             LONGLONG;
typedef __int64             LONG64;
typedef signed __int64      INT64;
typedef unsigned __int64    ULONGLONG;
typedef unsigned __int64    DWORDLONG;
typedef unsigned __int64    ULONG64;
typedef unsigned __int64    DWORD64;
typedef unsigned __int64    UINT64;

/** @brief ����ֵ(�ɹ�)																	*/
#define RET_SUCCESS				(0)

/** @brief ����ֵ(ʧ��)																	*/
#define RET_FAIL				(-1)

#define FREE_PTR(x)										\
{														\
	if (NULL != x)										\
	{													\
		delete x;										\
		x = NULL;										\
	}													\
}

#define FREE_ARR(x)										\
{														\
	if (NULL != x)										\
	{													\
		delete[] x;										\
		x = NULL;										\
	}													\
} 



#define _HTONS(x)	((((UINT16)(x) & 0xff00 )>> 8) | (((UINT16)(x) & 0xff) << 8))
#define _HTONL(x)	(((UINT32)(x) >> 24) | (((UINT32)(x) & 0xff0000) >> 8) | (((UINT32)(x) & 0xff) << 24) | (((UINT32)(x) & 0xff00) << 8))			


//��־���
#define LOG CLog::GetInstance().OutPutLog
#define LOGERR(x) CLog::GetInstance().OutPutLog("[%s %d] %s\n",__FUNCTION__,__LINE__,x)
#define LOGERR2(x,y) CLog::GetInstance().OutPutLog("[%s %d] %s %s\n",__FUNCTION__,__LINE__,x,y)
#define LOGSYSERR CLog::GetInstance().OutPutLog("[%s %d] error:%d\n",__FUNCTION__,__LINE__,GetLastError())

//����ת��Ϊ16���Ƹ�ʽ��ӡ
#define LOGHEX(data,len) CLog::GetInstance().OutPutLogHex(data,len, __FUNCTION__,__LINE__)


/**
* @brief eCommandType
*		�����ʾ����
*/
enum eCommandType
{
	eLogin				= 0x01,		/*��������*/
	eRealtimeData,					/*ʵʱ����*/
	eReissueData,					/*��������*/
	eLogout,						/*�����ǳ�*/
	eHeartbeat			= 0x07,		/*��������*/
	eTerminalTiming,				/*�ն�Уʱ*/
};



/**
* @brief eDataType
*		��������
*/
enum eDataType
{
	eBegin			= 0x00,			
	eVehicle		= 0x01,			/*��������*/
	eDrivingMotor,					/*�����������*/
	eFuelCell,						/*ȼ�ϵ������*/
	eEngine,						/*������������*/
	eVehiclePos,					/*����λ��*/
	eExtremum,						/*��ֵ����*/
	eAlarmInfo,						/*��������*/
	eVoltage,						/*��索��װ�õ�ѹ*/
	eTemperature,					/*��索��װ���¶�*/
	eEnd,
};

/**
* @brief eResponseType
*		�����ʾ����
*/
enum eResponseType
{
	eSuccess		 = 0x01,		/*������Ϣ��ȷ*/
	eFailure,						/*����δ�ɹ�*/
	eVinRepeat,						/*vin�ظ�����*/
	eCommand,						/*��ʾ���ݰ�Χ�����������Ӧ���*/
};

#pragma  pack (push,1)     //���ã���ָ��ԭ�����뷽ʽ����ѹջ�������µĶ��뷽ʽ����Ϊһ���ֽڶ���

/**
* @brief StruHDR
*		�ϱ�ƽ̨��24���ֽ�����ͷ
*/
typedef struct tagStruHDR
{
	//��ʼ��
	BYTE		m_StartCode[2];
	//�����ʶ
	BYTE		m_CommandCode;
	//Ӧ���ʶ
	BYTE		m_ResponsCode;
	//VIN
	BYTE		m_Vin[17];
	//���ܷ�ʽ
	BYTE		m_Encryption;
	//���ݳ���
	WORD		m_Len;
}StruHDR, *LPStruHDR;

/**
* @brief StruVehicle
*		��������
*/	
typedef struct tagStruVehicle
{
	//����״̬
	BYTE	m_VehicleState;						/*0x01:��������;0x02:Ϩ��;0x03:����״̬;0xFE:�쳣;0xFF:��Ч*/
	//���״̬
	BYTE	m_ChargeState;						/*0x01:ͣ�����;0x02:��ʻ���;0x03:δ���״̬;0x04:������;0xFF:��Ч*/
	//����ģʽ
	BYTE	m_DrivingMode;						/*0x01:����;0x02:�춯;0x03:ȼ��;0xFE:�쳣;0xFF:��Ч*/
	//����
	WORD	m_Speed;
	//���
	DWORD	m_Mileage;
	//�ܵ�ѹ
	WORD	m_Voltage;
	//�ܵ���
	WORD	m_Current;
	//SOC
	BYTE	m_Soc;
	//DC״̬
	BYTE	m_DCState;
	//��λ
	BYTE	m_Gear;
	//��Ե����
	WORD	m_Resistance;
	//����̤���г�ֵ
	BYTE	m_AcceleratorPedalValue;
	//�ƶ�̤��
	BYTE	m_BreakPedal;
}StruVehicle, *LPStruVehicle;



/**
* @brief StruMotor
*		�����������
*/
typedef struct tagStruMotor
{
	//������к�
	BYTE			m_Seq;
	//���״̬ 0x01:�ĵ�,0x02:����,0x03�ر�״̬��0x04:׼��״̬��0xFE:�쳣��0xFF:��Ч
	BYTE			m_State;
	//��������¶�
	BYTE			m_ControlTemperature;
	//���ת��
	WORD			m_RotateSpeed;
	//���Ť��
	WORD 			m_Torque;
	//����¶�
	BYTE  			m_Temperature;
	//��������������ѹ
	WORD 			m_InputVoltage;
	//���������ֱ��ĸ�ߵ���
	WORD 			m_Current;
}StruMotor, *LPStruMotor;

/**
* @brief StruDrivingMotor
*		�����������
*/
typedef struct tagStruDrivingMotor
{
	//�����������
	BYTE				m_Num;
	//�������������
	vector<StruMotor>	m_pElment;
}StruDrivingMotor, *LPStruDrivingMotor;


/**
* @brief StruFuelCell
*		ȼ�ϵ������
*/
typedef struct tagStruFuelCell
{
	//ȼ�ϵ�ص�ѹ
	WORD				m_Voltage;
	//ȼ�ϵ�ص���
	WORD				m_Current;
	//ȼ������
	WORD				m_Consumption;
	//ȼ�ϵ���¶�̽������ N ��Χ:0~65531
	WORD				m_ProbeSum;
	//̽���¶�ֵ 1*N
	vector<BYTE>		m_ProbeTempVec;
	//��ϵͳ������¶� ��Χ��0��2400
	WORD				m_MaxTemperature;
	//��ϵͳ������¶�̽�����
	BYTE				m_TempProbeNo;
	//��ϵͳ�����Ũ��
	WORD				m_MaxDensity;
	//��ϵͳ�����Ũ�ȴ���������
	BYTE				m_DenProbeNo;
	//��ϵͳ�����ѹ��
	WORD				m_MaxPressure;
	//��ϵͳ�����ѹ������������
	BYTE				m_PresProbeNo;
	//��ѹ DC/DC״̬
	BYTE				m_DCState;
}StruFuelCell, *LPStruFuelCell;


/**
* @brief StruEngine
*		����������
*/
typedef struct tagStruEngine
{
	//������״̬ 0x01:����״̬,0x02:�ر�״̬,0xFE:�쳣��0xFF:��Ч
	BYTE		m_State;
	//�����ٶ�
	WORD		m_CrankSpeed;
	//ȼ��������
	WORD		m_FuelConsumptionRate;
}StruEngine, *LPStruEngine;

/**
* @brief StruVehiclePos
*		����λ�����ݸ�ʽ
*/
typedef struct tagStruVehiclePos
{
	//��λ״̬
	BYTE		m_State;
	//����
	DWORD		m_Longitude;
	//γ��
	DWORD		m_Latitude;
}StruVehiclePos, *LPStruVehiclePos;

/**
* @brief StruExtremum
*		��ֵ���ݸ�ʽ
*/
typedef struct tagStruExtremum
{
	//��ߵ�ѹ�����ϵͳ��
	BYTE		m_MaxVolSubsystemNo;
	//��ߵ�ѹ��ص������
	BYTE		m_MaxVolBatteryNo;
	//��ص����ѹ���ֵ
	WORD		m_MaxVoltage;
	//��͵�ѹ�����ϵͳ��
	BYTE		m_MinVolSubsystemNo;
	//��͵�ѹ��ص������
	BYTE		m_MinVolBatteryNo;
	//��ص����ѹ���ֵ
	WORD		m_MinVoltage;
	//����¶���ϵͳ��
	BYTE		m_MaxTempSubsystemNo;
	//����¶�̽�����
	BYTE		m_MaxTempProbeNo;
	//����¶�ֵ
	BYTE		m_MaxTemperature;
	//����¶���ϵͳ��
	BYTE		m_MinTempSubsystemNo;
	//����¶�̽�����
	BYTE		m_MinTempProbeNo;
	//����¶�ֵ
	BYTE		m_MinTemperature;

}StruExtremum, *LPStruExtremum;


/**
* @brief StruFaultData
*		����������
*/
typedef struct tagStruFaultData
{
	WORD	m_ErrorCode;
	WORD	m_Canid;
	BYTE	m_RawPacket[8];
}StruFaultData,*LPStruFaultData;


/**
* @brief StruAlarmInfo
*		�������ݸ�ʽ
*/
typedef struct tagStruAlarmInfo
{
	//������ߵȼ�
	BYTE			m_MaxAlarmLevel;
	//ͨ�ñ�����־
	DWORD			m_ComAlarmMark;
	//�ɳ�索��װ�ù������� N1
	BYTE			m_ChargeKitFaultSum;
	//�ɳ�索��װ�ù��ϴ����б� 4*N1
	vector<StruFaultData>	m_ChargeKitFaultCodeList;
	//��������������� N2
	BYTE			m_MotorFaultSum;
	//������������������ϴ����б� 4*N2
	vector<StruFaultData>	m_MotorFaultCodeList;
	//�������������� N3
	BYTE			m_EngineFaultSum;
	//�����������������ϴ����б� 4*N3
	vector<DWORD>	m_EngineFaultCodeList;
	//������������ N4
	BYTE			m_OhterFaultSum;
	//�����������������ϴ����б� 4*N4
	vector<StruFaultData>	m_OtherFaultCodeList;


}StruAlarmInfo, *LPStruAlarmInfo;

/**
* @brief StruSubVoltage
*		��索����ϵͳ��ѹ���ݸ�ʽ
*/
typedef struct tagStruSubVoltage
{
	//���
	BYTE			m_Sequence;
	//��索��װ�õ�ѹ
	WORD			m_Voltage;
	//��索��װ�õ���
	WORD			m_Current;
	//����������
	WORD			m_BatterySum;
	//��֡��ʼ������
	WORD			m_FrameBatterySeq;
	//��֡���������� m(hex),��Χ��1-200
	BYTE			m_FrameBatterySum;
	//�����ص�ѹ	2*m,��Χ��0V��60.000V
	vector<WORD>	m_pSingleBatteryVoltage;
}StruSubVoltage, *LPStruSubVoltage;

/**
* @brief StruVoltage
*		��索��װ�õ�ѹ���ݸ�ʽ
*/
typedef struct tagStruVoltage
{
	//��ϵͳ����
	BYTE					m_Num;
	//������ϵͳ��
	vector<StruSubVoltage>	m_pElment;
}StruVoltage, *LPStruVoltage;


/**
* @brief StruSubTemperature
*		��索����ϵͳ�¶����ݸ�ʽ
*/
typedef struct tagStruSubTemperature
{
	//���
	BYTE			m_Sequence;
	//��索���¶�̽����� N(hex)
	WORD			m_ProbeNum;
	//��索����ϵͳ���¶�̽���⵽���¶�ֵ N
	vector<BYTE>	m_TemperatureVec;
}StruSubTemperaturea, *LPStruSubTemperature;

/**
* @brief StruTemperature
*		��索��װ���¶����ݸ�ʽ
*/
typedef struct tagStruTemperature
{
	//��ϵͳ����
	BYTE						m_Num;
	//�����ʶ
	vector<StruSubTemperaturea>	m_pElment;
}StruTemperature, *LPStruTemperature;

/**
* @brief StruDate
*		ʱ����Ϣ
*/
typedef struct tagStruDate
{
	//��
	BYTE				m_Year;
	//��
	BYTE				m_Mon;
	//��
	BYTE				m_Day;
	//ʱ
	BYTE				m_Hour;
	//��
	BYTE				m_Min;
	//��
	BYTE				m_Sec;
}StruDate, *LPStruDate;

/**
* @brief StruVehicleLogin
*		�����������ݸ�ʽ
*/
typedef struct tagStruVehicleLogin
{
	//���ݲɼ�ʱ��
	BYTE				m_Time[6];
	//������ˮ��
	WORD				m_Seq;
	//ICCID
	BYTE				m_IccId[20];
	//�ɳ�索����ϵͳ���� n 0��250
	BYTE				m_SubSystemCount;
	//�ɳ�索����ϵͳ���볤�� m ��Χ0��50
	BYTE				m_CodeLen;
	//�ɳ�索����ϵͳ���� n*m
	vector<BYTE>		m_Code;
}StruVehicleLogin, *LPStruVehicleLogin;


#pragma pack(pop)          //���ã��ָ�����״̬

class CUtility
{
public:
	//transform strings to hex
	static bool ConvertStr2Hex(const unsigned char *in, int ilen, string &out)
	{
		if (ilen == 0 || in == NULL)
		{
			return false;
		}
		std::stringstream ss;
		for (int i =0 ; i < ilen; i++)
		{
			//�ַ�ת����16���ƴ����ss��
			ss << std::hex <<(in[i] >> 4) << (in[i] & 0x0f);
		}
		ss >> out;
		return true;
	}
	//transform hex to strings
	static bool ConvertHex2Str(const unsigned char *in, int ilen, string &out)
	{
		if (ilen == 0 || ilen % 2 != 0 || in == NULL)
		{
			return false;
		}
		out.resize(ilen / 2);
		std::stringstream s1;
		int temp = 0;
		for (int i = 0; i < ilen; i += 2)
		{
			//�ַ�ת����16���ƴ����ss��
			s1 << std::hex << in[i] << in[i + 1];
			//��16�����ַ��ض���int������
			s1 >> temp;
			s1.clear();
			//�ַ�����������
			out[i / 2] = temp;
		}
		return true;
	}
};
#if 0
#define DELEGATE
#else
#define GB32960
#endif
