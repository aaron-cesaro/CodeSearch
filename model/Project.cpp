#include "Project.h"
#include <QDebug>


/*--------------get functions--------------*/

Project::Project(std::string n, std::string a, std::string l, std::string p, std::string lic) :
                 name(n), author(a), language(l), projectType(p), license(lic) {
}

std::string Project::getName() const {
    return name;
}

std::string Project::getAuthor() const {
    return author;
}

std::string Project::getLanguage() const {
    return language;
}

std::string Project::getProjectType() const {
    return projectType;
}
std::string Project::getLicense() const {
    return license;
}

/*--------------set functions--------------*/

void Project::setName(std::string newName) {
    name = newName;
}

void Project::setAuthor(std::string newAuthor) {
    author = newAuthor;
}

void Project::setLanguage(std::string newLanguage) {
    language = newLanguage;
}

void Project::setProjectType(std::string newProjectType) {
    projectType = newProjectType;
}

void Project::setLicense(std::string lic) {
    license = lic;
}



















