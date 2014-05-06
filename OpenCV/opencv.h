#include <opencv/cv.h>
#include <opencv/highgui.h>

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

//�ǵ���
int susan_corner_dete(char*filename); 
int harris_corner_dete(char*filename);
int harris_corner_dete_improve(char*filename);
int fast_corner_dete(char*filename);


//�Ҷ�ͼ���ֵ��
int mythreshold(char*filename);

//����ͼ��ROI
int ROIimg(char*filename);
int roi_mat();//�÷�������mat��ʽ


//��ɫ����
int color_cluster(char *filename,int nCuster);

//ͼ����ת
int rotate_nearest_neibgour(char*filename);

//͸�ӽ���
int rectify();

//ͨ������ͺϲ�
void channel_split_merge(char*picname);
 
//Fetureѧϰ
int fast_feature(char*filename); 
int sift_feature();
int surf_feature();
int surf_feature_opencv();	

//xml��д
int xml_read_write(void);
int opencv_xml_write(char* photoname,Localtion areainfo);

//ͼ�����ţ���ֵ��
int inter_value(char*filename);