#ifndef REPLENISHMENTDIALOG_H
#define REPLENISHMENTDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QTableWidget>

class ReplenishmentDialog : public QDialog {
    Q_OBJECT

public:
    explicit ReplenishmentDialog(QWidget* parent = nullptr);

//sss
    struct ReplenishmentData {
        int termIndex;
        double moneyValue;
    };

    QList<ReplenishmentData> getReplenishmentData() const;
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

#endif // REPLENISHMENTDIALOG_H
