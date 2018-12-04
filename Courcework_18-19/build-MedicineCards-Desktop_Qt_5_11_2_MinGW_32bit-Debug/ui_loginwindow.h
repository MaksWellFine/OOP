/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralWidget;
    QPushButton *buttonLogin;
    QLabel *labelLogin;
    QLabel *labelPassword;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->setWindowModality(Qt::NonModal);
        LoginWindow->resize(450, 250);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setMinimumSize(QSize(450, 250));
        LoginWindow->setMaximumSize(QSize(450, 250));
        centralWidget = new QWidget(LoginWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonLogin = new QPushButton(centralWidget);
        buttonLogin->setObjectName(QStringLiteral("buttonLogin"));
        buttonLogin->setGeometry(QRect(250, 180, 181, 51));
        QFont font;
        font.setPointSize(12);
        buttonLogin->setFont(font);
        labelLogin = new QLabel(centralWidget);
        labelLogin->setObjectName(QStringLiteral("labelLogin"));
        labelLogin->setGeometry(QRect(30, 50, 150, 40));
        labelLogin->setFont(font);
        labelLogin->setAlignment(Qt::AlignCenter);
        labelPassword = new QLabel(centralWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setGeometry(QRect(30, 100, 150, 40));
        labelPassword->setFont(font);
        labelPassword->setAlignment(Qt::AlignCenter);
        lineEditLogin = new QLineEdit(centralWidget);
        lineEditLogin->setObjectName(QStringLiteral("lineEditLogin"));
        lineEditLogin->setGeometry(QRect(200, 50, 200, 40));
        lineEditLogin->setFont(font);
        lineEditPassword = new QLineEdit(centralWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(200, 100, 200, 40));
        lineEditPassword->setFont(font);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        LoginWindow->setCentralWidget(centralWidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "\320\222\321\205\321\226\320\264 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        buttonLogin->setText(QApplication::translate("LoginWindow", "\320\243\320\262\321\226\320\271\321\202\320\270", nullptr));
        labelLogin->setText(QApplication::translate("LoginWindow", "\320\233\320\276\320\263\321\226\320\275:", nullptr));
        labelPassword->setText(QApplication::translate("LoginWindow", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
