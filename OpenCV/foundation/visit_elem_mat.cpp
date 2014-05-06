#include <opencv2/core/core.hpp>
#include <highgui/highgui.hpp>

using namespace cv;

void visit_elem_Mat(char*picname)
{
	int div=4;
	Mat img=imread(picname);
	namedWindow("origin",1);
    imshow("origin",img);

	/********��ʽһ��at<typename>(i,j)*******/
	Mat_<uchar> im=img;
	for (int i=0;i<img.rows;i++)
	{
		for (int j=0;j<img.cols;j++)
		{
			img.at<Vec3b>(i,j).val[0]=img.at<Vec3b>(i,j).val[0]/div*div+div/2;
			img.at<Vec3b>(i,j).val[1]=img.at<Vec3b>(i,j).val[1]/div*div+div/2;
			img.at<Vec3b>(i,j).val[2]=img.at<Vec3b>(i,j).val[2]/div*div+div/2;
			
			im(i,j)=im(i,j)/div*div+div/2;
		}
	}
	namedWindow("output",1);
	imshow("output",im);
	waitKey(1000);


	/********��ʽ����ָ��������ͼ��*******/
	//Mat *output;
	//output.create(img.size(),img.type());
	



	
	

}