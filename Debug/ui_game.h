/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QPushButton *go_home;
    QPushButton *exit;
    QPushButton *showLowGame;

    void setupUi(QWidget *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName(QStringLiteral("game"));
        game->resize(400, 300);
        go_home = new QPushButton(game);
        go_home->setObjectName(QStringLiteral("go_home"));
        go_home->setGeometry(QRect(20, 110, 93, 28));
        exit = new QPushButton(game);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(20, 170, 93, 28));
        showLowGame = new QPushButton(game);
        showLowGame->setObjectName(QStringLiteral("showLowGame"));
        showLowGame->setGeometry(QRect(20, 60, 93, 28));

        retranslateUi(game);
        QObject::connect(exit, SIGNAL(clicked()), game, SLOT(close()));

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QWidget *game)
    {
        game->setWindowTitle(QApplication::translate("game", "Form", Q_NULLPTR));
        go_home->setText(QApplication::translate("game", "\350\277\224\345\233\236\344\270\273\351\241\265\351\235\242", Q_NULLPTR));
        exit->setText(QApplication::translate("game", "\351\200\200\345\207\272", Q_NULLPTR));
        showLowGame->setText(QApplication::translate("game", "lowgame", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
