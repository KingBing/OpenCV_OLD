//Function�� ���������ѧϰ
//Source:http://blog.csdn.net/augusdi/article/details/9000893
//Status: �ı��ֻ�������Ļ��Ƶȼ�
//Improve:
//Info:[11/19/2014 jmy]

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <math.h>
 

#define w 500
int levels = 3;
CvSeq* contours = 0;
 
void on_contourtrackbar(int pos)
{
    IplImage* cnt_img = cvCreateImage( cvSize(w,w), 8, 3 );
    CvSeq* _contours = contours;
    int _levels = levels - 3;
	
	// get to the nearest face to make it look more funny
    if( _levels <= 0 ) 
        _contours = _contours->h_next->h_next->h_next->h_next->h_next->h_next->h_next->v_next->h_next->h_next;
    //_contours = _contours->v_next;
    
	cvZero( cnt_img );
    cvDrawContours( cnt_img, _contours, CV_RGB(255,0,0), CV_RGB(0,255,0), _levels);//, 3, CV_AA, cvPoint(0,0) );

	/*_levels:
	3���������������������������������������
	2��������������������������
	1:����������
	0���ҵ��ĵ�һ��������
	-1����һ����������������������
	-2����һ�����������������������������������


	_contours->h_next:ͬ������һ������
	_contours->v_next:�����µ��²�����
	*/
    cvShowImage( "contours", cnt_img );
    cvReleaseImage( &cnt_img );
}
 
int CvContours( int argc, char** argv )
{
    CvMemStorage* storage = cvCreateMemStorage(0);

	//����Ц��ͼ
    IplImage* img = cvCreateImage( cvSize(w,w), 8, 1 );
    cvZero( img );
    for(int  i=0; i < 6; i++ )
    {
        int dx = (i%2)*250 - 30;//0%2=0;
        int dy = (i/2)*150;
        CvScalar white = cvRealScalar(255);
        CvScalar black = cvRealScalar(0);
        if( i == 0 )
        {
            for(int j = 0; j <= 10; j++ )
            {
                double angle = (j+5)*CV_PI/21;
                cvLine(img, cvPoint(cvRound(dx+100+j*10-80*cos(angle)),
                    cvRound(dy+100-90*sin(angle))),
                    cvPoint(cvRound(dx+100+j*10-30*cos(angle)),
                    cvRound(dy+100-30*sin(angle))), white, 1, 8, 0);
            }
        }
 
        cvEllipse( img, cvPoint(dx+150, dy+100), cvSize(100,70), 0, 0, 360, white, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(30,20), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(30,20), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(15,15), 0, 0, 360, white, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(15,15), 0, 0, 360, white, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(5,5), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(5,5), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+150, dy+100), cvSize(10,5), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+150, dy+150), cvSize(40,10), 0, 0, 360, black, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+27, dy+100), cvSize(20,35), 0, 0, 360, white, -1, 8, 0 );
        cvEllipse( img, cvPoint(dx+273, dy+100), cvSize(20,35), 0, 0, 360, white, -1, 8, 0 );
    }
 
    cvNamedWindow( "image", 1 );
    cvShowImage( "image", img );


    //Ѱ������
    cvFindContours( img, storage, &contours, sizeof(CvContour),
                    2, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
 
    //comment this out if you do not want approximation
    //contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
    //cvApproxPoly: �ƽ����� ���� �ƽ������Ƿ���


    cvNamedWindow( "contours", 1 );
    cvCreateTrackbar( "levels+3", "contours", &levels, 7, on_contourtrackbar );
    on_contourtrackbar(0);
    
	cvWaitKey(0);
    cvReleaseMemStorage( &storage );
    cvReleaseImage( &img );
 
    return 0;
}