#include "impls.h"
#include <algorithm>

float compute_iou(const cv::Rect& a, const cv::Rect& b) {
    /**
     * 要求：
     *      有一个重要的指标叫做“交并比”，简称“IOU”，可以用于衡量
     * 两个矩形的重合程度，本练习要求自行学习交并比的计算方式，计算输入
     * 的两个矩形的交并比。
     * 
     * 提示：
     * (1) 注意OpenCV中规定的xy坐标系方向跟平常的xy坐标系不一样。（向下为y轴正方向，向右为x轴正方向）
     * (2) 注意矩形的x, y, width, height四个属性在坐标系内的含义。
     * (3) 注意分母不要除以0（不过我们不会测试这一点）
     * 
     * 通过条件：
     * 运行测试点，显示通过就行，不通过会告诉你哪一组矩形错了。
    */
    // IMPLEMENT YOUR CODE HERE
    //找左上角交集坐标，越往左上下x,y越小。交集左上角坐标要找相对右下方的。即x,y更大
    int x1,y1;
    x1=std::max(a.x,b.x);
    y1=std::max(a.y,b.y);
    //找右下角交集坐标，自然与左上相反。
    int x2,y2;
    x2=std::min((a.x+a.width),(b.x+b.width));
    y2=std::min((a.y+a.height),(b.y+b.height));
    //计算交集面积
    int A_rea= std::max(0, x2 - x1)*std::max(0, y2 - y1);
    //计算并集面积
    //先算a,b面积
    int a_area=a.width*a.height;
    int b_area=b.width*b.height;
    //并集面积
    int a_rea=a_area+b_area-A_rea;
    //计算交并比(iou)
    
    float I_ou;
    if(a_rea!=0)
    I_ou=static_cast<float>(A_rea)/static_cast<float>(a_rea);
    return I_ou;
} 