#include"prefilter.h"



void sobel_x(Mat &src, Mat &dst, int preFilterCap, int height, int width)
{
	dst = Mat::zeros(cv::Size(width-2, height-2), CV_8UC1);
	for (int row = 1; row < height-1; row++)
		for (int col = 1; col < width-1; col++)
		{
			int value_result=0;
			int sum = -src.at<uchar>(row-1,col-1) - 2*src.at<uchar>(row,col-1) - src.at<uchar>(row+1,col-1)
				+src.at<uchar>(row-1,col+1) + 2*src.at<uchar>(row,col+1) + src.at<uchar>(row+1,col+1);

			//int sum = -src.at<uchar>(row-1,col-1) - 2*src.at<uchar>(row,col-1) - src.at<uchar>(row+1,col-1)
			//	+src.at<uchar>(row-1,col) + 2*src.at<uchar>(row,col) + src.at<uchar>(row+1,col);

			//int sum = (src.at<uchar>(row,col) -src.at<uchar>(row,col-1));


			if (sum < -preFilterCap)
				value_result = 0;
			else if (sum >= preFilterCap)
			{
				value_result = 2*preFilterCap;

			}
			else
				value_result = sum + preFilterCap;


			dst.at<uchar>(row-1,col-1) = value_result;

		}


}


void SqureMean(Mat &src, Mat &dst, int W)
{
	int height = src.rows;
	int width = src.cols;
	dst = Mat::zeros(cv::Size(width, height), CV_8UC1);
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
		{
			int sum = 0; int cnt = 0;
			for (int ii = -1 * W / 2; ii <= W / 2; ii++)
				for (int jj = -1 * W / 2; jj <= W / 2; jj++)
				{
					int row_cur = row + ii;
					int col_cur = col + jj;
					if (row_cur < height && row_cur >= 0 && col_cur >= 0 && col_cur < width)
					{
						sum += src.at<unsigned char>(row_cur, col_cur);
						cnt++;
					}
					if (cnt >0)
					{
						int mean = sum*1.0 / cnt;
						int em_sum = 0;
						if (row_cur < height && row_cur >= 0 && col_cur >= 0 && col_cur < width)
						{
							em_sum += (src.at<unsigned char>(row_cur, col_cur) - mean)*(src.at<unsigned char>(row_cur, col_cur) - mean);
						}

						dst.at<unsigned char>(row, col) = sqrt(1.0*em_sum / cnt)*12;
					}
				}
		}
}

Mat MedianFilter3x3(Mat &dispL)
{
	int height = dispL.rows;
	int width = dispL.cols;
	Mat disp_median(height-2, width-2, CV_8UC1);

	//ofstream sortfile("sortfile.txt");
	for (int row = 1; row < height - 1; row++)
	{
		for (int col = 1; col < width - 1; col++)
		{			
			vector<uchar> col1_tmp;
			vector<uchar> col2_tmp;
			vector<uchar> col3_tmp;

			for(int row_m = -1;row_m<=1;row_m++)
			{
				uchar d_tmp = dispL.at<uchar>(row+row_m,col-1);
				col1_tmp.push_back(d_tmp);
				d_tmp = dispL.at<uchar>(row+row_m,col);
				col2_tmp.push_back(d_tmp);
				d_tmp = dispL.at<uchar>(row+row_m,col+1);
				col3_tmp.push_back(d_tmp);

			}

			sort(col1_tmp.begin(),col1_tmp.end());
			sort(col2_tmp.begin(),col2_tmp.end());
			sort(col3_tmp.begin(),col3_tmp.end());

			vector<uchar> row1_tmp;
			vector<uchar> row2_tmp;
			vector<uchar> row3_tmp;
			row1_tmp.push_back(col1_tmp[0]);
			row1_tmp.push_back(col2_tmp[0]);
			row1_tmp.push_back(col3_tmp[0]);

			row2_tmp.push_back(col1_tmp[1]);
			row2_tmp.push_back(col2_tmp[1]);
			row2_tmp.push_back(col3_tmp[1]);

			row3_tmp.push_back(col1_tmp[2]);
			row3_tmp.push_back(col2_tmp[2]);
			row3_tmp.push_back(col3_tmp[2]);

			sort(row1_tmp.begin(),row1_tmp.end());
			sort(row2_tmp.begin(),row2_tmp.end());
			sort(row3_tmp.begin(),row3_tmp.end());


			vector<uchar> final_3;
			final_3.push_back(row1_tmp[2]);
			final_3.push_back(row2_tmp[1]);
			final_3.push_back(row3_tmp[0]);

			sort(final_3.begin(),final_3.end());


			disp_median.at<uchar>(row-1,col-1) = final_3[1];

		}
	}

	return disp_median;
}

