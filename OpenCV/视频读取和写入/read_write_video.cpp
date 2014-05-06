#include <cv.h>  
#include <highgui.h>  

int read_write_video(char*videoin,char*videoout)  
{  

	CvCapture *capture=NULL;  
	capture=cvCreateFileCapture(videoin);  
	if(!capture) return -1;  
	IplImage *bgr_frame=cvQueryFrame(capture);  
	double fps=cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);  
	//��cvSize��������һ��CvSize���͵ı���size�����Ⱥ͸߶���������Ƶ�ļ���ͬ  
	CvSize size=cvSize((int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH),  
		(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT));  
	//��cvCreateVideoWriter�����½�һ��CvVideoWriter*���ͱ��������������Ƶ�ļ�  
	CvVideoWriter *writer=cvCreateVideoWriter(videoout,CV_FOURCC('M','J','P','G'),fps,size);  

	cvNamedWindow("ת�������Ƶ", CV_WINDOW_AUTOSIZE);
	IplImage *logpolar_frame=cvCreateImage(size,IPL_DEPTH_8U,3); 
	while((bgr_frame=cvQueryFrame(capture))!=NULL)  
	{  
		//��cvLogPolar������ͼ��ӳ�䵽��ָ���ռ�  
		/*cvLogPolar(bgr_frame,logpolar_frame,cvPoint2D32f(bgr_frame->width/2,  
		bgr_frame->height/2),40,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS);  */
		
		cvLine(bgr_frame,cvPoint(12,14),cvPoint(60,60),CV_RGB(30,20,100));
		cvRectangle(bgr_frame,cvPoint(12,14),cvPoint(60,60),CV_RGB(255,0,0));
		  
		cvWriteFrame(writer,bgr_frame); //��cvWriteFrame��������ָ���ռ��ͼ�񱣴浽writer�� 
		cvShowImage("ת�������Ƶ", bgr_frame); //�ڴ�������ʾ���ɵ���Ƶ��  

		char c=cvWaitKey(33);  
		if (c == 27) break; //������ESC��ʱ���˳����ڣ�  


	}  
	
	cvReleaseVideoWriter(&writer);  
	cvReleaseImage(&logpolar_frame);  
	cvReleaseCapture(&capture);  
	
	return 0;  
}  