QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
#QMAKE_CXXFLAGS += -Wa,-mbig-obj

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ReplenishmentDialog.cpp \
    WithdrawDialog.cpp \
    backend/credit.c \
    backend/deposit.c \
    backend/s21_calc_base.c \
    backend/s21_calc_input_check.c \
    backend/s21_calc_others.c \
    backend/s21_calc_preprocess.c \
    core/s21_calc_infix_to_polish.c \
    core/s21_calculate.c \
    graphwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ReplenishmentDialog.h \
    WithdrawDialog.h \
    backend/calc_support.h \
    core/calc_core.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
