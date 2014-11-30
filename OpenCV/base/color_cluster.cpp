#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

/*
	�ó�������OpenCV�е�K��ֵ���ຯ��Kmeans2��ͼ�������ɫ���࣬�ﵽ�ָ��Ŀ�ġ�
	��д�˺�����Ŀ���ǣ�Kmeans2�������÷���Щ�����գ��ο������٣������Ƕ�ͼ����в����������٣������˺ܾ�Ҳ�Ҳ���,
	�ҵ�������Ҳ���в��ˣ����������Լ��㶨�ˣ������ҷ���һ�£�����Ҳο�����ʡ�������Kmeans2����ͼ���濪����ʱ��
	,����һЩ��·��

	�����Ӷ�ӡ��ͼ��sample.bmp������ɫ����

	���д˳���һ��Ҫ���ú�OpenCv������������


	 KMeans2
	 ���ո����������Ŀ���������Ͻ��о��� 
 
	 void cvKMeans2( const CvArr* samples, int cluster_count,  CvArr* labels, CvTermCriteria termcrit );
	 samples 
	 ���������ĸ������ÿ������һ�С� 
	 cluster_count 
	 �������ľ�����Ŀ 
	 labels 
	 �������������ÿ��������Ӧ������ʶ 
	 termcrit 
	 ָ������������������ͣ��򾫶ȣ����ε�������ľ������ĵ��ƶ����룩 
	 ���� cvKMeans2 ִ�� k-means �㷨 ���� cluster_count ���������Ĳ����������з��࣬��� labels(i) Ϊ���� i ������ʶ�� 
 */

//����˵����nCusterΪ���������
int color_cluster(char *filename,int nCuster )
{
	IplImage* img=cvLoadImage(filename);

	int i,j;
	CvMat *samples=cvCreateMat((img->width)*(img->height),1,CV_32FC3);//������������CV_32FC3����32λ����3ͨ������ɫͼ��
	CvMat *clusters=cvCreateMat((img->width)*(img->height),1,CV_32SC1);//��������Ǿ���CV_32SF1����32λ����1ͨ��

	int k=0;
	for (i=0;i<img->width;i++)
	{
		for (j=0;j<img->height;j++)
		{
			CvScalar s;
			//��ȡͼ��������ص����ͨ��ֵ��BGR��
			s.val[0]=(float)cvGet2D(img,j,i).val[0];//B
			s.val[1]=(float)cvGet2D(img,j,i).val[1];//G
			s.val[2]=(float)cvGet2D(img,j,i).val[2];//R
			cvSet2D(samples,k++,0,s);//�����ص���ͨ����ֵ��˳��������������
		}
	}

	//��������������ڿ���ͨ��ѧϰȷ����������
	cvKMeans2(samples,nCuster,clusters,cvTermCriteria(CV_TERMCRIT_ITER,100,1.0));//��ʼ���࣬����100�Σ���ֹ���1.0

	//����������ʾ��ͼ�񣬶�ֵͼ��
	IplImage *binimg=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	
	//�������ڵ�����ʾÿ����������ͼ��
	IplImage *cluster_img0=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	IplImage *cluster_img1=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	IplImage *cluster_img2=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);



	k=0;
	int val=0;
	float step=255/(nCuster-1);

	CvScalar bg={255,0,0,0};//��������Ϊ��ɫ
	for (i=0;i<img->width;i++)
	{
		for (j=0;j<img->height;j++)
		{
			cvSet2D(cluster_img0,j,i,bg);
			cvSet2D(cluster_img1,j,i,bg);
			cvSet2D(cluster_img2,j,i,bg);
		}
	}
	for (i=0;i<img->width;i++)
	{
		for (j=0;j<img->height;j++)
		{
			val=(int)clusters->data.i[k++];
			CvScalar s;
			s.val[0]=255-val*step;//����ǽ���ͬ���ȡ��ͬ������ֵ��
			cvSet2D(binimg,j,i,s);	

			//��ÿ��������з���
			switch(val)
			{
				case 0:
					cvSet2D(cluster_img0,j,i,s);break;//��ɫ��
				case 1:
					cvSet2D(cluster_img1,j,i,s);break;//��ɫ��
				case 2:
					cvSet2D(cluster_img2,j,i,s);break;//��ɫ��
				default:
					break;
			}	
		
		}
    }


	cvSaveImage("PicVideo//cluster_img0.png",cluster_img0);
	cvSaveImage("PicVideo//cluster_img1.png",cluster_img1);
	cvSaveImage("PicVideo//cluster_img2.png",cluster_img2);


	cvNamedWindow( "ԭʼͼ��", 1 ); 
	cvShowImage( "ԭʼͼ��", img  );


	cvNamedWindow( "����ͼ��", 1 ); 
	cvShowImage( "����ͼ��", binimg  );
	cvSaveImage("PicVideo//clusterimg.png",binimg);
	cvWaitKey(0); //�ȴ�����

	cvDestroyWindow( "ԭʼͼ��" );
	cvDestroyWindow( "����ͼ��" );

	cvReleaseImage( &img ); 
	cvReleaseImage( &binimg );
	cvReleaseImage(&cluster_img0);
	cvReleaseImage(&cluster_img1);
	cvReleaseImage(&cluster_img0);

	return 0;

}


