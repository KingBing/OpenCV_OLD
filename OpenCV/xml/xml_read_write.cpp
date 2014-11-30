#include <highgui.h>  
#include <cv.h>  
#include <iostream>  
#include <iomanip>  
#include "opencv.h"

using namespace std; 



/**********дXML***********/  
int xml_read_write()  
{  
	int a=1;  
	float b=2.;  
	double c[]={4.5,6.7,8.9};  
	
	CvFileStorage *fs=cvOpenFileStorage("test.xml",0,CV_STORAGE_WRITE);  
	cvWriteComment(fs,"text location",1);  
	
	//��ʼд���� 
	cvStartWriteStruct(fs,"DATA",CV_NODE_MAP,0,cvAttrList(0,0));   

	//д����������a  
	cvWriteInt(fs,"a",a);  
	//д�븡��������b  
	cvWriteReal(fs,"b",b); 
	
	//д������c����  
	cvStartWriteStruct(fs,"c",CV_NODE_SEQ,0,cvAttrList(0,0));  
	cvWriteRawData(fs,c,3,"d");  
	cvEndWriteStruct(fs);

	cvEndWriteStruct(fs); 
	cvReleaseFileStorage(&fs);  
	return 0;
	
} 

/**********��ȡXML***********/  
int xml_mat_read()
{
	int i,j;  
	CvMat *readbyname,*readbynode;  
	CvFileNode *mat_node;//�ļ����  
	CvFileStorage *fs_read=NULL;//�ļ��洢  
	fs_read=cvOpenFileStorage("mat.xml",0,CV_STORAGE_READ);  
	readbyname = (CvMat *)cvReadByName(fs_read,NULL,"mat",NULL);  
	mat_node = cvGetFileNodeByName(fs_read,NULL,"mat");  
	readbynode = (CvMat *)cvRead(fs_read,mat_node);  
	for (i=0;i<3;i++)  
	{  
		for (j=0;j<3;j++)  
		{  
			cout<<CV_MAT_ELEM(*readbynode,int,i,j);  
		}  
		cout<<endl;  
	}  
	cvReleaseFileStorage(&fs_read);  
	cvReleaseMat(&readbynode);  
	cvReleaseMat(&readbyname);  

	return 0;  

}

/**********дXML***********/  
int opencv_xml_write(char* photoname,const Localtion areainfo)  
{  
	// �����ļ��洢����  
	CvFileStorage *fs=cvOpenFileStorage("location.xml",0,CV_STORAGE_WRITE,"UTF-8");   
	cvWriteComment(fs,"test xml file",1);  

	// ��ʼд�ṹ��������ͼmap��Ҳ���������ֵ�����ڵ㼯��  
	/*
	const char *attr[4]={"imagename=photoname","width=1","height=2","AreaNum=9"};
	CvAttrList imageinfo=cvAttrList(attr,0);
	*/
	cvStartWriteStruct(fs,"Tagset",CV_NODE_MAP,"id_size",cvAttrList(0,0));  
	
	cvWriteComment(fs,"text area info",1);  
	cvWriteString(fs,"IMG",photoname);
	cvWriteInt(fs,"Height",18); 
	cvWriteInt(fs,"Width",18);  
 
	cvWriteInt(fs,"areas_num",4);  
	int area_info[4]={areainfo.lx,areainfo.ly,areainfo.rx,areainfo.ry};  
	// ��ʼд�ṹ������������sequence�������ֵ�����ڵ㼯��  
    cvStartWriteStruct(fs,"area_coor",CV_NODE_SEQ);  
	cvWriteRawData(fs,area_info,4,"i");   
	cvEndWriteStruct(fs);  
	 
 
	cvEndWriteStruct(fs);   
	cvReleaseFileStorage(&fs);  
	return 0;
}   
