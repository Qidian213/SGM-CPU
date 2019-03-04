#include"cost.h"

int Count1(long long col)  
{  
    int c=0;  
    while(col)  
    {  
        col&=col-1;  
        c++;  
    }  
    return c;  
} 


//与窗口中的5x5均值作比较
void CalulateCT( Mat &src, vector<long long> &CT, int width, int height, int windows_r, int windows_c)
{

	for (int row = windows_r; row < height - windows_r; row++)
		for (int col = windows_c; col < width - windows_c; col++)
		{
			long long res = 0;
			int sum =0;
			for (int m = -2; m <= 2; m++)
				for (int n = -2; n <= 2; n++)
				{
					sum += src.at<uchar>(row+m, col+n);
				}


			for (int m = -windows_r; m <= windows_r; m++)
				for (int n = -windows_c; n <= windows_c; n++)
				{
					res <<= 1;
					if(src.at<uchar>(row+m, col+n) < sum/25)
					{	
						res |= 1;
					}
				}

			CT.push_back(res);
		}
}

//求均值用16个值
void CalulateCT_1( Mat &src, vector<long long> &CT, int width, int height, int windows_r, int windows_c)
{

	for (int row = windows_r; row < height - windows_r; row++)
		for (int col = windows_c; col < width - windows_c; col++)
		{
			long long res = 0;
			int sum =0;
			for (int m = -1; m <= 2; m++)
				for (int n = -1; n <= 2; n++)
				{
					sum += src.at<uchar>(row+m, col+n);
				}

			//if(row == 4 && col == 8)
			//	cout<<(sum/16)<<endl;

			for (int m = -windows_r; m <= windows_r; m++)
				for (int n = -windows_c; n <= windows_c; n++)
				{
					res <<= 1;
					if(src.at<uchar>(row+n, col+m) < sum/16)
					{	
						res |= 1;
					}
				}

			CT.push_back(res);
		}
}

void AD_single( Mat &src,int width,int height,unsigned int *dst, int windows_r, int windows_c)
{
	int index= 0;
	for (int row = windows_r; row < height - windows_r; row++)
		for (int col = windows_c; col < width - windows_c; col++)
		{
			int sum =0;
			for (int m = -1; m <= 2; m++)
				for (int n = -1; n <= 2; n++)
				{
					sum += src.at<unsigned char>(row+m, col+n);
				}
				sum = sum/16;


				int sum_ad = 0;
				for (int m = -2; m <= 2; m++)
					for (int n = -2; n <= 2; n++)
					{
						sum_ad += abs(src.at<unsigned char>(row+m, col+n) - sum);
					}

					dst[index++] = sum_ad;
		}
}

void hamin(unsigned int *src1,unsigned int *src2,int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid)
{
	//ofstream of("hamin.txt");
	for(int row = 0; row < height ; row ++)
	{
		//int ii = row;
		for(int col = 0; col < width  ; col ++)
		{
			vector<LR_TYPE> cpd;
			unsigned int left = src1[row*width + col];
			for(int i = 0; i < Dmax; i++)
			{
				if(col>=i)
				{
					unsigned int right = src2[row*width + col - i];
					unsigned int xor_res = left^right;
					int cnt = Count1(xor_res);
					cpd.push_back(Count1(xor_res));
					//of << cnt << " ";
				}else
				{
					cpd.push_back(init_valid);
					//of << 12 << " ";
				}
			}
			cpds.push_back(cpd);
			//of << endl;
		}
	}
}

void hamin_96(vector<long long> &CT_L, vector<long long> &CT_R, int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid)
{
	//ofstream of("hamin.txt");
	for(int row = 0; row < height ; row ++)
	{
		//int ii = row;
		for(int col = 0; col < width  ; col ++)
		{
			vector<LR_TYPE> cpd;
			long long left = CT_L[row*width + col];
			for(int i = 0; i < Dmax; i++)
			{
				if(col>=i)
				{
					long long right = CT_R[row*width + col - i];
					long long xor_res = left^right;
					float cnt = Count1(xor_res);
					cpd.push_back(Count1(xor_res));
				}else
				{
					cpd.push_back(init_valid);
				}
			}
			//for(int i = 32; i < 96; i+=2)
			//{
			//	if(col>=i)
			//	{
			//		long long right = CT_R[row*width + col - i];
			//		long long xor_res = left^right;
			//		int cnt = Count1(xor_res);
			//		cpd.push_back(Count1(xor_res));
			//		//of << cnt << " ";
			//	}else
			//	{
			//		cpd.push_back(init_valid);
			//		//of << 24 << " ";
			//	}
			//}	
			cpds.push_back(cpd);
		}
	}
}


void cost_AD(unsigned int *src1,unsigned *src2,int width, int height, vector< vector<LR_TYPE> > &cpds, int Dmax, LR_TYPE init_valid)
{

	for(int row = 0; row < height ; row ++)
	{
		for(int col = 0; col < width  ; col ++)
		{
			vector<LR_TYPE> cpd;
			LR_TYPE left = src1[row*width + col];
			for(int i = 0; i < Dmax; i++)
			{
				LR_TYPE xor_res = 0;
				if(col>=i)
				{
					LR_TYPE right = src2[row*width + col - i];
					if (left > right)
						xor_res = left - right;
					else
					  	xor_res = right - left;
					if (xor_res >= init_valid)
						xor_res = init_valid;
					cpd.push_back(xor_res);
					
				}else				
					cpd.push_back(init_valid);				
			}
/*			for(int i = 32; i < 96; i+=2)
			{
				LR_TYPE xor_res = 0;
				if(col>=i)
				{
					LR_TYPE right = src2[row*width + col - i];
					
					if (left > right)
						xor_res = left - right;
					else
					  	xor_res = right - left;

					if (xor_res >= init_valid)
						xor_res = init_valid;

					cpd.push_back(xor_res);
									
				}else				
					cpd.push_back(init_valid);			
			}*/	
			cpds.push_back(cpd);

		}
	}
}


void adCensus(vector< vector<LR_TYPE> > &cost_ad, vector< vector<LR_TYPE> > &cost_census, vector< vector<LR_TYPE> > &cost_adcensus, LR_TYPE alpha,  int width, int height, int Dmax)
{
	for(int row = 0; row < height ; row ++)
	{
		for(int col = 0; col < width  ; col ++)
		{
			vector<LR_TYPE> c_ad,c_census;
			vector<LR_TYPE> c_adcensus;
			c_ad     = cost_ad[row*width + col];
			c_census = cost_census[row*width + col];

			for(int i = 0; i < Dmax; i++)
			{
				LR_TYPE dist_uint;

				dist_uint = c_ad[i]*alpha/16 + (16 - alpha)*c_census[i]/16;

				c_adcensus.push_back(dist_uint);


			}

			//if (row == 0 && col == 54)
			//{
			//	for(int i = 63 ;i>=0;i--)
			//		cout<<dec<<i<<" "<<hex<<c_adcensus[i]<<endl;
			//}
			cost_adcensus.push_back(c_adcensus);



			
		}
	}
}


void adCensusSky1(vector< vector<LR_TYPE> > &cost_ad, vector< vector<LR_TYPE> > &cost_census, vector< vector<LR_TYPE> > &cost_adcensus, LR_TYPE alpha,  int width, int height, int Dmax, Mat &sky_)
{
	LR_TYPE max_ad=0;
	for(int row = 0; row < height ; row ++)
	{
		for(int col = 0; col < width  ; col ++)
		{
			vector<LR_TYPE> c_ad,c_census;
			vector<LR_TYPE> c_adcensus;
			c_ad     = cost_ad[row*width + col];
			c_census = cost_census[row*width + col];

			LR_TYPE dist_uint;

			for(int i = 0; i < Dmax; i++)
			{

				//dist_uint = c_ad[i]*alpha/32 + (32 - alpha)*c_census[i]/32;
				dist_uint = c_ad[i] + c_census[i];
				//if (c_ad[i] < c_census[i])
				//	dist_uint = c_ad[i];
				//else
				//	dist_uint = c_census[i];

				if (max_ad < dist_uint)
					max_ad = dist_uint;

				//if ( sky_.at<uchar>(row,col) == 0)		
				c_adcensus.push_back(dist_uint);



			}

			cost_adcensus.push_back(c_adcensus);




		}
	}

	cout<<"max_ad: "<<max_ad<<endl;
}

void GetRightCosts(vector< vector<LR_TYPE> >& cpds,int width, int height, int disp_N, vector< vector<LR_TYPE> >& new_cpds, LR_TYPE invalid_data)
{
	for(int row = 0; row < height; row ++)
		for(int col = 0; col < width ; col ++)
		{
			vector<LR_TYPE> new_cpd;
			for(int d = 0; d < disp_N; d++)
			{
				if(col +d < width )
					new_cpd.push_back(cpds[row*width + col +d][d]);
				else
					new_cpd.push_back(invalid_data*4);
			}
			new_cpds.push_back(new_cpd);
		}
}

void weight_c_cal(Mat &image, int height, int width, int window_size,  int gamma, vector<vector<float> > &weight_c)
{
	//计算色彩（灰度）权重
	for(int row = window_size;row < height - window_size;row++)
	{
		for(int col = window_size;col < width - window_size;col++)
		{
			//窗口
			vector<float> weight_1;
			for(int i = -window_size;i <= window_size;i++)
			{
				for(int j = -window_size;j <= window_size;j++)
				{
					unsigned char gray_diff = abs(image.at<uchar>(row,col) - image.at<uchar>(row + i,col + j));
					float exp_gray_diff = - pow(gray_diff,2);
					float weight = exp(exp_gray_diff/(2*gamma*gamma));
					weight_1.push_back(weight);
				}
			}
			weight_c.push_back(weight_1);
		}
	}

	cout<<"weight_c_cal complete"<<endl;

}

//空间权重无需重复计算,仅与窗口大小相关
void weight_r_cal(int window_size,  int gamma, vector<float> &weight_r)
{
	for(int i = -window_size;i <= window_size;i++)
	{
		for(int j = -window_size;j <= window_size;j++)
		{
			int range = -(i)*(i) - (j)*(j);
			int weight = exp(range/(2*gamma*gamma));
			weight_r.push_back(weight);
		}
	}

	cout<<"weight_r_cal complete"<<endl;
}

unsigned int match_cost_bf(int row, int col, char d, int window_size, vector<vector<float> > &weight_c, vector<float> &weight_r, Mat &hm,Mat &hm_1)
{
	int width = 640 - window_size*2;
	unsigned int cost_new     = 0;
	float sum_weight = 0.0;
	for(int i = -window_size;i <= window_size;i++)
	{
		for(int j = -window_size;j <= window_size;j++)
		{
			float a = weight_c[(row-window_size)*width+(col-window_size)][(i+window_size)*(2*window_size+1)+(j+window_size)]* weight_r[(i+window_size)*(2*window_size+1)+(j+window_size)];
			sum_weight += a;
			int gray_diff = (col+j-d)>d ? abs( hm.at<uchar>(row+i,col+j) - hm_1.at<uchar>(row+i,col+j-d) ) : 255;
			cost_new   += a*gray_diff;
		}
	}
	cost_new = cost_new/sum_weight;
	return cost_new;
}


