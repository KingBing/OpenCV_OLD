//-----------------------------------��ͼ��ƽ����------------------------------
//	����:��ͨ�˲�
//		  ---blur
//		  ---GaussianBlur
//		  ---medianBlur
//  �ο���http://blog.csdn.net/xiaowei_cqu/article/details/7785365
//  �汾:opencv2.4.2
//  ˵����˫���˲��Ĳ������������������������˲�Ч��
//-------------------------------------------------------------------------

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int opencv2_filter(char*path)
{
    using namespace cv;

    Mat image=imread(path);
    cvtColor(image,image,CV_BGR2GRAY);//opencv2.0��ͨ��ת������

    Mat blurResult;
    Mat gaussianResult;
    Mat medianResult;
	Mat bilateraResult;

    blur(image,blurResult,Size(5,5));  //��ģ����OpenCV�е� blur�����ǽ��б�׼�����˲���
    GaussianBlur(image,gaussianResult,Size(5,5),1.5); //��˹�˲�
    medianBlur(image,medianResult,5); //��ֵ�˲�
	bilateralFilter(image, bilateraResult, 3, 20, 20,0);//˫���˲�

    namedWindow("blur");imshow("blur",blurResult);
    namedWindow("Gaussianblur");imshow("Gaussianblur",gaussianResult);
    namedWindow("medianBlur");imshow("medianBlur",medianResult);
	namedWindow("bilateralBlur");imshow("bilateralBlur",medianResult);

    waitKey();
    return 0;
}