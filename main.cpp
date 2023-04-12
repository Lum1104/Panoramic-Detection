// IPRControlCenterSdkDemo1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "include/DataReceiveInterface.h"
#include "include/inc/stdafx.h"
#include "include/inc/NetDataStruct.h"
#include <iostream>
using namespace Iray;

int main()
{
	//��ʼ�����ݽӿڶ���
	Iray::DataReceiveInterface* m_pDataRevInterFace = new Iray::DataReceiveInterface();
	std::string strIp = "127.0.0.1";
	//��������
	std::cout << "connecting to " << strIp << std::endl;
	bool bIsConnected = m_pDataRevInterFace->connectToHost(strIp);
	if (bIsConnected == false) {
		std::cout << std::endl << "connect failed!" << std::endl;
		return 0;
	}
	//��ȡ�汾��
	std::string version = m_pDataRevInterFace->getVersion();
	std::cout << "version: " << version << std::endl;
	panoramaData panorData;
	while (1)
	{
		//��ȡȫ��֡����,8λ�Ҷ�����
		if (m_pDataRevInterFace->getPanorFrame(panorData, 10) == 0)
		{
			std::cout << version << std::endl;
			std::cout << "width: " << panorData.width << " height: " << panorData.height << std::endl;
			//ȫ������
			panorData.data;
		}

		//Sleep(10);
	}

	//�Ͽ�����
	m_pDataRevInterFace->disconnectFromHost(strIp);
	delete m_pDataRevInterFace;
	return 0;
}