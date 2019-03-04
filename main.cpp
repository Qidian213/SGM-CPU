#include"image.h"
#include"cost.h"
#include"dp.h"
#include"post_processing.h"
#include"prefilter.h"
//#include"AD_postProcess.h"
#include"select_disp.h"

Mat outputDisp_4(Mat img1, Mat img2, float *pparams ,vector<vector<LR_TYPE> >&sum_4, int Dmax= 128, int init_valid = 49,LR_TYPE invalid_data = 210,int windows_c =4,int windows_r =4)
{
	int width0  = img1.cols;
	int height0 = img1.rows;
	int width1 = width0 - 2 * windows_c;
	int height1 = height0 - 2 * windows_r;
	Mat disp_l(height1,width1,CV_8UC1);
	/******************************************************************** CT初始代价 ******************************************************************************/
	//ct
	vector<long long>  CT_L;
	vector<long long>  CT_R;	 
	CalulateCT_1(img1, CT_L, width0, height0, windows_r, windows_c);
	CalulateCT_1(img2, CT_R, width0, height0, windows_r, windows_c);
	vector< vector<LR_TYPE> > cpds;
	hamin_96(CT_L,CT_R,width1, height1, cpds, Dmax, init_valid);
    vector<long long>().swap(CT_L);
    vector<long long>().swap(CT_R);
	/******************************************************************** 动态规划 左图 ******************************************************************************/
	vector<vector<LR_TYPE> > costs_L;
	vector<vector<LR_TYPE> > costs_R; /// LU
	vector<vector<LR_TYPE> > costs_U;
	vector<vector<LR_TYPE> > costs_D; /// RU

	Mat disp_L(height1,width1,CV_8UC1);
	Mat disp_U(height1,width1,CV_8UC1);
	Mat disp_R(height1,width1,CV_8UC1);
	Mat disp_D(height1,width1,CV_8UC1);

	dynamic_L (cpds, width1, height1, costs_L, pparams, img1, Dmax, invalid_data, windows_r, windows_c); 
	dynamic_U (cpds, width1, height1, costs_U, pparams, img1, Dmax, invalid_data, windows_r, windows_c);  		 
	dynamic_R (cpds, width1, height1, costs_R, pparams, img1, Dmax, invalid_data, windows_r, windows_c); 		
	dynamic_D (cpds, width1, height1, costs_D, pparams, img1, Dmax, invalid_data, windows_r, windows_c); 

	cost_select_opencvsgbm(costs_L, height1, width1, Dmax,  disp_L, 0.05);
	cost_select_opencvsgbm(costs_U, height1, width1, Dmax,  disp_U, 0.05);
	cost_select_opencvsgbm(costs_R, height1, width1, Dmax,  disp_R, 0.05);
	cost_select_opencvsgbm(costs_D, height1, width1, Dmax,  disp_D, 0.05);
  
    vector<vector<LR_TYPE> >().swap(cpds);

//	vector<vector<LR_TYPE> > sum_4;
	Viterbi_avg4(costs_L,costs_R,costs_U,costs_D,sum_4, width1, height1, Dmax);

    vector<vector<LR_TYPE> >().swap(costs_L);
    vector<vector<LR_TYPE> >().swap(costs_R);
    vector<vector<LR_TYPE> >().swap(costs_U);
    vector<vector<LR_TYPE> >().swap(costs_D);

	/******************************************* 左视差 ***********************************************/
	cost_select_opencvsgbm(sum_4, height1, width1, Dmax,  disp_l, 0.05);
	imshow("disp_L",disp_l);

//	/******************************************************************** 亚像素求解 ******************************************************************************/
//	Mat frac(height1,width1,CV_8UC1);
//	Mat frac_flag(height1,width1,CV_8UC1);

//	cal_frac_float(sum_4,disp_l,width1,height1,frac,frac_flag, Dmax);
//    imshow("disp_cal",disp_l*8);
    return disp_l;
//	/******************************************************************** 动态规划 右图 ******************************************************************************/ 
//	vector<vector<LR_TYPE> > costs_LDRU_avg_r;
//	GetRightCosts(sum_4, width1, height1, Dmax, costs_LDRU_avg_r, invalid_data);

//	Mat disp_r(height1,width1,CV_8UC1);

//	cost_select_opencvsgbm(costs_LDRU_avg_r, height1, width1, Dmax,  disp_r, 0.05);
//	imshow("disp_R",disp_r*8);


//	/******************************************************************** Lrcheck ******************************************************************************/
//	Mat dispL_check(height1,width1,CV_8UC1);
//	LRcheck(disp_l, disp_r, dispL_check, width1, height1, 1, Dmax);

//	imshow("LR_check",dispL_check*8);

//	/******************************************************************** 整数小数结合 ******************************************************************************/
//	Mat disp_combine(height1,width1,CV_16UC1);
//	combine_int_float(dispL_check,frac,frac_flag, disp_combine, Dmax);
//	imshow("disp_combine",disp_combine*8);

//	/******************************************************************** 填洞 ******************************************************************************/
//	Mat disp_spot;
//	SpotCheck16Bits(disp_combine, disp_spot);
//	imshow("disp_spot",disp_spot*8);

//	Mat dispSpot1;
//	SpotCheck16Bits_1(disp_spot, dispSpot1);
//	imshow("dispSpot1",dispSpot1*8);

//	/******************************************************************** 中值滤波 ******************************************************************************/
//	Mat disp_median_2 = MedianFilter5x5_16bits(dispSpot1);
//	imshow("disp_median_2",disp_median_2*8);
//	return disp_median_2;
}

static float *pparams; 

 int main()
 {
		//读入图片并显示
		Mat  img1 = imread("/home/zzg/DeepLearning/VS_640_out_v6.4/left.png",0);
		Mat  img2 = imread("/home/zzg/DeepLearning/VS_640_out_v6.4/right.png",0);

		pparams = new float[img1.rows*img1.cols*8];
		for(int i=0; i< img1.rows*img1.cols*8 ;i +=8 )
	    {
	        /// down to up
	        pparams[i] = 5.0;
	        pparams[i+1] = 16.0;
	        /// left to right 
	        pparams[i+2] = 5.0;
	        pparams[i+3] = 86.0;
	        /// up to down 
	        pparams[i+4] = 5.0;
	        pparams[i+5] = 16.0;
	        /// right to left
	        pparams[i+6] = 5.0;
	        pparams[i+7] = 86.0;
	    }
	    vector<vector<LR_TYPE> > d_mcost;
	    
		Mat final_disp1 = outputDisp_4(img1,img2,pparams,d_mcost);
        

        cv::imwrite("disp.png",final_disp1);
        cv::waitKey(0);
 }
 



