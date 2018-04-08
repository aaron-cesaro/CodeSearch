#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>

#include "registerForm.h"
#include "mainWindow.h"

registerForm::registerForm(QWidget *parent, bool user) : QDialog(parent), isUser(user) {

    setGeometry(550,200,400,400);
    setStyleSheet("background-color: #f7f8f8;");

    titleImage = new QLabel(this);
    QPixmap image(":/register.png");
    titleImage->setPixmap(image);

    QHBoxLayout *regImageLayout = new QHBoxLayout;
    regImageLayout->addSpacing(73);
    regImageLayout->addWidget(titleImage);

    regUserName = new QLabel(tr("Select a Name"));
    regUserNameText = new QLineEdit;

    regPsw = new QLabel(tr("Select a Password"));
    regPswText = new QLineEdit;
    regPswText->setEchoMode(QLineEdit::Password);

    regEmail = new QLabel(tr("Type your Email"));
    regEmailText = new QLineEdit;

    regButton = new QPushButton(tr("Register"));
    regCancel = new QPushButton(tr("Cancel"));

    QHBoxLayout *regBottomLayout = new QHBoxLayout;
    regBottomLayout->addWidget(regButton);
    regBottomLayout->addStretch();
    regBottomLayout->addWidget(regCancel);

    QVBoxLayout *registerLayout = new QVBoxLayout;
    registerLayout->addLayout(regImageLayout);
    registerLayout->addSpacing(20);
    registerLayout->addWidget(regUserName);
    registerLayout->addWidget(regUserNameText);
    registerLayout->addWidget(regPsw);
    registerLayout->addWidget(regPswText);
    registerLayout->addWidget(regEmail);
    registerLayout->addWidget(regEmailText);
    registerLayout->addSpacing(20);
    registerLayout->addLayout(regBottomLayout);

    setLayout(registerLayout);

    connect(regCancel, SIGNAL(clicked()), this, SLOT(on_cancel()));
    connect(regButton, SIGNAL(clicked()), this, SLOT(on_register()));

}

void registerForm::on_cancel() {
    close();
}

void registerForm::on_register() {
    if(checkMail(regEmailText->text()) && !regUserNameText->text().isEmpty() && !regPswText->text().isEmpty()) {
        saveXml *saveUser = new saveXml();
        saveUser->saveUserInfo(regUserNameText->text(), regPswText->text(), regEmailText->text(), "0", "FreeUser", true);
        hide();
        if (isUser) {
            mainWindow *window = new mainWindow(regUserNameText->text());
            window->show();
        }
        else {
            userInfoContainer.push_back(regUserNameText->text().toStdString());
            userInfoContainer.push_back(regPswText->text().toStdString());
            userInfoContainer.push_back(regEmailText->text().toStdString());
        }
        delete saveUser;
    }
    else {
        QMessageBox::warning(0, "Error!", "Please type a valid email address");

    }
}

QPushButton *registerForm::getRegButton() const {
    return regButton;
}

bool registerForm::checkMail(const QString &email) const {
    QRegExp regEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    regEx.setCaseSensitivity(Qt::CaseInsensitive);
    regEx.setPatternSyntax(QRegExp::RegExp);
    return regEx.exactMatch(email);
}

QVector<std::string> registerForm::getUserInfo() const {
    return userInfoContainer;
}
