#pragma once

#include <windows.h>
#include <vector>
#include <iostream>

#pragma pack(1)

// 时间戳
struct TimeData
{
	int year;		// 年
	int month;		// 月
	int day;		// 日
	int hour;		// 时
	int minute;		// 分
	int second;		// 秒

	bool operator==(const TimeData &tData) const
	{
		return this->year == tData.year && this->month == tData.month
			&& this->day == tData.day && this->hour == tData.hour
			&& this->minute == tData.minute && this->second == tData.second;
	}
};

// 目标坐标
struct TargetPos
{
	int iPosX;		// 目标中心点x
	int iPosY;		// 目标中心点y
	int iRectX;		// 目标检测框x
	int iRectY;		// 目标检测框y
	int iRectWidth;	// 目标检测框宽
	int iRectHeight;// 目标检测框高
};

struct PosData
{
	int iPosX;
	int iPosY;
};

// 单个目标信息
struct TargetData
{
	int id;				// 目标ID
	int type;			// 目标类型
	TargetPos curPos;	// 目标坐标
	int iDistance;		// 目标距离
	int iTrackPosNum;	// 轨迹个数
	std::vector<PosData> vecTrackPos;	// 轨迹数据
	int iImgWidth;		// 切片宽
	int iImgHeight;		// 切片高
	int imgDataLen;		// 切片数据长度
	unsigned char *data; // 切片数据,为RGB 32位数据
};

// 报警数据
struct AlarmData
{
	std::string strIp;		// 设备IP
	TimeData alarmTime;	// 报警时间
	short iPitchAngle;	// 俯仰角度,放大10倍
	int iImgWidth;		// 全景图宽
	int iImgHeight;		// 全景图高
	int iTargetNum;		// 目标个数
	std::vector<TargetData> vecTargetData;	// 目标数据

	bool operator==(const AlarmData &data) const 
	{
		return this->strIp == data.strIp && this->alarmTime == data.alarmTime;
	}
};

// @brief 全景数据类(8位灰度数据)
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

	unsigned width; //全景图宽度
	unsigned height;//全景图高度
	unsigned char *data;//全景帧数据
	unsigned dataLength; //全景帧数据长度
};

struct InfraredImgData
{
	std::string strIp;
	TimeData imgTime;
	int iImgWidth;		// 全景图宽
	int iImgHeight;		// 全景图高 
	int imgDataLen;
	unsigned char *data;
};

#pragma pack()