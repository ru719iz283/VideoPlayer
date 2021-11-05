/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *Open_red;
    QAction *Close_Red;
    QWidget *centralwidget;
    QLabel *lb_VideoCodec;
    QLabel *lb_AudioCodec;
    QLabel *lb_GOP;
    QLineEdit *le_Url;
    QPushButton *pb_Connect;
    QLabel *lb_Resolution;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1193, 303);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setStyleSheet(QLatin1String("QLabel{\n"
"font:16px;\n"
"}\n"
"QPushButton {\n"
"border:none;\n"
"border-radius:4px;\n"
"background:#00B49C;\n"
"color:#EEEEEE;\n"
"font:16px;\n"
"}\n"
"QPushButton::pressed {\n"
"background:#55CBBC;\n"
"}\n"
"QPushButton::!enabled {\n"
"background:#AAAAAA;\n"
"}"));
        MainWindow->setIconSize(QSize(24, 24));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        Open_red = new QAction(MainWindow);
        Open_red->setObjectName(QStringLiteral("Open_red"));
        Close_Red = new QAction(MainWindow);
        Close_Red->setObjectName(QStringLiteral("Close_Red"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lb_VideoCodec = new QLabel(centralwidget);
        lb_VideoCodec->setObjectName(QStringLiteral("lb_VideoCodec"));
        lb_VideoCodec->setGeometry(QRect(20, 40, 150, 30));
        lb_AudioCodec = new QLabel(centralwidget);
        lb_AudioCodec->setObjectName(QStringLiteral("lb_AudioCodec"));
        lb_AudioCodec->setGeometry(QRect(190, 40, 150, 30));
        lb_GOP = new QLabel(centralwidget);
        lb_GOP->setObjectName(QStringLiteral("lb_GOP"));
        lb_GOP->setGeometry(QRect(370, 40, 150, 30));
        le_Url = new QLineEdit(centralwidget);
        le_Url->setObjectName(QStringLiteral("le_Url"));
        le_Url->setGeometry(QRect(20, 10, 460, 30));
        pb_Connect = new QPushButton(centralwidget);
        pb_Connect->setObjectName(QStringLiteral("pb_Connect"));
        pb_Connect->setGeometry(QRect(490, 10, 100, 30));
        lb_Resolution = new QLabel(centralwidget);
        lb_Resolution->setObjectName(QStringLiteral("lb_Resolution"));
        lb_Resolution->setGeometry(QRect(540, 40, 150, 30));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        Open_red->setText(QApplication::translate("MainWindow", "Open(&O)", 0));
        Close_Red->setText(QApplication::translate("MainWindow", "Close(&C)", 0));
        lb_VideoCodec->setText(QString());
        lb_AudioCodec->setText(QString());
        lb_GOP->setText(QString());
        le_Url->setText(QApplication::translate("MainWindow", "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov", 0));
        pb_Connect->setText(QApplication::translate("MainWindow", "Connect", 0));
        lb_Resolution->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
