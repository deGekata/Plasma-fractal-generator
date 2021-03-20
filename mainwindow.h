#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <cstdlib>
#include <qstring.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct my_struct {
        double hue;
        double sat;
        double lig;
        my_struct(double h = 0, double s = 0, double l = 0){
            hue = h;
            sat = s;
            lig = l;
        }
    };
    MainWindow(QWidget *parent = nullptr);
    void Process(int x1, int y1, int x2, int y2);
    ~MainWindow();

    QVector<QVector<my_struct>> mas;
    const QSize gsize = QSize(1025, 1025);
private:

    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
