#include "graphwindow.h"
#include "mainwindow.h"

GraphWindow::GraphWindow(QWidget *parent) : QMainWindow(parent)
{
    drawingField = new QLabel(this);
    setCentralWidget(drawingField);

    // Здесь можете настроить стиль окна, заголовок и т.д.

    // Если хотите сразу задать изображение, вызовите функцию setGraphPixmap
}

void GraphWindow::setGraphPixmap(const QPixmap &pixmap)
{
    drawingField->setPixmap(pixmap);
}

void GraphWindow::getData(double &minV, double &maxV) {
    xMin = minV;
    xMax = maxV;
    yMin = xMin;
    yMax = xMax;

    if (xMin >= xMax) {
        xMin = -10;
        xMax = 10;
        minV = -10;
        maxV = 10;
    }
    yMin = xMin;
    yMax = xMax;

    qDebug() << "xMin:" << xMin << " xMax:" << xMax << " yMin:" << yMin << " yMax:" << yMax;

}

void GraphWindow::recountPixels() {
    onePixelX = 640.0 / (xMax - xMin);
    onePixelY = 640.0 / (yMin - yMax);
    Ox = fabs(xMin);
    Oy = yMax;
}

void GraphWindow::drawGraph(std::string strS) {
    pictHeight = 640;
    pictWidth = 640;
    QPixmap graph(640, 640);
    QPainter paint;
    QPainterPath path;
    paint.begin(&graph);
    paint.eraseRect(0, 0, 640, 640);
    drawAxis(paint); // Рисование осей и сетки
//    qDebug() << strS << " s";
    paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));

    double step = (xMax - xMin) * 0.001;
    char *ptr = &strS[0];

    for (double tmp = xMin; tmp <= xMax; tmp += step) {
        Node *polish = parseInput(ptr);
        polish = s21_infixToPolsih(polish, tmp);
        y = s21_calculation(polish);

        // Преобразование координат и отрисовка точки
        double xPixel = (tmp - xMin) * onePixelX + Ox; // Учтите смещение Ox
        double yPixel = (y - yMax) * onePixelY + Oy; // Учтите смещение Oy
        paint.drawPoint(xPixel, yPixel);

        qDebug() << /*tmp << " " << y << */ xPixel << " " << yPixel;
        paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
        //        paint.drawPath(path);
    }
    paint.end();

    setGraphPixmap(graph);
    show();
}


void GraphWindow::drawAxis(QPainter &paint) {
    paint.setPen(QColor(0,0,255));

    paint.drawLine(pictWidth / 2, 0, pictWidth / 2, 1000);
    paint.drawLine(0, pictHeight / 2, 1000, pictHeight / 2);

    int step = 20;
//    step = 20;

    paint.setPen(QColor(0, 0, 0, 100));

    double x = xMin;
    double x_step = fabs(xMin - xMax) / 32.;

    for (int i = 0; i < pictWidth; i += step, x += x_step) {
        if (!(i % 80) && i != 0) {
            paint.setPen(QColor(0, 0, 0, 255));
            paint.drawLine(i, 0, i, 1000);
            paint.drawText(i, pictHeight, QString::number(x, 'g', 3));
        } else {
            paint.setPen(QColor(0, 0, 0, 100));
            paint.drawLine(i, 0, i, 1000);
        }
    }

    step = 20;
    double y = yMin;
    double y_step = fabs(yMin - yMax) / 32.;

    for (int i = 0; i < pictHeight; i += step, y += y_step) {
        if (!(i % 80) && i != 0) {
            paint.setPen(QColor(0, 0, 0, 255));
            paint.drawLine(0, i, 1000, i);
            if (i == pictHeight / 2)
                paint.drawText(0, pictHeight - i, "0");
            else
                paint.drawText(0, pictHeight - i, QString::number(y, 'g', 3));
        } else {
            paint.setPen(QColor(0, 0, 0, 100));
            paint.drawLine(0, i, 1000, i);
        }
    }
}

