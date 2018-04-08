#ifndef CODESEARCH_PROJECTCONTAINER_H
#define CODESEARCH_PROJECTCONTAINER_H

#include "Project.h"
#include <vector>

class Project;

class projectContainer {

private:
    std::vector<Project *> userProjectList;

public:
    void addProject(Project *);
    void deleteProject(std::string, std::string);
    void clearProjectList();
    void setProjectList(std::vector<Project *>);
    std::vector<Project *> getUserProjectList() const;

};


#endif //CODESEARCH_PROJECTCONTAINER_H
