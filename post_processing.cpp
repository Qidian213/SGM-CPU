#include"post_processing.h"

void SpotCheck3_cost(Mat &disp_in, Mat &disp_out, int width, int height, int Dmax, Mat &flag_cost)
{
	for (int row = 3; row < height-3; row++)
	{
		for (int col = 3; col < width-3; col++)
		{

			//统计0的个数
			int count_num_zero = 0;
			//for (int m = -3; m <= 3; m++)
			//	for (int n = -3; n <= 3; n++)
			//	{	
			//		uchar data_tmp = disp_in.at<uchar>(row+n, col+m);
			//		if (data_tmp == 0)
			//			count_num_zero++;
			//	}
			int data_cost = flag_cost.at<uchar>(row, col);

			int count_num = 0;
			uchar data_centor = disp_in.at<uchar>(row, col);
			for (int m = -3; m <= 3; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row-3, col+m);
				if (data_tmp +3 < data_centor)
					count_num++;
			}
			for (int m = -3; m <= 3; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+3, col+m);
				if (data_tmp +3 < data_centor)
					count_num++;
			}
			for (int m = -2; m <= 2; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+m, col+3);
				if (data_tmp +3 < data_centor)
					count_num++;
			}	
			for (int m = -2; m <= 2; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+m, col-3);
				if (data_tmp +3 < data_centor)
					count_num++;
			}	

			//5x5的窗口统计
			int count_num_5 = 0;
			for (int m = -2; m <= 2; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row-2, col+m);
				if (data_tmp +3 < data_centor)
					count_num_5++;
			}
			for (int m = -2; m <= 2; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+2, col+m);
				if (data_tmp +3 < data_centor)
					count_num_5++;
			}
			for (int m = -1; m <= 1; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+m, col+2);
				if (data_tmp +3 < data_centor)
					count_num_5++;
			}	
			for (int m = -1; m <= 1; m++)
			{	
				uchar data_tmp = disp_in.at<uchar>(row+m, col-2);
				if (data_tmp +3 < data_centor)
					count_num_5++;
			}


			if (count_num > 12 || count_num_5 > 8 || data_cost == 1)   //一共24个点
				disp_out.at<uchar>(row-3,col-3) = 0;
			else
				disp_out.at<uchar>(row-3,col-3) = disp_in.at<uchar>(row, col);
		}
	}
}



void cal_frac(vector< vector<LR_TYPE> > cpds,Mat &disp,int width,int height,Mat &frac, int Dmax)
{
	//ofstream outfile("frac.txt");
	for(int row = 0; row < height; row ++)
	for(int col = 0; col < width ; col ++)
	{
		if(disp.at<uchar>(row,col) != 64) 
		{
			unsigned int d = disp.at<uchar>(row,col);
			vector<LR_TYPE> cpd_all = cpds[row*width + col];

			unsigned int CPD_1 =  cpd_all[d];
			unsigned int CPD_0 =  d>0?cpd_all[d-1]:1023;
			unsigned int CPD_2 =  d<Dmax-1?cpd_all[d+1]:1023;


			//分母
			unsigned int third_bit = 0;
			int dividend = 0;
			int divisor = 1023;
		    if( CPD_0 >= CPD_2 )
			{
				third_bit = 0;
				dividend = CPD_0 - CPD_2;
				divisor  = CPD_0 - CPD_1;
			}
			else
			{
				third_bit = 4;
				dividend = CPD_2 - CPD_0;
				divisor  = CPD_2 - CPD_1;   
			}

			unsigned int two_bits = 0;
			if (dividend*4 < divisor )
				two_bits = 0;
			else if (dividend*2 < divisor)
				two_bits = 1;
			else if (dividend*4 < divisor*3)
				two_bits = 2;
			else if (dividend < divisor)
				two_bits = 3;	
			else
				two_bits = 0;
			
			frac.at<uchar>(row,col) = uchar(two_bits + third_bit);
	
		}
		else
			frac.at<uchar>(row,col) = 0;

	}
}

void combine_int_frac(Mat &disp,Mat &frac,int width,int height,Mat &disp_combine, int Dmax)
{
	for(int row = 0; row < height; row ++)
		for(int col = 0; col < width ; col ++)
		{
			uchar integer_t = disp.at<uchar>(row,col);
			uchar frac_tmp = frac.at<uchar>(row+6,col+6);

			if(row == 1 && col == 8)
				cout<<int(integer_t)<<"  "<<int(frac_tmp)<<endl;

			if (integer_t == 0)
				disp_combine.at<uchar>(row,col) = 0;
			else
			{
				if (frac_tmp >= 4)
					disp_combine.at<uchar>(row,col) = uchar(integer_t*4 +4-frac_tmp);
				else
					disp_combine.at<uchar>(row,col) = uchar(integer_t*4 +frac_tmp);
			}


		}
}

//8位亚像素
void cal_frac_float(vector< vector<LR_TYPE> > cpds,Mat &disp,int width,int height,Mat &frac, Mat &frac_flag, int Dmax)
{
	//ofstream outfile("frac.txt");
	for(int row = 0; row < height; row ++)
		for(int col = 0; col < width ; col ++)
		{

			unsigned int d = disp.at<uchar>(row,col);
			vector<LR_TYPE> cpd_all = cpds[row*width + col];

			unsigned int CPD_1 =  cpd_all[d];
			unsigned int CPD_0 =  d>0?cpd_all[d-1]:cpd_all[1];
			unsigned int CPD_2 =  d<Dmax-1?cpd_all[d+1]:cpd_all[Dmax-2];

			
			float fraction = (2.0*CPD_0 + 2.0*CPD_2 - 4.0*CPD_1)==0 ? 0 :(CPD_0*1.0 - CPD_2*1.0)/(2.0*CPD_0 + 2.0*CPD_2 - 4.0*CPD_1);
			int fraction_flag = 0;
			unsigned char fraction_256 = 0; 
			if(fraction >= 0 )
			{
				frac.at<uchar>(row,col) = fraction*256;
				fraction_256 = fraction*256;
				frac_flag.at<uchar>(row,col) = 0;
			}else
			{
				frac.at<uchar>(row,col) = abs(fraction*256);
				fraction_256 = abs(fraction*256);
				frac_flag.at<uchar>(row,col) = 1;
				fraction_flag = 1;
			}

			if(row == 2 && col == 16)
			{
				cout<<d<<endl;
				cout<<CPD_1<<"  "<<CPD_0<<"  "<<CPD_2<<endl;
				cout<<fraction_flag<<"   "<<int(fraction_256)<<endl;
			}


		}

}

//整数与8位亚像素结合
void combine_int_float(Mat &disp, Mat &frac, Mat &frac_flag, Mat &disp_combine, int Dmax)
{
	for(int row = 0; row < disp.rows; row ++)
		for(int col = 0; col < disp.cols ; col ++)
		{
			uchar integer_t = disp.at<uchar>(row,col);
			//uchar integer_real = integer_t<32?integer_t:2*integer_t - 32;
			uchar frac_tmp  = frac.at<uchar>(row,col);
			uchar fraction_flag = frac_flag.at<uchar>(row,col);
			if (integer_t != 0)
				disp_combine.at<unsigned short>(row,col) =  fraction_flag > 0 ? (integer_t)*256 - frac_tmp  : integer_t*256 + frac_tmp;
			else
				disp_combine.at<unsigned short>(row,col) = 0;

		}
}

void LRcheck(Mat &dispL,Mat &dispR, Mat &dispL_check, int width, int height, int threshold, int Dmax)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			 uchar left_d = dispL.at<uchar>(row,col);
			 uchar right_d =0;
			 if ( col-left_d >= 0)
				right_d = dispR.at<uchar>(row,col-left_d);
			 else
				right_d = left_d + 3;

			if (abs(left_d - right_d)> threshold  || left_d < 1)
			{
				dispL_check.at<uchar>(row,col) = 0;

			}
			else
			{
				dispL_check.at<uchar>(row,col) = left_d;
			}
		
		}
	}
}

//去噪声
void SpotCheck16Bits(Mat &disp_in, Mat &disp_out)
{
	int width	= disp_in.cols;
	int height	= disp_in.rows;
	int windowRow = 3;
	int windowCol = 3;
	int dataDiff  = 3*256;
	disp_out	= Mat::zeros(disp_in.size(),disp_in.type());
	typedef short IMGTYPE;
	for (int row = windowRow; row < height-windowRow; row++)
	{
		for (int col = windowCol; col < width-windowCol; col++)
		{

			int count_num = 0;
			IMGTYPE data_centor = disp_in.at<IMGTYPE>(row, col);
			for (int m = -windowCol; m <= windowCol; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row-windowRow, col+m);
				if (data_tmp + dataDiff < data_centor)
					count_num++;
			}
			for (int m = -windowCol; m <= windowCol; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+windowRow, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}
			for (int m = -windowRow + 1; m <= windowRow - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col+windowCol);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}	
			for (int m = -windowRow + 1; m <= windowRow - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col-windowCol);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}	

			//7x7的窗口统计
			int count_num_5 = 0;
			int windowW     = 2;

			for (int m = -windowW; m <= windowW; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row-windowW, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}
			for (int m = -windowW; m <= windowW; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+windowW, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}
			for (int m = -windowW + 1; m <= windowW - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col+windowW);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}	
			for (int m = -windowW + 1; m <= windowW - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col-windowW);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}

			///////count_num 24 ;count_num_5  16
			if (count_num > 20 || count_num_5 > 12 )   //一共24个点
				disp_out.at<IMGTYPE>(row,col) = 0;
			else
				disp_out.at<IMGTYPE>(row,col) = disp_in.at<IMGTYPE>(row, col);

		}
	}
}

//填洞
void SpotCheck16Bits_1(Mat &disp_in, Mat &disp_out)
{
	int width	= disp_in.cols;
	int height	= disp_in.rows;
	int windowRow = 3;
	int windowCol = 3;
	int dataDiff  = 3*256;
	disp_out	= Mat::zeros(disp_in.size(),disp_in.type());
	typedef short IMGTYPE;
	for (int row = 2*windowRow; row < height-2*windowRow; row++)
	{
		for (int col = 2*windowCol; col < width-2*windowCol; col++)
		{

			int count_num = 0;
			IMGTYPE data_centor = disp_in.at<IMGTYPE>(row, col);
			for (int m = -windowCol; m <= windowCol; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row-windowRow, col+m);
				if (data_tmp + dataDiff < data_centor)
					count_num++;
			}
			for (int m = -windowCol; m <= windowCol; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+windowRow, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}
			for (int m = -windowRow + 1; m <= windowRow - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col+windowCol);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}	
			for (int m = -windowRow + 1; m <= windowRow - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col-windowCol);
				if (data_tmp + dataDiff  < data_centor)
					count_num++;
			}	

			//7x7的窗口统计
			int count_num_5 = 0;
			int windowW     = 3;

			for (int m = -windowW; m <= windowW; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row-windowW, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}
			for (int m = -windowW; m <= windowW; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+windowW, col+m);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}
			for (int m = -windowW + 1; m <= windowW - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col+windowW);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}	
			for (int m = -windowW + 1; m <= windowW - 1; m++)
			{	
				IMGTYPE data_tmp = disp_in.at<IMGTYPE>(row+m, col-windowW);
				if (data_tmp + dataDiff  < data_centor)
					count_num_5++;
			}

			int data_left =0;
			int data_right =0;
			int data_up =0;
			int data_down =0;
			//left
			for (int m = -1; m >= -windowCol; m--)
			{
				int data_tmp = disp_in.at<IMGTYPE>(row, col+m);
				if (data_tmp != 0)
				{
					data_left = data_tmp;
					break;
				}

			}

			//right
			for (int m = 1; m <= windowCol; m++)
			{
				int data_tmp = disp_in.at<IMGTYPE>(row, col+m);
				if (data_tmp != 0)
				{
					data_right = data_tmp;
					break;
				}

			}
			//up
			for (int m = -1; m >= -windowRow; m--)
			{
				int data_tmp = disp_in.at<IMGTYPE>(row+m, col);
				if (data_tmp != 0)
				{
					data_up = data_tmp;
					break;
				}

			}

			for (int m = 1; m <= windowRow; m++)
			{
				int data_tmp = disp_in.at<IMGTYPE>(row+m, col);
				if (data_tmp != 0)
				{
					data_down = data_tmp;
					break;
				}

			}

			int average = (data_left + data_right + data_up + data_down)/4;

			int min_1 = data_left < data_right ? data_left : data_right;
			int min_2 = data_up < data_down ? data_up : data_down;
			int min_3 = min_1 < min_2 ? min_2 : min_1;


			if (disp_in.at<IMGTYPE>(row, col) == 0 && min_3 > 0)
				disp_out.at<IMGTYPE>(row,col) = min_3;
			//else if (count_num > 20 || count_num_5 > 12 ) 
			//	disp_out.at<IMGTYPE>(row,col) = 0;
			else
				disp_out.at<IMGTYPE>(row,col) = disp_in.at<IMGTYPE>(row, col);
		}
	}
}



Mat MedianFilter5x5(Mat &disp_in)
{
	int height = disp_in.rows;
	int width  = disp_in.cols;

	int windows_w = 2;
	int windows_h = 2;


	Mat disp_tmp(height-2*windows_h,width-2*windows_w,CV_8UC1,Scalar(0));




	//ofstream sortfile("sortfile.txt");
	for (int row = windows_h; row < height - windows_h; row++)
	{		
		for (int col = windows_w; col < width - windows_w; col++)
		{
			vector<uchar> row11_sort;
			for(int col_n = -windows_w;col_n<= windows_w;col_n++)
			{
				vector<uchar> col5_sort;
				for(int row_m = -windows_h;row_m<= windows_h ;row_m++)
				{
					col5_sort.push_back(disp_in.at<uchar>(row + row_m,col + col_n));
				}
				sort(col5_sort.begin(),col5_sort.end());
				row11_sort.push_back(col5_sort[windows_h]);

			}
			sort(row11_sort.begin(),row11_sort.end());
			disp_tmp.at<uchar>(row-windows_h,col-windows_w) = row11_sort[windows_w];

		}
	}
	return disp_tmp;
	

}

Mat MedianFilter5x5_16bits(Mat &disp_in)
{
	int height = disp_in.rows;
	int width  = disp_in.cols;

	int windows_w = 2;
	int windows_h = 2;

	Mat disp_tmp(height,width,CV_16UC1,Scalar(0));


	//ofstream sortfile("sortfile.txt");
	for (int row = windows_h + 6; row < height - windows_h -6; row++)
	{		
		for (int col = windows_w + 6; col < width - windows_w -6; col++)
		{
			vector<unsigned short> row11_sort;
			for(int col_n = -windows_w;col_n<= windows_w;col_n++)
			{
				vector<unsigned short> col5_sort;
				for(int row_m = -windows_h;row_m<= windows_h ;row_m++)
				{
					col5_sort.push_back(disp_in.at<unsigned short>(row + row_m,col + col_n));
				}
				sort(col5_sort.begin(),col5_sort.end());
				row11_sort.push_back(col5_sort[windows_h]);

			}
			sort(row11_sort.begin(),row11_sort.end());
			disp_tmp.at<unsigned short>(row,col) = row11_sort[windows_w];

		}
	}
	return disp_tmp;


}




