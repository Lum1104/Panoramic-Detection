#pragma once
#include "inc/base-def.h"
#include "inc/NetDataStruct.h"
#include "core/iray-errno.h"
#include <string>

namespace Iray
{
	class DataHandler;
	//@brief 数据接口类，实现了连接服务端和获取数据的接口
	class EXPORT_API DataReceiveInterface
	{
	public:
		//@brief 默认构造函数，用此构造函数，则要调用 connectToHost 函数建立连接
		DataReceiveInterface();
		//@brief 重载构造函数 用此构造函数，则自动连接服务端，不用调 connectToHost 函数
		//获取数据前用 isConnected 函数判断是否连接
		DataReceiveInterface(const std::string & strIp);
		~DataReceiveInterface();

		//@brief 获取SDK版本号
		//@return 版本号字符串
		std::string getVersion() const;

		//@brief 与服务端目标主机建立连接
		//@param strIp - 入参，ip地址，如：192.168.1.33
		//@return 返回true,表示连接成功，返回false,则连接失败
		bool connectToHost(const std::string & strIp);

		//@brief 从服务端目标主机断开连接
		//@param strIp - 入参，ip地址，如：192.168.1.33
		//@return 返回true,表示断开成功，返回false,则断开失败
		bool disconnectFromHost(const std::string & strIp);

		//@brief 判断是否已经建立连接
		//@return 返回true,表示已建立连接，返回false,则未建立连接
		bool isConnected() const;

		//@brief 获取全景帧数据
		//@param panorData - 出参，用来存放获取的全景帧数据，panoramaData定义在文件 NetDataStruct.h 中
		//@param iTimeout - 入参，超时时间,单位：毫秒
		//@return 执行成功返回 0， 执行失败返回错误码
		//@note 错误码定义在 iray-errno.h 中
	    int getPanorFrame(panoramaData & panorData, unsigned int iTimeout);

		//@brief 获取报警数据
		//@param alarmData - 出参，用来存放获取的报警数据，AlarmData定义在文件 NetDataStruct.h 中
		//@param iTimeout - 入参，超时时间，单位：毫秒
		//@return 执行成功返回 0， 执行失败返回错误码
		//@note 错误码定义在 iray-errno.h 中
		int getAlarmData(AlarmData & alarmData, unsigned int iTimeout);
	private:
		//私有数据处理工具
		DataHandler *m_pDataHandler;
	};
}

