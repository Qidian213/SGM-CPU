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


int getP2(const float& alpha, const unsigned int& I_p, const unsigned int& I_pr, const int& gamma, const int& P2min);

LR_TYPE min4(LR_TYPE d1,LR_TYPE d2,LR_TYPE d3,LR_TYPE d4);

//Èô²»Î¨Ò»Êä³ö-1
int minVector_index(vector<int> &vs);

int minVector_index_only(vector<int> &vs);

LR_TYPE minVector(vector<LR_TYPE> &vs);

void dynamic_L(vector< vector<LR_TYPE> > cpds, int width, int height, vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , 
              LR_TYPE invalid_data, int windows_r, int windows_c);
void dynamic_U(vector< vector<LR_TYPE> > cpds, int width, int height, vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax ,
              LR_TYPE invalid_data, int windows_r, int windows_c);
void dynamic_D(vector< vector<LR_TYPE> > cpds, int width, int height, vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , 
              LR_TYPE invalid_data, int windows_r, int windows_c);
void dynamic_R(vector< vector<LR_TYPE> > cpds, int width, int height, vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , 
              LR_TYPE invalid_data, int windows_r, int windows_c);

void Viterbi_avg4(vector< vector<LR_TYPE> >& cpds_1,vector<vector<LR_TYPE> >&cpds_2,vector< vector<LR_TYPE> >& cpds_3,vector<vector<LR_TYPE> >&cpds_4,vector<vector<LR_TYPE> >&cpds_1234, int width, int height,int disp_N);
