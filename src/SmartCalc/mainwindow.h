#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WithdrawDialog.h"
#include "qtablewidget.h"
#include "qcustomplot.h"

#include "ReplenishmentDialog.h"
#include "graphwindow.h"
#include <QDate>
#include <QMainWindow>

#include <QVector>
#include <QWidget>
#include <QtGui>

#ifdef __cplusplus
extern "C" {
#endif
#include "core/calc_core.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


//    QFrame* output;

    WithdrawDialog* withdrawDialog;
    ReplenishmentDialog *replenishmentDialog;

    void allocMemory();

  private:
    Ui::MainWindow* ui;

    //    QTableWidget *twAdd;

  private slots:
    void buttonClicked();
    void dotClicked();

    void digitNumbers();

    void baseOperations();
    void bracketOperations();

    //    void handleEqualShortcut();

    void logClicked();
    void xClicked();

    void deleteOneCharacter();
    void clearLine();
    void on_pushButton_equals_clicked();
    void on_pushButtonCalculateCredit_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButtonCalculateDeposit_clicked();
    void on_pushButton_minusDepo_clicked();
    void on_pushButton_plusDepo_clicked();
};

#endif // MAINWINDOW_H
