#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    if (input.empty() || scale <= 0) {
        // 处理错误情况
        return cv::Mat();
    }
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE
   cv::Mat output(new_rows,new_cols,input.type());
    if(input.channels()==3||input.channels()==4)
    {
      for(int i=0;i<new_rows;++i)
     {
        for(int j=0;j<new_cols;++j)
        {
          float x=j/scale;
          float y=i/scale;
          int x1,x2,y1,y2;
        x1 = std::min(static_cast<int>(x), input.cols - 2);
        y1 = std::min(static_cast<int>(y), input.rows - 2);
        x2 = std::min(x1 + 1, input.cols - 1);
        y2 = std::min(y1 + 1, input.rows - 1);
        
        
          if (x2 < input.cols && y2 < input.rows)
          {
          float dx = x - x1;
          float dy = y - y1;
          float dx1 = 1 - dx;
          float dy1 = 1 - dy;
          cv::Vec3b color1=input.at<cv::Vec3b>(y1,x1);
          cv::Vec3b color2=input.at<cv::Vec3b>(y1,x2);
          cv::Vec3b color3=input.at<cv::Vec3b>(y2,x1);
          cv::Vec3b color4=input.at<cv::Vec3b>(y2,x2);
          cv::Vec3b output_color;
         output_color [0] = static_cast<uchar>(color1[0] * dx1 * dy1 + color2[0] * dx * dy1 + color3[0] * dx1 * dy + color4[0] * dx * dy);
         output_color [1] = static_cast<uchar>(color1[1] * dx1 * dy1 + color2[1] * dx * dy1 + color3[1] * dx1 * dy + color4[1] * dx * dy);
         output_color [2] = static_cast<uchar>(color1[2] * dx1 * dy1 + color2[2] * dx * dy1 + color3[2] * dx1 * dy + color4[2] * dx * dy);
        output.at<cv::Vec3b>(i,j)=output_color;
          }
        }

     }
    
    }
    
    return output;
    
   
  
}
