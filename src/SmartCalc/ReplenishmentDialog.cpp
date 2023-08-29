#include "ReplenishmentDialog.h"
#include <QDebug>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

ReplenishmentDialog::ReplenishmentDialog(QWidget* parent) : QDialog(parent) {
    setFixedSize(400, 400);
    setWindowTitle("Добавить или удалить пополнение");
    periodComboBox = new QComboBox(this);
    periodComboBox->addItems(QStringList() << "Раз в месяц"
                                           << "Раз в пол года"
                                           << "Раз в год");

    twAdd = new QTableWidget(this);
    twAdd->setColumnCount(2);
    twAdd->setColumnWidth(0, 210);
    twAdd->setColumnWidth(1, 150);
    twAdd->setHorizontalHeaderLabels(QStringList() << "Периодичность снятий"
                                                   << "Сумма");

    amountSpinBox = new QDoubleSpinBox(this);
    amountSpinBox->setRange(0, 100000000);

    currentPeriod = periodComboBox->currentText();
    currentAmount = amountSpinBox->value();

    qDebug() << currentAmount;

    addButton = new QPushButton("Добавить", this);
    removeButton = new QPushButton("Удалить", this);
    closeButton = new QPushButton("Закрыть", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(periodComboBox);
    layout->addWidget(amountSpinBox);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(closeButton);
    layout->addWidget(twAdd);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &ReplenishmentDialog::addRowDecrease);
    connect(removeButton, &QPushButton::clicked, this,
            &ReplenishmentDialog::removeRowDecrease);
    connect(closeButton, &QPushButton::clicked, this, &ReplenishmentDialog::accept);
}

void ReplenishmentDialog::addRowDecrease() {
    QString period = periodComboBox->currentText();
    double amount = amountSpinBox->value();

    int row = twAdd->rowCount();
    if (row < 255) {
        QComboBox* cmb = new QComboBox(twAdd);
        QDoubleSpinBox* dsb = new QDoubleSpinBox(twAdd);
        cmb->addItems(QStringList() << "Раз в месяц"
                                    << "Раз в пол года"
                                    << "Раз в год");

        dsb->setRange(0, 100000000);
        twAdd->insertRow(row);
        twAdd->setCellWidget(row, 0, cmb);
        twAdd->setCellWidget(row, 1, dsb);

        // Записываем текущие значения в соответствующие члены класса
        currentPeriod = period;
        currentAmount = amount;

        cmb->setCurrentText(currentPeriod);
        dsb->setValue(currentAmount);

        qDebug() << "Добавлено: " << currentPeriod << ", " << currentAmount;
    }
    qDebug() << "plusAdd";
}


void ReplenishmentDialog::removeRowDecrease() {
    int row = twAdd->rowCount();
    if (row > 0) {
        twAdd->removeRow(row - 1);
    }
}

QString ReplenishmentDialog::getPeriod() const {
    return periodComboBox->currentText();
}

double ReplenishmentDialog::getAmount() const { return amountSpinBox->value(); }

//для допа
int ReplenishmentDialog::getRowCount() const {
    return twAdd->rowCount();
}

QList<ReplenishmentDialog::ReplenishmentData> ReplenishmentDialog::getReplenishmentData() const {
    QList<ReplenishmentData> data;

    for (int i = 0; i < twAdd->rowCount(); i++) {
        ReplenishmentData item;
        item.termIndex = qobject_cast<QComboBox*>(twAdd->cellWidget(i, 0))->currentIndex();
        item.moneyValue = qobject_cast<QDoubleSpinBox*>(twAdd->cellWidget(i, 1))->value();
        data.append(item);
    }

    return data;
}
