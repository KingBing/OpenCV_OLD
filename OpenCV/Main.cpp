#include "opencv.h"

int main(int argc,char*argv[])
{
	//��ȡ�ļ����ڵ�ָ����ʽ�������ļ�
	//char filename[50];
	//for (int i=1;i<6;i++)
	//{
	//	sprintf(filename,"PicVideo/videoimg/video_%d_cr.jpg",i);
	//	printf("���ڴ���%s\n",filename);
	//	//Ҫ���еĴ���
	//	color_cluster(filename,2);
	//	cvWaitKey(0);
	//}
	
	
	char*videoname="PicVideo//test_o2.mp4";
	char*imagename="PicVideo//fruits.png";
		
	/*���� */
    //rgb2hsv(imagename); //��ɫ�ռ�ת��
	//CalcVariance() ;//����Э�������
	//ReadSaveRGB();//��ȡͼ�������ֵ��������txt�ļ���
    //visit_elem_Iplimage(imagename);
	//BrightContrastAdjust(imagename);//���ȺͶԱȶȵ���

	
	
	/*��Ƶ��д */
    read_write_video(videoname,"out.wmv");
	//images2video();
	//read_video_info(argc,argv);

	
	/*����ʶ�� */
	//face_detection(imagename);
	
	/*����ʶ�� */
	//walker_detection(imagename);
	
	/*�Ҷ�ͼ���ֵ��*/
	//mythreshold(imagename);
	
	
	/*����ͼ��ROI*/
	//ROIimg(imagename);
	//roi_mat(); 
	//roi_merge();
	
	/*��ɫ����*/
	//color_cluster(imagename,2);
		
	/*ͨ������ͺϲ�*/
	//channel_split_merge();

	/*xml��д*/
	//xml_read_write();
	//Localtion areainfo={12,12,23,23};
	//opencv_xml_write(imagename,areainfo);

	/*���ʺͲ������ص�ֵ*/
	//visit_elem_Iplimage(imagename);
	//visit_elem_Mat(imagename);

	getchar();

	return 0;

  
}