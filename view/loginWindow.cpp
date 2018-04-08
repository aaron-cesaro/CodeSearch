#include "loginWindow.h"
#include "mainWindow.h"
#include <QPainter>
#include <QMessageBox>

loginWindow::loginWindow(QWidget *parent) : QDialog(parent) {
    setGeometry(550,250,450,300);
    setStyleSheet("background-color:#f7f8f8;");

    loginImage = new QLabel(this);
    QPixmap image(":/CodeSearch.png");
    loginImage->setPixmap(image);
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addSpacing(60);
    imageLayout->addWidget(loginImage);

    userNameLabel = new QLabel(tr("User Name"));
    userNameLineEdit = new QLineEdit(this);

    passwordLabel = new QLabel(tr("Password"));
    passwordLineEdit = new QLineEdit(passwordLabel);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    signInButton = new QPushButton(tr("Register"));

    logInButton = new QPushButton("Login");
    logInButton->setGeometry(0,0,50,20);
    logInButton->setDefault(true);

    adminButton = new QPushButton(tr("admin"));

    QHBoxLayout *loginBottomLayout = new QHBoxLayout;
    loginBottomLayout->addWidget(signInButton);
    loginBottomLayout->addSpacing(50);
    loginBottomLayout->addWidget(adminButton);
    loginBottomLayout->addSpacing(50);
    loginBottomLayout->addWidget(logInButton);

    QVBoxLayout *loginLayout = new QVBoxLayout;
    loginLayout->addLayout(imageLayout);
    loginLayout->addWidget(userNameLabel);
    loginLayout->addWidget(userNameLineEdit);
    loginLayout->addWidget(passwordLabel);
    loginLayout->addWidget(passwordLineEdit);
    loginLayout->addSpacing(30);
    loginLayout->addLayout(loginBottomLayout);

    setLayout(loginLayout);

    connect(logInButton, SIGNAL(clicked()), this, SLOT(on_logIn()));
    connect(signInButton, SIGNAL(clicked()), this, SLOT(on_register()));
    connect(adminButton, SIGNAL(clicked()), this, SLOT(on_admin()));

    show();
}

bool loginWindow::checkUserName(const QString &user) {
    filePath = ("savedData/usersData/" + user + ".xml");
    QFile *file = new QFile(filePath);

    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, "Error!", "User doesn't exists");
        return false;
    }
    else
        return true;
}

bool loginWindow::checkPassword(const QString &psw, const QString &user) {
    loadXml *loadPsw = new loadXml();
    loadPsw->loadAccountInfo(user.toStdString());

    if(loadPsw->passwordStore == psw) {
        return true;
    }
    else {
        QMessageBox::warning(0, "Error!", "Password incorrect");
        return false;
    }
}

//------------------------PUBLIC SLOTS--------------------------------

void loginWindow::on_logIn() {
    if(checkUserName(userNameLineEdit->text()) && checkPassword(passwordLineEdit->text(), userNameLineEdit->text())) {
        hide();
        mainWindow *window = new mainWindow(userNameLineEdit->text());
        window->show();
    }
    else {
        QMessageBox::warning(0, "Login Error!", "Incorrect Username/Password, Try again");
    }
}


void loginWindow::on_register() {
    signIn = new registerForm(nullptr);
    hide();
    signIn->show();
    delete this;
}

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void loginWindow::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void loginWindow::on_admin() {
    if(userNameLineEdit->text() == "admin" && passwordLineEdit->text() == "admin") {
        adminWindow = new adminFunction(userNameLineEdit->text());
        hide();
        adminWindow->show();
        delete this;
    }
    else {
        QMessageBox::warning(0, "Admin Login Error!", "Incorrect administrator credentials, Try again");
    }
}
