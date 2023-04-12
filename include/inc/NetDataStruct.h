#pragma once

#include <windows.h>
#include <vector>
#include <iostream>

#pragma pack(1)

// ʱ���
struct TimeData
{
	int year;		// ��
	int month;		// ��
	int day;		// ��
	int hour;		// ʱ
	int minute;		// ��
	int second;		// ��

	bool operator==(const TimeData &tData) const
	{
		return this->year == tData.year && this->month == tData.month
			&& this->day == tData.day && this->hour == tData.hour
			&& this->minute == tData.minute && this->second == tData.second;
	}
};

// Ŀ������
struct TargetPos
{
	int iPosX;		// Ŀ�����ĵ�x
	int iPosY;		// Ŀ�����ĵ�y
	int iRectX;		// Ŀ�����x
	int iRectY;		// Ŀ�����y
	int iRectWidth;	// Ŀ������
	int iRectHeight;// Ŀ������
};

struct PosData
{
	int iPosX;
	int iPosY;
};

// ����Ŀ����Ϣ
struct TargetData
{
	int id;				// Ŀ��ID
	int type;			// Ŀ������
	TargetPos curPos;	// Ŀ������
	int iDistance;		// Ŀ�����
	int iTrackPosNum;	// �켣����
	std::vector<PosData> vecTrackPos;	// �켣����
	int iImgWidth;		// ��Ƭ��
	int iImgHeight;		// ��Ƭ��
	int imgDataLen;		// ��Ƭ���ݳ���
	unsigned char *data; // ��Ƭ����,ΪRGB 32λ����
};

// ��������
struct AlarmData
{
	std::string strIp;		// �豸IP
	TimeData alarmTime;	// ����ʱ��
	short iPitchAngle;	// �����Ƕ�,�Ŵ�10��
	int iImgWidth;		// ȫ��ͼ��
	int iImgHeight;		// ȫ��ͼ��
	int iTargetNum;		// Ŀ�����
	std::vector<TargetData> vecTargetData;	// Ŀ������

	bool operator==(const AlarmData &data) const 
	{
		return this->strIp == data.strIp && this->alarmTime == data.alarmTime;
	}
};

// @brief ȫ��������(8λ�Ҷ�����)
class panoramaData
{
public:
	panoramaData() {
		width = 0;
		height = 0;
		dataLength = 0;
		data = NULL;
	}

	panoramaData(int iWidth, int iHeight) { 
		width = iWidth;
		height = iHeight;
		dataLength = iWidth * iHeight;
		data = new unsigned char[dataLength];
	}

	panoramaData(const panoramaData & panorData)
	{
		width = panorData.width;
		height = panorData.height;
		dataLength = panorData.dataLength;
		data = new unsigned char[panorData.dataLength];
		memmove(this->data, panorData.data, panorData.dataLength);
	}

	panoramaData& operator=(const panoramaData & panorData)
	{
		if (this != &panorData) {
			if (this->dataLength != panorData.dataLength) {
				if (this->data) {
					delete[] data;
					data = NULL;
				}
				data = new unsigned char[panorData.dataLength];
			}

			width = panorData.width;
			height = panorData.height;
			dataLength = panorData.dataLength;
			memmove(this->data, panorData.data, panorData.dataLength);
		}
		return *this;
	}

	~panoramaData() {
		delete[]data;
		data = NULL;
	}

	unsigned width; //ȫ��ͼ���
	unsigned height;//ȫ��ͼ�߶�
	unsigned char *data;//ȫ��֡����
	unsigned dataLength; //ȫ��֡���ݳ���
};

struct InfraredImgData
{
	std::string strIp;
	TimeData imgTime;
	int iImgWidth;		// ȫ��ͼ��
	int iImgHeight;		// ȫ��ͼ�� 
	int imgDataLen;
	unsigned char *data;
};

#pragma pack()