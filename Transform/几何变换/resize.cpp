#include "cv.h"  
#include "highgui.h"  
#include <math.h>  

int resize(int argc,char*argv[])  
{  
	IplImage* src = 0;  
	IplImage* dst = 0;  
	double scale=0.618;//���ű���  
	CvSize dst_size;//�����ά�����ο�  

	if((argc==2) && (src =cvLoadImage(argv[1],1))!=0)  
	{  
		dst_size.width = (int)(src->width * scale);  
		dst_size.height = (int)(src->height * scale);//ȷ����ͼ�ľ��ο�  
		dst=cvCreateImage(dst_size,src->depth,src->nChannels);//����ͼ��ͷ  
		cvResize(src,dst,CV_INTER_LINEAR);//ʹ��˫���Բ�ֵ��Сͼ��  
		cvNamedWindow("src",CV_WINDOW_AUTOSIZE);  
		cvNamedWindow("dst",CV_WINDOW_AUTOSIZE);  
		cvShowImage("src",src);  


		cvShowImage("dst",dst);  
		cvWaitKey(-1);  
		cvReleaseImage( &src );  
		cvReleaseImage( &dst );  
		cvDestroyWindow("src");  
		cvDestroyWindow("dst");  
	}  

	return 0;  

} 