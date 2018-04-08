#include "adminFunction.h"

adminFunction::adminFunction(const QString &admin) {

    //set window's design
    setWindowTitle("Code Search");
    setGeometry(400,150,0,0);
    setMinimumSize(1024,699);
    setMaximumSize(1024,699);
    setStyleSheet("background-color:white");

    //create Application
    adminApp = new mainApplication(nullptr, admin);
    setCentralWidget(adminApp);
    adminApp->setStyleSheet("margin-top: 3px");

    //create menu and toolbar
    createToolbarActions();
    createToolbar();

    //create window design
    createSpaceBar();

    //Loading Settings
    loadSettings();
}

/*--------------Private functions--------------*/

void adminFunction::createToolbarActions() {

    //Toolbar's Buttons
    //UserList
    userListToolbarButton = new toolbarButton(tr("User List"), this);
    userListToolbarButton->setShortcut(tr("Ctrl+U"));
    userListToolbarButton->setStyleSheet("background-color: #DCDCDC;"
                                         "padding:10px; "
                                         "border: 1px solid silver; ");
    connect(userListToolbarButton, SIGNAL(clicked()), userListToolbarButton, SLOT(changeSelected()));
}

//add all actions to main toolbar
void adminFunction::createToolbar() {
    mainToolbar = addToolBar("Main");

    mainToolbar->addWidget(userListToolbarButton);
    mainToolbar->setStyleSheet("padding-right: 20px; "
                                       "padding-bottom: 20px; "
                                       "border:none;"
                                       "border-top-left-radius: 10px;"
                                       "border-top-right-radius: 10px;");
    mainToolbar->setMovable(false);
}

void adminFunction::createSpaceBar() {
    QWidget* line = new QWidget(this);
    line->setStyleSheet("background-color: #DCDCDC; "
                                "margin-left:4px; ");
    line->setGeometry(0,45,3000,3);
}

void adminFunction::loadSettings() {

}
