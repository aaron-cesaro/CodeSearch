#ifndef CODESEARCH_ADMINFUNCTION_H
#define CODESEARCH_ADMINFUNCTION_H

#include <QMainWindow>
#include "toolbarButton.h"
#include "mainApplication.h"
#include <QToolBar>

class adminFunction: public QMainWindow {

    Q_OBJECT

public:
    adminFunction(const QString &);

protected:
    //startUp tasks
    void createToolbarActions();
    void createToolbar();
    void createSpaceBar();
    void loadSettings();

private:
    mainApplication *adminApp;

    //Toolbar's Action
    QToolBar *mainToolbar;
    toolbarButton *userListToolbarButton;
    QString user;

};


#endif //CODESEARCH_ADMINFUNCTION_H
