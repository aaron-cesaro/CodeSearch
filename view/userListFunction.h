#ifndef CODESEARCH_USERLISTFUNCTION_H
#define CODESEARCH_USERLISTFUNCTION_H

#include <QWidget>

#include "../controller/projectsListController.h"
#include "loadXml.h"
#include "userList.h"

class userListFunction: public QWidget {

    Q_OBJECT

public:
    userListFunction(QWidget * = nullptr);
    void paintEvent(QPaintEvent *) override;
    userList *listOfUsers;
};


#endif //CODESEARCH_USERLISTFUNCTION_H
