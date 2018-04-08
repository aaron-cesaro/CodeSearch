#ifndef CODESEARCH_PROJECTSLISTCONTROLLER_H
#define CODESEARCH_PROJECTSLISTCONTROLLER_H

#include "../model/Project.h"
#include "../view/projectsList.h"
#include "../view/loadXml.h"
#include "../view/userListFunction.h"
#include "../model/Account.h"
#include "../model/projectContainer.h"
#include "AccountController.h"

class projectsListController {

private:
    AccountController *userAccountController;
    projectsList *searchedProjectView;

public:
    class projectTableRow {
    public:
        QTableWidgetItem *rowName;
        QTableWidgetItem *rowAuthor;
        QTableWidgetItem *rowLanguage;
        QTableWidgetItem *rowType;
        QTableWidgetItem *rowLicense;
        projectTableRow(QTableWidgetItem * = nullptr, QTableWidgetItem * = nullptr,
                        QTableWidgetItem * = nullptr, QTableWidgetItem * = nullptr,
                        QTableWidgetItem * = nullptr);
    };
    projectsListController(projectsList *view, AccountController *);
    projectsList *setProjectsListView();
    projectsList *setSearchedProjectListView();
    int matchedProjects(int, bool) const;
    void loadSearchedProjects();
    void clearRowProjectList();
    void setProjectsRowContainer(std::vector<Project *>);
    void loadProjectList();
    projectsList *getSearchedProjectView() const;
    QVector<QString> searchedProjects;
    projectsList *projectView;
    QVector<projectTableRow *> projectRowContainer;
    QVector<projectTableRow *> searchedProjectRowContainer;

};


#endif //CODESEARCH_PROJECTSLISTCONTROLLER_H
