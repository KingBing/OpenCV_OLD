#include "opencv2/opencv.hpp"
#include "windows.h"
#include "fstream"

using namespace std;
using namespace cv;


int hog_svm_test()
{

	CvSVM svm = CvSVM();
	svm.load("HOG_SVM_DATA.xml");//����ѵ���õ�xml�ļ�������ѵ������10K����д����
	//�������    
	IplImage *test;  
	char result[300]; //���Ԥ���� 
	test = cvLoadImage("8.png", 1); //��Ԥ��ͼƬ����ϵͳ�Դ��Ļ�ͼ���������д
	if (!test)
	{
		MessageBox(NULL,TEXT("��Ԥ��ͼ�񲻴��ڣ�"),TEXT("��ʾ"),MB_ICONWARNING);
		return -1;
	}
	IplImage* trainTempImg=cvCreateImage(cvSize(28,28),8,3);
	cvZero(trainTempImg);    
	cvResize(test,trainTempImg);     
	HOGDescriptor *hog=new HOGDescriptor(cvSize(28,28),cvSize(14,14),cvSize(7,7),cvSize(7,7),9);      
	vector<float>descriptors;//��Ž��       
	hog->compute(trainTempImg, descriptors,Size(1,1), Size(0,0)); //Hog��������      
	cout<<"HOG dims: "<<descriptors.size()<<endl;  //��ӡHog����ά����������324
	CvMat* SVMtrainMat=cvCreateMat(1,descriptors.size(),CV_32FC1);   
	int n=0;    
	for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)    
	{    
		cvmSet(SVMtrainMat,0,n,*iter);    
		n++;    
	}   

	int ret = svm.predict(SVMtrainMat);//�����
	sprintf(result, "%d\r\n",ret );

	cvNamedWindow("dst",1);
	cvShowImage("dst",test);

	MessageBox(NULL,result,TEXT("Ԥ����"),MB_OK);

	cvReleaseImage(&test);
	cvReleaseImage(&trainTempImg);
	return 0;
}