#include "impls.h"
#include<iostream>
using namespace std;

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    std::vector<cv::Vec4i> hierarchy;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray_image;
    cv::Mat binary_image;
    cv::cvtColor(input, gray_image, cv::COLOR_BGR2GRAY);//转灰度
    cv::threshold(gray_image, binary_image, 0, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);//二值化
    std::vector<std::vector<cv::Point>> contours;//定义contours用来储存轮廓
    cv::findContours(binary_image, contours,hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
   cv::Rect bounding_rect=cv::boundingRect(contours[0]);//计算外接矩形，rect类
    cv::RotatedRect min_area_rect=cv::minAreaRect(contours[0]);//计算最小外接矩形，Rotatedrect类
    //最小外接矩形一般是旋转的，所以用rotatedrect类，包含center、size 和 angle 三个成员，分别代表矩形的中心点坐标、矩形的大小和旋转角度。
    res.first=bounding_rect;
    res.second=min_area_rect;
    return res;
}