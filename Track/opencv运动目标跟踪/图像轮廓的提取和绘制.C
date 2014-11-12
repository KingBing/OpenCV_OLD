#include "highgui.h"
#include "cv.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int i=0;
    int mode = CV_RETR_CCOMP;//������ȡ����ģʽ
    int contours_num=0;//��ȡ��������Ŀ
    CvScalar external_color;//���������ߵ���ɫ
    CvScalar hole_color;
    CvMemStorage *storage = cvCreateMemStorage(0);
    CvSeq *contours =0;//�洢��ȡ������ͼ��

    IplImage *pImg = NULL;
    IplImage *pContourImg = NULL;//��ʾ��ȡ������ͼ��
    IplImage *src=/blog.armyourlife.info/cvLoadImage("1.png",1);

    pImg = cvCreateImage(cvGetSize(src),src->depth,1);
    pContourImg =cvCreateImage(cvGetSize(pImg),IPL_DEPTH_8U,3);
    cvCvtColor(src,pImg,CV_BGR2GRAY);//����ȡ��ͼ��ת��Ϊ�Ҷ�ͼ��
    cvNamedWindow("src",1);
    cvNamedWindow("contour",1);
    cvShowImage("src",src);//��ʾԭͼ
    cvThreshold(pImg,pImg,200,255,CV_THRESH_BINARY);//��ֵ��
    mode = CV_RETR_LIST;
    contours_num=cvFindContours(pImg,storage,&contours,sizeof(CvContour),mode,CV_CHAIN_APPROX_NONE);
    cout<<contours_num<<" "<<endl;//��ӡ�ҵ�����������Ŀ
    for (;contours!=0;contours=contours->h_next)
    {
        hole_color=CV_RGB(rand()&255,rand()&255,rand()&255);
        external_color = CV_RGB(rand()&255,rand()&255,rand()&255);
        cvDrawContours(pContourImg,contours,external_color,hole_color,1,2,8);
    }

    cvShowImage("contour",pContourImg);
    cvWaitKey(0);
    cvReleaseImage(&src);
    cvReleaseImage(&pImg);
    cvReleaseImage(&pContourImg);
    cvReleaseMemStorage(&storage);
} 



