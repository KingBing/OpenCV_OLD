#include "kalman.h"
#include "ui_kalman.h"
#include <iostream>

using namespace std;

kalman::kalman(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kalman)
{
    //�ڹ��캯���ж���������У�
    img.create(500, 500, CV_8UC3);
    cout<<img.rows<<endl;
    //״̬ά��2������ά��1��û�п�����
    KF.init(2, 1, 0);
    //״ֵ̬�����Ƕȣ����ٶȣ�
    state.create(2, 1, CV_32F);
    processNoise.create(2, 1, CV_32F);
    measurement = Mat::zeros(1, 1, CV_32F);
    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(kalman_process()));

    ui->setupUi(this);
    //���������ui->setupUi(this)���棬��Ϊֻ���������ܷ���ui->textBrowser
    ui->textBrowser->setFixedSize(500, 500);
}

kalman::~kalman()
{
    delete ui;
}

void kalman::on_startButton_clicked()
{
    /*
      ʹ��kalma����һ
      ������䵽forǰ����kalman�ĳ�ʼ�����̣�һ����ʹ��kalman�����ʱ��Ҫ��ʼ����ֵ�У�
      ת�ƾ��󣬲������󣬹�������Э�����������Э����������Э�������
      ǰһ״̬У�����ֵ����ǰ�۲�ֵ
    */

    //������ֵΪ0����׼��0.1�Ķ�ά��˹������
    randn( state, Scalar::all(0), Scalar::all(0.1) );
    //transitionMatrixΪ��KalmanFilter�е�һ��������Mat�ͣ���Kalmanģ���е�״̬ת�ƾ���
    //ת�ƾ���Ϊ[1,1;0,1],2*2ά��
    KF.transitionMatrix = *(Mat_<float>(2, 2) << 1, 1, 0, 1);

    //����setIdentity�Ǹ���������Խ��߸���ֵͬ��Ĭ�϶Խ���ֵֵΪ1
    setIdentity(KF.measurementMatrix);
    //ϵͳ���������������
    setIdentity(KF.processNoiseCov, Scalar::all(1e-5));
    //�������������������
    setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
    //����������Э�������
    setIdentity(KF.errorCovPost, Scalar::all(1));
    //statePostΪУ��״̬���䱾�ʾ���ǰһʱ�̵�״̬
    randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));
    //���ö�ʱ��ʱ��,Ĭ���������ö�ʱ�������޶�ʱ������SingleShotΪfalse
    //�����������Ϊtrue����ö�ʱ��ֻ�ܶ�ʱһ��
    //���������ÿ��33ms��ȥִ��һ��kalman������
    timer->start(33);
 //   timer->setSingleShot( true );

}


void kalman::kalman_process()
{
    Point2f center(img.cols*0.5f, img.rows*0.5f);
    float R = img.cols/3.f;
    //state�д����ʼ�ǣ�stateΪ��ʼ״̬
    double stateAngle = state.at<float>(0);
    Point statePt = calcPoint(center, R, stateAngle);


    /*
      ʹ��kalma�����
      ����kalman������predict�����õ�״̬��Ԥ��ֵ����
    */
    //predicted state (x'(k)): x'(k)=A*x(k-1)+B*u(k)
    //����x(k-1)Ϊǰ���У��״̬�������������У��״̬��Ԥ���
    //��У��״̬corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    //���뱾ʱ�̵�Ԥ��ֵ��У��ֵ�й�ϵ
    Mat prediction = KF.predict();
    //��kalmanԤ����ǽǶ�
    double predictAngle = prediction.at<float>(0);
    Point predictPt = calcPoint(center, R, predictAngle);

    randn( measurement, Scalar::all(0), Scalar::all(KF.measurementNoiseCov.at<float>(0)));

    // generate measurement
    //�������Ĳ���
    measurement += KF.measurementMatrix*state;
   // measurement += KF.measurementMatrix*prediction;

    double measAngle = measurement.at<float>(0);
    Point measPt = calcPoint(center, R, measAngle);

    // plot points
    //���define����ǻ�2���߶�(�߳��ܶ�)����ʵ���ǻ�һ����X�������
    #define drawCross( center, color, d )                                 \
        line( img, Point( center.x - d, center.y - d ),                \
                     Point( center.x + d, center.y + d ), color, 1, CV_AA, 0); \
        line( img, Point( center.x + d, center.y - d ),                \
                     Point( center.x - d, center.y + d ), color, 1, CV_AA, 0 )

    img = Scalar::all(0);
    //״̬�����ɫ
    drawCross( statePt, Scalar(255,255,255), 3 );
    //����������ɫ
    drawCross( measPt, Scalar(0,0,255), 3 );
    //Ԥ��������ɫ
    drawCross( predictPt, Scalar(0,255,0), 3 );
    //��ʵֵ�Ͳ���ֵ֮���ú�ɫ����������
    line( img, statePt, measPt, Scalar(0,0,255), 3, CV_AA, 0 );
    //��ʵֵ�͹���ֵ֮���û�ɫ����������
    line( img, statePt, predictPt, Scalar(0,255,255), 3, CV_AA, 0 );


    /*
      ʹ��kalma������
      ����kalman������correct�����õ�����۲�ֵУ�����״̬����ֵ����
    */
    //��Ȼ�ú����з���ֵMat�����ǵ��øú���У������У��ֵ�Ѿ�������KF��statePost
    //���ˣ�corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    KF.correct(measurement);

    randn( processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));
    //���������Ļ���������Բ���˶������˵�������������Բ���˶�����Ϊ������ԭ���˶�������ܻ�ı�
    state = KF.transitionMatrix*state + processNoise;

    imwrite("../kalman/img.jpg", img);
    ui->textBrowser->clear();
    //ui->textBrowser->setFixedSize(img.cols, img.rows);
    ui->textBrowser->append("<img src=../kalman/img.jpg>");
}


void kalman::on_closeButton_clicked()
{
    close();
}
