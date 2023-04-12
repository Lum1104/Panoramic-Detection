#pragma once
#include "inc/base-def.h"
#include "inc/NetDataStruct.h"
#include "core/iray-errno.h"
#include <string>

namespace Iray
{
	class DataHandler;
	//@brief ���ݽӿ��࣬ʵ�������ӷ���˺ͻ�ȡ���ݵĽӿ�
	class EXPORT_API DataReceiveInterface
	{
	public:
		//@brief Ĭ�Ϲ��캯�����ô˹��캯������Ҫ���� connectToHost ������������
		DataReceiveInterface();
		//@brief ���ع��캯�� �ô˹��캯�������Զ����ӷ���ˣ����õ� connectToHost ����
		//��ȡ����ǰ�� isConnected �����ж��Ƿ�����
		DataReceiveInterface(const std::string & strIp);
		~DataReceiveInterface();

		//@brief ��ȡSDK�汾��
		//@return �汾���ַ���
		std::string getVersion() const;

		//@brief ������Ŀ��������������
		//@param strIp - ��Σ�ip��ַ���磺192.168.1.33
		//@return ����true,��ʾ���ӳɹ�������false,������ʧ��
		bool connectToHost(const std::string & strIp);

		//@brief �ӷ����Ŀ�������Ͽ�����
		//@param strIp - ��Σ�ip��ַ���磺192.168.1.33
		//@return ����true,��ʾ�Ͽ��ɹ�������false,��Ͽ�ʧ��
		bool disconnectFromHost(const std::string & strIp);

		//@brief �ж��Ƿ��Ѿ���������
		//@return ����true,��ʾ�ѽ������ӣ�����false,��δ��������
		bool isConnected() const;

		//@brief ��ȡȫ��֡����
		//@param panorData - ���Σ�������Ż�ȡ��ȫ��֡���ݣ�panoramaData�������ļ� NetDataStruct.h ��
		//@param iTimeout - ��Σ���ʱʱ��,��λ������
		//@return ִ�гɹ����� 0�� ִ��ʧ�ܷ��ش�����
		//@note �����붨���� iray-errno.h ��
	    int getPanorFrame(panoramaData & panorData, unsigned int iTimeout);

		//@brief ��ȡ��������
		//@param alarmData - ���Σ�������Ż�ȡ�ı������ݣ�AlarmData�������ļ� NetDataStruct.h ��
		//@param iTimeout - ��Σ���ʱʱ�䣬��λ������
		//@return ִ�гɹ����� 0�� ִ��ʧ�ܷ��ش�����
		//@note �����붨���� iray-errno.h ��
		int getAlarmData(AlarmData & alarmData, unsigned int iTimeout);
	private:
		//˽�����ݴ�����
		DataHandler *m_pDataHandler;
	};
}

