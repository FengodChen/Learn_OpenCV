#include "fengod_compare.hpp"
#include <string>

using namespace std;

void GauBlurCmp(cv::String f_name)
{
    // 得到输入矩阵
    cv::Mat img_in = cv::imread(f_name);

    // 定义输出矩阵
    cv::Mat img_out = img_in.clone();

    // 命名窗口以及方式
    cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

    // 高斯模糊(输入矩阵，输出矩阵，高斯核大小，X方向标准差，Y方向标准差)
    GaussianBlur(img_in, img_out, cv::Size(5,5), 3, 3);
    GaussianBlur(img_out, img_out, cv::Size(5,5), 3, 3);

    // 显示图像
    imshow(f_name+"in", img_in);
    imshow(f_name+"out", img_out);

    // 等待
    cv::waitKey(0);

}
void BilFiltCmp(cv::String f_name)
{
    // 得到输入矩阵
    cv::Mat img_in = cv::imread(f_name, cv::IMREAD_COLOR);

    // 定义输出矩阵
    cv::Mat img_out;

    // 命名窗口以及方式
    cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

    // 双边模糊(输入矩阵，输出矩阵，高斯核直径，色彩空间标准差，坐标空间标准差)
    cv::bilateralFilter(img_in, img_out, GS_LEN, GS_LEN*2, GS_LEN/2);
    // bilateralFilter(img_out, img_out, 10, 10*2, 10/2);

    // 显示图像
    cv::imshow(f_name+"in", img_in);
    cv::imshow(f_name+"out", img_out);

    // 等待
    cv::waitKey(0);
}

void CannyCmp(cv::String f_name)
{    
    // 灰度化输入
    // Mat img_in = imread(f_name,IMREAD_GRAYSCALE);
    // 定义输出矩阵
    // Mat img_out;

    cv::Mat img_in = cv::imread(f_name);
    cv::Mat img_in_g;
    cv::Mat img_out;

    // 灰度化转换
    cv::cvtColor(img_in, img_in_g, cv::COLOR_BGR2GRAY);
    

    // 命名窗口以及方式
    cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

    // 高斯模糊(源矩阵，输出矩阵，高斯核大小，X方向标准差，Y方向标准差)
    cv::GaussianBlur(img_in_g, img_out, cv::Size(5,5), 3, 3);
    // GaussianBlur(img_out, img_out, Size(5,5), 3, 3);

    // Canny边缘算法(源矩阵，输出矩阵，滞后性低阀值，滞后性高阀值，应用Sobel算子孔径大小)
    cv::Canny(img_out, img_out, THRES_HOLD__, THRES_HOLD__*3);

    // 缩小一半
    cv::pyrDown(img_in, img_in);
    cv::pyrDown(img_out, img_out);

    // 显示图像
    cv::imshow(f_name+"in", img_in);
    cv::imshow(f_name+"out", img_out);

    // 等待
    cv::waitKey(0);

}

void GauBlurVideoCmp(cv::String f_name)
{
    // 得到输入矩阵
    cv::VideoCapture cap;
    if (f_name == "0")  // 如果输入为0则打开摄像头
    {
        cap.open(0);
    } else              // 否则使用视频
    {
        cap.open(f_name);
    }

    // 每一帧的矩阵
    cv::Mat frame_in, frame_out;


    for(;;)
    {
        cap >> frame_in;
        if (frame_in.empty())   // 若到了视频结尾
        {
            break;
        }
        // 命名窗口以及方式
        cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
        cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

        // 高斯模糊(输入矩阵，输出矩阵，高斯核大小，X方向标准差，Y方向标准差)
        cv::GaussianBlur(frame_in, frame_out, cv::Size(5,5), 3, 3);

        // 显示图像
        cv::imshow(f_name+"in", frame_in);
        cv::imshow(f_name+"out", frame_out);

        // 30帧
        cv::waitKey(30);
    }
}

void CannyVideoCmp(cv::String f_name)
{
    // 得到输入矩阵
    cv::VideoCapture cap;
    if (f_name == "0")  // 如果输入为0则打开摄像头
    {
        cap.open(0);
    } else              // 否则使用视频
    {
        cap.open(f_name);
    }

    // 每一帧的矩阵
    cv::Mat frame_in, frame_in_g, frame_out;


    for(;;)
    {
        cap >> frame_in;
        if (frame_in.empty())   // 若到了视频结尾
        {
            break;
        }
        // 命名窗口以及方式
        cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
        cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

        // 灰度化转换
        cv::cvtColor(frame_in, frame_in_g, cv::COLOR_BGR2GRAY);

        // 高斯模糊(输入矩阵，输出矩阵，高斯核大小，X方向标准差，Y方向标准差)
        cv::GaussianBlur(frame_in_g, frame_out, cv::Size(5,5), 3, 3);

        // 双边模糊(输入矩阵，输出矩阵，高斯核直径，色彩空间标准差，坐标空间标准差)
        // 不知为何这个有错误，错误信息：
        /*
         * terminate called after throwing an instance of 'cv::Exception'
         * what():  OpenCV(4.0.0) /home/fengodchen/Documents/opencv-4.0.0/modules/imgproc/src/canny.cpp:952: error: (-215:Assertion failed) (_dst.getObj() != _src.getObj() || _src.type() == CV_8UC1) && "Inplace parameters are not supported" in function 'Canny'
         * 
         * Aborted (core dumped)
         */
        // cv::bilateralFilter(frame_in, frame_out, GS_LEN, GS_LEN*2,  GS_LEN/2);

        // Canny边缘算法(源矩阵，输出矩阵，滞后性低阀值，滞后性高阀值，应用Sobel算子孔径大小)
        cv::Canny(frame_out, frame_out, THRES_HOLD__, THRES_HOLD__*3);

        // 显示图像
        cv::imshow(f_name+"in", frame_in);
        cv::imshow(f_name+"out", frame_out);

        // 30帧
        cv::waitKey(30);
    }
}
void BilFiltVideoCmp(cv::String f_name)
{
    // 得到输入矩阵
    cv::VideoCapture cap;
    if (f_name == "0")  // 如果输入为0则打开摄像头
    {
        cap.open(0);
    } else              // 否则使用视频
    {
        cap.open(f_name);
    }

    // 每一帧的矩阵
    cv::Mat frame_in, frame_out;


    for(;;)
    {
        cap >> frame_in;
        if (frame_in.empty())   // 若到了视频结尾
        {
            break;
        }
        // 命名窗口以及方式
        cv::namedWindow(f_name+"in", cv::WINDOW_AUTOSIZE);
        cv::namedWindow(f_name+"out", cv::WINDOW_AUTOSIZE);

        // 双边模糊(输入矩阵，输出矩阵，高斯核直径，色彩空间标准差，坐标空间标准差)
        cv::bilateralFilter(frame_in, frame_out, GS_LEN, GS_LEN*2,  GS_LEN/2);

        // 显示图像
        cv::imshow(f_name+"in", frame_in);
        cv::imshow(f_name+"out", frame_out);

        // 30帧
        cv::waitKey(30);
    }
}

void BilFiltVideoSav(cv::String f_name)
{
    // 得到输入矩阵
    cv::VideoCapture cap;
    if (f_name == "0")  // 如果输入为0则打开摄像头
    {
        cap.open(0);
    } else              // 否则使用视频
    {
        cap.open(f_name);
    }

    // 每一帧的矩阵
    cv::Mat frame_in, frame_out;

    // 打开输出视频
    cv::VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(f_name + "_out.avi",                                // 输出名字
        cap.get(cv::CAP_PROP_FOURCC),                                   // 输出格式
        cap.get(cv::CAP_PROP_FPS),                                      // 输出帧率
        cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH),                     // 输出大小（宽度，高度）
        cap.get(cv::CAP_PROP_FRAME_HEIGHT))
    );


    for(;;)
    {
        cap >> frame_in;
        if (frame_in.empty())   // 若到了视频结尾
        {
            break;
        }

        // 双边模糊(输入矩阵，输出矩阵，高斯核直径，色彩空间标准差，坐标空间标准差)
        cv::bilateralFilter(frame_in, frame_out, GS_LEN, GS_LEN*2,  GS_LEN/2);

        // 将处理后的视频输出给输出
        outputVideo << frame_out;
    }

}

void CannyVideoSav(cv::String f_name)
{
    // 得到输入矩阵
    cv::VideoCapture cap;
    if (f_name == "0")  // 如果输入为0则打开摄像头
    {
        cap.open(0);
    } else              // 否则使用视频
    {
        cap.open(f_name);
    }

    // 每一帧的矩阵
    cv::Mat frame_in, frame_out, frame_in_g;

    // 打开输出视频
    cv::VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(f_name + "out.avi",                                // 输出名字
        cap.get(cv::CAP_PROP_FOURCC),                                   // 输出格式
        cap.get(cv::CAP_PROP_FPS),                                      // 输出帧率
        cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH),                     // 输出大小（宽度，高度）
        cap.get(cv::CAP_PROP_FRAME_HEIGHT))
    );


    for(;;)
    {
        cap >> frame_in;
        if (frame_in.empty())   // 若到了视频结尾
        {
            break;
        }

        // 灰度化转换
        cv::cvtColor(frame_in, frame_in_g, cv::COLOR_BGR2GRAY);

        // 高斯模糊(输入矩阵，输出矩阵，高斯核大小，X方向标准差，Y方向标准差)
        cv::GaussianBlur(frame_in_g, frame_out, cv::Size(5,5), 3, 3);

        // Canny边缘算法(源矩阵，输出矩阵，滞后性低阀值，滞后性高阀值，应用Sobel算子孔径大小)
        cv::Canny(frame_out, frame_out, THRES_HOLD__, THRES_HOLD__*3);

        // 将处理后的视频输出给输出
        outputVideo << frame_out;
    }

}
