#ifndef CODESEARCH_ADMINCONTROLLER_H
#define CODESEARCH_ADMINCONTROLLER_H

#include "../model/Administrator.h"
#include "../view/userListFunction.h"
#include "../view/loadXml.h"

#include <QList>

class adminController {

public:
    class userTableRow {
    public:
        QTableWidgetItem *rowUserName;
        QTableWidgetItem *rowUserPassword;
        QTableWidgetItem *rowUserEmail;
        QTableWidgetItem *rowUserNumberOfProjects;
        QTableWidgetItem *rowUserAccountType;
        userTableRow(QTableWidgetItem * = nullptr, QTableWidgetItem * = nullptr,
                     QTableWidgetItem * = nullptr, QTableWidgetItem * = nullptr,
                     QTableWidgetItem * = nullptr);
    };
    adminController(Administrator *, userListFunction *, QWidget *);
    Administrator *adminModel;
    userListFunction *adminView;
    userListFunction *setUserListView();
    QVector<userTableRow *> userRowContainer;
    void clearUserRowContainer();
    void loadUserList();
    void loadUserRowList(std::vector<Account *>);

};


#endif //CODESEARCH_ADMINCONTROLLER_H
