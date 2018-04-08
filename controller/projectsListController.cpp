#include <QTableWidget>
#include <QDebug>
#include <QFile>
#include <QtWidgets/QMessageBox>
#include "projectsListController.h"

projectsListController::projectTableRow::projectTableRow(QTableWidgetItem *n, QTableWidgetItem *a,
                                                         QTableWidgetItem *lan, QTableWidgetItem *t,
                                                         QTableWidgetItem *lic) :
        rowName(n), rowAuthor(a), rowLanguage(lan), rowType(t), rowLicense(lic) {}

projectsListController::projectsListController(projectsList *view, AccountController *accountController) :
                                               projectView(view), userAccountController(accountController) {

    QString filePath = QString::fromStdString("savedData/applicationData/" + userAccountController->getAccountModel()->getName() + "ProjectList.xml");
    QFile *file = new QFile(filePath);

    projectView = new projectsList(0,5);
    searchedProjectView = new projectsList(0,5);


    if (file->open(QIODevice::ReadOnly | QFile::Text)) {
        loadProjectList();
        setProjectsRowContainer(userAccountController->getAccountModel()->getProjectList()->getUserProjectList());
    }
}

projectsList *projectsListController::setProjectsListView() {
    return projectView;
}

projectsList *projectsListController::setSearchedProjectListView() {
    return searchedProjectView;
}

void projectsListController::loadSearchedProjects() {
    bool selectionType = false;
    if(searchedProjects[2] != "") {
        selectionType = true;
    }
    int match = matchedProjects(userAccountController->getAccountModel()->getNumberOfProjects(), selectionType);
    if(match) {
        searchedProjectView->setRowCount(match);
        clearRowProjectList();
        for (int i = 0, j = -1; i < userAccountController->getAccountModel()->getNumberOfProjects() && j < match; ++i) {
            QTableWidgetItem *name = new QTableWidgetItem(
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getName()));
            QTableWidgetItem *author = new QTableWidgetItem(
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getAuthor()));
            QTableWidgetItem *language = new QTableWidgetItem(
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLanguage()));
            QTableWidgetItem *type = new QTableWidgetItem(
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getProjectType()));
            QTableWidgetItem *license = new QTableWidgetItem(
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLicense()));

            searchedProjectRowContainer.push_back(new projectTableRow(name, author, language, type, license));

            if (!selectionType &&
                       searchedProjects[0] ==
                       QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getName()) &&
                       searchedProjects[1] ==
                       QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getAuthor()) &&
                       searchedProjects[3] == QString::fromStdString(
                       userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLanguage())) {
                j++;
                searchedProjectView->setItem(j, 0, searchedProjectRowContainer[i]->rowName);
                searchedProjectView->setItem(j, 1, searchedProjectRowContainer[i]->rowAuthor);
                searchedProjectView->setItem(j, 2, searchedProjectRowContainer[i]->rowLanguage);
                searchedProjectView->setItem(j, 3, searchedProjectRowContainer[i]->rowType);
                searchedProjectView->setItem(j, 4, searchedProjectRowContainer[i]->rowLicense);
            }
            else {
                if (selectionType &&
                    searchedProjects[0] ==
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getName()) &&
                    searchedProjects[1] ==
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getAuthor()) &&
                    searchedProjects[2] ==
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getProjectType())&&
                    searchedProjects[3] ==
                    QString::fromStdString(userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLanguage())) {
                    j++;
                    searchedProjectView->setItem(j, 0, searchedProjectRowContainer[i]->rowName);
                    searchedProjectView->setItem(j, 1, searchedProjectRowContainer[i]->rowAuthor);
                    searchedProjectView->setItem(j, 2, searchedProjectRowContainer[i]->rowLanguage);
                    searchedProjectView->setItem(j, 3, searchedProjectRowContainer[i]->rowType);
                    searchedProjectView->setItem(j, 4, searchedProjectRowContainer[i]->rowLicense);
                }
            }
        }
        searchedProjects.clear();
    }
}

int projectsListController::matchedProjects(int index, bool type) const {
    int counter = 0;
    for(int i = 0; i < index; ++i) {
        std::string projectMatchName, projectMatchAuthor, projectMatchType, projectMatchLanguage;
        projectMatchName = searchedProjects[0].toStdString();
        projectMatchAuthor = searchedProjects[1].toStdString();
        projectMatchType = searchedProjects[2].toStdString();
        projectMatchLanguage = searchedProjects[3].toStdString();
        if(!type && userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getName() == projectMatchName &&
           userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getAuthor() == projectMatchAuthor &&
           userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLanguage() == projectMatchLanguage) {
           counter++;
        }
        else {
            if (userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getName() == projectMatchName &&
                userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getAuthor() == projectMatchAuthor &&
                userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getProjectType() == projectMatchType &&
                userAccountController->getAccountModel()->getProjectList()->getUserProjectList()[i]->getLanguage() == projectMatchLanguage) {
                counter++;
            }
        }
    }
    return counter;
}

void projectsListController::clearRowProjectList() {
    //clear projects list
    for(auto it = projectRowContainer.begin(); it != projectRowContainer.end(); ++it) {
        delete (*it);
        it = projectRowContainer.erase(it);
        it--;
    }
    //clear searched projects list
    for(auto it = searchedProjectRowContainer.begin(); it != searchedProjectRowContainer.end(); ++it) {
        delete (*it);
        it = searchedProjectRowContainer.erase(it);
        it--;
    }
}

void projectsListController::setProjectsRowContainer(std::vector<Project *> listOfProjects) {
    if(!searchedProjectRowContainer.isEmpty())
        searchedProjectRowContainer.clear();

    projectView->setRowCount(userAccountController->getAccountModel()->getNumberOfProjects());
    //write rows and save project/s
    for(int i = 0; i < listOfProjects.size(); ++i) {
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(listOfProjects[i]->getName()));
        QTableWidgetItem *author = new QTableWidgetItem(QString::fromStdString(listOfProjects[i]->getAuthor()));
        QTableWidgetItem *language = new QTableWidgetItem(QString::fromStdString(listOfProjects[i]->getLanguage()));
        QTableWidgetItem *type = new QTableWidgetItem(QString::fromStdString(listOfProjects[i]->getProjectType()));
        QTableWidgetItem *license = new QTableWidgetItem(QString::fromStdString(listOfProjects[i]->getLicense()));

        projectRowContainer.push_back(new projectTableRow(name, author, language, type, license));

        projectView->setItem(i,0,projectRowContainer[i]->rowName);
        projectView->setItem(i,1,projectRowContainer[i]->rowAuthor);
        projectView->setItem(i,2,projectRowContainer[i]->rowLanguage);
        projectView->setItem(i,3,projectRowContainer[i]->rowType);
        projectView->setItem(i,4,projectRowContainer[i]->rowLicense);
    }
}

void projectsListController::loadProjectList() {
    loadXml *loadPrjInfo = new loadXml;
    loadPrjInfo->loadProjectInfo(userAccountController->getAccountModel()->getName());
    //write rows and save project/s
    userAccountController->getAccountModel()->getProjectList()->clearProjectList();
    int index = userAccountController->getAccountModel()->getNumberOfProjects();
    userAccountController->getAccountModel()->setNumberOfProjects(0);
    for(int i = 0; i < index; ++i) {
        QString projectName = loadPrjInfo->userProjectsInfoList[i*5];
        QString projectAuthor = loadPrjInfo->userProjectsInfoList[1 + i*5];
        QString projectLanguage = loadPrjInfo->userProjectsInfoList[2 + i*5];
        QString projectType = loadPrjInfo->userProjectsInfoList[3 + i*5];
        QString projectLicense = loadPrjInfo->userProjectsInfoList[4 + i*5];

        userAccountController->getAccountModel()->addProject(new Project(projectName.toStdString(), projectAuthor.toStdString(),
                                   projectLanguage.toStdString(), projectType.toStdString(),
                                   projectLicense.toStdString()));
    }
    delete loadPrjInfo;
}

projectsList *projectsListController::getSearchedProjectView() const {
    return searchedProjectView;
}
