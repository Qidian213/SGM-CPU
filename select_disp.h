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

void GetMinIndex(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin);

void GetDispByMin(vector< vector<LR_TYPE> >& cpds, int width, int height,int disp_N,Mat &disp);


void GetDisp_cost(Mat &sky_, int width, int height, Mat &disp_out);

void GetDisp_sky(Mat &disp, Mat &sky_, int width, int height, Mat &disp_out);

void GetInitCostSky(vector< vector<LR_TYPE> > cpds_ad, Mat &sky_, int width, int height, vector< vector<LR_TYPE> > cpds_out);

void GetDisp_l_andCost(vector< vector<LR_TYPE> >& cpds, int width, int height,int Dmax,Mat &disp, Mat &img_cost, int cost_th);

void cost_select_opencvsgbm(vector<vector<LR_TYPE> > &lastcost, int height, int width, int DMax,  Mat &CheckLowTexture, float threshold);

void GetDisp_l(vector< vector<LR_TYPE> >& cpds, int width, int height,int Dmax,Mat &disp);
