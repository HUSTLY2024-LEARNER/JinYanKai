#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

Mat BGR2HSV(Mat in_image){
	int height=in_image.rows;
	int width=in_image.cols;
	
	float r,g,b;
	float h,s,v;
	float max,min;
	Mat hsv=Mat ::zeros(height,width,CV_32FC3);
	
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<height;x++)
		{
			r=(float)in_image.at<Vec3b>(y,x)[2]/255;
			g=(float)in_image.at<Vec3b>(y,x)[1]/255;
			b=(float)in_image.at<Vec3b>(y,x)[0]/255;
			
			
			
			max = fmax(r,fmax(g,b));
			min=fmin(r,fmin(g,b));
			if(max==min){
				h=0;
			}
			else if(min==b){
				h=60*(g-r)/(max-min)+60;
			}
			else if(min==r){
				h=60*(b-g)/(max-min)+180;
			}
			else if(min==g){
				h=60*(r-b)/(max-min)+300;
			}
			s=max-min;
			v=max;
			
			hsv.at<Vec3f>(y,x)[1]=s;
			hsv.at<Vec3f>(y,x)[2]=v;
		}
	}
	return hsv;
}
/*Mat HSV2BGR(Mat hsv){
	int height=hsv.rows;
	int width=hsv.cols;
	float h,s,v;
	double c,_h,_x;
	double r,g,b;
	Mat out=Mat::zeros(height,width,CV_8UC3);
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<height;x++)
		{
			
			h=hsv.at<Vec3f>(y,x)[0];
			s=hsv.at<Vec3f>(y,x)[1];
			v=hsv.at<Vec3f>(y,x)[2];
			c=s;
			_h=h/60;
			_x=c*(1-abs(fmod(_h,2)-1));
			r=g=b=v-c;
			if (_h < 1) {
				r += c;
				g += _x;
			}
			else if (_h < 2) {
				r += _x;
				g += c;
			}
			else if (_h < 3) {
				g += c;
				b += _x;
			}
			else if (_h < 4) {
				g += _x;
				b += c;
			}
			else if (_h < 5) {
				r += _x;
				b += c;
			}
			else if (_h < 6) {
				r += c;
				b += _x;
			}
			
			
			out.at<cv::Vec3b>(y, x)[0] = (uchar)(b * 255);
			out.at<cv::Vec3b>(y, x)[1] = (uchar)(g * 255);
			out.at<cv::Vec3b>(y, x)[2] = (uchar)(r * 255);
		}
	}
	return out;
}*/
			
			
			
			
			
			
			
			
int main(int argc,const char* argv[])
{
	Mat out;
	Mat in_image=imread("/home/jinyankai/mission1.jpg",cv::IMREAD_COLOR);
	
	namedWindow("input photo",WINDOW_AUTOSIZE);
	imshow("input photo",in_image);
	
	out=BGR2HSV(in_image);
	
	imshow("processed",out);
	waitKey(0);
	return 0;
}/*   */
//
