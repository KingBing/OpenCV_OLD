//�ú����Ĺ����ǽ�ȡԭʼͼ��Ĳ������򱣴�Ϊһ����ͼ��

#include <cv.h>
#include <highgui.h>
#include "../opencv.h"


int ROIimg(char*filename)
{
	 IplImage *pSrc = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	 if (!pSrc)
	 {
		printf("����ʧ�ܣ�");
		return 0;
	 }
	 cvNamedWindow("SRC",1);
	 cvShowImage("SRC",pSrc);

	 CvSize ROISize=cvSize(30,40);
	 cvSetImageROI(pSrc,cvRect(0,0,ROISize.width,ROISize.height));//����ԭͼ��ROI
	 
	 
	 IplImage* pDest = cvCreateImage(ROISize,pSrc->depth,pSrc->nChannels);//����Ŀ��ͼ��,��СΪROI�Ĵ�С
	 cvCopy(pSrc,pDest); //����ͼ��
	 cvResetImageROI(pSrc);//Դͼ����������ROI
	 
	 cvNamedWindow("ROI",1);
	 cvShowImage("ROI",pDest);
	 cvSaveImage("PicVideo/Roi.jpg",pDest);//����Ŀ��ͼ��
	 
	 color_cluster("PicVideo/Roi.jpg",2);
	 cvWaitKey(0);

}


