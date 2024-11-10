#include "impls.h"


std::vector<cv::Mat> erode(const cv::Mat& src_erode, const cv::Mat& src_dilate) {
    /**
     * TODO: 先将图像转换为灰度图像, 然后二值化，然后进行腐蚀操作，具体内容：
     *  1. 将彩色图片 src_erode 转换为灰度图像
     *  2. 将灰度图像进行二值化
     *  3. 将二值化后的两张图片 分别进行 腐蚀 和 膨胀操作
     *  此任务需要你不断调整 erode 和 dilate 函数 的参数，以达到目标效果
     * HINT: 你可能需要以下函数
     *  1. 图像的腐蚀函数 cv::erode，该函数会扩大黑色部分，去除小的白色区域，参数如下
     *      void cv::erode(
     *          InputArray  src,        // 输入的二值图像
     *          OutputArray dst,        // 输出的二值图像
     *          InputArray  kernel,     // 腐蚀的核
     *          Point       anchor = Point(-1,-1), // 锚点
     *          int         iterations = 1,        // 迭代次数
     *          int         borderType = BORDER_CONSTANT, // 边界类型
     *          const Scalar& borderValue = morphologyDefaultBorderValue() // 边界值
     *      )
     *  2. 图像的膨胀函数 cv::dilate，该函数会扩大白色部分，去掉小的的黑色区域，参数如下
     *      void cv::dilate(
     *          InputArray  src,        // 输入的二值图像
     *          OutputArray dst,        // 输出的二值图像
     *          InputArray  kernel,     // 膨胀的核
     *          Point       anchor = Point(-1,-1), // 锚点
     *          int         iterations = 1,        // 迭代次数
     *          int         borderType = BORDER_CONSTANT, // 边界类型
     *          const Scalar& borderValue = morphologyDefaultBorderValue() // 边界值
     *      )
     *  3. 图像的腐蚀和膨胀的核可以使用 cv::getStructuringElement 函数生成，参数如下
     *      cv::Mat cv::getStructuringElement(
     *          int         shape,      // 核的形状 (具体类型可以参考网络资料，或者利用 vscode 的代码提示)
     *          Size        ksize,      // 核的大小
     *          Point       anchor = Point(-1,-1) // 锚点
     *      )
     *       膨胀腐蚀操作的本质是对图像进行卷积(暂时可以理解为在一个像素区域内取平均的意思)操作，
     *      核的大小决定了这个区域的大小
     *   PS: 这里的 二值化函数的参数需要看设置为 thresh = 50, maxval = 255, type = THRESH_BINARY
     *   GOAL:
     *     1. 腐蚀结果图片中，女孩头发里的白点被消除了(类似答案中的样子)
     *     2. dilate 之后的图像中，图中的小脚被消除了(类似答案中的样子)
     *     以上两个检查点需要自己检查，满足条件 则输入 p 通过, 否则输入 f 表示不通过
     */
    cv::Mat dst_erode, dst_dilate;

    // TODO: 在这里实现你的代码
    //创建保存灰度图像等的类
    cv::Mat gray_image,gray_image1;
    cv::Mat binary_image, binary_image1;
    //转灰度，函数 cv::cvtColor(输入, 输出, 颜色码（转换成什么颜色）);（也可自己规定通道数，否则自动）
    cv::cvtColor(src_erode, gray_image, cv::COLOR_BGR2GRAY);
     cv::cvtColor(src_dilate, gray_image1, cv::COLOR_BGR2GRAY);
    //二值化
    cv::threshold(gray_image, binary_image, 50, 255, cv::THRESH_BINARY);
     cv::threshold(gray_image1, binary_image1, 50, 255, cv::THRESH_BINARY);
    //imshow(" ",binary_image);
    //腐蚀与膨胀
    //创建自定义核
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(4, 4),cv::Point(1,1));
    cv::Mat kernel2= cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(1,1));
     cv::Mat kernel3= cv::getStructuringElement(cv::MORPH_RECT,cv::Size(2,2),cv::Point(1,1));
    //腐蚀
    cv::erode(binary_image, dst_erode,kernel2);
    cv::erode(dst_erode, dst_erode,kernel2);
    cv::erode(dst_erode, dst_erode,kernel2);
    //膨胀
    cv::dilate(binary_image1, dst_dilate, kernel1,cv::Point(-1,-1),4);
    return {dst_erode, dst_dilate};
}
