// IPRControlCenterSdkDemo1.cpp : 定义控制台应用程序的入口点。
//
#include "include/DataReceiveInterface.h"
#include "include/inc/stdafx.h"
#include "include/inc/NetDataStruct.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace Iray;

int main()
{
	//初始化数据接口对象
	Iray::DataReceiveInterface* m_pDataRevInterFace = new Iray::DataReceiveInterface();
	std::string strIp = "192.168.3.115";
	//建立连接
	std::cout << "connecting to " << strIp << std::endl;
	bool bIsConnected = m_pDataRevInterFace->connectToHost(strIp);
	if (bIsConnected == false) {
		std::cout << std::endl << "connect failed!" << std::endl;
		return 0;
	}
	//获取版本号
	std::string version = m_pDataRevInterFace->getVersion();
	std::cout << "version: " << version << std::endl;
	panoramaData panorData;
	while (1)
	{
		//获取全景帧数据,8位灰度数据
		if (m_pDataRevInterFace->getPanorFrame(panorData, 10) == 0)
		{
			std::cout << version << std::endl;
			std::cout << "width: " << panorData.width << " height: " << panorData.height << std::endl;
			std::cout << "Resize to 35840, 1024" << std::endl;
			//全景数据
			cv::Mat img(panorData.height, panorData.width, CV_8UC1, panorData.data);
			cv::resize(img, img, cv::Size(35840, 1024));
			cv::imshow("img", img);
			cv::imwrite("panoramic.png", img);
			cv::waitKey(1);
			return 0;
		}
	}

	//断开连接
	m_pDataRevInterFace->disconnectFromHost(strIp);
	delete m_pDataRevInterFace;
	return 0;
}
