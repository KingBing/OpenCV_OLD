int i,j;
uchar* imgArray;
uchar* array;


imgArray=(uchar*)image->imageData;//ͼ�����ݵ�ָ��
for (i=0;i<image->height;i++)
{
array=imgArray+image->widthStep*i;//��ǰ�е�ָ��
for (j=0;j<image->width;j++)
{
if(array[j*3]>thr)//��ǰ����ֵ������ֵ
prinrf("i=%d j=%d",i,j);//�������
}
}
