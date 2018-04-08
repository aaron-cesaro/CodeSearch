#include <QDebug>
#include <iostream>
#include "projectContainer.h"

void projectContainer::addProject(Project *newProject) {
    userProjectList.push_back(newProject);
}

std::vector<Project *> projectContainer::getUserProjectList() const {
    return userProjectList;
}

void projectContainer::clearProjectList() {
    for(auto it = userProjectList.begin(); it != userProjectList.end(); ++it) {
        delete (*it);
        it = userProjectList.erase(it);
        it--;
    }
}

void projectContainer::deleteProject(std::string name, std::string author) {
    bool found = false;
    for(std::vector<Project *>::iterator it = userProjectList.begin();
        it != userProjectList.end() && !found; ++it) {
        if((*it)->getName() == name && (*it)->getAuthor() == author) {
            delete *it;
            it = userProjectList.erase(it);
            found = true;
        }
    }
    if(found)
        std::cout << "Progetto eliminato\n";
}

void projectContainer::setProjectList(std::vector<Project *> newProjList) {
    userProjectList = newProjList;
}
