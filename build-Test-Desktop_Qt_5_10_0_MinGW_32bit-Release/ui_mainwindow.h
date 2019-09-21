/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *rle;
    QSpacerItem *verticalSpacer_3;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(499, 345);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QFont font1;
        font1.setPointSize(11);
        comboBox->setFont(font1);
        comboBox->setIconSize(QSize(16, 16));

        verticalLayout_2->addWidget(comboBox);

        verticalSpacer_2 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        radioButton->setFont(font2);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(12);
        radioButton_2->setFont(font3);

        verticalLayout->addWidget(radioButton_2);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer);

        rle = new QPushButton(centralWidget);
        rle->setObjectName(QStringLiteral("rle"));
        rle->setFont(font3);

        verticalLayout_4->addWidget(rle);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer_3);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_5->addWidget(progressBar);


        verticalLayout_6->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 499, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Archiver/Encryptors", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        label->setAccessibleName(QApplication::translate("MainWindow", "0", nullptr));
#endif // QT_NO_ACCESSIBILITY
        label->setText(QApplication::translate("MainWindow", "Archivators/Encryptors", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Data Encryption Standard  \321\210\320\270\321\204\321\200\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Rivest Cipher 4  \321\210\320\270\321\204\321\200\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Run-length encoding \320\260\321\200\321\205\321\226\320\262\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274  \320\245\320\260\321\204\321\204\320\274\320\260\320\275\320\260 \320\260\321\200\321\205\321\226\320\262\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));

        groupBox->setTitle(QString());
        radioButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\210\320\270\321\204\321\200\321\203\320\262\320\260\321\202\320\270", nullptr));
        radioButton_2->setText(QApplication::translate("MainWindow", "\320\240\320\276\320\267\321\210\320\270\321\204\321\200\321\203\320\262\320\260\321\202\320\270", nullptr));
        rle->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\270 \321\204\320\260\320\271\320\273", nullptr));
        progressBar->setFormat(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
