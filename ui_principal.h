/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graph.h"

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QWidget *centralWidget;
    QLabel *readByteLabel;
    Graph *openGLWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *startPushButton;
    QPushButton *stopPushButton;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *sendLineEdit;
    QPushButton *sendPushButton;
    QMenuBar *menuBar;
    QMenu *menu_Puerto;

    void setupUi(QMainWindow *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QStringLiteral("Principal"));
        Principal->resize(468, 451);
        centralWidget = new QWidget(Principal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        readByteLabel = new QLabel(centralWidget);
        readByteLabel->setObjectName(QStringLiteral("readByteLabel"));
        readByteLabel->setGeometry(QRect(300, 20, 151, 31));
        readByteLabel->setTextFormat(Qt::PlainText);
        readByteLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        readByteLabel->setWordWrap(true);
        openGLWidget = new Graph(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 80, 451, 331));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 261, 77));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout_2->setContentsMargins(10, 10, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        startPushButton = new QPushButton(widget);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));

        verticalLayout->addWidget(startPushButton);

        stopPushButton = new QPushButton(widget);
        stopPushButton->setObjectName(QStringLiteral("stopPushButton"));

        verticalLayout->addWidget(stopPushButton);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        sendLineEdit = new QLineEdit(widget);
        sendLineEdit->setObjectName(QStringLiteral("sendLineEdit"));

        verticalLayout_2->addWidget(sendLineEdit);

        sendPushButton = new QPushButton(widget);
        sendPushButton->setObjectName(QStringLiteral("sendPushButton"));

        verticalLayout_2->addWidget(sendPushButton);


        horizontalLayout_2->addLayout(verticalLayout_2);

        Principal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Principal);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 468, 26));
        menu_Puerto = new QMenu(menuBar);
        menu_Puerto->setObjectName(QStringLiteral("menu_Puerto"));
        Principal->setMenuBar(menuBar);

        menuBar->addAction(menu_Puerto->menuAction());

        retranslateUi(Principal);

        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QMainWindow *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Principal", Q_NULLPTR));
        readByteLabel->setText(QApplication::translate("Principal", "Puerto Cerrado", Q_NULLPTR));
        startPushButton->setText(QApplication::translate("Principal", "&Comenzar", Q_NULLPTR));
        stopPushButton->setText(QApplication::translate("Principal", "&Parar", Q_NULLPTR));
        sendPushButton->setText(QApplication::translate("Principal", "&Enviar", Q_NULLPTR));
        menu_Puerto->setTitle(QApplication::translate("Principal", "&Puerto", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
