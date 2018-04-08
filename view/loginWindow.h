#ifndef CODESEARCH_LOGINWINDOW_H
#define CODESEARCH_LOGINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include "registerForm.h"
#include "adminFunction.h"

class loginWindow: public QDialog {

    Q_OBJECT

public:
    loginWindow(QWidget * = nullptr);
    void paintEvent(QPaintEvent *) override;
    bool checkUserName(const QString &);
    bool checkPassword(const QString &, const QString &);

public slots:
    void on_logIn();
    void on_register();
    void on_admin();

private:
    QLabel *userNameLabel;
    QLabel *passwordLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *loginImage;
    QPushButton *logInButton;
    QString filePath;
    QPushButton *signInButton;
    registerForm *signIn;
    QPushButton *adminButton;
    adminFunction *adminWindow;

};


#endif //CODESEARCH_LOGINWINDOW_H
