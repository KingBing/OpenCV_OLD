/*===============================================//
���ܣ�RGB��ȡ������
ʱ�䣺02/23/2012 SkySeraph
//===============================================*/
#include "iostream"
#include <fstream>
using namespace std;

#include "cv.h"
#include "highgui.h"

//#pragma comment(lib,"highgui.lib")
//#pragma comment(lib,"cv.lib")
//#pragma comment(lib,"cvaux.lib")
//#pragma comment(lib,"cxcore.lib")

int ReadSaveRGB()
{
    /* ��
    IplImage*img =  cvLoadImage("rgb.bmp",-1);
    if(img==NULL)
        return 0;
    CvScalar p;
    ofstream outfile("d:\\rgb.txt");
    outfile<<"ͼ���͸�:"<<img->width<<"*"<<img->height<<endl;
    for(int i=0;i<img->height;i++)
    {
        for(int j=0;j<img->width;j++)
        {
            p = cvGet2D(img,i,j);
            outfile<<p.val[0] <<" "<<p.val[1]<<" "<<p.val[2] <<" "<<endl;
        }    
    }    
*/
///*  ��
    IplImage* img =  cvLoadImage("PicVideo//rgb.png",-1);
    CvScalar p;
    ofstream outfile1("b.txt");
    ofstream outfile2("g.txt");
    ofstream outfile3("r.txt");
    outfile1<<"ͼ���͸�:"<<img->width<<"*"<<img->height<<endl;
    outfile1<<"ͼ��Bֵ"<<endl;
    outfile2<<"ͼ���͸�:"<<img->width<<"*"<<img->height<<endl;
    outfile2<<"ͼ��Gֵ"<<endl;
    outfile3<<"ͼ���͸�:"<<img->width<<"*"<<img->height<<endl;
    outfile3<<"ͼ��Rֵ"<<endl;
    //cvFlip(img);
    for(int i=0;i<img->width;i++)
    {
        for(int j=0;j<img->height;j++)
        {
            p = cvGet2D(img,j,i);//���õ�cvGet2D�ķ���
            outfile1<<p.val[0]<<" ";
            outfile2<<p.val[1]<<" ";
            outfile3<<p.val[2]<<" ";
        }
        outfile1<<endl;
        outfile2<<endl;
        outfile3<<endl;
    }   

    return 0;
}