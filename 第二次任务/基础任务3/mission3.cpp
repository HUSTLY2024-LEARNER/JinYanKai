
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat Image_Preprocessing(Mat temp)//图像预处理
{
	Mat kernel = getStructuringElement(MORPH_RECT, Size(25, 25), Point(-1, -1));
	Mat open_gray_blur_Image;
	morphologyEx(temp, open_gray_blur_Image, MORPH_OPEN, kernel);
	Mat rst;
	subtract(temp, open_gray_blur_Image, rst, Mat());
	imshow("rst", rst);
	Mat Canny_Image;
	Canny(rst, Canny_Image, 400, 200, 3);
	imshow("Canny_Image", Canny_Image);
	return Canny_Image;
}

Mat Morphological_Processing(Mat temp)//形态学处理
{
	//图片膨胀处理
	Mat dilate_image, erode_image;
	//自定义核：进行 x 方向的膨胀腐蚀
	Mat elementX = getStructuringElement(MORPH_RECT, Size(25, 1));
	Mat elementY = getStructuringElement(MORPH_RECT, Size(1, 19));
	Point point(-1, -1);
	dilate(temp, dilate_image, elementX, point, 2);
	erode(dilate_image, erode_image, elementX, point, 4);
	dilate(erode_image, dilate_image, elementX, point, 2);
	//自定义核：进行 Y 方向的膨胀腐蚀
	erode(dilate_image, erode_image, elementY, point, 1);
	dilate(erode_image, dilate_image, elementY, point, 2);
	//平滑处理
	Mat median_Image;
	medianBlur(dilate_image, median_Image, 15);
	medianBlur(median_Image, median_Image, 15);
	imshow("中值滤波", median_Image);
	return median_Image;
}

//车牌定位
Mat Locate_License_Plate(Mat temp, Mat src, Mat gray_src)
{
	vector<vector<Point>> contours;
	findContours(temp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//画出轮廓
	drawContours(temp, contours, -1, Scalar(255), 1);
	//轮廓表示为一个矩形
	Mat Roi;
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rect = minAreaRect(Mat(contours[i]));
		Point2f p[4];
		rect.points(p);
		double axisLongTemp = 0.0, axisShortTemp = 0.0;//矩形的长边和短边
		axisLongTemp = sqrt(pow(p[1].x - p[0].x, 2) + pow(p[1].y - p[0].y, 2));  //计算长轴
		axisShortTemp = sqrt(pow(p[2].x - p[1].x, 2) + pow(p[2].y - p[1].y, 2)); //计算短轴
		double LengthTemp;//中间变量
		if (axisShortTemp > axisLongTemp)//若短轴大于长轴，交换数据
		{
			LengthTemp = axisLongTemp;
			axisLongTemp = axisShortTemp;
			axisShortTemp = LengthTemp;
		}
		double rectArea = axisLongTemp*axisShortTemp;//计算矩形面积
		double Area = contourArea(Mat(contours[i]));//轮廓面积
		double rectDegree = Area / rectArea;//计算矩形度
		if (axisLongTemp / axisShortTemp >= 2.2 && axisLongTemp / axisShortTemp <= 5.1 && rectDegree > 0.63 && rectDegree < 1.37 && rectArea>2000 && rectArea < 50000)//通过划定长宽比，矩形度以及矩形面积的变化范围划定车牌区域（该部分可视实际情况而调整）
		{
			for (int i = 0; i < 4; i++)       //划线框出车牌区域
				line(src, p[i], p[((i + 1) % 4) ? (i + 1) : 0], Scalar(0, 0, 255), 2, 8, 0);

			float width_height = (float)rect.size.width / (float)rect.size.height;
			float angle = rect.angle;
			if (width_height < 1)//处理图像中旋转角度大于90度的车牌
				angle = angle + 90;
			Mat rotMat = getRotationMatrix2D(rect.center, angle, 1);//获得矩形的旋转矩阵
			Mat warpImg;
			warpAffine(gray_src, warpImg, rotMat, src.size(), INTER_CUBIC);
			imshow("仿射变换", warpImg);
			//图像切割
			Size minRectSize = rect.size;
			if (width_height < 1)
				swap(minRectSize.width, minRectSize.height);
			getRectSubPix(warpImg, minRectSize, rect.center, Roi);
		}
	}
	//imshow("test", src);
	imshow("车牌提取结果", Roi);
	return Roi;
}

int main(){
			//加载图像
	Mat src, gray_src;
	src = imread("/home/jinyankai/mission3.jpeg");
	//图像预处理
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	Mat gray_blur_Image;
	GaussianBlur(gray_src, gray_blur_Image, Size(3, 3), 0, 0);
	Mat Canny_Image = Image_Preprocessing(gray_blur_Image);
	//形态学处理
	Mat median_Image = Morphological_Processing(Canny_Image);
	//车牌定位：矩形轮廓查找与筛选：
	Mat contour_Image;
	//查找轮廓会改变源图像信息，需要重新拷贝图像
	contour_Image = median_Image.clone();
	Mat Roi = Locate_License_Plate(contour_Image, src, gray_src);
	imshow("车牌提取结果", Roi);
	waitKey(0);
	//创建仿射变换目标图像与原图像尺寸类型相同
	
	return 0;
}

