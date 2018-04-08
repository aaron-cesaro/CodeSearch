#ifndef CODESEARCH_ACCOUNT_H
#define CODESEARCH_ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include <QXmlStreamWriter>

#include "projectContainer.h"
#include "Project.h"

class Account {

private:
    std::string name;
    std::string email;
    std::string password;

protected:
    int numberOfProjects;
    bool premiumAccount;
    projectContainer *projectList;

public:
    Account(std::string = std::string(), std::string = std::string(),
            std::string = std::string(), int = 0, bool = false);
    virtual ~Account();

    //get function
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;
    projectContainer *getProjectList() const;
    int getNumberOfProjects() const;
    bool isPremiumAccount() const;

    //set functions
    virtual void addProject(Project *) = 0;
    virtual Project *getProject(Project *);
    void deleteProject(std::string, std::string);
    virtual void increaseNumberOfProjects() = 0;
    void decreaseNumberOfProjects();
    void setName(std::string);
    void setEmail(std::string);
    void setPassword(std::string);
    virtual void setNumberOfProjects(int );
    virtual void setPremiumUser();
};


#endif //CODESEARCH_ACCOUNT_H
