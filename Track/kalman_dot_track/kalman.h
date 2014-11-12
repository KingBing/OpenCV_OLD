#ifndef KALMAN_H
#define KALMAN_H

#include <QDialog>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

using namespace cv;

namespace Ui {
class kalman;
}

class kalman : public QDialog
{
    Q_OBJECT
    
public:
    explicit kalman(QWidget *parent = 0);
    ~kalman();
    
private slots:

    void on_startButton_clicked();

    void kalman_process();

    void on_closeButton_clicked();

private:
    Ui::kalman *ui;
    Mat img, state, processNoise, measurement;
    KalmanFilter KF;
    QTimer *timer;
    //����Բ�ĺ��ܳ�����Բ���ϵĽǶȣ���Բ���ϵ�����
    static inline Point calcPoint(Point2f center, double R, double angle)
    {
        //sinǰ���и�����������ΪͼƬ�Ķ������������Ͻ�
        return center + Point2f((float)cos(angle), (float)-sin(angle))*(float)R;
    }

};

#endif // KALMAN_H
