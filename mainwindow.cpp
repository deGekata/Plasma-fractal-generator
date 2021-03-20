#include "mainwindow.h"
#include "ui_mainwindow.h"

double scale = 0.3125;

void MainWindow::Process(int x1, int y1, int x2, int y2){
    //    qDebug() << x1 << y1 << " x1,y1 " << x2 << y2 << " x2,y2 pre ";
    //    qDebug() << mas[x1][y1] << mas[x1][y2] << mas[x2][y1] << mas[x2][y2];
    //    qDebug() << " aft";
    double cur_rnd;
    cur_rnd = (2.0 * rand() / RAND_MAX - 1) * (2 * scale * rand() / RAND_MAX - scale) * (abs(x1-x2) + abs(y1-y2));


    //    my_struct(mas[1][1].hue;
    mas[(x1 + x2) / 2][(y1 + y2) / 2] = my_struct(
                (static_cast<int>((mas[x1][y1].hue + mas[x2][y2 ].hue + mas[x1][y2].hue + mas[x2][y1].hue) / 4 + cur_rnd ) % 360 + 360) % 360, 255, 150);

    mas[x1][(y2 + y1) / 2] = my_struct((mas[x1][y1].hue + mas[x1][y2].hue) / 2, 255, 150);

    mas[x2][(y2 + y1) / 2] = my_struct((mas[x2][y1].hue + mas[x2][y2].hue) / 2, 255, 150);

    mas[(x1 + x2) / 2][y1] = my_struct((mas[x1][y1].hue + mas[x2][y1].hue) / 2, 255, 150);

    mas[(x1 + x2) / 2][y2] = my_struct((mas[x1][y2].hue + mas[x2][y2].hue) / 2, 255, 150);

    //    qDebug() << mas[x1][(y2 + y1) / 2] << mas[x2][(y2 + y1) / 2] << mas[(x1 + x2) / 2][y1] << mas[(x1 + x2) / 2][y2];
    if(abs(x1 - x2) <= 2){
        return;
    }
    //    qDebug() << " left top";
    Process(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
    //    qDebug() << " right top";
    Process((x1 + x2) / 2, y1, x2, (y1 + y2) / 2);
    //    qDebug() << " left down";
    Process(x1, (y1 + y2) / 2, (x1 + x2) / 2, y2);
    //    qDebug() << " right down";
    Process((x1 + x2) / 2, (y1 + y2) / 2, x2, y2);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(gsize);


    srand(time(0));
    for(int i = 0; i < 100; ++i) {
        mas.resize(this->width());
        for(int it = 0; it < mas.size(); ++it){
            mas[it].resize(this->height());
        }
        my_struct tmp = my_struct(rand() % 360, 255, 150);//, rand() % 256, rand() % 256 );
        mas[0][0] = tmp;
        tmp = my_struct(rand() % 360, 255, 150);// rand() % 256, rand() % 256 );
        mas[0][mas.size() - 1] = tmp;
        tmp = my_struct(rand() % 360, 255, 150);//  % 256, rand() % 256, rand() % 256 );
        mas[mas.size() - 1][0] = tmp;
        tmp = my_struct(rand() % 360, 255, 150);// % 256, rand() % 256, rand() % 256 );
        mas[mas.size() - 1][mas.size() - 1] = tmp;

        mas[mas.size() / 2][mas.size() / 2]= my_struct(
                    (mas[0][0].hue + mas[0][mas.size()-1].hue + mas[mas.size()-1][0].hue + mas[mas.size()-1][mas.size()-1].hue) / 4, 255, 150);


        mas[0][(mas.size() + 0) / 2]= my_struct((mas[0][0].hue + mas[0][mas.size() - 1].hue) / 2, 255, 150);


        mas[mas.size() - 1][(mas.size() + 0) / 2] = my_struct((mas[mas.size() - 1][0].hue + mas[mas.size() - 1][mas.size() - 1].hue) / 2, 255, 150);


        mas[(0 + mas.size()) / 2][0] = my_struct((mas[0][0].hue + mas[mas.size() - 1][0].hue) / 2, 255, 150);


        mas[(0 + mas.size()) / 2][mas.size() - 1] = my_struct((mas[0][mas.size() - 1].hue + mas[mas.size() - 1][mas.size() - 1].hue) / 2, 255, 150);



        //    qDebug() << mas[mas.size() / 2][mas.size() / 2];
        Process(0, 0, mas.size() / 2, mas.size() / 2);
        Process(mas.size() / 2, 0, mas.size() - 1,mas.size() / 2);
        Process(0, mas.size() / 2, mas.size() / 2 ,mas.size() - 1);
        Process(mas.size()/ 2, mas.size() / 2, mas.size() - 1, mas.size() - 1);
        QImage* img = new QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
        QPainter* painter = new QPainter(img);
        QPen pen;
        QPixmap* pix;// = new QPixmap(this->size());
        for(int i = 0; i < mas.size(); ++i){
            for(int j = 0; j < mas.size(); ++j){
                //            qDebug() << mas[i][j] << i << j;
                pen.setColor(QColor::fromHsv(mas[i][j].hue, mas[i][j].lig, mas[i][j].sat));
                painter->setPen(pen);
                painter->drawPoint(i, j);
            }
        }
        pix = new QPixmap(QPixmap::fromImage(*img));
        //    delete img;
        QString name = QString("test") + QString::fromStdString(std::to_string(i)) + QString(".jpg");
        qDebug() << img->save(name);
        qDebug() << pix->size();
        delete pix;
        scale += 0.05;
    }
    //    pix = new QPixmap(*pix);
    //    pix->fill(QColor("white"));
    //    ui->label->setPixmap(*pix);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

