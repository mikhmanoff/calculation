#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <iostream>

#include "qcustomplot.h"

class MainWindow;

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);

    MainWindow *mainW;

    void setGraphPixmap(const QPixmap &pixmap);
    void drawAxis(QPainter &paint);

    double x, y;
    void drawGraph(std::string strS = NULL);  // функция, отвечающая за отрисовку графика
    void recountPixels();  // в зависимости от точности (об этом позже) считаем
        // количество пикселей на один условный сантиметр
    void getData(double &minV, double &maxV);  // получаем значения границ графика и точности

private:
    QLabel *drawingField;

    double xMin, xMax;
    double yMin, yMax;

    int pictWidth, pictHeight;  // ширина и высота картинки
    double step;                // шаг (точность)
    double onePixelX, onePixelY;  // количество пикселей на шаг
    double Ox, Oy;
};

#endif // GRAPHWINDOW_H
