#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*�ṩ��4��ֱ�߼�ⷽ����ʵ��*/

//-----------------------------------����ⷽ��һ��------------------------------
//	����:���ֱ�ߣ���ͳ��ĳһֱ��ָ�������ڵ�ֱ�������������α�ע
//  ˵����Switch between standard and probabilistic Hough transform by changing
//		  "#if 1" to "#if 0" and back 
//-------------------------------------------------------------------------------


#pragma region ��ⷽ��һ

int callinenum(CvSeq*lines,int y_value,int height,int varinace,CvPoint*end_line);

int line_dete_1(char*filename)
{
	IplImage* src = cvLoadImage( filename, 0 );
	if (!src){
		printf("����ͼ��:%sʧ�ܣ�\n",filename);
		return -1;
	}
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;
	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
	cvCanny( src, dst, 50, 200, 3 );
	cvCvtColor( dst, color_dst, CV_GRAY2BGR );//ΪʲôҪ�ѻҶ�ͼת��Ϊ��ɫͼ��
#if 0
	lines = cvHoughLines2( dst, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 100, 0, 0 );

	for( i = 0; i < MIN(lines->total,100); i++ )
	{
		float* line = (float*)cvGetSeqElem(lines,i);
		float rho = line[0];
		float theta = line[1];
		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		cvLine( color_dst, pt1, pt2, CV_RGB(255,0,0), 3, CV_AA, 0 );
	}
#else
	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 50, 100, 20 );
	printf("����������ֱ�߹���%d��\n",lines->total);
	int num_line=0;
	int height=10;//�̶����Ϊ10���·�����

	for( i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
	   
		//�Լ��ֱ�ߵĴ���
		char variace=5;
		if (abs(line[0].x-line[1].x)<variace) //��ֱֱ��
			cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

		if (abs(line[0].y-line[1].y)<variace) //ˮƽֱ��
		  	cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );
	   
	    //�����ο�
	   //CvPoint*end_line=NULL;
	   //num_line=callinenum(lines,line[0].y,height,variace,end_line);//ͳ������ֱ�ߵ�����
	   //if (num_line>10)//��ֱ�������ж�
	   //{
		  // //����ֱ����height�ĸ߶������ı����򣬻����α�ע
		  // cvRectangle(color_dst,line[0],end_line[1],CV_RGB(0,255,0),1);
	   //}


	}

#endif

	cvNamedWindow( "ԭʼͼ�񣨻ҶȻ�)", 1 );
	cvNamedWindow( "(ˮƽ����ֱ)ֱ�߼����", 1 );
	cvShowImage( "ԭʼͼ�񣨻ҶȻ�)", src );
	cvShowImage( "(ˮƽ����ֱ)ֱ�߼����", color_dst );
	cvSaveImage("��ˮƽ����ֱ)ֱ�߼����.png",color_dst);

	cvWaitKey(0);

	return 0;
}


//ͳ��ÿ��ֱ���¹̶�����height�µ�ֱ������
int callinenum(CvSeq*lines,int y_value,int height,int varinace,CvPoint*end_line)
{
  
	int line_number=0;

	for(int i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);//ָ��һ��ֱ��
		if (line[0].y<y_value+height)
		{	
			line_number++;
			end_line=line;//�������������һ��ֱ��
	    }
		
	}
	return line_number;;//����ֱ�ߵ�����
}
#pragma endregion ��ⷽ��һ


//-----------------------------------�����ģ�����------------------------------
//	����:opencvֱ�߼�����,�ڴ˽���Ϊ�ο�
//  ˵����Switch between standard and probabilistic Hough transform by changing 
//        "#if 1" to "#if 0" and back 
//------------------------------------------------------------------------------

#pragma region ��ⷽ����

int line_dete_2(char*filename)
{
	IplImage* src;
	if((src=cvLoadImage(filename, 0))!= 0)
	{
		IplImage* dst = cvCreateImage( cvGetSize(src), 8, 1 );
		IplImage* color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* lines = 0;
		int i;
		cvCanny( src, dst, 50, 200, 3 );  //�Ƚ��б�Ե���
		cvCvtColor( dst, color_dst, CV_GRAY2BGR );
#if 0
		lines = cvHoughLines2( dst, storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 100, 0, 0 );

		for( i = 0; i < MIN(lines->total,100); i++ )
		{
			float* line = (float*)cvGetSeqElem(lines,i);
			float rho = line[0];
			float theta = line[1];
			CvPoint pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000*(-b));
			pt1.y = cvRound(y0 + 1000*(a));
			pt2.x = cvRound(x0 - 1000*(-b));
			pt2.y = cvRound(y0 - 1000*(a));
			cvLine( color_dst, pt1, pt2, CV_RGB(255,0,0), 1, 8 );
		}
#else
		lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 80, 30, 10 );
		for( i = 0; i < lines->total; i++ )
		{
			CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
			cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, 8 );
		}
#endif
		cvNamedWindow( "Source", 1 );
		cvShowImage( "Source", src );

		cvNamedWindow( "Hough", 1 );
		cvShowImage( "Hough", color_dst );

		cvWaitKey(0);
		return 0;
	}
}
#pragma endregion ��ⷽ����


//------------------------------�����ģ��3��------------------------------
//	����:���ֱ�ߣ�ֱ�߱�ź��ļ�����
//-------------------------------------------------------------------------

#pragma region ��ⷽ����

int callinenum_hor(CvSeq*lines,int y_value,int height,char variace,int hor_hit[]);
int callinenum_ver(CvSeq*lines,int x_value,int width,char variace,int ver_hit[]);

FILE *fp;

int line_dete_3(char*filename)
{
	
	IplImage* src = cvLoadImage( filename, 0 );
	IplImage* dst;
	IplImage* color_dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;

	if( !src ){
		printf("ͼ�����ʧ�ܣ�\n");
		return -1;
	}

	//�ļ���¼����
	if ((fp=fopen("hit.txt","w"))==NULL){
		printf("���ļ�ʧ��");
		exit(1);
	}

	//ͼ���Ų���
	CvFont font;
	cvInitFont(&font,CV_FONT_HERSHEY_PLAIN,0.8,0.8,0.5,1.3,8);


	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );

	cvCanny( src, dst, 50, 200, 3 );
	cvCvtColor( dst, color_dst, CV_GRAY2BGR );//ΪʲôҪ�ѻҶ�ͼת��Ϊ��ɫͼ��
	cvRectangle(color_dst,cvPoint(0,0),cvPoint(25,25),CV_RGB(0,0,255),1);//���β���

	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 20, 100, 20 );
	
	char variace=10;//����Χ
	int line_number=0;
	int line_number_limit=5;
	int arealimit=30;//�̶����Ϊ10���·�����

	//ͳ��ˮƽ����ֱֱ�ߵ�����
	int hor_num=0;
	int ver_num=0;
	int hor_ver_num=0;

	//��¼ˮƽ����ֱֱ�߱�����
	int hor_hit[400];
	int ver_hit[400];

	fprintf(fp,"����ֱ��(������б��ˮƽ)����%d��\n",lines->total);

	for( int i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);//���ÿ��ֱ��
		
		//ˮƽֱ�߼��
		if (abs(line[0].y-line[1].y)<variace)
		{  	
			hor_num++;
			hor_ver_num++;

			fprintf(fp,"-------��%d��ֱ����ˮƽֱ��-----------\n",i);
			cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );
			
			//ֱ�߱��
			char number[10];
			sprintf(number,"%d",i);
			cvPutText(color_dst,number,line[0],&font,CV_RGB(32,69,207));

			line_number=callinenum_hor(lines,line[0].y,arealimit,variace,hor_hit);

			if (line_number>line_number_limit)
			{
				for(int j=0;j<400;j++)
				{
				   if(i==hor_hit[j]){
					   fprintf(fp,"     ��%d��ˮƽֱ�߱�������.....\n",i);
					   break;   
				   }
				}

				cvRectangle(color_dst,line[0],cvPoint(line[1].x,line[1].y+arealimit),CV_RGB(0,255,0),1);				
			}
		}
		 //��ֱֱ�߼��
		if (abs(line[0].x-line[1].x)<variace)
		{
			ver_num++;
			hor_ver_num++;
			fprintf(fp,"-------��%d��ֱ������ֱֱ��-----------\n",i);
			cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );
			
			//ֱ�߱��
			char number[10];
			sprintf(number,"%d",i);
			cvPutText(color_dst,number,line[0],&font,CV_RGB(184,32,207));

			line_number=callinenum_ver(lines,line[0].x,arealimit,variace,ver_hit);

			if (line_number>line_number_limit)
			{
				for (int j=0;j<400;j++)
				{
					if (i==ver_hit[j]){
					   fprintf(fp,"    ��%d��ֱֱ���Ѿ���������ĳ�����������ڡ�������\n",i);
					   break;
					}
				}

				cvRectangle(color_dst,line[0],cvPoint(line[1].x+arealimit,line[1].y),CV_RGB(0,255,0),1);	
			}
		}

	}
	fprintf(fp,"ˮƽ����ֱֱ�߹���%d\n",hor_ver_num);
	fprintf(fp,"ˮƽֱ�߹���%d\n",hor_num);
	fprintf(fp,"��ֱֱ�߹���%d\n",ver_num);

	fclose(fp);

	cvNamedWindow( "ֱ�߼�⣨input��", 1 );
	cvNamedWindow( "ֱ�߼�⣨output��", 1 );

	cvShowImage( "ֱ�߼�⣨input��", src );
	cvShowImage( "ֱ�߼�⣨output��", color_dst );


	cvSaveImage("line_detected.jpg",color_dst);

	cvWaitKey(0);

	return 0;
}


/* function:ͳ��ÿ��ֱ���¹̶�arealimit��Ȼ򳤶��µ�ֱ������
 *	paras:
 *		CvSeq*lines-->���е�ֱ��
 *		y_value-->Ҫͳ�Ƶ��y����ֵ
 *		x_value-->Ҫͳ�Ƶ��x����ֵ
 *		height-->Ҫͳ�ƵĴ�ֱ�����С
 *		width-->Ҫͳ�Ƶ�ˮƽ�����С
 */
int callinenum_hor(CvSeq*lines,int y_value,int height,char variace,int hor_hit[])
{
    int number=0;
	for(int i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		if (abs(line[0].y-line[1].y)<variace)
			if ((y_value<line[0].y)&&(line[0].y<y_value+height))
			  {
				  number++;
				  //��¼�����������е�ˮƽֱ�߱��
				  hor_hit[i]=i;
				  fprintf(fp,"   ��ˮƽֱ���¹̶����������ˮƽֱ�߱�ţ�%d\n",i);
			  }
	}
	return number;
}

int callinenum_ver(CvSeq*lines,int x_value,int width,char variace,int ver_hit[])
{
	int number=0;
	for(int i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		if (abs(line[0].x-line[1].x)<variace)
		  if ((x_value<line[0].x)&&(line[0].x<x_value+width))
			{
				number++;
				//��¼�����������е���ֱֱ�߱��
				ver_hit[i]=i;
				 fprintf(fp,"   ����ֱֱ�����ҵ�������ֱֱ�߱�ţ�%d\n",i);
		    }

	}
	return number;
}
#pragma endregion ��ⷽ����


//------------------------------�����ģ���ġ�------------------------------
//	����:���ñ�׼hough�任��������ǿֱ��ת����ax+by+c=0��
//-------------------------------------------------------------------------

#pragma region ��ⷽ����

int houghlinestd(char *filename)
{
	IplImage* imgTest = cvLoadImage(filename,0);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;

	lines = cvHoughLines2( imgTest, storage, CV_HOUGH_STANDARD,1,CV_PI/180, 5, 0, 0 );
	float* line = (float*)cvGetSeqElem(lines,0);
	float rho = line[0];          // distance from (0,0) to the line
	float theta = line[1];        // angle between x-axis and the normal to the line

	double thetaDegree = theta/3.1415*180;

	IplImage* imgRes = cvCreateImage(cvSize(imgTest->width,imgTest->height),IPL_DEPTH_8U,3);
	cvSetZero(imgRes);

	double a,b,c;                // ax+by+c=0
	if (theta>CV_PI/2)
	{
		theta = CV_PI-theta;
		if (theta>CV_PI/4)
		{
			a = 1/tan(theta);
			b = -1;
			c = rho/sin(theta);
		}
		else
		{
			a = 1;
			b = -tan(theta);
			c = rho/cos(theta);
		}
	}
	else
	{
		if (theta>CV_PI/4)
		{
			a = -1/tan(theta);
			b = -1;
			c = rho/sin(theta);
		}
		else
		{
			a = -1;
			b = -tan(theta);
			c = rho/cos(theta);
		}
	}

	if (abs(a)>abs(b))        // using x = -b/a*y-c/a
	{
		for (int h=0;h<imgRes->height;h++)
		{
			int w = -b/a*h-c/a;
			if (w<imgRes->width && w>=0)
			{
				imgRes->imageData[h*imgRes->widthStep+3*w] = 255;
			}
		}
	}
	else                    // using y = -a/b*x-c/b
	{
		for (int w=0;w<imgRes->width;w++)
		{    

			int h = -a/b*w-c/b;
			if (h<imgRes->height && h>=0)
				imgRes->imageData[h*imgRes->widthStep+3*w] = 255;
		}
	}
	cvSaveImage("PicVideo/houghline.jpg",imgRes);
	cvReleaseImage(&imgRes);
	cvReleaseImage(&imgTest);
	return 0;
}
#pragma endregion ��ⷽ����