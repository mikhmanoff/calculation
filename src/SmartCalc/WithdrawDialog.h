#ifndef WITHDRAWDIALOG_H
#define WITHDRAWDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QTableWidget>

// class QTableWidget; // Предварительное объявление, чтобы избежать циклических
//  зависимостей

class WithdrawDialog : public QDialog {
    Q_OBJECT

  public:
    explicit WithdrawDialog(QWidget* parent = nullptr);

      //sss
      struct WithdrawData {
          int termIndex;
          double moneyValue;
      };

      QList<WithdrawData> getWithdrawData() const;
      //sss

    QString getPeriod() const;
    double getAmount() const;
    int getRowCount() const;

  private slots:
    void addRowDecrease();
    void removeRowDecrease();

  private:
    QComboBox* periodComboBox;
    QDoubleSpinBox* amountSpinBox;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* closeButton;
    QTableWidget* twAdd; // Указатель на таблицу, куда добавлять строки

    QString currentPeriod;
    double currentAmount;

    // Другие члены класса, если необходимо
};

#endif // WITHDRAWDIALOG_H
