#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


//��Ե���
void susan(char* path);
void krisch(char* path);
void histogram(char* path);
void roberts(char *path);
void laplace(char *path);
void laplace_mat(char*path);
void prewitt(char *path);
void canny(char *path);
void sobel(char *path);
void log(char *path);

int canny_trackbar(char*filename);//����ϸ�ؽ�canny���÷�,���������ڲ���
int edge_trackbar( char*path);//����ë����

//ֱ�߼��
int stdhoughlinedete(char *filename);
int line_dete_2(char*filename);

//Բ���
int hough_circle(char*filename);

//���μ��
int square_detection();

//��ֵ��
int binaryzation(char*path);
int adaptiveThreshold(char*path);

//�������
int contour1();
int contour2();




