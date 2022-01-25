QT       += core gui
QT       += xml
QT       += charts
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = icon.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barChart.cpp \
    lineChart.cpp \
    chart.cpp \
    controller.cpp \
    data.cpp \
    dataHandler.cpp \
    fileHandler.cpp \
    main.cpp \
    model.cpp \
    pieChart.cpp \
    window.cpp

HEADERS += \
    barChart.h \
    chart.h \
    controller.h \
    data.h \
    dataHandler.h \
    fileHandler.h \
    lineChart.h \
    model.h \
    pieChart.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
