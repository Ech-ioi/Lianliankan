/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QPushButton *go_game;
    QPushButton *exit;

    void setupUi(QDialog *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QStringLiteral("Home"));
        Home->resize(400, 300);
        go_game = new QPushButton(Home);
        go_game->setObjectName(QStringLiteral("go_game"));
        go_game->setGeometry(QRect(130, 120, 93, 28));
        exit = new QPushButton(Home);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(130, 180, 93, 28));

        retranslateUi(Home);
        QObject::connect(exit, SIGNAL(clicked()), Home, SLOT(close()));

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QDialog *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "Dialog", Q_NULLPTR));
        go_game->setText(QApplication::translate("Home", "\350\277\233\345\205\245\346\270\270\346\210\217", Q_NULLPTR));
        exit->setText(QApplication::translate("Home", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
