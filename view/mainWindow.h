#ifndef CODESEARCH_MAINWINDOW_H
#define CODESEARCH_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QToolBar>
#include <QAction>

#include "toolbarButton.h"
#include "mainApplication.h"

class mainWindow : public QMainWindow {

    Q_OBJECT

public:
    mainWindow(const QString & = QString());
    QPushButton *getPremiumButton() const;
    void closeEvent(QCloseEvent *) override;

public slots:
    virtual void toNormalStatus();

protected:
    //startUp tasks
    virtual void createToolbarActions();
    virtual void createToolbar();
    virtual void createSpaceBar();

private:
    //Toolbar's Action
    QToolBar *mainToolbar;
    toolbarButton *searchToolbarButton;
    //toolbarButton *userListToolbarButton;
    toolbarButton *uploadToolbarButton;
    toolbarButton *accountToolbarButton;
    QPushButton *premiumButton;
    QVector<toolbarButton *> toolbarButtonList;
    QString user;
    //main application
    mainApplication *mainApp;

};


#endif //CODESEARCH_MAINWINDOW_H
