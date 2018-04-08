#include "FreeUser.h"
#include <iostream>

FreeUser::FreeUser(std::string n, std::string p, std::string e, unsigned int u, bool t) :
                   Account(n,p,e,u,t) {}

FreeUser::FreeUser(const Account &other) : Account(other) {}

/*--------------set functions--------------*/

void FreeUser::increaseNumberOfProjects() {
    if(getNumberOfProjects() < 10)
        numberOfProjects++;
    else {
        std::cout << "max number of projects exceded\n";
    }
}

/*--------------add functions--------------*/

void FreeUser::addProject(Project *newProject) {
    if(getNumberOfProjects() < 10) {
        getProjectList()->addProject(newProject);
        increaseNumberOfProjects();
    }
    else {
        std::cout << "max projects exceded\n";
    }
}

void FreeUser::setPremiumUser() {
    if(!isPremiumAccount()) {
        Account::setPremiumUser();
    }
}

