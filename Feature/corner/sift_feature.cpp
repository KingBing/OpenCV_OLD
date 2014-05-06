// sift_test.cpp : �������̨Ӧ�ó������ڵ㡣

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp> //��Ϊ���������Ѿ�������opencv��Ŀ¼�����԰��䵱���˱���Ŀ¼һ��
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace cv;
using namespace std;

void readme();

int sift_feature()
{
	Mat img_1=imread("./PicVideo/box.png",CV_LOAD_IMAGE_GRAYSCALE);//�궨��ʱCV_LOAD_IMAGE_GRAYSCALE=0��Ҳ���Ƕ�ȡ�Ҷ�ͼ��
	Mat img_2=imread("./PicVideo/box_in_scene.png",CV_LOAD_IMAGE_GRAYSCALE);//һ��Ҫ�ǵ�����·����б�߷�������Matlab�������෴��

	if(!img_1.data || !img_2.data)//�������Ϊ��
	{
		cout<<"opencv error"<<endl;
		return -1;
	}
	cout<<"open right"<<endl;

	//��һ������SIFT���Ӽ��ؼ���

	SiftFeatureDetector detector;//���캯�������ڲ�Ĭ�ϵ�
	vector<KeyPoint> keypoints_1,keypoints_2;//����2��ר���ɵ���ɵĵ����������洢������

	detector.detect(img_1,keypoints_1);//��img_1ͼ���м�⵽��������洢��������keypoints_1��
	detector.detect(img_2,keypoints_2);//ͬ��

	//��ͼ���л���������
	Mat img_keypoints_1,img_keypoints_2;

	drawKeypoints(img_1,keypoints_1,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);//���ڴ��л���������
	drawKeypoints(img_2,keypoints_2,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);

	imshow("sift_keypoints_1",img_keypoints_1);//��ʾ������
	imshow("sift_keypoints_2",img_keypoints_2);

	//������������
	SiftDescriptorExtractor extractor;//���������Ӷ���

	Mat descriptors_1,descriptors_2;//������������ľ���

	extractor.compute(img_1,keypoints_1,descriptors_1);//������������
	extractor.compute(img_2,keypoints_2,descriptors_2);

	//��burte force����ƥ����������
	BruteForceMatcher<L2<float>>matcher;//����һ��burte force matcher����
	vector<DMatch>matches;
	matcher.match(descriptors_1,descriptors_2,matches);

	//����ƥ���߶�
	Mat img_matches;
	drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);//��ƥ������Ľ�������ڴ�img_matches��

	//��ʾƥ���߶�
	imshow("sift_Matches",img_matches);//��ʾ�ı���ΪMatches
	waitKey(0);
	return 0;
}