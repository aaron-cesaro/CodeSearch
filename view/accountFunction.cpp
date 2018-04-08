//
// Created by nan on 02/04/17.
//

#include <QPainter>
#include <QStyleOption>
#include <QtWidgets/QHBoxLayout>
#include "accountFunction.h"

//-------------Public---------------

accountFunction::accountFunction(QWidget *parent) : QWidget(parent) {
    setVisible(false);
    setStyleSheet("background-color: #f7f8f8; "
                  "border: 1px solid silver; "
                  "border-radius: 5px");

    //initializing accountFunctionView info
    accountName = new QLabel("Account Name:");
    accountName->setStyleSheet("text-decoration: underline; border: none; ");
    accountNameText = new QLabel();
    accountNameText->setStyleSheet("border: none; "
                                   "padding: 8px; ");

    accountEmail = new QLabel("Account Email:");
    accountEmail->setStyleSheet("text-decoration: underline; "
                                "border: none; ");
    accountEmailText = new QLabel();
    accountEmailText->setStyleSheet("border: none; "
                                    "border-right: none; "
                                    "border-radius: 0px; "
                                    "padding: 8px; ");

    accountProjects = new QLabel("Projects Uploaded:");
    accountProjects->setStyleSheet("border: none; "
                                   "text-decoration: underline; ");
    accountProjectsText = new QLabel();
    accountProjectsText->setStyleSheet("border: none; "
                                       "padding: 8px; ");

    accountType = new QLabel("Account Type:");
    accountType->setStyleSheet("border: none; "
                               "text-decoration: underline; ");
    accountTypeText = new QLabel();
    accountTypeText->setStyleSheet("border: none; "
                                   "padding: 8px; ");
    
    //setting up layout
    QHBoxLayout *accountNameLayout = new QHBoxLayout;
    accountNameLayout->addWidget(accountName);
    accountNameLayout->addSpacing(-500);
    accountNameLayout->addWidget(accountNameText);

    QHBoxLayout *accountEmailLayout = new QHBoxLayout;
    accountEmailLayout->addWidget(accountEmail);
    accountEmailLayout->addSpacing(-500);
    accountEmailLayout->addWidget(accountEmailText);

    QHBoxLayout *accountProjectsLayout = new QHBoxLayout;
    accountProjectsLayout->addWidget(accountProjects);
    accountProjectsLayout->addSpacing(-500);
    accountProjectsLayout->addWidget(accountProjectsText);

    QHBoxLayout *accountTypeLayout = new QHBoxLayout;
    accountTypeLayout->addWidget(accountType);
    accountTypeLayout->addSpacing(-500);
    accountTypeLayout->addWidget(accountTypeText);
    
    QVBoxLayout *verticalMainAccountLayout = new QVBoxLayout;
    verticalMainAccountLayout->addLayout(accountNameLayout);
    verticalMainAccountLayout->addLayout(accountEmailLayout);
    verticalMainAccountLayout->addLayout(accountProjectsLayout);
    verticalMainAccountLayout->addLayout(accountTypeLayout);
    verticalMainAccountLayout->addStretch();
    setLayout(verticalMainAccountLayout);
}

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void accountFunction::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
