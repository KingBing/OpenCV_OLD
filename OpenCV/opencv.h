#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

/*******����*********/
struct Localtion{  
	unsigned int lx;  
	unsigned int ly;  
	unsigned int rx;  
	unsigned int ry;    
};

//����
int rgb2hsv(char*filename); //��ɫ�ռ�ת��
int CalcVariance() ;//����Э�������
int ReadSaveRGB();
int BrightContrastAdjust(char*path );//���ȺͶԱȶȵ���


//��Ƶ��ȡ��д��
int read_write_video(char*videoin,char*videoout); 
int images2video();  
int read_video_info(int para_num, char* paras[]);

//���ʺͲ������ص�ֵ
void visit_elem_Iplimage(char*picname);
void visit_elem_Mat(char*picname);

//�������
int face_detection(char*filename);
//���˼��
int walker_detection(char*filename);

//�Ҷ�ͼ���ֵ��
int mythreshold(char*filename);


//����ͼ��ROI
int ROIimg(char*filename);
int roi_mat();//�÷�������mat��ʽ
int roi_merge();//����roi��ͼ���ں�

//��ɫ����
int color_cluster(char *filename,int nCuster);

//ͨ������ͺϲ�
void channel_split_merge();
 
//xml��д
int xml_read_write(void);
int opencv_xml_write(char* photoname,Localtion areainfo);

