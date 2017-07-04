/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QWidget *centralWidget;
    QPushButton *startPushButton;
    QLabel *readByteLabel;
    QPushButton *stopPushButton;
    QMenuBar *menuBar;
    QMenu *menu_Puerto;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QStringLiteral("Principal"));
        Principal->resize(400, 300);
        centralWidget = new QWidget(Principal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        startPushButton = new QPushButton(centralWidget);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));
        startPushButton->setGeometry(QRect(60, 110, 75, 23));
        readByteLabel = new QLabel(centralWidget);
        readByteLabel->setObjectName(QStringLiteral("readByteLabel"));
        readByteLabel->setGeometry(QRect(260, 110, 91, 31));
        stopPushButton = new QPushButton(centralWidget);
        stopPushButton->setObjectName(QStringLiteral("stopPushButton"));
        stopPushButton->setGeometry(QRect(60, 150, 75, 23));
        Principal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Principal);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menu_Puerto = new QMenu(menuBar);
        menu_Puerto->setObjectName(QStringLiteral("menu_Puerto"));
        Principal->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Principal);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Principal->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Principal);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Principal->setStatusBar(statusBar);

        menuBar->addAction(menu_Puerto->menuAction());

        retranslateUi(Principal);

        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QMainWindow *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Principal", Q_NULLPTR));
        startPushButton->setText(QApplication::translate("Principal", "&Comenzar", Q_NULLPTR));
        readByteLabel->setText(QApplication::translate("Principal", "Puerto Cerrado", Q_NULLPTR));
        stopPushButton->setText(QApplication::translate("Principal", "&Parar", Q_NULLPTR));
        menu_Puerto->setTitle(QApplication::translate("Principal", "&Puerto", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
