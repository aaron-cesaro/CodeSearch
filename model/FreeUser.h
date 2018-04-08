#ifndef CODESEARCH_FREEUSER_H
#define CODESEARCH_FREEUSER_H

#include <list>
#include <string>

#include "Account.h"
#include "Project.h"

class FreeUser : public Account {

public:
    FreeUser(std::string n = std::string(), std::string = std::string(), std::string = std::string(),
             unsigned int = 0, bool = false);
    FreeUser(const Account &);
    //add methods
    virtual void increaseNumberOfProjects() override;
    virtual void addProject(Project *newProject) override;
    virtual void setPremiumUser() override;

};


#endif //CODESEARCH_FREEUSER_H
