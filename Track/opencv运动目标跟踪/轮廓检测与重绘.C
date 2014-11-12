/**************��ȡģʽ. 
CV_RETR_EXTERNAL - ֻ��ȡ���������� 
CV_RETR_LIST - ��ȡ�������������ҷ����� list �� 
CV_RETR_CCOMP - ��ȡ�������������ҽ�����֯Ϊ����� hierarchy: ����Ϊ��ͨ�����Χ�߽磬�β�Ϊ�����ڲ�߽硣 
CV_RETR_TREE - ��ȡ���������������ع�Ƕ��������ȫ�� hierarchy method 
*********************************/
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int i=0;
    int mode=CV_RETR_EXTERNAL;//��ȡ������ģʽ
    int contours_num=0;//ͼ������ȡ��������Ŀ
    CvMemStorage *storage=cvCreateMemStorage(0);//��������ʱ��Ҫ�Ĵ洢����
    CvSeq *contour =0;//���ô洢��ȡ������ָ��
    IplImage *img=cvLoadImage("lena.jpg",0);
    cvThreshold(img,img,128,255,CV_THRESH_BINARY);//��ֵ��
    IplImage *pContourImg = cvCreateImage(cvGetSize(img),
        IPL_DEPTH_8U,3);
    cvNamedWindow("windows",1);
    cvShowImage("windows",img);//��ʾ��ֵͼ
    /*cvFindContours������������*/
    mode=CV_RETR_EXTERNAL;//��ȡ�������������
    contours_num=cvFindContours(img,storage,&contour,
        sizeof(CvContour),mode,CV_CHAIN_APPROX_NONE);
    cout<<"������������ĿΪ��"<<contours_num<<" "<<endl;

    /*��㽫��������*/
    CvSeqReader reader;//������
    int count=0;
    if (contour!=0)
    {
        count=contour->total;
        cout<<count<<endl;
    }

    cvStartReadSeq(contour,&reader,0);
    CvPoint pt1;
    CvScalar color=CV_RGB(255,255,255);
    cvNamedWindow("contour",1);
    cvShowImage("contour",pContourImg);
    for (i=0;i<count;i++)//����ͼ��
    {
        CV_READ_SEQ_ELEM(pt1,reader);//����һ����
        cvCircle(pContourImg,pt1,1,color);//����һ���㣨����һ����һ�����ش�СΪ�뾶��Բ��
        cvShowImage("contour",pContourImg);
        cvWaitKey(5);
    }
    cvWaitKey(0);

    cvReleaseImage(&img);
    cvReleaseImage(&pContourImg);
    cvReleaseMemStorage(&storage);
    return 0;
} 



