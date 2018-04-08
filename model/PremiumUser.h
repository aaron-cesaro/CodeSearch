#ifndef CODESEARCH_PREMIUMUSER_H
#define CODESEARCH_PREMIUMUSER_H

#include "FreeUser.h"

class PremiumUser : public FreeUser {

public:
    PremiumUser(std::string = std::string(), std::string = std::string(), std::string = std::string(),
                unsigned int = 0, bool = true);
    PremiumUser(const Account &);
    //add methods
    virtual void increaseNumberOfProjects() override;
    virtual void addProject(Project *newProject) override;

};


#endif //CODESEARCH_PREMIUMUSER_H
