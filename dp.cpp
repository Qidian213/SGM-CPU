#include"dp.h"

int diff_LR = 30;
float getP2(const float& alpha, const unsigned int& I_p, const unsigned int& I_pr, const float& gamma, const float& P2min)
{
    float result;
	float temp = alpha * abs((int)I_p-(int)I_pr);
    result = gamma - temp; 
    if (result < P2min)
        result = P2min;
    return result;
}

LR_TYPE min4(LR_TYPE d1,LR_TYPE d2,LR_TYPE d3,LR_TYPE d4)
{
	LR_TYPE min12 = d1 < d2 ? d1 : d2;
	LR_TYPE min34 = d3 < d4 ? d3 : d4;

	return min12 < min34 ? min12 : min34;
}

//若不唯一输出-1
int minVector_index(vector<int> &vs)
{
	int min = INT_MAX;
	int min_index = 0;
	for (unsigned int index = 0; index < vs.size(); index++)
	{
		if(vs[index] < min)
		{
			min = vs[index];
			min_index = index;
		}
	}
	return min_index;
}

int minVector_index_only(vector<int> &vs)
{
	int min = INT_MAX;
	int last_min = INT_MAX;
	int min_index = 0;
	for (unsigned int index = 0; index < vs.size(); index++)
	{
		if(vs[index] <= min)
		{
			last_min = min;
			min = vs[index];
			min_index = index;
		}
	}
	//return 95*last_min >= 100*min? min_index:0;
	return last_min !=  min ? min_index : 0;
}

LR_TYPE minVector(vector<LR_TYPE> &vs)
{
	int min = INT_MAX;
	for (unsigned int index = 0; index < vs.size(); index++)
	{
		if(vs[index] < min)
		{
			min = vs[index];
		}
	}
	return min;
}

int row_co = 3;
int col_co = 170;

bool p_switch =true;

void dynamic_L(vector< vector<LR_TYPE> > cpds, int width, int height,vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , LR_TYPE invalid_data, int windows_r, int windows_c)
{

	vector< vector<LR_TYPE> > Lr1_left(width, vector<LR_TYPE>(Dmax,invalid_data));      vector<LR_TYPE> Lr1_mins(width,invalid_data);

	vector<LR_TYPE> Lr1_last(Dmax,invalid_data);                                       LR_TYPE Lr1_min_last = invalid_data;
	vector<LR_TYPE> Lr1_const(Dmax,invalid_data); 

	LR_TYPE max_L = 0;
	for(int row = 0; row < height; row ++)
	{
	    for(int col = 0; col < width ; col ++)
	    {
		    vector<LR_TYPE>& cpd = cpds[row*width + col];
		
		    vector<LR_TYPE> Lr1_Left = col>0 ? Lr1_last:vector<LR_TYPE>(Dmax,invalid_data);
		    LR_TYPE Lr1_min = col>0 ? Lr1_min_last:invalid_data;


		    vector<LR_TYPE> Lr1s;
		    vector<int>  Lr_sum;

            float P1 = pparams[row*width*8+col*8+2];
            float P2 = pparams[row*width*8+col*8+3];
            
		    for(int d = 0; d < Dmax; d ++)
		    {
			    LR_TYPE cpd_i = cpd[d];

			    LR_TYPE Lr1_d   = Lr1_Left[d];
			    LR_TYPE Lr1_ds1 = ( d > 0)  ? Lr1_Left[d-1]:invalid_data;
			    LR_TYPE Lr1_da1 = ( d < Dmax-1) ? Lr1_Left[d+1]:invalid_data;

			    LR_TYPE Lr1 ;
			   // Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1_sgm,Lr1_da1+P1_sgm,Lr1_min+P2_sgm) - Lr1_min;
                Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1,Lr1_da1+P1,Lr1_min+P2) - Lr1_min;

			    if( max_L < Lr1)
				    max_L = Lr1;

			    Lr1s.push_back(Lr1);
			    Lr_sum.push_back(Lr1);
		    }

		    new_cpds.push_back(Lr1s);

		    //求取最小值
		    LR_TYPE Lr1_c_min = minVector(Lr1s);


		    Lr1_left[col]  = Lr1s;
		    Lr1_mins[col]  = Lr1_c_min;

		    //Lr1
		    if (col < 2)
		    {
			    Lr1_last      = Lr1_const;
			    Lr1_min_last  = invalid_data;
		    }
		    else
		    {
			    Lr1_last      = Lr1_left[col-2];
			    Lr1_min_last  = Lr1_mins[col-2];
		    }
	    }
	}
	cout<<"max_L :"<<float(max_L)<<endl;
}

void dynamic_U(vector< vector<LR_TYPE> > cpds, int width, int height, vector<vector<LR_TYPE> >& new_cpds,float *pparams,  Mat &img_data, int Dmax , LR_TYPE invalid_data, int windows_r, int windows_c)
{
	vector< vector<LR_TYPE> > Lr3_Ups(width, vector<LR_TYPE>(Dmax,invalid_data));      vector<LR_TYPE> Lr3_mins(width,invalid_data);
	LR_TYPE max_U = 0;
	for(int row = 0; row < height; row ++)
	{
	    for(int col = 0; col < width ; col ++)
	    {
		    vector<LR_TYPE>& cpd = cpds[row*width + col];
		

		    vector<LR_TYPE> Lr3_Up     = Lr3_Ups[col];                           LR_TYPE Lr3_min = Lr3_mins[col];

		    vector<LR_TYPE> Lr3s;
		    vector<int>  Lr_sum;
		    
            float P1 = pparams[row*width*8+col*8+4];
            float P2 = pparams[row*width*8+col*8+5];

		    for(int d = 0; d < Dmax; d ++)
		    {
		
			    LR_TYPE cpd_i = cpd[d];


			    LR_TYPE Lr3_d   = Lr3_Up[d];
			    LR_TYPE Lr3_ds1 = (d > 0)    ? Lr3_Up[d-1]:invalid_data;
			    LR_TYPE Lr3_da1 = (d < Dmax-1)   ? Lr3_Up[d+1]:invalid_data;
			    //LR_TYPE Lr3 = cpd_i + min4(Lr3_d,Lr3_ds1+P1,Lr3_da1+P1,Lr3_min+P2)-Lr3_min;

			    LR_TYPE Lr3 ;
				//Lr3 = cpd_i + min4(Lr3_d,Lr3_ds1+P1_sgm,Lr3_da1+P1_sgm,Lr3_min+P2_sgm) - Lr3_min;
			    Lr3 = cpd_i + min4(Lr3_d,Lr3_ds1+P1,Lr3_da1+P1,Lr3_min+P2) - Lr3_min;
			    
			    if( max_U < Lr3)
				    max_U = Lr3;

			    Lr3s.push_back(Lr3);
	
			    Lr_sum.push_back(Lr3);
		    }
		    new_cpds.push_back(Lr3s);
		    //求取最小值
		    LR_TYPE Lr3_c_min = minVector(Lr3s);

		    //Lr3
		    Lr3_Ups[col]  = Lr3s;
		    Lr3_mins[col] = Lr3_c_min;
	    }
	}
	cout<<"max_U :"<<float(max_U)<<endl;
}

void dynamic_R(vector< vector<LR_TYPE> > cpds, int width, int height,vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , LR_TYPE invalid_data, int windows_r, int windows_c)
{

	vector< vector<LR_TYPE> > Lr1_left(width, vector<LR_TYPE>(Dmax,invalid_data));      vector<LR_TYPE> Lr1_mins(width,invalid_data);

	vector<LR_TYPE> Lr1_last(Dmax,invalid_data);                                       LR_TYPE Lr1_min_last = invalid_data;
	vector<LR_TYPE> Lr1_const(Dmax,invalid_data); 

	LR_TYPE max_L = 0;

	//给定new_cpds大小
	new_cpds = vector<vector<LR_TYPE> >(width*height,vector<LR_TYPE>(Dmax,0));

	for(int row = 0; row < height; row ++)
	{
	    for(int col = width-1; col >=0 ; col --)
	    {
		    vector<LR_TYPE>& cpd = cpds[row*width + col];

		    vector<LR_TYPE> Lr1s;

            float P1 = pparams[row*width*8+col*8+6];
            float P2 = pparams[row*width*8+col*8+7];
            
		    for(int d = 0; d < Dmax; d ++)
		    {
			    LR_TYPE cpd_i = cpd[d];
			    LR_TYPE Lr1 ;
			    if(col<width-1)
			    {
				    LR_TYPE Lr1_d   = Lr1_left[col+1][d];
				    LR_TYPE Lr1_ds1 = ( d > 0)  ? Lr1_left[col+1][d-1]:invalid_data;
				    LR_TYPE Lr1_da1 = ( d < Dmax-1) ? Lr1_left[col+1][d+1]:invalid_data;

					//Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1_sgm,Lr1_da1+P1_sgm,Lr1_mins[col+1]+P2_sgm) - Lr1_mins[col+1];
					Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1,Lr1_da1+P1,Lr1_mins[col+1]+P2) - Lr1_mins[col+1];
			    }
			    else
			    {
				    Lr1 = invalid_data;
			    }
				    if( max_L < Lr1)
					    max_L = Lr1;

				    Lr1s.push_back(Lr1);
		    }
		    new_cpds[row*width+col]=(Lr1s);
		    //求取最小值
		    LR_TYPE Lr1_c_min = minVector(Lr1s);
		    Lr1_left[col]  = Lr1s;
		    Lr1_mins[col]  = Lr1_c_min;
	    }
	}
	cout<<"max_R :"<<float(max_L)<<endl;
}

void dynamic_D(vector< vector<LR_TYPE> > cpds, int width, int height,vector<vector<LR_TYPE> >& new_cpds,float *pparams, Mat &img_data, int Dmax , LR_TYPE invalid_data, int windows_r, int windows_c)
{

	vector< vector<LR_TYPE> > Lr1_left(width, vector<LR_TYPE>(Dmax,invalid_data));      vector<LR_TYPE> Lr1_mins(width,invalid_data);

	vector<LR_TYPE> Lr1_last(Dmax,invalid_data);                                       LR_TYPE Lr1_min_last = invalid_data;
	vector<LR_TYPE> Lr1_const(Dmax,invalid_data); 

	LR_TYPE max_L = 0;

	//给定new_cpds大小
	new_cpds = vector<vector<LR_TYPE> >(width*height,vector<LR_TYPE>(Dmax,0));

	for(int row = height-1; row >=0; row --)
	{
	    for(int col = 0; col < width ; col ++)
	    {
		    vector<LR_TYPE>& cpd = cpds[row*width + col];
		
		    vector<LR_TYPE> Lr1s;

            float P1 = pparams[row*width*8+col*8];
            float P2 = pparams[row*width*8+col*8+1];
            
		    for(int d = 0; d < Dmax; d ++)
		    {
			    LR_TYPE cpd_i = cpd[d];

			    LR_TYPE Lr1_d   = Lr1_left[col][d];
			    LR_TYPE Lr1_ds1 = ( d > 0)  ? Lr1_left[col][d-1]:invalid_data;
			    LR_TYPE Lr1_da1 = ( d < Dmax-1) ? Lr1_left[col][d+1]:invalid_data;

			    LR_TYPE Lr1 ;
			    //Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1_sgm,Lr1_da1+P1_sgm,Lr1_mins[col]+P2_sgm) - Lr1_mins[col];
			    Lr1 = cpd_i + min4(Lr1_d,Lr1_ds1+P1,Lr1_da1+P1,Lr1_mins[col]+P2) - Lr1_mins[col];
			    if( max_L < Lr1)
				    max_L = Lr1;

			    Lr1s.push_back(Lr1);
		    }

		    new_cpds[row*width+col]=(Lr1s);
		    //求取最小值
		    LR_TYPE Lr1_c_min = minVector(Lr1s);
		    Lr1_left[col]  = Lr1s;
		    Lr1_mins[col]  = Lr1_c_min;
	    }
	}
	cout<<"max_D :"<<float(max_L)<<endl;
}

void Viterbi_avg4(vector< vector<LR_TYPE> >& cpds_1,vector<vector<LR_TYPE> >&cpds_2,vector< vector<LR_TYPE> >& cpds_3,vector<vector<LR_TYPE> >&cpds_4,vector<vector<LR_TYPE> >&cpds_1234, int width, int height,int disp_N)
{
	for(int row = 0; row < height; row ++)
		for(int col = 0; col < width ; col ++)
	{
		vector<LR_TYPE> cpd_L = cpds_1[row*width + col];
		vector<LR_TYPE> cpd_R = cpds_2[row*width + col];
		vector<LR_TYPE> cpd_U = cpds_3[row*width + col];
		vector<LR_TYPE> cpd_D = cpds_4[row*width + col];
		vector<LR_TYPE> cpd_UD;
		for(int u = 0; u < disp_N; u++)
		{
			LR_TYPE cpd_L_u = cpd_L[u];
			LR_TYPE cpd_R_u = cpd_R[u];
			LR_TYPE cpd_U_u = cpd_U[u];
			LR_TYPE cpd_D_u = cpd_D[u];
			cpd_UD.push_back((cpd_L_u+ cpd_R_u+ cpd_U_u+cpd_D_u));
		}
		cpds_1234.push_back(cpd_UD);
	}
}



