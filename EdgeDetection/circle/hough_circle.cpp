//-----------------------------------��HoughCircle��⡿------------------------------
//	����:�ڻҶ�ͼ������Բ
//  �ο���http://blog.csdn.net/hitwengqi/article/details/6883299
//-------------------------------------------------------------------------

#include <highgui.h>
#include <math.h>
#include <cv.h>

int hough_circle(char*filename)
{
	IplImage* src = cvLoadImage( filename, 1);
	IplImage*gray=cvCreateImage(cvGetSize(src),src->depth,1);
	cvCvtColor(src,gray,CV_BGR2GRAY);
	IplImage* dst = cvCreateImage( cvGetSize(src),src->depth,1 );
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvSmooth(gray, dst, CV_GAUSSIAN, 5, 5 );  //����
	
	//cvHoughCircles������Ҫ����ÿһ�������ݶȵķ�����˻����ڲ��Զ�����cvSobel,����ֵ��Եͼ��Ĵ����ǱȽ��ѵ�
	CvSeq* results = cvHoughCircles(  
		dst,
		storage,
		CV_HOUGH_GRADIENT,
		2,  //�ۼ���ͼ��ķֱ���
		src->width/10
		);

	for( int i = 0; i < results->total; i++ )
	{
		float* p = ( float* )cvGetSeqElem( results, i );
		//����Բ�任
		CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
		cvCircle(
			src,
			pt,  //ȷ��Բ��
			cvRound( p[2] ),  //ȷ���뾶
			CV_RGB(255,0, 0 )
			);  //��Բ����
	}

	cvNamedWindow( "cvHoughCircles", 1 );
	cvShowImage( "cvHoughCircles", src );
	
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&gray);
	cvReleaseImage(&dst);
	return 0;
}