#include "mainWindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QHBoxLayout>

/*--------------Public--------------*/

mainWindow::mainWindow(const QString &userWindow) : user(userWindow){
    //set window's design
    setWindowTitle("Code Search");
    setGeometry(400,150,0,0);
    setMinimumSize(1024,699);
    setMaximumSize(1024,699);
    setStyleSheet("background-color:white");

    //create Application
    mainApp = new mainApplication(nullptr, user);
    setCentralWidget(mainApp);
    mainApp->setStyleSheet("margin-top: 3px");



    //create menu and toolbar
    createToolbarActions();
    createToolbar();

    //create window design
    createSpaceBar();
}

void mainWindow::toNormalStatus() {
    for(auto it = toolbarButtonList.begin(); it != toolbarButtonList.end(); ++it) {
        (*it)->setNormalStatus();
    }
}

/*--------------Private functions--------------*/

void mainWindow::createToolbarActions() {

    //Toolbar's Buttons
    searchToolbarButton = new toolbarButton(tr("Search"), this);
    searchToolbarButton->setStyleSheet("background-color: #DCDCDC;"
                                       "padding:10px; "
                                       "border: 1px solid silver; ");
    searchToolbarButton->setFont(QFont("italic", 14, QFont::StyleNormal));
    searchToolbarButton->setShortcut(tr("Ctrl+R"));
    connect(searchToolbarButton, SIGNAL(clicked()), this, SLOT(toNormalStatus()));
    connect(searchToolbarButton, SIGNAL(clicked()), searchToolbarButton, SLOT(changeSelected()));
    connect(searchToolbarButton, SIGNAL(clicked()), mainApp, SLOT(showSearch()));

    //Upload
    uploadToolbarButton = new toolbarButton(tr("Upload"), this);
    uploadToolbarButton->setShortcut(tr("Ctrl+P"));

    connect(uploadToolbarButton, SIGNAL(clicked()), this, SLOT(toNormalStatus()));
    connect(uploadToolbarButton, SIGNAL(clicked()), uploadToolbarButton, SLOT(changeSelected()));
    QObject::connect(uploadToolbarButton, SIGNAL(clicked()), mainApp, SLOT(showUpload()));

    //Account
    accountToolbarButton = new toolbarButton(tr("Account"), this);
    accountToolbarButton->setShortcut(tr("Ctrl+A"));
    connect(accountToolbarButton, SIGNAL(clicked()), this, SLOT(toNormalStatus()));
    connect(accountToolbarButton, SIGNAL(clicked()), accountToolbarButton, SLOT(changeSelected()));
    QObject::connect(accountToolbarButton, SIGNAL(clicked()), mainApp, SLOT(showAccount()));

    //create premium button
    premiumButton = new QPushButton("Premium", this);
    premiumButton->setStyleSheet("margin-left: 650px;"
                                 "text-decoration: underline;");

    connect(premiumButton, SIGNAL(clicked()), mainApp, SLOT(on_Premium_Button()));

}

//add all actions to main toolbar
void mainWindow::createToolbar() {
    mainToolbar = addToolBar("Main");

    mainToolbar->addWidget(searchToolbarButton);
    //mainToolbar->addWidget(userListToolbarButton);
    mainToolbar->addWidget(uploadToolbarButton);
    mainToolbar->addWidget(accountToolbarButton);

    mainToolbar->addWidget(premiumButton);
    mainToolbar->setStyleSheet("padding-right: 20px; "
                               "padding-bottom: 20px; "
                               "border:none;"
                               "border-top-left-radius: 10px;"
                               "border-top-right-radius: 10px;");
    mainToolbar->setMovable(false);
    //populate toolbar Action List
    toolbarButtonList.push_back(searchToolbarButton);
    //toolbarButtonList.push_back(userListToolbarButton);
    toolbarButtonList.push_back(uploadToolbarButton);
    toolbarButtonList.push_back(accountToolbarButton);
}

void mainWindow::createSpaceBar() {
    QWidget* line = new QWidget(this);
    line->setStyleSheet("background-color: #DCDCDC; "
                        "margin-left:4px; ");
    line->setGeometry(0,45,3000,3);
}

/*--------------Private SLOTS--------------*/

void mainWindow::closeEvent(QCloseEvent *event) {
    int exitButton = QMessageBox::question(this,"Code Search","Are you sure you want to exit?\n",
                                           QMessageBox::No | QMessageBox::Yes,
                                           QMessageBox::Yes);
    if (exitButton == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

QPushButton *mainWindow::getPremiumButton() const {
    return premiumButton;
}
