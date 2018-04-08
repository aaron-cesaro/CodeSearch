#include "adminController.h"
#include "../model/PremiumUser.h"
#include "../model/FreeUser.h"
#include <QDebug>


adminController::userTableRow::userTableRow(QTableWidgetItem *rUN, QTableWidgetItem *rUP, QTableWidgetItem *rUE,
                                            QTableWidgetItem *rUNOP, QTableWidgetItem *rUAT) :
        rowUserName(rUN), rowUserPassword(rUP), rowUserEmail(rUE), rowUserNumberOfProjects(rUNOP), rowUserAccountType(rUAT) {}

adminController::adminController(Administrator *admin, userListFunction *userList, QWidget *parent): adminModel(admin), adminView(userList) {

    adminView = new userListFunction(parent);
    adminModel = new Administrator;

    loadUserList();
    loadUserRowList(adminModel->getAccountList());
}

userListFunction *adminController::setUserListView() {
    return adminView;
}

void adminController::loadUserList() {
    loadXml *loadUsers = new loadXml;
    int index = loadUsers->loadAdminInfo();
    for(int i = 0; i < index; ++i) {
        QString userName = loadUsers->userList[i * 5];
        QString userPassword = loadUsers->userList[1 + (i * 5)];
        QString userEmail = loadUsers->userList[2 + (i * 5)];
        QString userNumberOfProjects = loadUsers->userList[3 + (i * 5)];
        QString userAccountType = loadUsers->userList[4 + (i * 5)];
        bool type = false;
        if(userAccountType == "PremiumUser") {
            type = true;
            adminModel->addUserAccount(new PremiumUser(userName.toStdString(), userPassword.toStdString(),
                                                   userEmail.toStdString(), userNumberOfProjects.toUInt(), type));
        }
        else {
            adminModel->addUserAccount(new FreeUser(userName.toStdString(), userPassword.toStdString(),
                                                       userEmail.toStdString(), userNumberOfProjects.toUInt(), type));
        }
    }
    delete loadUsers;
}

void adminController::loadUserRowList(std::vector<Account *> modelUserList) {
    adminView->listOfUsers->setRowCount(int(modelUserList.size()));
    for(int i = 0; i < modelUserList.size(); ++i) {

        QTableWidgetItem *userNameVar = new QTableWidgetItem(QString::fromStdString(modelUserList[i]->getName()));
        QTableWidgetItem *userPswVar = new QTableWidgetItem(QString::fromStdString(modelUserList[i]->getPassword()));
        QTableWidgetItem *userEmailVar = new QTableWidgetItem(QString::fromStdString(modelUserList[i]->getEmail()));
        QTableWidgetItem *userNOPVar = new QTableWidgetItem(QString::number(modelUserList[i]->getNumberOfProjects()));
        QString accountType = "Free User";
        if(modelUserList[i]->isPremiumAccount()) {
            accountType = "Premium User";
        }

        QTableWidgetItem *userType = new QTableWidgetItem(accountType);

        userRowContainer.push_back(new userTableRow(userNameVar, userPswVar, userEmailVar, userNOPVar, userType));

        adminView->listOfUsers->setItem(i,0,userRowContainer[i]->rowUserName);
        adminView->listOfUsers->setItem(i,1,userRowContainer[i]->rowUserPassword);
        adminView->listOfUsers->setItem(i,2,userRowContainer[i]->rowUserEmail);
        adminView->listOfUsers->setItem(i,3,userRowContainer[i]->rowUserNumberOfProjects);
        adminView->listOfUsers->setItem(i,4,userRowContainer[i]->rowUserAccountType);
    }
}

void adminController::clearUserRowContainer() {
    for(auto it = userRowContainer.begin(); it != userRowContainer.end(); ++it) {
        delete *it;
        it = userRowContainer.erase(it);
        it--;
    }
}
