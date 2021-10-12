#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <QImage>
#include <vector>
#include <iostream>
#include <QTimer>
using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void guncelle_win();
    void gosterme(Mat &resim);

    void on_ekran_ac_clicked();

    void on_ekran_kapat_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer; // zaman
    VideoCapture kamera; //kamera
    Mat ekran; // kamera 0 atanan mat
    Mat resim; // void gosterme.
    QImage qt_resim; // Ekran

    Mat final_output;
        Mat background;
         Mat hsv;
          Mat mask1, mask2;
              Mat res1, res2;
};
#endif // MAINWINDOW_H
