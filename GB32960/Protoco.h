#pragma once
#include "Common.h"


/**
* @brief CBase������
*	GBT32960Э�����
*/
class CBase
{
public:
	CBase(eDataType type);
	~CBase();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
	virtual eDataType GetType();
public:
	eDataType m_type;
	BYTE* m_buf;
	UINT m_len;
};


/**
* @brief CVehicle������
*	��������
*/
class CVehicle : public CBase
{
public:
	CVehicle();
	~CVehicle();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//��������
	StruVehicle			m_vehicle;
};


/**
* @brief CDrivingMotor������
*	�����������
*/
class CDrivingMotor : public CBase
{
public:
	CDrivingMotor();
	~CDrivingMotor();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//�����������
	StruDrivingMotor	m_drivermotor;
};


/**
* @brief CFuelCell������
*	ȼ�ϵ������
*/
class CFuelCell : public CBase
{
public:
	CFuelCell();
	~CFuelCell();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//ȼ�ϵ������
	StruFuelCell		m_fuelcell;
};

/**
* @brief CEngine������
*	����������
*/
class CEngine : public CBase
{
public:
	CEngine();
	~CEngine();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//����������
	StruEngine			m_engin;
};

/**
* @brief CVehiclePos������
*	����λ�����ݸ�ʽ
*/
class CVehiclePos : public CBase
{
public:
	CVehiclePos();
	~CVehiclePos();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//����λ�����ݸ�ʽ
	StruVehiclePos		m_vehiclePos;
};

/**
* @brief CExtremum������
*	��ֵ���ݸ�ʽ
*/
class CExtremum : public CBase
{
public:
	CExtremum();
	~CExtremum();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//��ֵ���ݸ�ʽ
	StruExtremum		m_extremum;
};

/**
* @brief CAlarmInfo������
*	�������ݸ�ʽ
*/
class CAlarmInfo : public CBase
{
public:
	CAlarmInfo();
	~CAlarmInfo();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//�������ݸ�ʽ
	StruAlarmInfo		m_alarmInfo;
};

/**
* @brief CVoltage������
*	��索��װ�õ�ѹ���ݸ�ʽ
*/
class CVoltage : public CBase
{
public:
	CVoltage();
	~CVoltage();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//��索��װ�õ�ѹ���ݸ�ʽ
	StruVoltage		m_voltage;
};


/**
* @brief CTemperature������
*	��索��װ���¶����ݸ�ʽ
*/
class CTemperature : public CBase
{
public:
	CTemperature();
	~CTemperature();
public:
	virtual unsigned char* Serialize(BYTE* buf, UINT len);
	virtual int UnSerialize(BYTE* buf, UINT len);
public:
	//��索��װ���¶����ݸ�ʽ
	StruTemperature		m_temperature;
};

/**
* @brief CGBT32960PX37������
*	x37�ϱ�����
*/
class CGBT32960PX37
{
public:
	CGBT32960PX37();
	~CGBT32960PX37();
public:
	int Initialize();
	int Destroy();
	int CheckHDR(StruHDR hdr);
	CBase *GetDataObject(eDataType type);
	unsigned char* Serialize(BYTE* buf, UINT len);
	int UnSerialize(BYTE* buf, UINT len);

	bool Save2Xml();
public:
	map<eDataType, CBase*>	m_VehicleData;
public:
	//ͨ��ͷ
	StruHDR					m_head;
	//ʱ��
	StruDate				m_time;
	//��������
	CVehicle				m_vehicle;
	//�����������
	CDrivingMotor			m_motor;
	//ȼ�ϵ������
	CFuelCell				m_fuelcell;
	//����������
	CEngine					m_engin;
	//����λ�����ݸ�ʽ
	CVehiclePos				m_vehiclePos;
	//��ֵ���ݸ�ʽ
	CExtremum				m_extremum;
	//�������ݸ�ʽ
	CAlarmInfo				m_alarminfo;
	//��索��װ�õ�ѹ���ݸ�ʽ
	CVoltage				m_voltage;
	//��索��װ���¶����ݸ�ʽ
	CTemperature			m_emperature;
};

