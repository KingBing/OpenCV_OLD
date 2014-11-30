/* ���Ĳο���http://blog.csdn.net/xiaowei_cqu/article/details/7557063
 *	
 */

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

//cv1.x�ķ��ʷ�ʽ
void visit_elem_Iplimage(char*picname)
{
	IplImage*img=cvLoadImage(picname,0);
	IplImage*result=cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img,result);
	if (!img){
		printf("����ͼƬʧ�ܣ�\n");
	    exit(0);
	}
	cvNamedWindow("origin",CV_WINDOW_AUTOSIZE);
	cvShowImage("origin",img);
	
	/********��ͨ��**********/
	if (result->nChannels==1)
	{
		//��ʽһ:ֱ�ӷ��ʣ��ٶȿ쵫���׳���
		uchar*data1=(uchar*)result->imageData;
		for (int i=0;i<result->height;i++)
		{
			for (int j=0;j<result->width;j++)
			{
				*data1=((uchar*)(result->imageData+i*result->widthStep))[j];

				if (*data1<50)//��ɫ��ת
					*data1=255;
				else
					*data1=0;
			}
		}

		//��ʽ����ָ����ʣ������ǿ���ͨ������ָ�������ʣ������˹���
		//uchar*data_p=(uchar*)result->imageData;
		//int step=result->width/sizeof(uchar);
		//uchar*data2;
		//for (int i=0;i<result->height;i++)
		//{
		//	for (int j=0;j<result->width;j++)
		//	{
		//		*data2=data_p[i*step+j];

		//		if (*data2>200)//��ɫ��ת
		//			*data2=0;
		//		else
		//			*data2=255;
		//		
		//	}
		//}

		//��ʽ����cvGet2D��ʽ
		double tmp;  
		for(int i=0;i<result->height;i++)  
			for(int j=0;j<result->width;j++)  
				tmp=cvGet2D(result,i,j).val[0];  


		//��ʽ�ģ�




	}
	
	/*******��ͨ��*******/
	else
	{
		printf("��ͨ���������С�������");
		
		//��ʽһ��ָ�����
		uchar* data=(uchar *)result->imageData;  
		int step = result->widthStep/sizeof(uchar);  
		int chanels = result->nChannels;
		uchar temp='a';
		uchar *b=&temp,*g=&temp,*r=&temp;  //ָ��һ��Ҫ��ʼ����
		for(int i=0;i<result->height;i++) 
		{
			for(int j=0;j<result->width;j++)
			{  
			
				*b=data[i*step+j*chanels+0];  
				*g=data[i*step+j*chanels+1];  
				*r=data[i*step+j*chanels+2]; 
				
				*b=(uchar)i;
				*g=(uchar)j;
				*r=temp;

			}  
		}
		
		//��ʽ��:cvGet2D
		double tmpb,tmpg,tmpr;  
		for(int i=0;i<result->height;i++)
		{
			for(int j=0;j<result->width;j++)
			{  
				tmpb=cvGet2D(result,i,j).val[0];  
				tmpg=cvGet2D(result,i,j).val[1];  
				tmpr=cvGet2D(result,i,j).val[2];  
			} 
		}
		

	}

	cvNamedWindow("result",CV_WINDOW_AUTOSIZE);
	cvShowImage("result",result);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&img);
	cvReleaseImage(&result);


}