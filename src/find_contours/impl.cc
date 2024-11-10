#include "impls.h"


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
     * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
     * 
     * 提示：
     * 1. 使用cv::imshow来查看输入图像。
     * 2. 使用cv::drawContours来在一张图上绘制轮廓。
     * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理//二值化。
     * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
     * 
     * 通过条件：
     * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
     */
    
    std::vector<std::vector<cv::Point>> res;//理解为一个二维数组cv::point 是一个轮廓中的元素，这些轮廓被储存在一个大数组中
    std::vector<cv::Vec4i> hierarchy;//二维数组
    cv::Mat gray_image;
    cv::Mat binary_image;
    cv::cvtColor(input,gray_image,cv::COLOR_BGR2GRAY);//转灰度
    cv::threshold(gray_image,binary_image,127,255,cv::THRESH_BINARY);//二值化
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);//创建窗口
    cv::imshow("Display window", input);//查看原图
    cv::findContours(binary_image,res,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);//找轮廓
    //在使用findContours时将轮廓储存到了res中，但同时创建了一个表用来查找轮廓（利用的时轮廓间的层次关系）即hierarchy
    std::vector<std::vector<cv::Point>> inner_res;
    //hierarchy是一个数据结构
    /*hierarchy[i][0] 表示第 i 个轮廓的层次数组中的第一个元素，具体含义如下：
    hierarchy[i][0]：表示第 i 个轮廓的前一个轮廓（在轮廓列表中的索引）。
    如果一个轮廓没有前一个轮廓，或者它是列表中的第一个轮廓，那么这个值是 -1。
    hierarchy[i][1]表示后一个轮廓， hierarchy[i][2]表示当前轮廓父轮廓， hierarchy[i][3]表示子轮廓*/
  for(int i=0;i<hierarchy.size();i++)
  {
    if(hierarchy[i][2]==-1&&hierarchy[i][3]!=-1)
    {
     inner_res.push_back(res[i]);//将整个轮廓添加到inner_res后面
    }
  }//20~36行代码为找到最内层轮廓的办法，接下来学习使用drawcounters

    // IMPLEMENT YOUR CODE HERE
cv::Mat Drawingcontours1=input.clone();
drawContours(Drawingcontours1,inner_res,0,cv::Scalar(13,232,3),1);//使用了第1，2，3，4，5个参数
drawContours(Drawingcontours1,inner_res,1,cv::Scalar(100,23,3),1);
drawContours(Drawingcontours1,inner_res,2,cv::Scalar(13,23,200),1);
/*其中第一个参数image表示目标图像，
第二个参数contours表示输入的轮廓组，每一组轮廓由点vector构成，
第三个参数contourIdx指明画第几个轮廓，如果该参数为负值，则画全部轮廓，
第四个参数color为轮廓的颜色

第五个参数thickness为轮廓的线宽，如果为负值或CV_FILLED表示填充轮廓内部，
第六个参数lineType为线型，
第七个参数为轮廓结构信息，
第八个参数为maxLevel*/
imshow("我绘制的轮廓",Drawingcontours1);
    return inner_res;
}
#include "impls.h"


