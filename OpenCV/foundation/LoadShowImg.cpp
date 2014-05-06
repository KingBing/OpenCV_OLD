#include"../test.h";

void Load_Show_Img(char* filepath)
{

	/* cvLoadImage( filename, -1 ); 默认读取图像的原通道数 
		cvLoadImage( filename, 0 );强制转化读取图像为灰度图 
		cvLoadImage( filename, 1 );读取彩色图 
		*/

    IplImage *pImg;
	if(	(pImg = cvLoadImage( filepath, 1)) != 0 )
	{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", pImg );//显示图像
		cvWaitKey(0); //等待按键
		cvDestroyWindow( "Image" );//销毁窗口
		cvReleaseImage( &pImg ); //释放图像
		cvWaitKey(0); //等待按键

	}

	else{
		cout<<"加载失败"<<endl;
		cvWaitKey(0); //等待按键

	}

}
