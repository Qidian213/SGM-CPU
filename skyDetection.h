#include <fstream>
#include <vector>
#include <cmath>
#include <cxcore.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
typedef float LR_TYPE;


void label_sky_v(Mat &img_data,Mat &sky_label,int W);
void label_sky_v1(Mat &img_data,Mat &sky_label,int W);
void label_sky_v2(Mat &img_data,Mat &sky_label,int W);
void label_sky_v2_1(Mat &img_data,Mat &sky_label,int W, Mat &sobel_y);
void label_sky_v4(Mat &img_data,Mat &sky_label,int W);

void skyRegionGrowing(Mat img_, Mat& sky_);

void skyRegionGrowing_1(Mat img_, Mat& sky_);

void skyRegionGrowing_2(Mat img_, Mat& sky_, int W);

void SkyRemove(Mat &sky_, int width, int height, Mat &disp_in, Mat &disp);
