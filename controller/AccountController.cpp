#include "AccountController.h"
#include "../view/loadXml.h"
#include "../model/Account.h"
#include "../view/accountFunction.h"
#include "../model/PremiumUser.h"
#include "../model/FreeUser.h"
#include <QDebug>

AccountController::AccountController(Account *model, accountFunction *view, const QString &userInfo) :
                                     accountModel(model), accountView(view), user(userInfo) {
    loadFunction = new loadXml();

    //init model account info
    loadFunction->loadAccountInfo(userInfo.toStdString());

    if(loadFunction->accountType == "PremiumUser") {
        accountModel = new PremiumUser();
    }
    else
        accountModel = new FreeUser();
    if(accountModel) {
        accountModel->setName(loadFunction->nameStore.toStdString());
        accountModel->setPassword(loadFunction->passwordStore.toStdString());
        accountModel->setEmail(loadFunction->emailStore.toStdString());
        accountModel->setNumberOfProjects(loadFunction->numberOfProjectsStore.toInt());
    }
    //init view account info
    accountView = new accountFunction;
    accountView->accountNameText->setText(loadFunction->nameStore);
    accountView->accountEmailText->setText(loadFunction->emailStore);
    accountView->accountProjectsText->setText(loadFunction->numberOfProjectsStore);
    accountView->accountTypeText->setText(loadFunction->accountType);
}

accountFunction *AccountController::setAccountView() {
    return accountView;
}

std::vector<Project *> AccountController::getProjectList() const {
    return accountModel->getProjectList()->getUserProjectList();
}

Account *AccountController::getAccountModel() {
    return accountModel;
}

accountFunction *AccountController::getAccountView() const {
    return accountView;
}

void AccountController::setPremiumAccountModel(Account *upgradedUser) {
    accountModel = new PremiumUser(*upgradedUser);
}

