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

Mat outlierElimination(const Mat &leftDisp, const Mat &rightDisp);

void regionVoting(Mat &disparity, const vector<Mat> &upLimits, const vector<Mat> &downLimits,
                 const vector<Mat> &leftLimits, const vector<Mat> &rightLimits, bool horizontalFirst);

void properInterpolation(Mat &disparity, const Mat &leftImage);


void discontinuityAdjustment(Mat &disparity, const vector<vector<Mat> > &costs);

Mat subpixelEnhancement(Mat &disparity, const vector<vector<Mat> > &costs);
