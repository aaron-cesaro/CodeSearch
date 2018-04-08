#ifndef CODESEARCH_SEARCHFUNCTION_H
#define CODESEARCH_SEARCHFUNCTION_H

#include <QWidget>
#include <QString>
#include <QCheckBox>
#include <QComboBox> //drop-down menu
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>
#include <QtWidgets/QRadioButton>

#include "projectsList.h"

class searchFunction : public QWidget {

    Q_OBJECT

public:
    searchFunction(QWidget * = nullptr);
    void paintEvent(QPaintEvent *) override;
    QVector<QString> getOptions();
    QVector<QString> searchOptions;
    //buttons
    QPushButton *searchButton;
    QPushButton *resetButton;

public slots:
    void on_search();

private:
    //text-edit parameters
    QLabel *searchProjectLabel;
    QLineEdit *searchProjectLineEdit;
    QLabel *searchAuthorLabel;
    QLineEdit *searchAuthorLineEdit;

    //drop-down menus
    QComboBox *searchLanguageDropDown;
    QLabel *searchLanguageLabel;

    //checkboxes
    QRadioButton *searchSystemCheckBox;
    QRadioButton *searchApplicationCheckBox;
    QRadioButton *searchLibraryCheckBox;
    QRadioButton *searchUtilityCheckBox;

};


#endif //CODESEARCH_SEARCHFUNCTION_H
