// CompareImg1.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*2012-3-7 ���ܣ��Ƚ�����ͼ�������������Ӷ��ж�����ͼ������ƶ�*/

//#include "stdafx.h"
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>

int GetTexturePara(CvMat* paraMatri[4],double *texturePara);//
double GetVar(double ar[4]);//����������ķ���
double GetMean(double ar[4]);//����������ľ�ֵ
int GetGLCM(CvMat * ImgMat,double* texturePara);//�ɹ���������ȡ�������������
//��ͨ��GetTexturePara��������GetVar��GetMean����,������������ľ�ֵ�ͷ���
double comparePara(double* textureArray1,double* textureArray2);//�Ƚ�����ͼ������������������ش������ƶȵ�ֵ
double ComputeTextureDiff(IplImage *pImg1,IplImage *pImg2);//�Ƚ�����ͼ������ƶȣ����ȵ���GetGLCM������Ȼ����ú���comparePara

int CompareImg()
{

	IplImage *pImg1 = cvLoadImage("PIC/zx/(1)pp.png",-1);//��������ͼ��
	IplImage *pImg2 = cvLoadImage("PIC/zx/(3)Canny.png",-1);

	if (!pImg1 && !pImg2 )
	{
		return -1;
	}


	double dDiff = 0.0; //����ͼ�Ĳ��
	dDiff = ComputeTextureDiff(pImg1,pImg2);
   printf("����ͼ��Ĳ��Ϊ��%f",dDiff);
   cvWaitKey(0);
   

	return 0;
}


double comparePara(double* textureArray1,double* textureArray2)
{

	double paraDis[16];
	double sumPara=0;
	double tempmax= 0;
	for(int i=0;i<16;i++)
	{
		tempmax=textureArray1[i] > textureArray2[i] ? textureArray1[i] : textureArray2[i];
		if (tempmax==0)
		{
			tempmax = 1;
		}
		paraDis[i]= (textureArray1[i]-textureArray2[i])*(textureArray1[i]-textureArray2[i])/(tempmax*tempmax);

		sumPara += paraDis[i];

	}
	sumPara =1- sqrt(sumPara)/16;//���ƶ� ֵԽ�����ƶ�Խ��

	return sumPara;
}
double GetMean(double ar[4])//�����ֵ��GetGLCM�����л��õ�
{
	double sumValue=0;
	for (int i=0;i<4;i++)
	{
		sumValue += ar[i];
	}
	return (sumValue/4.0);
}
double GetVar(double ar[4])//���㷽��ֵ��GetGLCM�����л��õ�
{
	double sumValue=0;
	for (int i=0;i<4;i++)
	{
		sumValue += ar[i]*ar[i];
	}
	return (sumValue/4.0);
}
int GetTexturePara(CvMat* paraMatri[4],double *texturePara)
{
	double tempArray[4]={0};
	/*static double texturePara[16]={0};*/
	int textureNum=0;
	for(int paraNum=0;paraNum<8;paraNum++)
	{

		for (int i=0;i<4;i++)
		{
			tempArray[i] = cvGetReal1D(paraMatri[i],paraNum);   //����ÿһ�ж���ʾ��ͬ���������ֻ���ڲ�ͬ�ĽǶ��¶���

		}
		*(texturePara+textureNum)= GetMean(tempArray);
		*(texturePara+textureNum)=GetVar(tempArray) - (*(texturePara+textureNum))* (*(texturePara+textureNum));
		textureNum++;

	}
	return 0;
}

int GetGLCM(CvMat * ImgMat,double* texturePara)//���ɹ������������ص��������
{
	int i,j,m,n,dim;
	double  minvalue = 0.0,maxvalue = 0.0;
	int imgWidth,imgHeight;
	imgWidth = ImgMat->width;
	imgHeight = ImgMat->height;
	CvMat* ImgMatUchar = cvCreateMat(imgHeight,imgWidth,CV_8UC1);//ͼ��Ҷ�ֵ��Χ0-255
	cvMinMaxLoc(ImgMat,&minvalue,&maxvalue);//Ѱ�����ֵ��Сֵ

	//--------------------�������д���ʵ��ͼ���һ����������ֵ��һ����0-255
	cvConvertScale(ImgMat,ImgMat,1,-minvalue);//���Ա任ת������
	cvConvertScale(ImgMat,ImgMat,255/(maxvalue-minvalue),0);
	cvConvert(ImgMat,ImgMatUchar);

	//--------------------Ϊ����߼����ٶȣ������ͼ���������------------
	for(j=0;j<imgHeight;j++)
		for(i=0;i<imgWidth;i++)
			for (n=0;n<16;n++)//���طּ�
			{
				uchar temp = CV_MAT_ELEM(*ImgMatUchar,uchar,j,i);
				if (n*16<=temp&&(temp<=n*16+15))
				{
					*((uchar*)CV_MAT_ELEM_PTR(*ImgMatUchar,j,i)) = n;
				}
			}

			//------------------���㹲������ȡ����Ϊ1���Ƕ�Ϊ0,45,90,135------------
			//create comatrix
			CvMat* CoMatri[4];//���������飬openCV������÷�!!!! ����������
			for (dim =0;dim<4;dim++)
			{
				CoMatri[dim]=cvCreateMat(16,16,CV_64FC1);
				cvZero(CoMatri[dim]);
			}
			for (m=0;m<16;m++)//��16���Ҷȵȼ���16*16�Ĺ������󣬹�������Ĵ�С��ͼ��ĻҶȼ�����
			{
				for (n=0;n<16;n++)
				{
					//printf("%d",n*m);
					for(j=0;j<imgHeight;j++)//ͼ���С
					{
						for (i=0;i<imgWidth;i++)
						{
							uchar temp = CV_MAT_ELEM(*ImgMatUchar,uchar,j,i);//ͼ����ĳ������
							double tempMatValue;

							//ͳ��0�ȻҶȹ�������
							if (i<(imgWidth-1)&&(temp == m)&&(CV_MAT_ELEM((*ImgMatUchar),uchar,j,(i+1)) == n))
						 {
							 // printf("%d,%d,%d,%d\n",i,j,m,n);

							 tempMatValue = cvGetReal2D(CoMatri[0],m,n);
							 cvSetReal2D(CoMatri[0],m,n,(tempMatValue+1.0));//ͳ�Ƹ�����û����һ�����������ļ�1
							 cvSetReal2D(CoMatri[0],n,m,(tempMatValue+1.0));
						 }
							//ͳ��45�ȻҶȹ�������


							if((i<(imgWidth-1))&&(j>0)&&(temp == m)&&(CV_MAT_ELEM(*ImgMatUchar,uchar,j-1,i+1) == n))//�����ԭ�����ڣ������ж�����˳��ģ�

						 {
							 tempMatValue = cvGetReal2D(CoMatri[1],m,n);
							 cvSetReal2D(CoMatri[1],m,n,(tempMatValue+1.0));//ͳ�Ƹ�����û����һ�����������ļ�1
							 cvSetReal2D(CoMatri[1],n,m,(tempMatValue+1.0));
						 }
							//ͳ��90�ȻҶȹ�������
							if (j<(imgHeight-1)&&temp==m&&(CV_MAT_ELEM(*ImgMatUchar,uchar,j+1,i)==n))
						 {
							 tempMatValue = cvGetReal2D(CoMatri[2],m,n);
							 cvSetReal2D(CoMatri[2],m,n,(tempMatValue+1.0));//ͳ�Ƹ�����û����һ�����������ļ�1
							 cvSetReal2D(CoMatri[2],n,m,(tempMatValue+1.0));
						 }


							//ͳ��135�ȻҶȹ�������
							if (i<(imgWidth-1)&&j<(imgHeight-1)&&temp==m&&(CV_MAT_ELEM(*ImgMatUchar,uchar,j+1,i+1)==n))//�ж�Ҫ��˳�򣬱��������жϵ�ǰԪ���Ƿ�����һ������Ԫ�أ����򲻽����ж�
						 {
							 tempMatValue = cvGetReal2D(CoMatri[3],m,n);
							 cvSetReal2D(CoMatri[3],m,n,(tempMatValue+1.0));//ͳ�Ƹ�����û����һ�����������ļ�1
							 cvSetReal2D(CoMatri[3],n,m,(tempMatValue+1.0));
						 }


						}
					}
					//---------------��������ĶԽ����ϵ�ֵ------
					if (m == n)
					{
						for (dim =0;dim<4;dim++)//����֮һ�������� ������ѭ��
						{
							double tempMatValue1 = cvGetReal2D(CoMatri[dim],m,n);
							cvSetReal2D(CoMatri[dim],m,n,(tempMatValue1*2));
						}
					}


				}
			}


			// -------------------�Թ���������й�һ������------------------
			CvMat * NormalizedMat =cvCreateMat(16,16,CV_64FC1);
			for (dim=0;dim<4;dim++)
			{
				CvScalar sumValue = cvSum(CoMatri[dim]);
				cvSet(NormalizedMat,sumValue);//��ʼ������
				cvDiv(CoMatri[dim],NormalizedMat,CoMatri[dim]);//a./b->c ����2����������
			}

			//------------------���㹲������������������ء����Ծء���ص�--------------
			double energy[4] = {0};//����
			double entropy[4] = {0};
			double angleMoment[4] ={0};
			double inertia[4] = {0};
			double localSmooth[4] ={0};//�ֲ�ƽ��
			double Pmax[4] ={0};//������
			double DIS[4] = {0};//����
			double DifEntropy[4] = {0};//����
			double SumEntropy[4] = {0};//����
			double SumIndexVal= 0;
			double DifIndexVal = 0;
			double IndexVal[2*16-1] ={0};//���ڴ洢��x+y=kΪ�±�Ĺ��������е�ֵ
			double IndexValDif[16] ={0};//���ڴ洢��|x-y|=kΪ�±�Ĺ��������е�ֵ
			double sumVar[4] = {0};//���صķ���
			double difVar[4] = {0};//���صķ���
			//������еľ�ֵ
			//���ڹ�������Ϊ�Խ��󣬸��������еľ�ֵ���
			double dMean = 0.0;//��ÿһ�л����еľ�ֵ
			double dSum[16] = {0.0};//��¼ÿ���л����еĺ�
			double dStdDev = 0.0;//��ÿһ�л����еķ���
			double correlation[4]={0};
			CvMat * matEnergy[4];
			CvMat* matEntropy[4];
			CvScalar tempEnergy[4];
			for(dim=0;dim<4;dim++)
			{
				matEnergy[dim] = cvCreateMat(16,16,CV_64FC1);
				cvMul(CoMatri[dim],CoMatri[dim],matEnergy[dim]) ;
				tempEnergy[dim] = cvSum(matEnergy[dim]);
				energy[dim] = tempEnergy[dim].val[0];
			}


			for (dim=0;dim<4;dim++)
			{

				Pmax[dim]=0;
				for (i=0;i<16;i++)
				{
					for (j=0;j<16;j++)
					{
						double tempEntropy = cvGetReal2D(CoMatri[dim],i,j);
						if (tempEntropy != 0)
						{
							entropy[dim] += -tempEntropy*log(tempEntropy);//�����Ƕ��¹����������
						}
						angleMoment[dim]  += tempEntropy*tempEntropy;//�Ƕ��׾�UNI
						inertia[dim] += (double)(i-j)*(double)(i-j)*tempEntropy;//������߹��Ծ�
						localSmooth[dim] += tempEntropy/((double)(i-j)*(double)(i-j)+1);//�ֲ�ƽ��
						DIS[dim] += tempEntropy*abs(i-j);//������
						correlation[dim] += (i*j*tempEntropy); //��ص�һ���ּ���
						dSum[i] +=tempEntropy;
						if (tempEntropy>Pmax[dim])//������
						{
							Pmax[dim] = tempEntropy;
						}

					}

				}

				for (int k=0;k<(16*2-1);k++)//�������
				{
					SumIndexVal=0;//ע���ۼ�

					for(int g=0;(k<16)&&(g<=k);g++)
				 {

					 double sumInd= cvGetReal2D(CoMatri[dim],g,k-g);
					 if (sumInd>1e-15)
					 {
						 SumIndexVal +=(-1.0)* sumInd*log(sumInd);
					 }

				 }

					IndexVal[k] = SumIndexVal; //������x+y=kΪindex��Ԫ��ֵ������������漰�Ĳ���

				}
				SumEntropy[dim]=SumIndexVal;//�����Ƕ��µĺ���



				for(int k=0;k<(16*2-1);k++ )	//����sum variance
				{
					sumVar[dim] += (k-SumEntropy[dim])*(k-SumEntropy[dim])*(IndexVal[k]);//���صķ���

				}


				for(int k=0;k<16;k++)//�������
			 {
				 DifIndexVal = 0;
				 for (int g=0;g<16;g++)
				 {
					 //����if�������ʵ��abs(i-j)=k
					 if ((g-k)>=0&&(g-k)<16)
					 {
						 double difIndVal = cvGetReal2D(CoMatri[dim],g,g-k);
						 if (difIndVal>1e-15)
						 {
							 DifIndexVal += (-1.0)*difIndVal*log(difIndVal);
						 }

					 }

					 if ((g+k)>=0&&(g+k)<16)
					 {
						 double difIndVal = cvGetReal2D(CoMatri[dim],g,g+k);
						 if (difIndVal>1e-15)
						 {
							 DifIndexVal += (-1.0)*difIndVal*log(difIndVal);
						 }

					 }

				 }
				 IndexValDif[k] = DifIndexVal;//������|x-y|=kΪindex��Ԫ��ֵ������������漰�Ĳ���
			 }

				DifEntropy[dim] += DifIndexVal ;// ����


				for (int k=0;k<16;k++)// ������صķ���
				{
					difVar[dim]  += (k-DifEntropy[dim])*(k-DifEntropy[dim])*IndexValDif[k];
				}


				for (int x=0;x<16;x++)//��������еľ�ֵ
				{
					dMean += (x *dSum[x]);//���ֵ�����ַ�����������
				}

				for (int x=0;x<16;x++)//��������еķ���
				{
					dStdDev += (x - dMean)*(x-dMean)*dSum[x];//�󷽲�����ַ�����������
				}


				if(abs(dStdDev)>1e-15)//�����
				{

					correlation[dim] += (correlation[dim] - dMean*dMean)/dStdDev;
				}
				else
				{
					correlation[dim]=0;

				}
			}

			//-------------����һ�������ĸ��Ƕȹ�������������������Ĵ����---------------
			CvMat *paraMat[4];//���������ĸ��Ƕ�
			for (dim=0;dim<4;dim++)//
			{

				paraMat[dim] = cvCreateMat(1,8,CV_64FC1);//ÿ��������ĳ���Ƕ��¶�Ӧ��5���������������о���ʱ��λ1����Ϊ5��
				//���������setReal2Dʱ��ע��߶�ʼ��Ϊ1����Ӧ�����еĲ���cvSetReal2D(paraMat[dim],0,0,tempVal);
				//��һ��ʼ��Ϊ0����ʾ�иߣ���0��ʼ�����
				cvZero(paraMat[dim]);//��ʼ������

				double tempVal = energy[dim];//�������������ĸ�ֵ

				cvSetReal2D(paraMat[dim],0,0,tempVal);

				tempVal = entropy[dim];

				cvSetReal2D(paraMat[dim],0,1,tempVal);

				tempVal = angleMoment[dim];

				cvSetReal2D(paraMat[dim],0,2,tempVal);

				tempVal = inertia[dim];
				cvSetReal2D(paraMat[dim],0,3,tempVal);

				tempVal = localSmooth[dim];
				cvSetReal2D(paraMat[dim],0,4,tempVal);

				tempVal = correlation[dim];
				cvSetReal2D(paraMat[dim],0,5,tempVal);

				tempVal = Pmax[dim];
				cvSetReal2D(paraMat[dim],0,6,tempVal);

				tempVal = DIS[dim];
				cvSetReal2D(paraMat[dim],0,7,tempVal);

			}

			//�������ղ����������������ڲ�ͬ�Ƕ��ϵľ�ֵ�ͷ���
			//static double *textureArray=NULL;
			GetTexturePara(paraMat,texturePara);
			/*	return (double*)textureArray;*/
			return 0;

}


double ComputeTextureDiff(IplImage *pImg1,IplImage *pImg2)
{
	double dResult = 0.0;
	//--------------ͼ��ת��Ϊ����������-------------------------
	IplImage* pGrayImg1= cvCreateImage(cvGetSize(pImg1),pImg1->depth,1);//���ڴ洢�Ҷ�ͼ��
	IplImage* pGrayImg2= cvCreateImage(cvGetSize(pImg2),pImg2->depth,1);


	CvMat* pGrayMat1 = NULL; //ͼ��ת��Ϊ�����������
	pGrayMat1 = cvCreateMat(pGrayImg1->height,pGrayImg1->width,CV_64FC1);
	CvMat* pGrayMat2 = NULL; //ͼ��ת��Ϊ�����������
	pGrayMat2 = cvCreateMat(pGrayImg2->height,pGrayImg2->width,CV_64FC1);


	cvCvtColor(pImg1,pGrayImg1,CV_BGR2GRAY); //����ɫͼ��ת��Ϊ�Ҷ�ͼ��
	cvConvert(pGrayImg1,pGrayMat1); //����ɫͼ��ת��Ϊ�Ҷ�ͼ��,ע�������pGrayImg����ͼ��Mat��ת��

	cvCvtColor(pImg2,pGrayImg2,CV_BGR2GRAY); //����ɫͼ��ת��Ϊ�Ҷ�ͼ��
	cvConvert(pGrayImg2,pGrayMat2); //����ɫͼ��ת��Ϊ�Ҷ�ͼ��,ע�������pGrayImg����ͼ��Mat��ת��


	//compute:
	double texturePara1[16],texturePara2[16];
	/*double *ptexturePara1,*ptexturePara2;*/
	GetGLCM(pGrayMat1,texturePara1);
	GetGLCM(pGrayMat2,texturePara2);
	dResult = comparePara(texturePara1,texturePara2);


	return dResult;
}
