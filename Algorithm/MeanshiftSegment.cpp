//�ο���http://www.cnblogs.com/tornadomeet/archive/2012/06/06/2538695.html
// meanshift_segmentation.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;


Mat src,dst;
int spatialRad=10,colorRad=10,maxPryLevel=1;

//����û����ȥ
void meanshift_seg(int,void*)
{
    pyrMeanShiftFiltering(src,dst,spatialRad,colorRad,maxPryLevel);//����meanshiftͼ����������зָ�
	
    RNG rng=theRNG();
    Mat mask(dst.rows+2,dst.cols+2,CV_8UC1,Scalar::all(0));
    for(int i=0;i<dst.cols;i++)    //opencvͼ��Ⱦ���Ҳ�ǻ���0������
        for(int j=0;j<dst.rows;j++)
            if(mask.at<uchar>(j+1,i+1)==0)
            {
                Scalar newcolor(rng(256),rng(256),rng(256));
                floodFill(dst,mask,Point(i,j),newcolor,0,Scalar::all(1),Scalar::all(1));
				// floodFill(dst,mask,Point(i,j),newcolor,0,colorDiff,colorDiff);
            }
	
    imshow("dst",dst);
}

//�޸ķ���
//void meanshift_seg_s(int i,void*)
//{
//	spatialRad=i;
//	meanshift_seg();
//}
//
//void meanshift_seg_c(int i,void*)
//{
//	meanshift_seg();
//}
//
//void meanshift_seg_m(int i,void*)
//{
//	meanshift_seg();
//}




int MeanShiftSegment()
{
    
    namedWindow("src",1);
    namedWindow("dst",1);

    src=imread("test_a3(3).tif");
    CV_Assert(!src.empty());
	imshow("src",src);


    spatialRad=10;
    colorRad=10;
    maxPryLevel=1;

    //��ȻcreateTrackbar�����Ĳ���onChange����Ҫ����2��������ʽΪonChange(int,void*)
    //����������ϵͳ��Ӧ��������ʹ��createTrackbar����ʱ������õĺ������Բ���д����������
    //���Ŷ�����д����������ú�����ʵ�ֹ����л�����Ҫ����(int,void*)2����������
    createTrackbar("spatialRad","dst",&spatialRad,20,meanshift_seg);
    createTrackbar("colorRad","dst",&colorRad,20,meanshift_seg);
    createTrackbar("maxPryLevel","dst",&maxPryLevel,5,meanshift_seg);

	//meanshift_seg_s(spatialRad,0);
	//meanshift_seg_c(colorRad,0);
	//meanshift_seg_m(maxPryLevel,0);

	meanshift_seg(0,0);

   /*
	char c=(char)waitKey();
    if(27==c) return 0;
   */
	imshow("dst",src);

	waitKey();//���޵ȴ��û�������Ӧ
	//while(1);//���ﲻ����while(1)��ԭ������Ҫ�ȴ��û��Ľ�������while(1)û�иù��ܡ���Ȼ2�߶������޵ȴ������á�
    return 0;
}