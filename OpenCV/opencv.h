#include <opencv/cv.h>
#include <opencv/highgui.h>

/*******数据*********/
struct Localtion{  
	unsigned int lx;  
	unsigned int ly;  
	unsigned int rx;  
	unsigned int ry;    
};

//基础
int rgb2hsv(char*filename); //颜色空间转换
int CalcVariance() ;//计算协方差矩阵
int ReadSaveRGB();



//视频读取和写入
int read_write_video(char*videoin,char*videoout); 
int images2video();  
int read_video_info(int para_num, char* paras[]);

//访问和操作像素的值
void visit_elem_Iplimage(char*picname);
void visit_elem_Mat(char*picname);



//人脸检测
int face_detection(char*filename);


//行人检测
int walker_detection(char*filename);

//角点检测
int susan_corner_dete(char*filename); 
int harris_corner_dete(char*filename);
int harris_corner_dete_improve(char*filename);
int fast_corner_dete(char*filename);


//灰度图像二值化
int mythreshold(char*filename);

//设置图像ROI
int ROIimg(char*filename);
int roi_mat();//该方法采用mat格式


//颜色聚类
int color_cluster(char *filename,int nCuster);

//图像旋转
int rotate_nearest_neibgour(char*filename);

//透视矫正
int rectify();

//通道分离和合并
void channel_split_merge(char*picname);
 
//Feture学习
int fast_feature(char*filename); 
int sift_feature();
int surf_feature();
int surf_feature_opencv();	

//xml读写
int xml_read_write(void);
int opencv_xml_write(char* photoname,Localtion areainfo);

//图像缩放（插值）
int inter_value(char*filename);