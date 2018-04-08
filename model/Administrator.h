#ifndef CODESEARCH_ADMINISTRATOR_H
#define CODESEARCH_ADMINISTRATOR_H

#include "Account.h"
#include "Project.h"
#include <string>

class Administrator {

private:
    std::vector<Account *> accountList;

public:
    std::vector<Account *>  getAccountList() const;
    void setAccountList(std::vector<Account *>);
    Account *getUser(std::string, std::string) const;
    void addUserAccount(Account *);
    void deleteUser(std::string, std::string);
    void clearAccountList();
};


#endif //CODESEARCH_ADMINISTRATOR_H
