#include"image.h"


void labelNightPixel(Mat &img_data,Mat &sky_label,int TH)
{
	int width  = img_data.cols;
	int height = img_data.rows;

	sky_label = cv::Mat::zeros(img_data.rows,img_data.cols,CV_8UC1);

	for (int row = 0;row < height; row++)
	{
		for(int col = 0;col < width; col++)
		{
			if( img_data.at<uchar>(row,col) < TH)
				sky_label.at<uchar>(row,col) = 255;

		}

	}

}


void labelLeftBelowTH(Mat &img_data,Mat &sky_label,int TH)
{
	int width  = img_data.cols;
	int height = img_data.rows;

	sky_label = cv::Mat::zeros(img_data.rows,img_data.cols,CV_8UC1);

	for (int row = 0;row < height; row++)
	{
		for(int col = 0;col < width; col++)
		{
			if( img_data.at<uchar>(row,col) >= TH)
				sky_label.at<uchar>(row,col) = 255;

		}

	}

}


void GenerateFalseMap(cv::Mat &src, cv::Mat &disp)
{
    // color map
    float max_val = 255.0f;
    float map[8][4] = {{0,0,0,114},{0,0,1,185},{1,0,0,114},{1,0,1,174},
                       {0,1,0,114},{0,1,1,185},{1,1,0,114},{1,1,1,0}};
    float sum = 0;
    for (int i=0; i<8; i++)
      sum += map[i][3];

    float weights[8]; // relative   weights
    float cumsum[8];  // cumulative weights
    cumsum[0] = 0;
    for (int i=0; i<7; i++) {
      weights[i]  = sum/map[i][3];
      cumsum[i+1] = cumsum[i] + map[i][3]/sum;
    }

    int height_ = src.rows;
    int width_ = src.cols;
    // for all pixels do
    for (int v=0; v<height_; v++) {
      for (int u=0; u<width_; u++) {

        // get normalized value
        float val = std::min(std::max(src.data[v*width_ + u]/max_val,0.0f),1.0f);

        // find bin
        int i;
        for (i=0; i<7; i++)
          if (val<cumsum[i+1])
            break;

        // compute red/green/blue values
        float   w = 1.0-(val-cumsum[i])*weights[i];
        uchar r = (uchar)((w*map[i][0]+(1.0-w)*map[i+1][0]) * 255.0);
        uchar g = (uchar)((w*map[i][1]+(1.0-w)*map[i+1][1]) * 255.0);
        uchar b = (uchar)((w*map[i][2]+(1.0-w)*map[i+1][2]) * 255.0);
        disp.data[v*width_*3 + 3*u + 0] = b;
        disp.data[v*width_*3 + 3*u + 1] = g;
        disp.data[v*width_*3 + 3*u + 2] = r;
      }
    }
}

void ShowAndSave(Mat &disp, char * name)
		{
			Mat dst;
			equalizeHist(disp, dst );
			Mat dst_c= Mat::zeros(cv::Size(disp.cols,disp.rows),CV_8UC3);

			GenerateFalseMap(dst,dst_c);
			imshow(name,dst_c);
			imwrite(name,dst_c);

		}

void SaveColor(Mat &disp, char * name)
		{
			Mat dst;
			equalizeHist(disp, dst );
			Mat dst_c= Mat::zeros(cv::Size(disp.cols,disp.rows),CV_8UC3);

			GenerateFalseMap(dst,dst_c);
			imwrite(name,dst_c);

		}
void ShowColor(Mat &disp, char * name)
		{
			Mat dst;
			equalizeHist(disp, dst );
			Mat dst_c= Mat::zeros(cv::Size(disp.cols,disp.rows),CV_8UC3);

			GenerateFalseMap(dst,dst_c);
			imshow(name,dst_c);
			imwrite("dst_c.png",dst_c);

		}
