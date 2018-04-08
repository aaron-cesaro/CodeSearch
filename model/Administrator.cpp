#include "Administrator.h"
#include "PremiumUser.h"
#include "FreeUser.h"


/*--------------delete functions--------------*/

void Administrator::deleteUser(std::string Username, std::string email) {
    bool found = false;
    for(auto it = accountList.begin(); it != accountList.end() && !found; ++it) {
        if((*it)->getName() == Username && (*it)->getEmail() == email) {
            delete *it;
            accountList.erase(it);
            found = true;
        }
    }
    if(found)
        std::cout << "Utente " << Username << " eliminato\n";
}

void Administrator::setAccountList(std::vector<Account *> accList) {
    accountList = accList;
}

void Administrator::addUserAccount(Account *account) {
    accountList.push_back(account);
}

void Administrator::clearAccountList() {
    for(auto it = accountList.begin(); it != accountList.end(); ++it) {
        delete *it;
        accountList.erase(it);
        it--;
    }
}

std::vector<Account *>  Administrator::getAccountList() const {
    return accountList;
}

Account *Administrator::getUser(std::string name, std::string email) const {
    for(auto it = accountList.begin(); it != accountList.end(); ++it) {
        if((*it)->getName() == name && (*it)->getEmail() == email) {
            if(dynamic_cast<PremiumUser *>(*it))
                return dynamic_cast<PremiumUser *>(*it);
            else
                return dynamic_cast<FreeUser *>(*it);
        }
    }
    return nullptr;
}
