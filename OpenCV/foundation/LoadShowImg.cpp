#include"../test.h";

void Load_Show_Img(char* filepath)
{

	/* cvLoadImage( filename, -1 ); Ĭ�϶�ȡͼ���ԭͨ���� 
		cvLoadImage( filename, 0 );ǿ��ת����ȡͼ��Ϊ�Ҷ�ͼ 
		cvLoadImage( filename, 1 );��ȡ��ɫͼ 
		*/

    IplImage *pImg;
	if(	(pImg = cvLoadImage( filepath, 1)) != 0 )
	{
		cvNamedWindow( "Image", 1 );//��������
		cvShowImage( "Image", pImg );//��ʾͼ��
		cvWaitKey(0); //�ȴ�����
		cvDestroyWindow( "Image" );//���ٴ���
		cvReleaseImage( &pImg ); //�ͷ�ͼ��
		cvWaitKey(0); //�ȴ�����

	}

	else{
		cout<<"����ʧ��"<<endl;
		cvWaitKey(0); //�ȴ�����

	}

}
