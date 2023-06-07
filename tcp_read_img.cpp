#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
    io_service io_service;
    tcp::socket socket(io_service);
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("192.168.44.112", "6666");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // 连接服务器
    connect(socket, endpoint_iterator);
    cv::namedWindow("Infrared Image");
    cv::VideoWriter videoWriter("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, cv::Size(1280, 1024), false);
    // 循环读取数据并实时显示
    while (true)
    {
        // 读取固定长度的头部信息
        std::vector<char> buf(26);
        size_t len = socket.read_some(buffer(buf));
        std::cout << "Received " << len << " bytes\n";

        // 解析头部信息
        uint32_t head = *(uint32_t*)&buf[0];
        uint8_t format = buf[4];
        uint8_t seq = buf[5];
        uint32_t cut_pixels = *(uint32_t*)&buf[6];
        uint32_t width = *(uint32_t*)&buf[10];
        uint32_t height = *(uint32_t*)&buf[14];
        uint32_t reserved = *(uint32_t*)&buf[18];
        uint32_t data_len = *(uint32_t*)&buf[22];
        std::cout << "head: " << std::hex << head << std::endl;
        std::cout << "format: " << std::hex << (int)format << std::endl;
        std::cout << "seq: " << std::hex << (int)seq << std::endl;
        std::cout << "cut pixels: " << std::hex << cut_pixels << std::endl;
        std::cout << "width: " << std::dec << width << std::endl;
        std::cout << "height: " << std::dec << height << std::endl;
        std::cout << "reserved: " << std::hex << reserved << std::endl;
        std::cout << "data length: " << std::dec << data_len << std::endl;

        // 读取图像数据
        std::vector<char> data(data_len);
        size_t data_len_read = 0;
        while (data_len_read < data_len) {
            data_len_read += socket.read_some(buffer(data.data() + data_len_read, data_len - data_len_read));
        }
        std::cout << "Received " << data_len_read << " bytes of image data\n";

        // 处理图像数据
        cv::Mat img(height, width, CV_8UC1, data.data());
        cv::flip(img, img, -1);
        videoWriter.write(img);
        cv::resize(img, img, cv::Size(), 0.5, 0.5);
        cv::imshow("Infrared Image", img);
        char key = cv::waitKey(1);  // 等待1ms，处理窗口事件
        if (key == 'q')
            break;

        // 清空缓存
        buf.clear();
        data.clear();
    }
    videoWriter.release();
    cv::destroyWindow("Infrared Image");

    return 0;
}
