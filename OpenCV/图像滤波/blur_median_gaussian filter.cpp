#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
    using namespace cv;

    Mat image=imread("cat.png");
    cvtColor(image,image,CV_BGR2GRAY);

    Mat blurResult;
    Mat gaussianResult;
    Mat medianResult;

    blur(image,blurResult,Size(5,5));
    GaussianBlur(image,gaussianResult,Size(5,5),1.5);
    medianBlur(image,medianResult,5);

    namedWindow("blur");imshow("blur",blurResult);
    namedWindow("Gaussianblur");imshow("Gaussianblur",gaussianResult);
    namedWindow("medianBlur");imshow("medianBlur",medianResult);

    waitKey();
    return 0;
}