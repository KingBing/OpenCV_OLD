#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*meanshift����ͼ��ָ�*/
int MeanShiftSegment();



/*HOG��SVM*/
int hog_svm_train();
int hog_svm_test();


/*KNN�����㷨*/
int KNN();
int KNN1( int argc, char** argv );

/*ģ��ƥ��*/
int templateMatch();

/*Ŀ����*/
int find_obj();
int find_obj_calonder( int argc, char **argv );
int SURF_Homography();
