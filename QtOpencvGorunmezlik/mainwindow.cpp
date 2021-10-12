#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ekran_ac_clicked()
{
    kamera.open(0);
    if(!kamera.isOpened())
    {
        cout<<"Kamera Acilmadi!!!"<<endl;
    }
    else
       {
           cout<<"Kamera Acildi.."<<endl;


           connect(timer,SIGNAL(timeout()),this,SLOT(guncelle_win()));
           timer->start(20);
       }
}


void MainWindow::on_ekran_kapat_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(guncelle_win()));
    kamera.release();

    gosterme(resim);

    cout<<"Kamera Kapandi."<<endl;
}

void MainWindow::guncelle_win()
{

        for (int i = 0; i < 60; i++)
        {
            kamera >> background;
        }
     while(1)
     {


    kamera >> ekran;


            //flip(frame,frame,1);
            cvtColor(ekran, hsv, COLOR_BGR2HSV);


            inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), mask1);   // görünmez oluncak renk
            inRange(hsv, Scalar(170, 120, 70), Scalar(180, 255, 255), mask2);// görünmez oluncak renk

            mask1 = mask1 + mask2; // filterelemeleri topla

            Mat kernel = Mat::ones(3, 3, CV_32F);
            morphologyEx(mask1, mask1, cv::MORPH_OPEN, kernel); //görüntü iyileştirme
            morphologyEx(mask1, mask1, cv::MORPH_DILATE, kernel); //görüntü iyileştirme

            bitwise_not(mask1, mask2);//başka bir fonksiyondan aldığımız maskeyi bit bit tersliyoruz


            bitwise_and(ekran, ekran, res1, mask2);//orjinal video görüntüsü üzerinde pelerin gelecek yeri çıkarıyoruz
            bitwise_and(background, background, res2, mask1); // arka plan görüntüsünün üzerinde pelerin gelmeyecek yerleri çıkarıyoruz
            addWeighted(res1, 1, res2, 1, 0, final_output); //orjinal video görüntüsü üzerinde pelerin gelecek yeri çıkarıyoruz


            //görüntüle
            imshow("Gorunmezlik", final_output);
            imshow( "Orijinal", ekran );

            //Çıkmak için klavyede ESC'ye basın
            char c = (char)waitKey(25);
            if (c == 27)
                break;
            // Ayrıca bellek sızıntısını önlemek için kodda oluşturulan tüm matı serbest bırakın.
            ekran.release(), hsv.release(), mask1.release(), mask2.release(), res1.release(), res2.release(), final_output.release();

     }

}

void MainWindow::gosterme(Mat &resim)
{
    cvtColor(resim,resim,CV_BGR2RGB);

    qt_resim = QImage((const unsigned char*)(resim.data),resim.cols,resim.rows,QImage::Format_RGB888);

}
