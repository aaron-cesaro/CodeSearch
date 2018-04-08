#include "PremiumUser.h"

PremiumUser::PremiumUser(std::string n, std::string p, std::string e, unsigned int u, bool t) : FreeUser(n, p, e, u, t) {}

PremiumUser::PremiumUser(const Account &other) : FreeUser(other) {}

/*--------------set functions--------------*/

void PremiumUser::increaseNumberOfProjects() {
    numberOfProjects++;
}

/*--------------add functions--------------*/

void PremiumUser::addProject(Project *newProject) {
    getProjectList()->addProject(newProject);
    increaseNumberOfProjects();
}
