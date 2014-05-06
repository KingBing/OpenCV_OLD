#include <cv.h>  
#include <highgui.h>  

int images2video()  
{  
	
	char filename[50];

	double fps=22;
	CvSize size=cvSize(640,480);
	char*videoout="images2video.wmv";

	CvVideoWriter *writer=cvCreateVideoWriter(videoout,CV_FOURCC('M','J','P','G'),fps,size);  

	cvNamedWindow("ת�������Ƶ", CV_WINDOW_AUTOSIZE);
	IplImage *bgr_frame=cvCreateImage(size,IPL_DEPTH_8U,3); 

	//��ȡ�ļ����ڵ�ָ����ʽ�������ļ�
	for (int i=1;i<24;i++)
	{
		sprintf(filename,"PicVideo/frame2video/%d.png",i);
		printf("���ڴ���%s\n",filename);
		if((bgr_frame=cvLoadImage(filename))!=NULL)  
		{  
			cvLine(bgr_frame,cvPoint(12,14),cvPoint(60,60),CV_RGB(30,20,100));
			cvRectangle(bgr_frame,cvPoint(12,14),cvPoint(60,60),CV_RGB(255,0,0));

			cvWriteFrame(writer,bgr_frame); //��cvWriteFrame��������ָ���ռ��ͼ�񱣴浽writer�� 
			cvShowImage("ת�������Ƶ", bgr_frame); //�ڴ�������ʾ���ɵ���Ƶ��  

			char c=cvWaitKey(120);  
			if (c == 27) break; //������ESC��ʱ���˳����ڣ�  
		}  
		else
		{
			printf("����ͼƬʧ��\n");
			return -1;
		}
	
    }

	cvReleaseVideoWriter(&writer);  
	cvReleaseImage(&bgr_frame);   
	
	return 0;  
}  