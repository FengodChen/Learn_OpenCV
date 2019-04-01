#ifndef __FENGOD_COMPARE
#define __FENGOD_COMPARE

#include <opencv2/opencv.hpp>

#define THRES_HOLD__ (40)
#define GS_LEN (50)

/*
 * 得到高斯平滑处理的的图像并
 * 与原图像进行比较
 */
void GauBlurCmp(cv::String f_name);

/*
 * 得到双边平滑处理的图像并
 * 与原图像进行比较
 */
void BilFiltCmp(cv::String f_name);

/*
 * 得到边缘化图像并与原图像比较
 */
void CannyCmp(cv::String f_name);

/* 
 * 输出高斯平滑处理的视频
 */
void GauBlurVideoCmp(cv::String f_name);

/* 
 * 输出边缘化处理的视频
 */
void CannyVideoCmp(cv::String f_name);

/*
 * 得到双边平滑处理的图像并
 * 与原图像进行比较
 */
void BilFiltVideoCmp(cv::String f_name);

/*
 * 得到双边平滑处理的视频并
 * 保存
 */
void BilFiltVideoSav(cv::String f_name);

/* 
 * 得到边缘化处理的视频并
 * 保存
 */
void CannyVideoSav(cv::String f_name);

#endif