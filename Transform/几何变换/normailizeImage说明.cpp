#include <opencv2/opencv.hpp>
#include <iostream>

IplImage* NormalizeImage(IplImage *img,IplImage*out)

{

	//1��������һ����ͼ��

	    //IplImage* out = cvCreateImage(cvGetSize(img), 8, 3);

	//2����ȡͼ��߶ȺͿ����Ϣ������epslon��Ŀ���Ƿ�ֹ��0�Ĳ���������

		int width = img->width;
		int height = img->height;
		int redValue, greenValue, blueValue;
		double sum, epslon = 0.000001;

	//3�������һ���Ľ�������滻��ԭ����ֵ��

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				CvScalar src = {0};
					src=cvGet2D(img, y, x);
				redValue = src.val[0];
				greenValue = src.val[1];
				blueValue = src.val[2];
				// ����epslon��Ϊ�˷�ֹ����0���������
				sum = redValue + greenValue + blueValue + epslon;
				CvScalar des = cvScalar(redValue / sum * 255, greenValue / sum * 255, blueValue / sum * 255, src.val[4]);
				cvSet2D(out, y, x, des);

			}
		}     

	/*	4�����ع�һ�����ͼ��*/

			return out;

}

int main()
{
	 const char* filename="(1)pp.png";
	 IplImage * Inputimage = cvLoadImage ( filename );
	 IplImage * Outputimage= cvCreateImage(cvGetSize(Inputimage), 8, 3);
	 NormalizeImage(Inputimage,Outputimage);
	 cvShowImage("NormailizeImage",Outputimage);
     getchar();
	 return 0;

}