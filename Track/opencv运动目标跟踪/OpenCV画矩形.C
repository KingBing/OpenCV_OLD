CvPoint2D32f point4[4];
  cvBoxPoints( track_box, point4);//�õ�track_box�ĸ��ǵĵ������
  CvPoint pt[4];
  for(int i=0;i<4;i++)
  pt[i]=cvPoint((int)point4[i].x,(int)point4[i].y);//��CvPoint2D32f���͵ĵ�תΪCvPoint����
  CvPoint* ppt=pt;

int count=4;
  cvPolyLine( imageTrack, &ppt,&count,1,1,CV_RGB(255,0,0),4);//������
