#include <opencv2/core/core.hpp> 
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


int hog_feature()
{
	Mat trainImg; //��Ҫ������ͼƬ
	trainImg=imread("1.jpg",1);   //��ȡͼƬ
	HOGDescriptor *hog=new HOGDescriptor(cvSize(3,3),cvSize(3,3),cvSize(5,10),cvSize(3,3),9);  //������˼���ο�����1,2
	vector<float>descriptors;//�������
	hog->compute(trainImg, descriptors,Size(1,1), Size(0,0)); //���ü��㺯����ʼ����
	printf("%d\n",descriptors.size()); //����һ�½������Ĵ�С�������Ƿ��������2��Ԥ���� ������ȫһ������ƪ���ºܸ���

	sift("1.jpg");  //�����Ҹ�д��sift...
	for (int i=0;i<kp.size();i++) 
	{  //���ѭ��������������ǰ�����㸽��3*3������ݶ���Ϣͳ��
		printf("keypoint %d at %f %f\n",i,kp[i].first,kp[i].second);
		if (kp[i].first==picw) 
			kp[i].first--;
		if (kp[i].first==0) 
			kp[i].first=1;
		if (kp[i].second==pich) 
			kp[i].second--;
		if (kp[i].second==0) 
			kp[i].second=1;
		int pos=(kp[i].second-1)*(picw-2)+kp[i].first-1;
		for (int j=0;j<9;j++) 
		{
			res[j]+=descriptors[pos*9+j];
		}
	}
	puts("result:");
	for (int i=0;i<9;i++) printf("%lf ",res[i]); //������������������
	puts("");
	IplImage * respic;  //�����ֱ��ͼ����������и�res.jpg���һ���ֱ��ͼ����ͼ��û�����ͼ�ܲ��˳��򣬰Ѵ������´���ע�͵���
	if ((respic = cvLoadImage("res.jpg", 1)) == 0) 
		return -1; 
	double maxx=0;
	for (int i=0;i<9;i++) if (maxx<res[i]) maxx=res[i];
	for (int i=0;i<9;i++) cvRectangle(respic, cvPoint(150+51*i,(maxx-res[i])/maxx*(352-77)+77),
		cvPoint(201+51*i,351), CV_RGB(0, 0, 0),
		1, 8, 0);
	CvFont font;
	cvInitFont( &font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0 );
	itoa((int)maxx,outs,10);
	cvPutText(respic,outs,cvPoint(53,83),&font,CV_RGB(0, 0, 0));
	cvNamedWindow("image1",1);
	cvShowImage("image1", respic);
	cvWaitKey(0);  
	cvDestroyWindow("image1");

}

