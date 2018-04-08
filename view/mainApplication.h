#ifndef CODESEARCH_MAINAPPLICATION_H
#define CODESEARCH_MAINAPPLICATION_H

//Qt library
#include <QWidget>
//View
#include "searchFunction.h"
#include "userListFunction.h"
#include "uploadFunction.h"
#include "accountFunction.h"
//model
#include "../model/Account.h"
#include "../model/Project.h"
#include "../model/Administrator.h"
//controller
#include "../controller/AccountController.h"
#include "../controller/projectsListController.h"
#include "../controller/UploadController.h"
#include "../controller/adminController.h"
#include "premiumDialog.h"
#include "registerForm.h"

class mainApplication : public QWidget {

    Q_OBJECT

public:
    mainApplication(QWidget *, const QString &);
    void paintEvent(QPaintEvent *) override;
    void deleteProject(const QString &, const QString &, int);
    bool checkEditCondition(int) const;
    void editProject() const;
    void deleteUser(const QString &, const QString &, int);
    void addUserForAdmin();

public slots:
    void showSearch();
    void showUpload();
    void showAccount();
    void get_search_info();
    void cancel_search();
    void showProjectsContextMenu(const QPoint &);
    void showAdminContextMenu(const QPoint&);
    void update_project_list();
    void update_project_count();
    void on_Premium_Button();
    void on_Premium_Confirm();
    void updateUserList();
    void updateNewUserList();

private:
    void hideAll();
    //view Functions
    searchFunction *searchFunctionView;
    userListFunction *userListFunctionView;
    uploadFunction *uploadFunctionView;
    accountFunction *accountFunctionView;
    projectsList *projectListView;
    projectsList *searchedProjectListView;
    premiumDialog *premiumDialogWindow;
    registerForm *addUserDialog;

    //model Functions
    Account *accountModel;
    Administrator *administratorModel;

    //controller
    AccountController *applicationAccountController;
    projectsListController *applicationProjectController;
    UploadController *applicationUploadController;
    adminController *applicationAdminController;

    //aux var
    QString applicationUser;

};


#endif //CODESEARCH_MAINAPPLICATION_H
