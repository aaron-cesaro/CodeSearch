#include <QStyleOption>
#include <QPainter>
#include "userListFunction.h"
#include <QDebug>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QCloseEvent>

/*--------------Public--------------*/

userListFunction::userListFunction(QWidget *parent) : QWidget(parent) {
    setVisible(true);
    setStyleSheet("background-color: #f7f8f8; border: 1px solid silver; ");

    listOfUsers = new userList(50,5,this);
    listOfUsers->setGeometry(1,0,1004,625);
}

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void userListFunction::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}