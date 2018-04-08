#ifndef CODESEARCH_REGISTERFORM_H
#define CODESEARCH_REGISTERFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "saveXml.h"
#include "loadXml.h"

class registerForm : public QDialog {

    Q_OBJECT

public:
    registerForm(QWidget * = nullptr, bool = true);
    QPushButton *getRegButton() const;
    QVector<std::string> getUserInfo() const;

public slots:
    void on_cancel();
    void on_register();

private:
    QLabel *titleImage;
    QLabel *regUserName;
    QLineEdit *regUserNameText;
    QLabel *regPsw;
    QLineEdit *regPswText;
    QLabel *regEmail;
    QLineEdit *regEmailText;
    QPushButton *regButton;
    QPushButton *regCancel;
    QVector<std::string> userInfoContainer;
    bool isUser;
    bool checkMail(const QString &) const;
};


#endif //CODESEARCH_REGISTERFORM_H
