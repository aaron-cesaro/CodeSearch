#ifndef CODESEARCH_ACCOUNTCONTROLLER_H
#define CODESEARCH_ACCOUNTCONTROLLER_H

#include "../model/Account.h"
#include "../view/accountFunction.h"
#include "../view/loadXml.h"
#include "../model/PremiumUser.h"
#include <QString>

class Account;
class accountFunction;

class AccountController {

private:
    Account *accountModel;
    accountFunction *accountView;

public:
    AccountController(Account *model, accountFunction *view, const QString &);
    accountFunction *setAccountView();
    void setPremiumAccountModel(Account *);
    std::vector<Project *> getProjectList() const;
    Account *getAccountModel();
    accountFunction *getAccountView() const;
    loadXml *loadFunction;
    QString user;
};


#endif //CODESEARCH_ACCOUNTCONTROLLER_H