#include <vector>
#include <cmath>
#include <cxcore.h>
#include <iostream>
#include <fstream>

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
void labelNightPixel(Mat &img_data,Mat &sky_label,int TH);

void labelLeftBelowTH(Mat &img_data,Mat &sky_label,int TH);

void GenerateFalseMap(cv::Mat &src, cv::Mat &disp);

void ShowAndSave(Mat &disp, char * name);

void SaveColor(Mat &disp, char * name);

void ShowColor(Mat &disp, char * name);
