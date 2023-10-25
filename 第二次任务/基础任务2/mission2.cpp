#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main(int argc, char** argv){
    cv::Mat src;
    src = cv::imread("/home/jinyankai/mission1.jpg");
    if (src.empty()){
        printf("could not load image..\n");
        return -1;
    }
    cv::imshow("input", src);
 
    cv::Mat up_dst, down_dst;
    cv::pyrUp(src, up_dst); // 上采样
    cv::pyrDown(src, down_dst); // 下采样
 
    cv::imshow("pyrUp", up_dst);
    cv::imshow("pyrDown", down_dst);
 
    cv::waitKey(0);
    return 0;
}

