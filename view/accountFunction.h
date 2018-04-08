#ifndef CODESEARCH_ACCOUNTFUNCTION_H
#define CODESEARCH_ACCOUNTFUNCTION_H

#include <QWidget>
#include <QLabel>
#include <QXmlStreamReader>
#include "../controller/AccountController.h"

class accountFunction : public QWidget {

    Q_OBJECT

public:
    accountFunction(QWidget * = nullptr);
    void paintEvent(QPaintEvent *);
    //Labels
    QLabel *accountName;
    QLabel *accountNameText;
    QLabel *accountEmail;
    QLabel *accountEmailText;
    QLabel *accountProjects;
    QLabel *accountProjectsText;
    QLabel *accountType;
    QLabel *accountTypeText;
};


#endif //CODESEARCH_ACCOUNTFUNCTION_H
