#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*meanshift用于图像分割*/
int MeanShiftSegment();



/*HOG和SVM*/
int hog_svm_train();
int hog_svm_test();


/*KNN分类算法*/
int KNN();
int KNN1( int argc, char** argv );