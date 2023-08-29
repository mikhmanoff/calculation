#include "mainwindow.h"

#include "ui_mainwindow.h"
//#include "qcustomplot.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    allocMemory();

    // Инициализация twAdd
    //    twAdd = ui->twAdd; // Если вы назвали QTableWidget в Qt Designer twAdd

    ui->plainTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    output = new QFrame(this);
//    output->setFixedSize(400, 400);
//    output->hide();
//    output->setLayout(ui->plainTextEdit);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitNumbers()));

    connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
            SLOT(baseOperations()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_power, SIGNAL(clicked()), this,
            SLOT(baseOperations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this,
            SLOT(baseOperations()));

    connect(ui->pushButton_sin, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this,
            SLOT(bracketOperations()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dotClicked()));
    connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(xClicked()));

    connect(ui->pushButton_del, SIGNAL(clicked()), this,
            SLOT(deleteOneCharacter()));
    connect(ui->pushButton_clear_all, SIGNAL(clicked()), this,
            SLOT(clearLine()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::buttonClicked() {
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->plainTextEdit->setTextCursor(cursor);
    ui->plainTextEdit->ensureCursorVisible();
}

void MainWindow::dotClicked() {
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + ".");

    buttonClicked();
}

void MainWindow::digitNumbers() {
    ui->plainTextEdit->canPaste();

    QPushButton* button = (QPushButton*)sender();
    QString text =
        ui->plainTextEdit->toPlainText(); // get text from input field
    QString number = button->text();
    QString result = text + number;
    ui->plainTextEdit->setPlainText(result);

    buttonClicked();
}

void MainWindow::baseOperations() {
    QPushButton* button = (QPushButton*)sender();

    QString text = ui->plainTextEdit->toPlainText();
    QString operation = button->text();
    QString result = text + operation;
    ui->plainTextEdit->setPlainText(result);

    buttonClicked();
}

void MainWindow::bracketOperations() {
    QPushButton* button = (QPushButton*)sender();

    QString text = ui->plainTextEdit->toPlainText();
    QString operation = button->text();
    QString result = text + operation + "(";
    ui->plainTextEdit->setPlainText(result);

    buttonClicked();
}

void MainWindow::logClicked() {
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "log(");

    buttonClicked();
}

void MainWindow::xClicked() {
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "x");

    buttonClicked();
}

void MainWindow::deleteOneCharacter() {
    QString s = ui->plainTextEdit->toPlainText();
    if (s.length() > 0) {
        QString newtext = s.remove(s.length() - 1, 1);
        ui->plainTextEdit->setPlainText(
            newtext); // Обновляем текст в plainTextEdit
    }
}

void MainWindow::clearLine() { ui->plainTextEdit->setPlainText(""); }

// void MainWindow::handleEqualShortcut() {
//     // QPushButton *button = (QPushButton *)sender();

//    on_pushButton_equals_clicked();
//}

void MainWindow::on_pushButton_equals_clicked() {
    QString expressionText =
        ui->plainTextEdit->toPlainText(); // Получение текста из plainTextEdit
    std::string expressionStr =
        expressionText.toStdString(); // Преобразование в std::string
    const char* expressionPtr =
        expressionStr.c_str(); // Получение указателя на c-style строку
    int error = checkInputString(expressionPtr); // Проверка ввода

    if (error == 0) {
        QString str_x =
            ui->plainTextEdit
                ->toPlainText(); // Получение текста из plainTextEdit_x
        double x = str_x.toDouble(); // Преобразование в число

        Node* polish = NULL;
        polish = parseInput(expressionPtr);
        polish = s21_infixToPolsih(polish, x);
        double result = s21_calculation(polish);

        QString resultStr = QString::number(
            result, 'f', 7); // Преобразование результата в строку
        ui->plainTextEdit->setPlainText(
            resultStr); // Вывод результата в plainTextEdit
    } else {
        ui->plainTextEdit->setPlainText(
            "ERROR!"); // Вывод сообщения об ошибке в plainTextEdit
    }
}

void MainWindow::on_pushButtonCalculateCredit_clicked() {
    double creditSum = ui->doubleSpinBox_creditSum->value();
    double interestRate = ui->doubleSpinBox_interestRate->value();
    int creditTime = ui->spinBox_creditTime->value();

    int monthOrYear = ui->comboBox_yearOrmonth->currentIndex();

    if (monthOrYear == 1) {
        creditTime *= 12;
    }

    int differOrAnnuit = ui->comboBox_paymentType->currentIndex();

    if (differOrAnnuit == 0) {
        double monthPayment =
            qRound(monthAnnuity(creditSum, creditTime, interestRate) * 100.0) /
            100.0;
        double totalPayment = qRound(monthPayment * creditTime * 100.0) / 100.0;
        double overPayment = qRound((totalPayment - creditSum) * 100.0) / 100.0;

        ui->lineEditMonthlyPayout->setText(
            QString("%L1").arg(monthPayment, 0, 'f', 2));
        ui->lineEditTotalPayment->setText(
            QString("%L1").arg(totalPayment, 0, 'f', 2));
        ui->lineEditOverPayment->setText(
            QString("%L1").arg(overPayment, 0, 'f', 2));
    } else {
        QDate date_current = QDate::currentDate().addMonths(creditTime);
        //        date_current.addMonths(creditTime);

        double Sn = creditSum / creditTime;
        double payment = Sn + creditSum * interestRate / 100 *
                                  (date_current.daysInYear() / 12.0) /
                                  date_current.daysInYear();
        double first = payment;
        double total = payment;
        for (int i = 1; i < creditTime; i++) {
            payment = Sn + (creditSum - i * Sn) * interestRate / 100 *
                               (date_current.daysInYear() / 12.0) /
                               date_current.daysInYear();
            total += payment;
            date_current = date_current.addMonths(1);
        }

        double last = payment;
        ui->lineEditMonthlyPayout->setText(
            QString("%L1").arg(first, 0, 'f', 2) + " ... " +
            QString("%L1").arg(last, 0, 'f', 2));
        ui->lineEditOverPayment->setText(
            QString("%L1").arg(total - creditSum, 0, 'f', 2));
        ui->lineEditTotalPayment->setText(QString("%L1").arg(total, 0, 'f', 2));
    }
}

//graph
void MainWindow::on_pushButton_graph_clicked() {
    GraphWindow *graphWindow = new GraphWindow();
    graphWindow->mainW = this;
    QPixmap graph(640, 640);

    double minValue = ui->doubleSpinBox_xMin->value();
    double maxValue = ui->doubleSpinBox_xMax->value();

    graphWindow->getData(minValue, maxValue);
    ui->doubleSpinBox_xMin->setValue(minValue);
    ui->doubleSpinBox_xMax->setValue(maxValue);
    graphWindow->recountPixels();
    graphWindow->drawGraph(ui->plainTextEdit->toPlainText().toStdString());

    graphWindow->show();
}

void MainWindow::on_pushButtonCalculateDeposit_clicked() {
    Deposit dp;

//    ReplenishmentDialog replenishmentDialog(this);
    int rowCountrep = replenishmentDialog->getRowCount();
    int remCountrep = withdrawDialog->getRowCount();
    QList<ReplenishmentDialog::ReplenishmentData> replenishmentData = replenishmentDialog->getReplenishmentData();
    QList<WithdrawDialog::WithdrawData> withdrawData = withdrawDialog->getWithdrawData();

    dp.depositAmount = ui->doubleSpinBox_depositTotal->value();
    dp.periodOfPlacement = ui->spinBox_depositPeriod->value();
    dp.interestRate = ui->doubleSpinBox_depositRate->value();
    dp.taxRate = ui->doubleSpinBox_interestRate_depo->value();
    dp.paymentsType = ui->comboBox_frequency->currentIndex();
    dp.interestCapitalization = ui->checkBox_capital->isChecked() ? 1 : 0;
    dp.currentMoth = ui->spinBox_startMonth->value();
    dp.currentYear = ui->spinBox_startYear->value();
    dp.currentDay = ui->spinBox_startDay->value();

    dp.addCount = rowCountrep;
    for (int i = 0; i < replenishmentData.size(); i++) {
        dp.replenishmentList[i].term = replenishmentData[i].termIndex;
        dp.replenishmentList[i].money = replenishmentData[i].moneyValue;

        qDebug() << replenishmentData[i].termIndex << " " << replenishmentData[i].moneyValue << " пополнение";
    }

    dp.remCount = remCountrep;
    for (int i = 0; i < withdrawData.size(); i++) {
        dp.listPartialWithdrawals[i].term = withdrawData[i].termIndex;
        dp.listPartialWithdrawals[i].money = withdrawData[i].moneyValue;

        qDebug() << withdrawData[i].termIndex << " " << withdrawData[i].moneyValue << " снятие";
    }

    depositCalcCore(&dp);

    ui->lineEditDepoPercent->setText(QString::number(dp.sumInterest, 'f', 2));
    ui->lineEditDepoAll->setText(QString::number(dp.sumEndTerm, 'f', 2));
    ui->lineEditDepoTax->setText(QString::number(dp.sumTax, 'f', 2));
}

void MainWindow::on_pushButton_minusDepo_clicked() {
    withdrawDialog->show();
}

void MainWindow::on_pushButton_plusDepo_clicked()
{
    replenishmentDialog->show();
}

void MainWindow::allocMemory() {
    replenishmentDialog = new ReplenishmentDialog(this);
    withdrawDialog = new WithdrawDialog(this);
    replenishmentDialog->hide();
    withdrawDialog->hide();
}
