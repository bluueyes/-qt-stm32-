/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboPort;
    QLabel *label_2;
    QComboBox *comboSerial;
    QPushButton *btnConnect;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QSpinBox *spinFanSpeed;
    QPushButton *btnSetFan;
    QSpacerItem *verticalSpacer;
    QPushButton *btnSave;
    QWidget *splite;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTemp;
    QChartView *widgetChartContainer;
    QLabel *labelHum;
    QChartView *widgetChartContainer_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(887, 603);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(100, 80));
        widget->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setContentsMargins(0, -1, 3, -1);
        label = new QLabel(widget_3);
        label->setObjectName("label");
        label->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboPort = new QComboBox(widget_3);
        comboPort->addItem(QString());
        comboPort->addItem(QString());
        comboPort->setObjectName("comboPort");
        comboPort->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(comboPort, 0, 1, 1, 1);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboSerial = new QComboBox(widget_3);
        comboSerial->addItem(QString());
        comboSerial->addItem(QString());
        comboSerial->addItem(QString());
        comboSerial->addItem(QString());
        comboSerial->addItem(QString());
        comboSerial->setObjectName("comboSerial");

        gridLayout->addWidget(comboSerial, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName("btnConnect");

        verticalLayout->addWidget(btnConnect);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 5);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        spinFanSpeed = new QSpinBox(widget_4);
        spinFanSpeed->setObjectName("spinFanSpeed");

        gridLayout_2->addWidget(spinFanSpeed, 0, 1, 1, 1);


        verticalLayout->addWidget(widget_4);

        btnSetFan = new QPushButton(widget);
        btnSetFan->setObjectName("btnSetFan");

        verticalLayout->addWidget(btnSetFan);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnSave = new QPushButton(widget);
        btnSave->setObjectName("btnSave");

        verticalLayout->addWidget(btnSave);


        horizontalLayout->addWidget(widget);

        splite = new QWidget(centralwidget);
        splite->setObjectName("splite");
        splite->setMaximumSize(QSize(2, 16777215));

        horizontalLayout->addWidget(splite);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        labelTemp = new QLabel(widget_2);
        labelTemp->setObjectName("labelTemp");
        labelTemp->setMaximumSize(QSize(60, 25));

        verticalLayout_2->addWidget(labelTemp);

        widgetChartContainer = new QChartView(widget_2);
        widgetChartContainer->setObjectName("widgetChartContainer");

        verticalLayout_2->addWidget(widgetChartContainer);

        labelHum = new QLabel(widget_2);
        labelHum->setObjectName("labelHum");
        labelHum->setMinimumSize(QSize(30, 0));
        labelHum->setMaximumSize(QSize(60, 25));

        verticalLayout_2->addWidget(labelHum);

        widgetChartContainer_2 = new QChartView(widget_2);
        widgetChartContainer_2->setObjectName("widgetChartContainer_2");

        verticalLayout_2->addWidget(widgetChartContainer_2);


        horizontalLayout->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\220\215\357\274\232", nullptr));
        comboPort->setItemText(0, QCoreApplication::translate("MainWindow", "COM3", nullptr));
        comboPort->setItemText(1, QCoreApplication::translate("MainWindow", "COM4", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        comboSerial->setItemText(0, QCoreApplication::translate("MainWindow", "4800", nullptr));
        comboSerial->setItemText(1, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboSerial->setItemText(2, QCoreApplication::translate("MainWindow", "14400", nullptr));
        comboSerial->setItemText(3, QCoreApplication::translate("MainWindow", "19200", nullptr));
        comboSerial->setItemText(4, QCoreApplication::translate("MainWindow", "38400", nullptr));

        btnConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\351\243\216\346\211\207\350\275\254\351\200\237:", nullptr));
        btnSetFan->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\225\260\346\215\256", nullptr));
        labelTemp->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246", nullptr));
        labelHum->setText(QCoreApplication::translate("MainWindow", "\346\271\277\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
