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


int Count1(long long col);

void CalulateCT( Mat &src, vector<long long> &CT, int width, int height, int windows_r, int windows_c);

void CalulateCT_1( Mat &src, vector<long long> &CT, int width, int height, int windows_r, int windows_c);

void AD_single( Mat &src,int width,int height,unsigned int *dst, int windows_r, int windows_c);

void cost_AD(unsigned int *src1,unsigned int *src2,int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid);

void CalulateCT_1( Mat &src,int width,int height,unsigned int *dst, int windows_r, int windows_c);

void CalulateCT_2( Mat &src,int width,int height,unsigned int *dst, int windows_r, int windows_c);

void hamin(unsigned int *src1,unsigned int *src2,int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid);

void hamin_96(vector<long long> &CT_L, vector<long long> &CT_R, int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid);


void cost_SAD_dual(Mat &src1,Mat &src2,int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid);

void adCensus(vector< vector<LR_TYPE> > &cost_ad, vector< vector<LR_TYPE> > &cost_census, vector< vector<LR_TYPE> > &cost_adcensus, LR_TYPE alpha, int width, int height, int Dmax);

void adCensusSky1(vector< vector<LR_TYPE> > &cost_ad, vector< vector<LR_TYPE> > &cost_census, vector< vector<LR_TYPE> > &cost_adcensus, LR_TYPE alpha,  int width, int height, int Dmax, Mat &sky_);

void GetRightCosts(vector< vector<LR_TYPE> >& cpds,int width, int height, int disp_N, vector< vector<LR_TYPE> >& new_cpds, LR_TYPE invalid_data);

void weight_r_cal(int window_size,  int gamma, vector<float> &weight_r);

void weight_c_cal(Mat &image, int height, int width, int window_size,  int gamma, vector<vector<float> > &weight_c);

unsigned int match_cost_bf(int row, int col, char d, int window_size, vector<vector<float> > &weight_c, vector<float> &weight_r, Mat &hm,Mat &hm_1);

