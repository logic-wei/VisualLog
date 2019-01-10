#-------------------------------------------------
#
# Project created by QtCreator 2018-12-25T23:18:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualLog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logviewer/logviewer.cpp \
    finder/finder.cpp \
    highlighter/highlighter.cpp \
    logviewer/logviewport.cpp \
    highlighter/logfilter.cpp \
    highlighter/jsonhighlighter.cpp \
    highlighter/jsontextedit.cpp

HEADERS += \
        mainwindow.h \
    logviewer/logviewer.h \
    finder/finder.h \
    highlighter/highlighter.h \
    logviewer/abstractlinefilter.h \
    logviewer/logviewport.h \
    highlighter/logfilter.h \
    highlighter/jsonhighlighter.h \
    highlighter/jsontextedit.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS += icon.ico
