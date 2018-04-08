#include "Account.h"
#include "../controller/AccountController.h"
#include <QDebug>

Account::Account(std::string n, std::string p, std::string e, int u, bool t) :
                 name(n), password(p), email(e), numberOfProjects(u), premiumAccount(t) {
    projectList = new projectContainer;
}

Account::~Account() {
    if(!projectList->getUserProjectList().empty()) {
        for(std::vector<Project *>::const_iterator it = projectList->getUserProjectList().begin();
            it != projectList->getUserProjectList().end(); ++it) {
            delete *it;
            it = projectList->getUserProjectList().erase(it);
            it--;
            decreaseNumberOfProjects();
        }
    }
}

/*--------------get functions--------------*/

std::string Account::getName() const {
    return name;
}

std::string Account::getEmail() const {
    return  email;
}


int Account::getNumberOfProjects() const {
    return numberOfProjects;
}

bool Account::isPremiumAccount() const {
    return premiumAccount;
}

/*--------------delete functions--------------*/

void Account::deleteProject(std::string name, std::string author) {
    if(numberOfProjects > 0) {
        projectList->deleteProject(name,author);
        decreaseNumberOfProjects();
    }
    else
        std::cout << "Progetto non presente\n";
}

/*--------------set functions--------------*/

void Account::decreaseNumberOfProjects() {
    if(numberOfProjects > 0)
        numberOfProjects--;
    else
        std::cout << "Nessun progetto uploadato\n";
}

void Account::setName(std::string newName) {
    name = newName;
}

void Account::setEmail(std::string newEmail) {
    email = newEmail;
}

Project *Account::getProject(Project *searchedProject) {
    if(!projectList->getUserProjectList().empty()) {
        for(std::vector<Project *>::const_iterator it = projectList->getUserProjectList().begin();
            it != projectList->getUserProjectList().end(); ++it) {
            if((*it)->getName() == searchedProject->getName()) {
                return *it;
            }
        }
        std::cout << "Progetto non trovato\n";
    }
    else {
        std::cout << "Nessun progetto in lista\n";
    }
    return nullptr;
}

void Account::setNumberOfProjects(int num) {
    numberOfProjects = num;
}

void Account::setPassword(std::string psw) {
    password = psw;
}

std::string Account::getPassword() const {
    return password;
}

projectContainer *Account::getProjectList() const {
    return projectList;
}

void Account::setPremiumUser() {
    premiumAccount = true;
}



