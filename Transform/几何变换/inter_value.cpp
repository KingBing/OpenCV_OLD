#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>  

int inter_value(char*filename)
{
	IplImage*src=cvLoadImage(filename);
	IplImage*dst=0;
	CvSize dst_cvsize;
	if (!src)
	{
	  printf("failure\n");
	  getchar();
	}
	else
	{ 
       double scale=4;
		dst_cvsize.width=(int)(src->width*scale);
		dst_cvsize.height=(int)(src->height*scale);
		dst=cvCreateImage(dst_cvsize,src->depth,src->nChannels);


		cvResize(src,dst,CV_INTER_CUBIC);
		//   CV_INTER_NN - ����ڲ�ֵ,
		//   CV_INTER_LINEAR - ˫���Բ�ֵ (ȱʡʹ��)
		//   CV_INTER_AREA - ʹ�����ع�ϵ�ز�������ͼ����Сʱ�򣬸÷������Ա��Ⲩ�Ƴ��֡���ͼ��Ŵ�ʱ�������� CV_INTER_NN ����
		//   CV_INTER_CUBIC - ������ֵ.


		cvNamedWindow("src",CV_WINDOW_AUTOSIZE);
		cvNamedWindow("dst",CV_WINDOW_AUTOSIZE);
		cvShowImage("src",src);
		cvShowImage("dst",dst);

		cvWaitKey();

		cvReleaseImage(&src);
		cvReleaseImage(&dst);
		cvDestroyWindow("scr");
		cvDestroyWindow("dst");

	 
	}
	
	return 0;

}