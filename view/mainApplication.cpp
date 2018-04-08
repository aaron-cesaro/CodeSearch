//view
#include "mainApplication.h"
#include "adminFunction.h"
#include "../model/FreeUser.h"
#include "../model/PremiumUser.h"
//Qt library
#include <QVBoxLayout>
#include <QPainter>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QString>
#include <QAction>

/*------------------Constructor--------------------*/

mainApplication::mainApplication(QWidget *parent, const QString &appUser) : QWidget(parent), applicationUser(appUser) {

    //set Application style
    setStyleSheet("background-color: #f7f8f8");
    QVBoxLayout *layout = new QVBoxLayout();

    if(appUser != "admin") {

        //initializing Functions

        //creating search function
        searchFunctionView = new searchFunction;

        //creating account function
        applicationAccountController = new AccountController(accountModel, accountFunctionView, applicationUser);
        accountFunctionView = applicationAccountController->setAccountView();

        //creating the project list
        applicationProjectController = new projectsListController(projectListView,
                                                                  applicationAccountController);

        projectListView = applicationProjectController->setProjectsListView();
        projectListView->setContextMenuPolicy(Qt::CustomContextMenu);


        searchedProjectListView = applicationProjectController->setSearchedProjectListView();
        searchedProjectListView->hide();

        //connecting search functionality
        connect(searchFunctionView->searchButton, SIGNAL(clicked()), searchFunctionView, SLOT(on_search()));
        connect(searchFunctionView->searchButton, SIGNAL(clicked()), this, SLOT(get_search_info()));
        connect(searchFunctionView->resetButton, SIGNAL(clicked()), this, SLOT(cancel_search()));
        //connecting context menu to the rows
        connect(projectListView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showProjectsContextMenu(const QPoint&)));

        //creating upload function
        applicationUploadController = new UploadController(uploadFunctionView,
                                                           applicationAccountController);
        uploadFunctionView = applicationUploadController->setUploadFunctionView();
        //update project list if a new project is uploaded
        connect(uploadFunctionView->uploadButton, SIGNAL(clicked()), this, SLOT(update_project_list()));
        connect(uploadFunctionView->uploadButton, SIGNAL(clicked()), this, SLOT(update_project_count()));

        //set Application Layout
        layout->addWidget(searchFunctionView);
        layout->addWidget(projectListView);
        layout->addWidget(searchedProjectListView);
        layout->addWidget(uploadFunctionView);
        layout->addWidget(accountFunctionView);

    }
    else {
        //creating admin window
        applicationAdminController = new adminController(administratorModel, userListFunctionView, this);
        userListFunctionView = applicationAdminController->setUserListView();

        layout->addWidget(userListFunctionView);
        userListFunctionView->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(userListFunctionView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showAdminContextMenu(const QPoint&)));
    }
    setLayout(layout);
}


/*--------------Public FUNCTIONS--------------*/

void mainApplication::hideAll() {
    searchFunctionView->setVisible(false);
    projectListView->setVisible(false);
    searchedProjectListView->setVisible(false);
    uploadFunctionView->setVisible(false);
    accountFunctionView->setVisible(false);
}

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void mainApplication::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void mainApplication::deleteProject(const QString & projectName, const QString & projectAuthor, int projectIndex) {
    //delete project from account project list
    applicationAccountController->getAccountModel()->deleteProject(projectName.toStdString(), projectAuthor.toStdString());
    //update table rows
    applicationProjectController->clearRowProjectList();
    applicationProjectController->setProjectsRowContainer(applicationAccountController->getProjectList());
    //update account view info
    applicationAccountController->getAccountView()->accountProjectsText->setText(QString::number(
            applicationAccountController->getAccountModel()->getNumberOfProjects()));
    //save updated project list to file
    saveXml *saveAux = new saveXml;
    saveAux->updateProjectInfo(applicationProjectController->projectRowContainer, QString::fromStdString(
            applicationAccountController->getAccountModel()->getName()));
    saveAux->updateAccountProjects(QString::fromStdString(applicationAccountController->getAccountModel()->getName()), true);

    Administrator *auxAdmin = new Administrator;
    adminController *auxAdminController = new adminController(auxAdmin, nullptr, nullptr);
    auxAdminController->adminView->hide();
    auxAdminController->adminModel->getUser(applicationAccountController->getAccountModel()->getName(),
                                            applicationAccountController->getAccountModel()->getEmail())->decreaseNumberOfProjects();
    saveAux->updateAdminInfo(auxAdminController->adminModel->getAccountList());

    delete saveAux;
    delete auxAdmin;
    delete auxAdminController;
}

bool mainApplication::checkEditCondition(int index) const {
    //compare user project's list info with edited project's table row info
    Project *thisProject = applicationAccountController->getProjectList()[index];
    projectsListController::projectTableRow *projectRow = applicationProjectController->projectRowContainer[index];
    //if there is any change return true, else return false;
    return QString::fromStdString(thisProject->getName()) != projectRow->rowName->text() ||
           QString::fromStdString(thisProject->getAuthor()) != projectRow->rowAuthor->text() ||
           QString::fromStdString(thisProject->getLanguage()) != projectRow->rowLanguage->text() ||
           QString::fromStdString(thisProject->getProjectType()) != projectRow->rowType->text();
}

void mainApplication::editProject() const {
    //save changes to file
    saveXml *saveAux = new saveXml;
    saveAux->updateProjectInfo(applicationProjectController->projectRowContainer,
                               QString::fromStdString(applicationAccountController->getAccountModel()->getName()), true);
    //clear projects table rows
    applicationProjectController->clearRowProjectList();
    //read updated info from file
    applicationProjectController->loadProjectList();
    //set table updated table rows
    applicationProjectController->setProjectsRowContainer(applicationAccountController->getProjectList());
    delete saveAux;
}

void mainApplication::deleteUser(const QString &userName, const QString &userEmail, int userIndex) {
    //delete project from account project list
    applicationAdminController->adminModel->deleteUser(userName.toStdString(), userEmail.toStdString());
    //clear and load table rows from accountList
    applicationAdminController->clearUserRowContainer();
    applicationAdminController->loadUserRowList(applicationAdminController->adminModel->getAccountList());
    //save updated info
    saveXml *saveAux = new saveXml;
    saveAux->updateAdminInfo(applicationAdminController->adminModel->getAccountList());
    saveAux->deleteUser(userName);

    delete saveAux;
}


/*--------------Public SLOTS-----------------*/

void mainApplication::showSearch() {
    if(!searchFunctionView->isVisible()) {
        hideAll();
        searchFunctionView->setVisible(true);
        projectListView->setVisible(true);
    }
}

void mainApplication::showUpload() {
    if(!uploadFunctionView->isVisible()) {
        hideAll();
        uploadFunctionView->setVisible(true);
    }
}

void mainApplication::showAccount() {
    if(!accountFunctionView->isVisible()) {
        hideAll();
        accountFunctionView->setVisible(true);
    }
}

void mainApplication::get_search_info() {
    applicationProjectController->searchedProjects = searchFunctionView->getOptions();
    if(!applicationProjectController->searchedProjects.isEmpty()) {
        bool selectionType = false;
        if(applicationProjectController->searchedProjects[2] != "") {
            selectionType = true;
        }
        if(applicationProjectController->matchedProjects(applicationAccountController->getAccountModel()->getNumberOfProjects(), selectionType)) {
            applicationProjectController->loadSearchedProjects();
            projectListView->hide();
            searchedProjectListView = applicationProjectController->setSearchedProjectListView();
            searchedProjectListView->setContextMenuPolicy(Qt::CustomContextMenu);
            searchedProjectListView->show();
            applicationProjectController->searchedProjects.clear();
        }
        else
            QMessageBox::information(0, "No result!", "No projects with this specifications. Try to change the selected language");
    }
    searchFunctionView->searchOptions.clear();
}

void mainApplication::cancel_search() {
    //hide searched project list rows
    searchedProjectListView->hide();
    //clear and load project list
    applicationProjectController->clearRowProjectList();
    applicationProjectController->setProjectsRowContainer(applicationAccountController->getProjectList());
    //show default project list rows
    projectListView->show();
}

void mainApplication::showAdminContextMenu(const QPoint &pos) {
    //find the the position in table's viewport
    QPoint globalPos = userListFunctionView->listOfUsers->viewport()->mapToGlobal(pos);

    //create action remove
    QMenu *contextAdminMenu = new QMenu;
    QAction *removeUser = new QAction("Remove user", nullptr);
    QAction *upgradeToPremium = new QAction("Upgrade to Premium", nullptr);
    QAction *addUser = new QAction("Add new user", nullptr);
    //add action to context menu
    contextAdminMenu->addAction(addUser);
    contextAdminMenu->addAction(removeUser);
    contextAdminMenu->addAction(upgradeToPremium);


    //find the selected row
    QModelIndexList tableIndex = applicationAdminController->adminView->listOfUsers->selectionModel()->selectedRows();
    QModelIndex selectedRowIndex;
    if(!tableIndex.isEmpty()) {
        selectedRowIndex = tableIndex[0];
        //clear index row table
        tableIndex.clear();

        QAction *selectedItem = contextAdminMenu->exec(globalPos);
        if(selectedItem && selectedItem->text() == "Remove user") {
            int exitButton = QMessageBox::information(this, "Code Search",
                                                      "Are you sure you want to remove this user?\n",
                    //options
                                                      QMessageBox::No | QMessageBox::Yes,
                    //default option
                                                      QMessageBox::Yes);
            if (exitButton == QMessageBox::Yes) {
                //remove selected project
                QString userNameToRemove = QString::fromStdString(
                        applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getName());
                QString userEmailToRemove = QString::fromStdString(
                        applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getEmail());
                deleteUser(userNameToRemove, userEmailToRemove, selectedRowIndex.row());
            }
        }
        else if(selectedItem && selectedItem->text() == "Upgrade to Premium") {
            int exitButton = QMessageBox::information(this, "Code Search",
                                                      "Are you sure you want to upgrade this user?\n",
                    //options
                                                      QMessageBox::No | QMessageBox::Yes,
                    //default option
                                                      QMessageBox::Yes);
            if (exitButton == QMessageBox::Yes) {
                saveXml *saveInfo = new saveXml;
                Administrator *auxAdmin = nullptr;
                adminController *auxAdminController = new adminController(auxAdmin, nullptr, nullptr);
                auxAdminController->adminView->hide();
                if(!auxAdminController->adminModel->getUser(applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getName(),
                        applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getEmail())->isPremiumAccount()) {
                    //set premium user
                    auxAdminController->adminModel->getUser(
                            applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getName(),
                            applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()]->getEmail())->setPremiumUser();

                    saveInfo->updateAdminInfo(auxAdminController->adminModel->getAccountList());

                    Account *auxAccount = applicationAdminController->adminModel->getAccountList()[selectedRowIndex.row()];

                    saveInfo->saveUserInfo(QString::fromStdString(auxAccount->getName()),
                                           QString::fromStdString(auxAccount->getPassword()),
                                           QString::fromStdString(auxAccount->getEmail()),
                                           QString::number(auxAccount->getNumberOfProjects()), "PremiumUser", false);
                    updateUserList();
                }
                else {
                    QMessageBox::warning(0, "Error!", "This account is already premium");
                }
                //clean all
                delete saveInfo;
                delete auxAdmin;
                delete auxAdminController;
            }
        }
        else if (selectedItem && selectedItem->text() == "Add new user"){
            addUserForAdmin();
            //updateUserList();
        }
    }
    delete contextAdminMenu;
    delete removeUser;
    delete upgradeToPremium;
    delete addUser;
}

void mainApplication::showProjectsContextMenu(const QPoint &pos) {
    if(!projectListView->isHidden()) {
        //find the the position in table's viewport
        QPoint globalPos = projectListView->viewport()->mapToGlobal(pos);
        //create actions
        QMenu *contextProjectsMenu = new QMenu;
        QAction *editProjectAction = new QAction("Edit changes", nullptr);
        QAction *removeProjectAction = new QAction("Remove", nullptr);
        //add actions to context menu
        contextProjectsMenu->addAction(editProjectAction);
        contextProjectsMenu->addAction(removeProjectAction);
        //find selected row
        QModelIndexList tableIndex = applicationProjectController->projectView->selectionModel()->selectedRows();
        QModelIndex selectedRowIndex;
        if(!tableIndex.isEmpty()) {
            selectedRowIndex = tableIndex[0];
            //clear index row table
            tableIndex.clear();

            QAction *selectedItem = contextProjectsMenu->exec(globalPos);
            if (selectedItem && selectedItem->text() == "Edit changes") {
                if (checkEditCondition(selectedRowIndex.row())) {
                    //edit project's changes
                    editProject();
                }
            } else if (selectedItem && selectedItem->text() == "Remove") {
                int exitButton = QMessageBox::information(this, "Code Search",
                                                          "Are you sure you want to remove this project?\n",
                        //options
                                                          QMessageBox::No | QMessageBox::Yes,
                        //default option
                                                          QMessageBox::Yes);
                if (exitButton == QMessageBox::Yes) {
                    //extract info from selected row
                    QString projectNameToRemove = applicationProjectController->projectRowContainer[selectedRowIndex.row()]->rowName->text();
                    QString projectAuthorToRemove = applicationProjectController->projectRowContainer[selectedRowIndex.row()]->rowAuthor->text();
                    //remove selected project
                    deleteProject(projectNameToRemove, projectAuthorToRemove, selectedRowIndex.row());
                }
            }
        }
        delete contextProjectsMenu;
        delete editProjectAction;
        delete removeProjectAction;
    }
}

void mainApplication::update_project_list() {
    if((dynamic_cast<FreeUser *>(applicationAccountController->getAccountModel()) &&
            applicationAccountController->getAccountModel()->getNumberOfProjects() <= 10)
            || dynamic_cast<PremiumUser *>(applicationAccountController->getAccountModel())) {
        //clear old project table row and set updated table rows
        applicationProjectController->clearRowProjectList();
        applicationProjectController->setProjectsRowContainer(applicationAccountController->getProjectList());
    }
}

void mainApplication::update_project_count() {
    if(dynamic_cast<PremiumUser *>(applicationAccountController->getAccountModel()) ||
      (dynamic_cast<FreeUser *>(applicationAccountController->getAccountModel()) &&
       applicationAccountController->getAccountModel()->getNumberOfProjects() <= 10)) {
        //update account page info
        applicationAccountController->getAccountView()->accountProjectsText->setText(
                QString::number(applicationAccountController->getAccountModel()->getNumberOfProjects()));
    }
}

void mainApplication::on_Premium_Button() {
    if(!dynamic_cast<PremiumUser *>(applicationAccountController->getAccountModel())) {
        premiumDialogWindow = new premiumDialog(this);
        premiumDialogWindow->show();
        connect(premiumDialogWindow->getPremiumConfirmButton(), SIGNAL(clicked()), this, SLOT(on_Premium_Confirm()));
    }
    else {
        QMessageBox::information(0, "Information!", "Your already are a Premium user");
    }
}

void mainApplication::on_Premium_Confirm() {
    QString codeText = premiumDialogWindow->getinsertCodeText()->text();
    if(codeText == "premium") {
        applicationAccountController->setPremiumAccountModel(applicationAccountController->getAccountModel());
        applicationAccountController->getAccountView()->accountTypeText->setText("PremiumUser");
        QMessageBox::information(0, "Congratulations!", "Your account has been upgraded to premium");
        premiumDialogWindow->hide();
        saveXml *saveUser = new saveXml;
        saveUser->saveUserInfo(QString::fromStdString(applicationAccountController->getAccountModel()->getName()),
                               QString::fromStdString(applicationAccountController->getAccountModel()->getPassword()),
                               QString::fromStdString(applicationAccountController->getAccountModel()->getEmail()),
                               QString::number(applicationAccountController->getAccountModel()->getNumberOfProjects()),
                               "PremiumUser", false);
        Administrator *auxAdmin = new Administrator;
        adminController *auxAdminController = new adminController(auxAdmin, nullptr, nullptr);
        auxAdminController->adminView->hide();
        auxAdminController->adminModel->getUser(applicationAccountController->getAccountModel()->getName(),
                                                applicationAccountController->getAccountModel()->getEmail())->setPremiumUser();

        saveUser->updateAdminInfo(auxAdminController->adminModel->getAccountList());
        delete premiumDialogWindow;
        delete saveUser;
        delete auxAdmin;
        delete auxAdminController;
    }
    else {
        QMessageBox::warning(0, "Wrong Code!", "the code you have entered is not valid");
    }
}

void mainApplication::addUserForAdmin() {
    addUserDialog = new registerForm(nullptr,false);
    addUserDialog->show();
    connect(addUserDialog->getRegButton(), SIGNAL(clicked()), this, SLOT(updateNewUserList()));
}

void mainApplication::updateUserList() {
    applicationAdminController->clearUserRowContainer();
    applicationAdminController->adminModel->clearAccountList();
    applicationAdminController->loadUserList();
    applicationAdminController->loadUserRowList(applicationAdminController->adminModel->getAccountList());
}

void mainApplication::updateNewUserList() {
    applicationAdminController->clearUserRowContainer();
    QVector<std::string> auxUserInfoContainer = addUserDialog->getUserInfo();
    applicationAdminController->adminModel->addUserAccount(new FreeUser(auxUserInfoContainer[0],
                                                                        auxUserInfoContainer[1],
                                                                        auxUserInfoContainer[2], 0));
    applicationAdminController->loadUserRowList(applicationAdminController->adminModel->getAccountList());
    delete addUserDialog;
}
