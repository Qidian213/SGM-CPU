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

void sobel_x(Mat &src, Mat &dst, int preFilterCap, int height, int width);

void SqureMean(Mat &src, Mat &dst, int W);
Mat MedianFilter3x3(Mat &dispL);

