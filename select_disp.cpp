#include"select_disp.h"




void GetMinIndex(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{

	vector<LR_TYPE>::iterator minist = std::min_element(cpds.begin(), cpds.end());  
	int minIndex = minist - cpds.begin();

	dataMin	 = cpds[minIndex];
	indexMin = cpdsIndex[minIndex];

}

void GetMinIndex_l1(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{

	vector<LR_TYPE> cpd_1;
	vector<LR_TYPE> cpd_2;
	vector<LR_TYPE> cpd_3;
	vector<LR_TYPE> cpd_4;
	vector<LR_TYPE> cpd_5;

	vector<LR_TYPE> cpd_num_1 ;
	vector<LR_TYPE> cpd_num_2 ;
	vector<LR_TYPE> cpd_num_3 ;
	vector<LR_TYPE> cpd_num_4 ;
	vector<LR_TYPE> cpd_num_5 ;

	//第一级 32 -16
	for(int i = 0;i<32;i+=2)
	{
		if(cpds[i] <= cpds[i+1])
		{
			cpd_1.push_back(cpds[i]);
			cpd_num_1.push_back(cpdsIndex[i]);
		}
		else
		{
			cpd_1.push_back(cpds[i+1]);
			cpd_num_1.push_back(cpdsIndex[i+1]);
		}
	}
	//第二级 16 -8
	for(int i = 0;i<16;i+=2)
	{
		if(cpd_1[i] <= cpd_1[i+1])
		{
			cpd_2.push_back(cpd_1[i]);
			cpd_num_2.push_back(cpd_num_1[i]);
		}
		else
		{
			cpd_2.push_back(cpd_1[i+1]);
			cpd_num_2.push_back(cpd_num_1[i+1]);
		}
	}
	//第三级8 - 4
	for(int i = 0;i < 8;i+=2)
	{
		if(cpd_2[i] <= cpd_2[i+1])
		{
			cpd_3.push_back(cpd_2[i]);
			cpd_num_3.push_back(cpd_num_2[i]);
		}
		else
		{
			cpd_3.push_back(cpd_2[i+1]);
			cpd_num_3.push_back(cpd_num_2[i+1]);
		}
	}
	//第四级4 - 2
	for(int i = 0;i<4;i+=2)
	{
		if(cpd_3[i] <= cpd_3[i+1])
		{
			cpd_4.push_back(cpd_3[i]);
			cpd_num_4.push_back(cpd_num_3[i]);
		}
		else
		{
			cpd_4.push_back(cpd_3[i+1]);
			cpd_num_4.push_back(cpd_num_3[i+1]);
		}
	}
	//第五级 2 - 1
	for(int i = 0;i<2;i+=2)
	{
		if(cpd_4[i] <= cpd_4[i+1])
		{
			cpd_5.push_back(cpd_4[i]);
			cpd_num_5.push_back(cpd_num_4[i]);
		}
		else
		{
			cpd_5.push_back(cpd_4[i+1]);
			cpd_num_5.push_back(cpd_num_4[i+1]);
		}
	}

	dataMin	 = cpd_5[0];
	indexMin = cpd_num_5[0];

}

void GetMinIndex_l2(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{


	vector<LR_TYPE> cpd_2;
	vector<LR_TYPE> cpd_3;
	vector<LR_TYPE> cpd_4;
	vector<LR_TYPE> cpd_5;

	vector<LR_TYPE> cpd_num_2 ;
	vector<LR_TYPE> cpd_num_3 ;
	vector<LR_TYPE> cpd_num_4 ;
	vector<LR_TYPE> cpd_num_5 ;

	//第二级 16 -8
	for(int i = 0;i<16;i+=2)
	{
		if(cpds[i] <= cpds[i+1])
		{
			cpd_2.push_back(cpds[i]);
			cpd_num_2.push_back(cpdsIndex[i]);
		}
		else
		{
			cpd_2.push_back(cpds[i+1]);
			cpd_num_2.push_back(cpdsIndex[i+1]);
		}
	}
	//第三级8 - 4
	for(int i = 0;i < 8;i+=2)
	{
		if(cpd_2[i] <= cpd_2[i+1])
		{
			cpd_3.push_back(cpd_2[i]);
			cpd_num_3.push_back(cpd_num_2[i]);
		}
		else
		{
			cpd_3.push_back(cpd_2[i+1]);
			cpd_num_3.push_back(cpd_num_2[i+1]);
		}
	}
	//第四级4 - 2
	for(int i = 0;i<4;i+=2)
	{
		if(cpd_3[i] <= cpd_3[i+1])
		{
			cpd_4.push_back(cpd_3[i]);
			cpd_num_4.push_back(cpd_num_3[i]);
		}
		else
		{
			cpd_4.push_back(cpd_3[i+1]);
			cpd_num_4.push_back(cpd_num_3[i+1]);
		}
	}
	//第五级 2 - 1
	for(int i = 0;i<2;i+=2)
	{
		if(cpd_4[i] <= cpd_4[i+1])
		{
			cpd_5.push_back(cpd_4[i]);
			cpd_num_5.push_back(cpd_num_4[i]);
		}
		else
		{
			cpd_5.push_back(cpd_4[i+1]);
			cpd_num_5.push_back(cpd_num_4[i+1]);
		}
	}

	dataMin	 = cpd_5[0];
	indexMin = cpd_num_5[0];

}

void GetMinIndex_l3(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{


	vector<LR_TYPE> cpd_3;
	vector<LR_TYPE> cpd_4;
	vector<LR_TYPE> cpd_5;

	vector<LR_TYPE> cpd_num_3 ;
	vector<LR_TYPE> cpd_num_4 ;
	vector<LR_TYPE> cpd_num_5 ;

	//第三级8 - 4
	for(int i = 0;i < 8;i+=2)
	{
		if(cpds[i] <= cpds[i+1])
		{
			cpd_3.push_back(cpds[i]);
			cpd_num_3.push_back(cpdsIndex[i]);
		}
		else
		{
			cpd_3.push_back(cpds[i+1]);
			cpd_num_3.push_back(cpdsIndex[i+1]);
		}
	}
	//第四级4 - 2
	for(int i = 0;i<4;i+=2)
	{
		if(cpd_3[i] <= cpd_3[i+1])
		{
			cpd_4.push_back(cpd_3[i]);
			cpd_num_4.push_back(cpd_num_3[i]);
		}
		else
		{
			cpd_4.push_back(cpd_3[i+1]);
			cpd_num_4.push_back(cpd_num_3[i+1]);
		}
	}
	//第五级 2 - 1
	for(int i = 0;i<2;i+=2)
	{
		if(cpd_4[i] <= cpd_4[i+1])
		{
			cpd_5.push_back(cpd_4[i]);
			cpd_num_5.push_back(cpd_num_4[i]);
		}
		else
		{
			cpd_5.push_back(cpd_4[i+1]);
			cpd_num_5.push_back(cpd_num_4[i+1]);
		}
	}

	dataMin	 = cpd_5[0];
	indexMin = cpd_num_5[0];

}

void GetMinIndex_l4(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{


	vector<LR_TYPE> cpd_4;
	vector<LR_TYPE> cpd_5;

	vector<LR_TYPE> cpd_num_4 ;
	vector<LR_TYPE> cpd_num_5 ;

	//第四级4 - 2
	for(int i = 0;i<4;i+=2)
	{
		if(cpds[i] <= cpds[i+1])
		{
			cpd_4.push_back(cpds[i]);
			cpd_num_4.push_back(cpdsIndex[i]);
		}
		else
		{
			cpd_4.push_back(cpds[i+1]);
			cpd_num_4.push_back(cpdsIndex[i+1]);
		}
	}
	//第五级 2 - 1
	for(int i = 0;i<2;i+=2)
	{
		if(cpd_4[i] <= cpd_4[i+1])
		{
			cpd_5.push_back(cpd_4[i]);
			cpd_num_5.push_back(cpd_num_4[i]);
		}
		else
		{
			cpd_5.push_back(cpd_4[i+1]);
			cpd_num_5.push_back(cpd_num_4[i+1]);
		}
	}

	dataMin	 = cpd_5[0];
	indexMin = cpd_num_5[0];

}

void GetMinIndex_l5(vector<LR_TYPE> & cpds, vector<LR_TYPE> & cpdsIndex, int &dataMin, int &indexMin)
{


	vector<LR_TYPE> cpd_5;

	vector<LR_TYPE> cpd_num_5 ;

	//第五级 2 - 1
	for(int i = 0;i<2;i+=2)
	{
		if(cpds[i] <= cpds[i+1])
		{
			cpd_5.push_back(cpds[i]);
			cpd_num_5.push_back(cpdsIndex[i]);
		}
		else
		{
			cpd_5.push_back(cpds[i+1]);
			cpd_num_5.push_back(cpdsIndex[i+1]);
		}
	}

	dataMin	 = cpd_5[0];
	indexMin = cpd_num_5[0];

}



void GetDispByMin(vector< vector<LR_TYPE> >& cpds, int width, int height,int disp_N,Mat &disp)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			vector<LR_TYPE> cpdPixel = cpds[row*width + col];
			vector<LR_TYPE> cpdLevelOneHigh;
			vector<LR_TYPE> cpdLevelOneLow;
			vector<LR_TYPE> cpdLevelOneHighIndex;
			vector<LR_TYPE> cpdLevelOneLowIndex;

			//第一级 64 - 32

			for(int i = 0;i< 64;i+=2)
			{
				if(cpdPixel[i] >= cpdPixel[i+1])
				{
					cpdLevelOneHigh.push_back(cpdPixel[i]);
					cpdLevelOneHighIndex.push_back(i);
					cpdLevelOneLow.push_back(cpdPixel[i+1]);
					cpdLevelOneLowIndex.push_back(i+1);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdPixel[i+1]);
					cpdLevelOneHighIndex.push_back(i+1);
					cpdLevelOneLow.push_back(cpdPixel[i]);
					cpdLevelOneLowIndex.push_back(i);
				}
			}
			//if (row == 100 && col == 100)
			//	for (int i = 0;i < 60;i++)
			//	{
			//		cout<<int(cpdLevelOneHigh[i])<<"  "<<int(cpdLevelOneHighIndex[i])<<endl;
			//	}

			int dataMin1  = 0;
			int indexMin1 = 0;
			GetMinIndex_l1(cpdLevelOneHigh,cpdLevelOneHighIndex,dataMin1, indexMin1);
			cpdLevelOneHigh.clear();
			cpdLevelOneHighIndex.clear();

;
			//第二级 32 - 16
			vector<LR_TYPE> cpdLevel2Low;
			vector<LR_TYPE> cpdLevel2LowIndex;
			for(int i = 0;i< 32;i+=2)
			{
				if(cpdLevelOneLow[i] >= cpdLevelOneLow[i+1])
				{
					cpdLevelOneHigh.push_back(cpdLevelOneLow[i]);
					cpdLevelOneHighIndex.push_back(cpdLevelOneLowIndex[i]);
					cpdLevel2Low.push_back(cpdLevelOneLow[i+1]);
					cpdLevel2LowIndex.push_back(cpdLevelOneLowIndex[i+1]);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdLevelOneLow[i+1]);
					cpdLevelOneHighIndex.push_back(cpdLevelOneLowIndex[i+1]);
					cpdLevel2Low.push_back(cpdLevelOneLow[i]);
					cpdLevel2LowIndex.push_back(cpdLevelOneLowIndex[i]);
				}
			}

			int dataMin2  = 0;
			int indexMin2 = 0;
			GetMinIndex_l2(cpdLevelOneHigh,cpdLevelOneHighIndex,dataMin2, indexMin2);
			cpdLevelOneHigh.clear();
			cpdLevelOneHighIndex.clear();

			//把较小值保留在datamin1
			if( dataMin2 <= dataMin1)
			{
				dataMin1  = dataMin2;
				indexMin1 = indexMin2;
			}

			//第三级 16 - 8 
			vector<LR_TYPE> cpdLevel3Low;
			vector<LR_TYPE> cpdLevel3LowIndex;
			for(int i = 0;i< 16;i+=2)
			{
				if(cpdLevel2Low[i] >= cpdLevel2Low[i+1])
				{
					cpdLevelOneHigh.push_back(cpdLevel2Low[i]);
					cpdLevelOneHighIndex.push_back(cpdLevel2LowIndex[i]);
					cpdLevel3Low.push_back(cpdLevel2Low[i+1]);
					cpdLevel3LowIndex.push_back(cpdLevel2LowIndex[i+1]);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdLevel2Low[i+1]);
					cpdLevelOneHighIndex.push_back(cpdLevel2LowIndex[i+1]);
					cpdLevel3Low.push_back(cpdLevel2Low[i]);
					cpdLevel3LowIndex.push_back(cpdLevel2LowIndex[i]);
				}
			}

			int dataMin3  = 0;
			int indexMin3 = 0;
			GetMinIndex_l3(cpdLevelOneHigh,cpdLevelOneHighIndex,dataMin3, indexMin3);
			cpdLevelOneHigh.clear();
			cpdLevelOneHighIndex.clear();

			//把较小值保留在datamin1
			if( dataMin3 <= dataMin1)
			{
				dataMin1  = dataMin3;
				indexMin1 = indexMin3;
			}



			//第四级 8 - 4
			vector<LR_TYPE> cpdLevel4Low;
			vector<LR_TYPE> cpdLevel4LowIndex;
			for(int i = 0;i< 8;i+=2)
			{
				if(cpdLevel3Low[i] >= cpdLevel3Low[i+1])
				{
					cpdLevelOneHigh.push_back(cpdLevel3Low[i]);
					cpdLevelOneHighIndex.push_back(cpdLevel3LowIndex[i]);
					cpdLevel4Low.push_back(cpdLevel3Low[i+1]);
					cpdLevel4LowIndex.push_back(cpdLevel3LowIndex[i+1]);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdLevel3Low[i+1]);
					cpdLevelOneHighIndex.push_back(cpdLevel3LowIndex[i+1]);
					cpdLevel4Low.push_back(cpdLevel3Low[i]);
					cpdLevel4LowIndex.push_back(cpdLevel3LowIndex[i]);
				}
			}

			int dataMin4  = 0;
			int indexMin4 = 0;
			GetMinIndex_l4(cpdLevelOneHigh,cpdLevelOneHighIndex,dataMin4, indexMin4);
			cpdLevelOneHigh.clear();
			cpdLevelOneHighIndex.clear();


			//把较小值保留在datamin1
			if( dataMin4 <= dataMin1)
			{
				dataMin1  = dataMin4;
				indexMin1 = indexMin4;
			}

			//第五级 4 - 2
			vector<LR_TYPE> cpdLevel5Low;
			vector<LR_TYPE> cpdLevel5LowIndex;
			for(int i = 0;i< 4;i+=2)
			{
				if(cpdLevel4Low[i] >= cpdLevel4Low[i+1])
				{
					cpdLevelOneHigh.push_back(cpdLevel4Low[i]);
					cpdLevelOneHighIndex.push_back(cpdLevel4LowIndex[i]);
					cpdLevel5Low.push_back(cpdLevel4Low[i+1]);
					cpdLevel5LowIndex.push_back(cpdLevel4LowIndex[i+1]);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdLevel4Low[i+1]);
					cpdLevelOneHighIndex.push_back(cpdLevel4LowIndex[i+1]);
					cpdLevel5Low.push_back(cpdLevel4Low[i]);
					cpdLevel5LowIndex.push_back(cpdLevel4LowIndex[i]);
				}
			}

			int dataMin5  = 0;
			int indexMin5 = 0;
			GetMinIndex_l5(cpdLevelOneHigh,cpdLevelOneHighIndex,dataMin5, indexMin5);
			cpdLevelOneHigh.clear();
			cpdLevelOneHighIndex.clear();

			//把较小值保留在datamin1
			if( dataMin5 <= dataMin1)
			{
				dataMin1  = dataMin5;
				indexMin1 = indexMin5;
			}

		//第六级 2 - 1
			vector<LR_TYPE> cpdLevel6Low;
			vector<LR_TYPE> cpdLevel6LowIndex;
			for(int i = 0;i< 2;i+=2)
			{
				if(cpdLevel5Low[i] >= cpdLevel5Low[i+1])
				{
					cpdLevelOneHigh.push_back(cpdLevel5Low[i]);
					cpdLevelOneHighIndex.push_back(cpdLevel5LowIndex[i]);
					cpdLevel6Low.push_back(cpdLevel5Low[i+1]);
					cpdLevel6LowIndex.push_back(cpdLevel5LowIndex[i+1]);
				}
				else
				{
					cpdLevelOneHigh.push_back(cpdLevel5Low[i+1]);
					cpdLevelOneHighIndex.push_back(cpdLevel5LowIndex[i+1]);
					cpdLevel6Low.push_back(cpdLevel5Low[i]);
					cpdLevel6LowIndex.push_back(cpdLevel5LowIndex[i]);
				}
			}


			//把较小值保留在datamin1
			if( cpdLevelOneHigh[0] <= dataMin1)
			{
				dataMin1  = cpdLevelOneHigh[0];
				indexMin1 = cpdLevelOneHighIndex[0];
			}

			if ( abs(int(cpdLevel6LowIndex[0]) - indexMin1) < 3)
				disp.at<uchar>(row,col) = int(cpdLevel6LowIndex[0]);
			else
				disp.at<uchar>(row,col) = 0;


		}

}


void GetDisp_l(vector< vector<LR_TYPE> >& cpds, int width, int height,int Dmax,Mat &disp)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			vector<LR_TYPE> cpd_LR = cpds[row*width + col];
			vector<LR_TYPE> cpd_1;
			vector<LR_TYPE> cpd_2;
			vector<LR_TYPE> cpd_3;
			vector<LR_TYPE> cpd_4;
			vector<LR_TYPE> cpd_5;

			vector<LR_TYPE> cpd_num_1 ;
			vector<LR_TYPE> cpd_num_2 ;
			vector<LR_TYPE> cpd_num_3 ;
			vector<LR_TYPE> cpd_num_4 ;
			vector<LR_TYPE> cpd_num_5 ;

			//if (row == 2 && col == 541)
			//{
			//	for(int i = 63 ;i>=0;i--)
			//		cout<<dec<<i<<" "<<hex<<cpds[row*width+col][i]<<endl;
			//}

			//第一级
			for(int i = 0;i<64;i+=2)
			{
				if(cpd_LR[i] <= cpd_LR[i+1])
				{
					cpd_1.push_back(cpd_LR[i]);
					cpd_num_1.push_back(i);
				}
				else
				{
					cpd_1.push_back(cpd_LR[i+1]);
					cpd_num_1.push_back(i+1);
				}
			}
			//第二级
			for(int i = 0;i<32;i+=2)
			{
				if(cpd_1[i] <= cpd_1[i+1])
				{
					cpd_2.push_back(cpd_1[i]);
					cpd_num_2.push_back(cpd_num_1[i]);
				}
				else
				{
					cpd_2.push_back(cpd_1[i+1]);
					cpd_num_2.push_back(cpd_num_1[i+1]);
				}
			}
			//第三级
			for(int i = 0;i<16;i+=2)
			{
				if(cpd_2[i] <= cpd_2[i+1])
				{
					cpd_3.push_back(cpd_2[i]);
					cpd_num_3.push_back(cpd_num_2[i]);
				}
				else
				{
					cpd_3.push_back(cpd_2[i+1]);
					cpd_num_3.push_back(cpd_num_2[i+1]);
				}
			}
			//第四级
			for(int i = 0;i<8;i+=2)
			{
				if(cpd_3[i] <= cpd_3[i+1])
				{
					cpd_4.push_back(cpd_3[i]);
					cpd_num_4.push_back(cpd_num_3[i]);
				}
				else
				{
					cpd_4.push_back(cpd_3[i+1]);
					cpd_num_4.push_back(cpd_num_3[i+1]);
				}
			}
			//第五级
			for(int i = 0;i<4;i+=2)
			{
				if(cpd_4[i] <= cpd_4[i+1])
				{
					cpd_5.push_back(cpd_4[i]);
					cpd_num_5.push_back(cpd_num_4[i]);
				}
				else
				{
					cpd_5.push_back(cpd_4[i+1]);
					cpd_num_5.push_back(cpd_num_4[i+1]);
				}
			}

			LR_TYPE d;
			if(cpd_5[0]*20 <= cpd_5[1]*19)
				d = cpd_num_5[0];
			else if(cpd_5[1]*20 <= cpd_5[0]*19)
				d = cpd_num_5[1];
			else
				d = 0;

			disp.at<uchar>(row,col) = d;

		}

}




void GetDisp_cost(Mat &sky_, int width, int height, Mat &disp_out)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			uchar sky_flag = 0;
			if(col>1 && col <width-2 && row >0)
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2) + sky_.at<uchar>(row-1,col-2)
				+ sky_.at<uchar>(row-1,col-1) + sky_.at<uchar>(row-1,col) + sky_.at<uchar>(row-1,col+1) + sky_.at<uchar>(row-1,col+2);
			else if (row ==0 && col>1 )
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2);

			if(sky_flag == 0)
				disp_out.at<uchar>(row,col) =  0;
			else
				disp_out.at<uchar>(row,col) =  1;
		}

}

void GetDisp_sky(Mat &disp, Mat &sky_, int width, int height, Mat &disp_out)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			uchar sky_flag = 0;
			if(col>1 && col <width-2 && row >0)
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2) + sky_.at<uchar>(row-1,col-2)
				+ sky_.at<uchar>(row-1,col-1) + sky_.at<uchar>(row-1,col) + sky_.at<uchar>(row-1,col+1) + sky_.at<uchar>(row-1,col+2);
			else if (row ==0 && col>1 )
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2);

			if(sky_flag == 0)
				disp_out.at<uchar>(row,col) =  disp.at<uchar>(row,col);
			else
				disp_out.at<uchar>(row,col) =  0;
		}

}


void GetInitCostSky(vector< vector<LR_TYPE> > cpds_ad, Mat &sky_, int width, int height, vector< vector<LR_TYPE> > cpds_out)
{

	vector<LR_TYPE> invalid_data;
	for(int i = 0; i < 64; i ++)
	{
		invalid_data[i] = 255;
	}


	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			uchar sky_flag = 0;
			if(col>1 && col <width-2 && row >0)
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2) + sky_.at<uchar>(row-1,col-2)
				+ sky_.at<uchar>(row-1,col-1) + sky_.at<uchar>(row-1,col) + sky_.at<uchar>(row-1,col+1) + sky_.at<uchar>(row-1,col+2);
			else if (row ==0 && col>1 )
				sky_flag = sky_.at<uchar>(row,col) + sky_.at<uchar>(row,col-1) + sky_.at<uchar>(row,col-2);

			if(sky_flag == 0)
				cpds_out[row*width+col] = cpds_ad[row*width+col];		
			else
				cpds_out[row*width+col] = invalid_data;

		}

}

void GetDisp_l_andCost(vector< vector<LR_TYPE> >& cpds, int width, int height,int Dmax,Mat &disp, Mat &img_cost, int cost_th)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			vector<LR_TYPE> cpd_LR = cpds[row*width + col];
			vector<LR_TYPE> cpd_1;
			vector<LR_TYPE> cpd_2;
			vector<LR_TYPE> cpd_3;
			vector<LR_TYPE> cpd_4;
			vector<LR_TYPE> cpd_5;

			vector<LR_TYPE> cpd_num_1 ;
			vector<LR_TYPE> cpd_num_2 ;
			vector<LR_TYPE> cpd_num_3 ;
			vector<LR_TYPE> cpd_num_4 ;
			vector<LR_TYPE> cpd_num_5 ;

			//if (row == 2 && col == 541)
			//{
			//	for(int i = 63 ;i>=0;i--)
			//		cout<<dec<<i<<" "<<hex<<cpds[row*width+col][i]<<endl;
			//}

			//第一级
			for(int i = 0;i<64;i+=2)
			{
				if(cpd_LR[i] <= cpd_LR[i+1])
				{
					cpd_1.push_back(cpd_LR[i]);
					cpd_num_1.push_back(i);
				}
				else
				{
					cpd_1.push_back(cpd_LR[i+1]);
					cpd_num_1.push_back(i+1);
				}
			}
			//第二级
			for(int i = 0;i<32;i+=2)
			{
				if(cpd_1[i] <= cpd_1[i+1])
				{
					cpd_2.push_back(cpd_1[i]);
					cpd_num_2.push_back(cpd_num_1[i]);
				}
				else
				{
					cpd_2.push_back(cpd_1[i+1]);
					cpd_num_2.push_back(cpd_num_1[i+1]);
				}
			}
			//第三级
			for(int i = 0;i<16;i+=2)
			{
				if(cpd_2[i] <= cpd_2[i+1])
				{
					cpd_3.push_back(cpd_2[i]);
					cpd_num_3.push_back(cpd_num_2[i]);
				}
				else
				{
					cpd_3.push_back(cpd_2[i+1]);
					cpd_num_3.push_back(cpd_num_2[i+1]);
				}
			}
			//第四级
			for(int i = 0;i<8;i+=2)
			{
				if(cpd_3[i] <= cpd_3[i+1])
				{
					cpd_4.push_back(cpd_3[i]);
					cpd_num_4.push_back(cpd_num_3[i]);
				}
				else
				{
					cpd_4.push_back(cpd_3[i+1]);
					cpd_num_4.push_back(cpd_num_3[i+1]);
				}
			}
			//第五级
			for(int i = 0;i<4;i+=2)
			{
				if(cpd_4[i] <= cpd_4[i+1])
				{
					cpd_5.push_back(cpd_4[i]);
					cpd_num_5.push_back(cpd_num_4[i]);
				}
				else
				{
					cpd_5.push_back(cpd_4[i+1]);
					cpd_num_5.push_back(cpd_num_4[i+1]);
				}
			}


			LR_TYPE d;
			LR_TYPE d_cost;


			if(cpd_5[0] >= cpd_5[1])
			{
				d_cost   = cpd_5[1];
				cpd_5[1] = cpd_5[0];
				cpd_5[0] = d_cost;

				d		= cpd_num_5[1];
				cpd_num_5[1] = cpd_num_5[0];
				cpd_num_5[0] = d;
			}


			d       = cpd_num_5[0];
			d_cost  = cpd_5[0];

			//if(cpd_5[0]*10 < cpd_5[1]*9 && cpd_5[0] < cost_th)
			if(cpd_5[0] < cpd_5[1])
			{
				d       = cpd_num_5[0];
				d_cost  = cpd_5[0];
			}
			else
			{
				d = 0;
				d_cost = cost_th;
			}


			disp.at<uchar>(row,col) = d;
			img_cost.at<uchar>(row,col) = d_cost;

		}

}

void cost_select_opencvsgbm(vector<vector<LR_TYPE> > &lastcost, int height, int width, int DMax,  Mat &CheckLowTexture, float threshold)
{
	unsigned char disp;
	for (int row = 0;row<height;row++)
		for (int col = 0;col<width;col++)
		{
			vector<LR_TYPE> pixelcost = lastcost[row*width + col];
			float pixelvolume[200];
			float MIN, SECMIN;
			for (int i = 0;i<DMax;i++)
			{
				pixelvolume[i] = pixelcost[i];
				//	cout << pixelvolume[i] << endl;
			}
			
			//冒泡排序
			for (int m = 0; m < 2; ++m)
			{
				int min = m;
				for (int n = m + 1; n < DMax; ++n)
					if (pixelvolume[n] < pixelvolume[min])
						min = n;
				//   Put found minimum element in its place  
				unsigned char temp = pixelvolume[m];
				pixelvolume[m] = pixelvolume[min];
				pixelvolume[min] = temp;
				if (m == 0)
				{
					disp = min;
				}
				
			}

			MIN = pixelvolume[0];
			SECMIN = pixelvolume[1];
			//cout << MIN << "  " << SECMIN << endl;
			float MP = float(abs(MIN - SECMIN)) / SECMIN;
			if (MP < threshold)

				CheckLowTexture.at<uchar>(row,col) =0;
			else
				CheckLowTexture.at<uchar>(row,col) = disp;
			
			
			//cout<<MIN<<":"<<SECMIN<<endl;
		}
}


void GetDisp(vector< vector<LR_TYPE> >& cpds, int width, int height,int disp_N,Mat &disp, Mat &img_cost , int cost_th)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			vector<LR_TYPE> cpd_LR = cpds[row*width + col];
			vector<LR_TYPE>::iterator minist = std::min_element(cpd_LR.begin(), cpd_LR.end());  
			int min_index = minist - cpd_LR.begin();

			vector<LR_TYPE> cpd_second ;
			for(vector<LR_TYPE>::iterator iter=cpd_LR.begin();iter!=cpd_LR.end();iter++)
			{
				int i = iter - cpd_LR.begin();
				if(iter !=minist )
					cpd_second.push_back(cpd_LR[i]);
			}
			vector<LR_TYPE>::iterator second_min = std::min_element(cpd_second.begin(), cpd_second.end()); 
			int second_index = second_min - cpd_second.begin();
			LR_TYPE diff_min = cpd_second[second_index] - cpd_LR[min_index];
			LR_TYPE second_big = cpd_second[second_index];
			LR_TYPE min_big = cpd_LR[min_index];

			//if(diff_min >= th_second )

			LR_TYPE d;
			LR_TYPE d_cost;

			//if(90*second_big >  min_big*100 &&  abs(min_index - second_index) < 3)
			{
				d       = LR_TYPE(min_index);
				d_cost  = min_big;
			}
			//disp.at<uchar>(row,col) =  uchar(min_index);
			//else
			//{
			//	d = 0;
			//	d_cost = cost_th;
			//}


			disp.at<uchar>(row,col) = d;
			img_cost.at<uchar>(row,col) = d_cost;


		}

}

//最小和次小挨着
void GetDisp_1(vector< vector<LR_TYPE> >& cpds, int width, int height,int disp_N,Mat &disp, Mat &img_cost , int cost_th)
{

	for(int row = 0; row < height; row ++)
		for(int col = 0; col <width  ; col ++)
		{
			vector<LR_TYPE> cpd_LR = cpds[row*width + col];
			vector<LR_TYPE>::iterator minist = std::min_element(cpd_LR.begin(), cpd_LR.end());  
			int min_index = minist - cpd_LR.begin();

			vector<LR_TYPE> cpd_second ;
			for(vector<LR_TYPE>::iterator iter=cpd_LR.begin();iter!=cpd_LR.end();iter++)
			{
				int i = iter - cpd_LR.begin();
				if(iter !=minist )
					cpd_second.push_back(cpd_LR[i]);
			}
			vector<LR_TYPE>::iterator second_min = std::min_element(cpd_second.begin(), cpd_second.end()); 
			int second_index = second_min - cpd_second.begin();
			LR_TYPE diff_min = cpd_second[second_index] - cpd_LR[min_index];
			LR_TYPE second_big = cpd_second[second_index];
			LR_TYPE min_big = cpd_LR[min_index];

			//if(diff_min >= th_second )

			LR_TYPE d;
			LR_TYPE d_cost;

			//if(90*second_big >  min_big*100 && min_big < cost_th  && abs(min_index - second_index) < 3)

			if(abs(min_index - second_index) < 3)
			{
				d       = LR_TYPE(min_index);
				d_cost  = min_big;
			}
			//disp.at<uchar>(row,col) =  uchar(min_index);
			else
			{
				d = 0;
				d_cost = cost_th;
			}


			disp.at<uchar>(row,col) = d;
			img_cost.at<uchar>(row,col) = d_cost;


		}

}
