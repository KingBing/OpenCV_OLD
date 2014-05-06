#include "opencv2/opencv.hpp"
#include "windows.h"
#include "fstream"

using namespace std;
using namespace cv;

int hog_svm_train()
{
	vector<string> img_path;//�����ļ�������   
	vector<int> img_catg;    
	int nLine = 0;    
	string buf;    
	ifstream svm_data( "hog_svm/train.txt" );//ѵ������ͼƬ��·����д�����txt�ļ��У�ʹ��bat�������ļ����Եõ����txt�ļ�     
	unsigned long n;     
	while( svm_data )//��ѵ�������ļ����ζ�ȡ����    
	{    
		if( getline( svm_data, buf ) )    
		{    
			nLine ++;    
			if( nLine % 2 == 0 )//ע����������ͼƬȫ·����ż�����Ǳ�ǩ 
			{    
				img_catg.push_back( atoi( buf.c_str() ) );//atoi���ַ���ת�������ͣ���־(0,1��2��...��9)��ע����������Ҫ��������𣬷�������    
			}    
			else    
			{    
				img_path.push_back( buf );//ͼ��·��    
			}    
		}    
	}    
	svm_data.close();//�ر��ļ�    
	CvMat *data_mat, *res_mat;    
	int nImgNum = nLine / 2; //nImgNum������������ֻ���ı�������һ�룬��һ���Ǳ�ǩ     
	data_mat = cvCreateMat( nImgNum, 324, CV_32FC1 );  //�ڶ���������������������������descriptors�Ĵ�С�����ģ�������descriptors.size()�õ����Ҷ��ڲ�ͬ��С������ѵ��ͼƬ�����ֵ�ǲ�ͬ��  
	cvSetZero( data_mat );    
	//���;���,�洢ÿ�����������ͱ�־    
	res_mat = cvCreateMat( nImgNum, 1, CV_32FC1 );    
	cvSetZero( res_mat );    
	IplImage* src;    
	IplImage* trainImg=cvCreateImage(cvSize(28,28),8,3);//��Ҫ������ͼƬ������Ĭ���趨ͼƬ��28*28��С���������涨����324�����Ҫ����ͼƬ��С����������debug�鿴һ��descriptors�Ƕ��٣�Ȼ���趨��������    

	//����HOG����  
	for( string::size_type i = 0; i != img_path.size(); i++ )    
	{    
		src=cvLoadImage(img_path[i].c_str(),1);    
		if( src == NULL )    
		{    
			cout<<" can not load the image: "<<img_path[i].c_str()<<endl;    
			continue;    
		}    

		cout<<" ���� "<<img_path[i].c_str()<<endl;    

		cvResize(src,trainImg);     
		HOGDescriptor *hog=new HOGDescriptor(cvSize(28,28),cvSize(14,14),cvSize(7,7),cvSize(7,7),9);      
		vector<float>descriptors;//��Ž��     
		hog->compute(trainImg, descriptors,Size(1,1), Size(0,0)); //Hog��������      
		cout<<"HOG dims: "<<descriptors.size()<<endl;        
		n=0;    
		for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)    
		{    
			cvmSet(data_mat,i,n,*iter);//�洢HOG���� 
			n++;    
		}       
		cvmSet( res_mat, i, 0, img_catg[i] );    
		cout<<" �������: "<<img_path[i].c_str()<<" "<<img_catg[i]<<endl;    
	}    


	CvSVM svm = CvSVM();//�½�һ��SVM      
	CvSVMParams param;//������SVMѵ����ز���  
	CvTermCriteria criteria;      
	criteria = cvTermCriteria( CV_TERMCRIT_EPS, 1000, FLT_EPSILON );      
	param = CvSVMParams( CvSVM::C_SVC, CvSVM::RBF, 10.0, 0.09, 1.0, 10.0, 0.5, 1.0, NULL, criteria );          

	svm.train( data_mat, res_mat, NULL, NULL, param );//ѵ������     
	svm.save( "HOG_SVM_DATA.xml" );  //����ѵ���õķ�����    

	//////////////////////ѵ�����////////////////////////

	//�������
	/*

	IplImage *test;  
	char result[512]; 
	vector<string> img_tst_path;
	ifstream img_tst( "D:/SVM_TEST.txt" );  //������ҪԤ���ͼƬ���ϣ�����ı����ŵ���ͼƬȫ·������Ҫ��ǩ
	while( img_tst )  
	{  
		if( getline( img_tst, buf ) )  
		{  
			img_tst_path.push_back( buf );  
		}  
	}  
	img_tst.close(); 

	ofstream predict_txt( "SVM_PREDICT.txt" );//��Ԥ�����洢������ı���   
	for( string::size_type j = 0; j != img_tst_path.size(); j++ )//���α������еĴ����ͼƬ    
	{    
		test = cvLoadImage( img_tst_path[j].c_str(), 1);    
		if( test == NULL ) {    
			cout<<" can not load the image: "<<img_tst_path[j].c_str()<<endl;    
			continue;    
		}
		IplImage* trainTempImg=cvCreateImage(cvSize(28,28),8,3);
		cvZero(trainTempImg);    
		cvResize(test,trainTempImg); 

		HOGDescriptor *hog=new HOGDescriptor(cvSize(28,28),cvSize(14,14),cvSize(7,7),cvSize(7,7),9);       
		vector<float>descriptors;//�������       
		hog->compute(trainTempImg, descriptors,Size(1,1), Size(0,0));     
		cout<<"HOG dims: "<<descriptors.size()<<endl;    
		CvMat* SVMtrainMat=cvCreateMat(1,descriptors.size(),CV_32FC1);    
		int n=0;    
		for(vector<float>::iterator iter=descriptors.begin();iter!=descriptors.end();iter++)    
		{    
			cvmSet(SVMtrainMat,0,n,*iter);    
			n++;    
		}    

		int ret = svm.predict(SVMtrainMat);//�����
		sprintf( result, "%s  %d\r\n",img_tst_path[j].c_str(),ret );
		predict_txt<<result;  //�����������ı�
	}
	predict_txt.close();  
	cvReleaseImage(&test);
	
	*/
	cvReleaseMat( &data_mat );    
	cvReleaseMat( &res_mat );  
	cvReleaseImage(&trainImg);


	return 0;
}