#include"../test.h";

int Canny(char*filename)
{
	IplImage* pImg = NULL; 
	IplImage* pCannyImg = NULL;

	//����ͼ��ǿ��ת��ΪGray
	if( (pImg = cvLoadImage( filename, 0)) != 0 )
	{
		
		//Ϊcanny��Եͼ������ռ�
		pCannyImg = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_8U,	1);
		
		//canny��Ե���
		cvCanny(pImg, pCannyImg, 50, 200, 3);

		//��������
		cvNamedWindow("src", 1);
		cvNamedWindow("canny",1);


		//��ʾͼ��
		/*cvShowImage( "src", pImg );
		cvShowImage( "canny", pCannyImg );*/
	
	
		 cvSaveImage("aPICT0025.jpg",pCannyImg);
	
		
		//cvWaitKey(0); //�ȴ�����

		//���ٴ���
		cvDestroyWindow( "src" );
		cvDestroyWindow( "canny" );
		//�ͷ�ͼ��
		cvReleaseImage( &pImg ); 
		cvReleaseImage( &pCannyImg ); 
			
		}
	  return 0;

 }



