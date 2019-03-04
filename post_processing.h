#include <fstream>
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


void cal_frac(vector< vector<LR_TYPE> > cpds,Mat &disp,int width,int height,Mat &frac, int Dmax);
void combine_int_frac(Mat &disp,Mat &frac,int width,int height,Mat &disp_combine, int Dmax);

void cal_frac_float(vector< vector<LR_TYPE> > cpds,Mat &disp,int width,int height,Mat &frac, Mat &frac_flag, int Dmax);
void combine_int_float(Mat &disp, Mat &frac, Mat &frac_flag, Mat &disp_combine, int Dmax);

void LRcheck(Mat &dispL,Mat &dispR, Mat &dispL_check, int width, int height, int threshold, int Dmax);

void SpotCheck16Bits(Mat &disp_in, Mat &disp_out);

void SpotCheck16Bits_1(Mat &disp_in, Mat &disp_out);



Mat MedianFilter5x5(Mat &disp_in);

Mat MedianFilter5x5_16bits(Mat &disp_in);
