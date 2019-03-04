#include"skyDetection.h"

int MULT = 50;







void label_sky_v1(Mat &img_data,Mat &sky_label,int W)
{
		int width  = img_data.cols;
		int height = img_data.rows;

		sky_label = cv::Mat::zeros(img_data.rows-W+1,img_data.cols-W+1,CV_8UC1);

		
		for (int row = W/2;row < height-W/2; row++)
		{
				int sky_th = 90;
			    Mat img_region = img_data(Range(row-1, row), Range(W/2, width-W/2-1));
                double sky_min_value,sky_max_value;
                minMaxLoc(img_region, &sky_min_value, &sky_max_value);	
				
				if (sky_max_value >= sky_th)
					sky_th = int(sky_max_value);

			//if( row < 10 )
			//	cout<<"row:"<<row-2<<"  "<<sky_th<<endl;

			int sky_point =0;
			int sum = 0;
			int th_diff = 0;
			for(int col = W/2 ;col < width-W/2; col++)
			{
				
				//求均值
				int sum_window=0;
				for(int i= -1;i<= 2;i++)
					for(int j= -1;j<= 2;j++)
					{
						unsigned char data = img_data.at<uchar>(row+i,col+j);
						sum_window += data;
	
					}

				int  average_window = sum_window/16;
				//求sad

				unsigned char data_last = img_data.at<uchar>(row,col-1);
				int sum_sad = 0;
				

				for(int i= -2;i<=2;i++)
					for(int j= -2;j<=2;j++)
					{
						unsigned char data = img_data.at<uchar>(row+i,col+j);
						sum_sad += abs((int)data- average_window);
	
					}
					
				if( sum_sad*2 < average_window) 					
				{	
					if (abs(average_window -sky_th) < sky_th/4 )
					{
					
						sky_point++;
						sky_label.at<unsigned char>(row-W/2,col-W/2) = 1;
					}

				}

			}
			if (sky_point < 30)
				break;
		}
				
}

//去太多。
void label_sky_v2(Mat &img_data,Mat &sky_label,int W)
{
	int width  = img_data.cols;
	int height = img_data.rows;

	sky_label = cv::Mat::zeros(img_data.rows-W+1,img_data.cols-W+1,CV_8UC1);


	for (int row = W/2;row <= height-W/2-1; row++)
	{
		int sky_th = 90;
		Mat img_region = img_data(Range(row-1, row), Range(2, width-W/2-1));
		double sky_min_value,sky_max_value;
		minMaxLoc(img_region, &sky_min_value, &sky_max_value);	


		//if (sky_max_value >= sky_th)
		sky_th = int(sky_max_value);

		int sky_point =0;
		int sum = 0;
		int th_diff = 0;
		for(int col = W/2 ;col <= width-W/2-1; col++)
		{

			//求均值
			int sum_window=0;
			for(int i= -1;i<=2;i++)
				for(int j= -1;j<=2;j++)
				{
					unsigned char data = img_data.at<uchar>(row+i,col+j);
					sum_window += data;

				}
				int  average_window = sum_window/16;
				//求sad

				unsigned char data_centor = img_data.at<uchar>(row,col);
				int sum_sad = 0;


				for(int i= -2;i<=2;i++)
					for(int j= -2;j<=2;j++)
					{
						unsigned char data = img_data.at<uchar>(row+i,col+j);
						sum_sad += abs((int)data- average_window);

					}


					if( sum_sad*4 < average_window) 					
					{	
						sky_point++;
						sky_label.at<unsigned char>(row-W/2,col-W/2) = 1;
					}
		}
		if (sky_point < 50)
			break;
	}

}

//包含边缘的去天空
void label_sky_v2_1(Mat &img_data,Mat &sky_label,int W, Mat &sobel_y)
{
	int width  = img_data.cols;
	int height = img_data.rows;

	Mat edge = cv::Mat::zeros(img_data.rows-W+1,img_data.cols-W+1,CV_8UC1);

	sky_label = cv::Mat::zeros(img_data.rows-W+1,img_data.cols-W+1,CV_8UC1);

	vector<uchar>  sobel_edge(width, 0);

	for (int row = W/2;row <= height-W/2-1; row++)
	{

		int sky_th = 90;
		Mat img_region = img_data(Range(row-1, row), Range(2, width-W/2-1));
		double sky_min_value,sky_max_value;
		minMaxLoc(img_region, &sky_min_value, &sky_max_value);	
		int sum_1_row = 0; 
		for(int col = 64 ;col < 576; col++)
		{
			sum_1_row += img_data.at<uchar>(row-1,col);
		}
		int aver_row = sum_1_row/512;

		sky_th = int(sky_max_value);

		//if(row == W/2)
		//{
		//	cout<<sky_max_value<<endl;
		//	cout<<sky_min_value<<endl;
		//	cout<<aver_row<<endl;
		//}

		//if (sky_max_value >= sky_th)


		//if( row < 10 )
		//	cout<<"row:"<<row-2<<"  "<<sky_th<<endl;

		int sky_point =0;
		int sum = 0;
		int th_diff = 0;
		for(int col = W/2 ;col <= width-W/2-1; col++)
		{

			if (sobel_y.at<uchar>(row, col) > 40 )
			{


				if(sobel_edge[col] == 0)
				{						
					//edge.at<uchar>(row,col) = 255;
					sobel_edge[col] = 1;
				}


			}
			//if(row == 6)
			//	cout<<(col-3)<<": "<<int(sobel_edge[col-W/2])<<" ";
			//cout<<endl;


			//求均值
			int sum_window=0;
			for(int i= -1;i<=2;i++)
				for(int j= -1;j<=2;j++)
				{
					unsigned char data = img_data.at<uchar>(row+i,col+j);
					sum_window += data;

				}
				int  average_window = sum_window/16;
				//求sad

				unsigned char data_centor = img_data.at<uchar>(row,col);
				int sum_sad = 0;


				for(int i= -2;i<=2;i++)
					for(int j= -2;j<=2;j++)
					{
						unsigned char data = img_data.at<uchar>(row+i,col+j);
						sum_sad += abs((int)data- average_window);

					}


					//if( sobel_edge[col] == 1 && sobel_edge[col-1] == 1 && sobel_edge[col+1] == 1) 
					if( sobel_edge[col] == 1) 
					{
						if (sum_sad*16 < average_window && average_window > sky_th*3/4)	
						{

							sky_point++;
							sky_label.at<unsigned char>(row-W/2,col-W/2) = 1;
						}
					}										
					else if( sum_sad*4 < average_window) 					
					{	

						//if ( sky_th - data_centor < sky_th/2 )
						//if ( average_window > sky_th/2 || average_window + average_window/4 > aver_row)

						{

							sky_point++;
							sky_label.at<unsigned char>(row-W/2,col-W/2) = 1;
						}
					}

		}
		if (sky_point < 50)
			break;
	}

	//imshow("edge", edge);

}

void skyRegionGrowing(Mat img_, Mat& sky_){
    sky_ = Mat(img_.rows, img_.cols, CV_8UC1, Scalar(255));
    
    //归一化的作用有多大
    //double min_val, max_val;
    //cv::minMaxLoc(img_, &min_val, &max_val);
    //img_.convertTo(img_, CV_8UC1, 255.0/(max_val-min_val));
    
    int sky_growing_threshold = 4;
    int sky_length_threshold = 6;
    int sky_value_threshold = 224;
    
    for (int row=0; row<img_.cols; row++){
        
        int offset_count = 0;
        
        for (int col = 0; col < img_.cols; col++) {
            
            //灰度值符合要求
            bool is_seed_point = (img_.at<uchar>(row,col) >= sky_value_threshold);
            if ( is_seed_point ) {
                //开始生长
                int offset;
                for (offset=1; offset < img_.cols-col ; offset++) {
                    int diff = abs( img_.at<uchar>(row,col+offset) - img_.at<uchar>(row,col+offset-1) );
                    bool is_growing = diff <= sky_growing_threshold ||  img_.at<uchar>(row,col+offset) > sky_value_threshold;
                    if (!is_growing) {
                        break;
                    }
                }

                //偏移量大于阈值
                if (offset > sky_length_threshold) {
                    Mat sky_region = sky_(Range(row, row+1), Range(col, col+offset));
                    sky_region.setTo( Scalar(0) );
                    
                    Mat img_region = img_(Range(row, row+1), Range(col+1, col+offset));
                    double sky_min_value;
                    cv::minMaxLoc(img_region, &sky_min_value);
                    sky_value_threshold = (sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
					sky_growing_threshold = sky_value_threshold/30;
//                    (sky_min_value > sky_value_threshold)?
//                                                sky_value_threshold:(sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
                    
                    //cout<<"sky_min_value "<<row  <<": "  <<sky_min_value  <<"\n";
                    //cout<<"sky_value_threshold of row "<<row  <<": "  <<sky_value_threshold  <<"\n\n";
                    
                    
                    offset_count++;
                }
                col += offset;
            }   //if (img_.at<uchar>(row,col) >  sky_value_threshold) {
        }   //for (int col = 0; col < img_.cols; col++)
        
        if (offset_count == 0) {
            return;
        }
    }   //for (int row=0; row<img_.cols; row++)
    
    return ;
}

void skyRegionGrowing_1(Mat img_, Mat& sky_){

	int cols = img_.cols;
	int rows = img_.rows;
    sky_ = Mat(img_.rows, img_.cols, CV_8UC1, Scalar(255));
    
    
    int sky_growing_threshold = 4;
    int sky_length_threshold = 6;
    int sky_value_threshold = 200;
    for(int col=0;col<cols;col++)
		if (img_.at<uchar>(0,col)> sky_value_threshold)
			sky_value_threshold = img_.at<uchar>(0,col);

	sky_value_threshold = sky_value_threshold*9/10;
	cout<<sky_value_threshold<<endl;

    for (int row=0; row<rows; row++){
        
        int offset_count = 0;
        
        for (int col = 0; col < cols; col++) {
            
            //灰度值符合要求
            bool is_seed_point = (img_.at<uchar>(row,col) >= sky_value_threshold);
            if ( is_seed_point ) {
                //开始生长
                int offset;
                for (offset=1; offset < cols-col ; offset++) {
                    int diff = abs( img_.at<uchar>(row,col+offset) - img_.at<uchar>(row,col+offset-1) );
                    bool is_growing = diff <= sky_growing_threshold ||  img_.at<uchar>(row,col+offset) > sky_value_threshold;
                    if (!is_growing) {
                        break;
                    }
                }

                //偏移量大于阈值
                if (offset > sky_length_threshold) {
                    Mat sky_region = sky_(Range(row, row+1), Range(col, col+offset));
                    sky_region.setTo( Scalar(0) );
                    
                    Mat img_region = img_(Range(row, row+1), Range(col+1, col+offset));
                    double sky_min_value;
                    cv::minMaxLoc(img_region, &sky_min_value);
                    sky_value_threshold = (sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
					sky_growing_threshold = sky_value_threshold/30;
//                    (sky_min_value > sky_value_threshold)?
//                                                sky_value_threshold:(sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
                    
                    //cout<<"sky_min_value "<<row  <<": "  <<sky_min_value  <<"\n";
                    //cout<<"sky_value_threshold of row "<<row  <<": "  <<sky_value_threshold  <<"\n\n";
                    
                    
                    offset_count++;
                }
                col += offset;
            }   //if (img_.at<uchar>(row,col) >  sky_value_threshold) {
        }   //for (int col = 0; col < img_.cols; col++)
        
        if (offset_count == 0) {
            return;
        }
    } 
    
    return ;
}

void skyRegionGrowing_2(Mat img_, Mat& sky_, int W){

	int cols = img_.cols;
	int rows = img_.rows;
    sky_ = Mat(img_.rows, img_.cols, CV_8UC1, Scalar(255));
    
    
    int sky_growing_threshold = 4;
    int sky_length_threshold = 6;
    int sky_value_threshold = 200;
    for(int col=0;col<cols;col++)
		if (img_.at<uchar>(0,col)> sky_value_threshold)
			sky_value_threshold = img_.at<uchar>(0,col);

	sky_value_threshold = sky_value_threshold*9/10;
	cout<<sky_value_threshold<<endl;

    for (int row=0; row<rows; row++){
      
        int offset_count = 0;
        
        for (int col = 0; col < cols; col++) {
			unsigned char data_o = img_.at<uchar>(row,col);
			int sum_sad_last =0;
			int sum_last =0;

			int sum_sad = 0;
			int sum = 0;
			for(int i= -W/2;i<=W/2;i++)
				for(int j= -W/2;j<=W/2;j++)
				{
					unsigned char data = img_.at<uchar>(row+i,col+j);
					sum_sad += abs((int)data- (int)data_o);
					sum += data;
	
				}  
            
            //灰度值符合要求
            bool is_seed_point = (img_.at<uchar>(row,col) >= sky_value_threshold);
            if ( is_seed_point ) {
                //开始生长
                int offset;
                for (offset=1; offset < cols-col ; offset++) {
                    int diff = abs( img_.at<uchar>(row,col+offset) - img_.at<uchar>(row,col+offset-1) );
                    bool is_growing = diff <= sky_growing_threshold ||  img_.at<uchar>(row,col+offset) > sky_value_threshold;
                    if (!is_growing) {
                        break;
                    }
                }

                //偏移量大于阈值
                if (offset > sky_length_threshold) {
                    Mat sky_region = sky_(Range(row, row+1), Range(col, col+offset));
                    sky_region.setTo( Scalar(0) );
                    
                    Mat img_region = img_(Range(row, row+1), Range(col+1, col+offset));
                    double sky_min_value;
                    cv::minMaxLoc(img_region, &sky_min_value);
                    sky_value_threshold = (sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
					sky_growing_threshold = sky_value_threshold/30;
//                    (sky_min_value > sky_value_threshold)?
//                                                sky_value_threshold:(sky_min_value + sky_value_threshold )/2;    //防止阈值降得过快
                    
                    //cout<<"sky_min_value "<<row  <<": "  <<sky_min_value  <<"\n";
                    //cout<<"sky_value_threshold of row "<<row  <<": "  <<sky_value_threshold  <<"\n\n";
                    
                    
                    offset_count++;
                }
                col += offset;
            }   //if (img_.at<uchar>(row,col) >  sky_value_threshold) {
        }   //for (int col = 0; col < img_.cols; col++)
        
        if (offset_count == 0) {
            return;
        }
    } 
    
    return ;
}

void SkyRemove(Mat &sky_, int width, int height, Mat &disp_in, Mat &disp)
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
			disp.at<uchar>(row,col) =  disp_in.at<uchar>(row,col);
		else
			disp.at<uchar>(row,col) =  0;
	}

}
