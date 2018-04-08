#include "searchFunction.h"
#include "mainApplication.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QtWidgets/QMessageBox>

searchFunction::searchFunction(QWidget *parent) : QWidget(parent) {
    //setting style
    setStyleSheet("background-color:#f7f8f8;"
                  "border: 1px solid;"
                  "border-color: silver;"
                  "border-radius: 5px;");
    setMaximumHeight(120);

    //initializing functionality
    searchProjectLabel = new QLabel(tr("Project"));
    searchProjectLabel->setStyleSheet("border: none; ");

    searchProjectLineEdit = new QLineEdit(this);
    searchProjectLineEdit->setStyleSheet("border-radius: none; "
                                         "background-color: white; ");
    searchProjectLabel->setBuddy(searchProjectLineEdit);

    searchAuthorLabel = new QLabel(tr("Author"));
    searchAuthorLabel->setStyleSheet("border: none; "
                                     "margin-left: 1px; ");
    searchAuthorLineEdit = new QLineEdit(this);
    searchAuthorLineEdit->setStyleSheet("border-radius: none;"
                                        "background-color: white; ");
    searchAuthorLabel->setBuddy(searchAuthorLineEdit);

    searchApplicationCheckBox = new QRadioButton(tr("Application"));
    searchApplicationCheckBox->setStyleSheet("border: none; ");
    searchSystemCheckBox = new QRadioButton(tr("System"));
    searchSystemCheckBox->setStyleSheet("border: none; ");
    searchLibraryCheckBox = new QRadioButton(tr("Library"));
    searchLibraryCheckBox->setStyleSheet("border: none; ");
    searchUtilityCheckBox = new QRadioButton(tr("Utility"));
    searchUtilityCheckBox->setStyleSheet("border: none; ");

    searchLanguageLabel = new QLabel(tr("Language"));
    searchLanguageLabel->setStyleSheet("border: none; "
                                       "text-decoration: underline; ");
    searchLanguageDropDown = new QComboBox(this);
    searchLanguageDropDown->setMinimumSize(127,15);
    searchLanguageDropDown->setStyleSheet("border-radius: none; "
                                          "background-color: white; "
                                          "border: 1px solid silver; "
                                          "selection-background-color: LightGrey; "
                                          "selection-color: black; ");
    searchLanguageDropDown->addItem(tr("C++"));
    searchLanguageDropDown->addItem(tr("Java"));
    searchLanguageDropDown->addItem(tr("Python"));
    searchLanguageDropDown->addItem(tr("Scala"));

    searchButton = new QPushButton("Search", this);
    searchButton->setCheckable(true);

    searchButton->setMaximumWidth(100);
    searchButton->setMinimumHeight(30);
    searchButton->setStyleSheet("border: 2px solid silver; "
                                "border-radius: 5px; "
                                "background-color: white; ");
    searchButton->setStyleSheet("QPushButton:pressed { "
                                "border: 2px solid silver; "
                                "border-radius: 5px; "
                                "background-color: white; "
                                "}");
    resetButton = new QPushButton("Reset", this);
    resetButton->setChecked(true);

    resetButton->setMaximumWidth(100);
    resetButton->setMaximumHeight(30);
    resetButton->setStyleSheet("border: 2px solid silver; "
                                        "border-radius: 5px; "
                                        "background-color: white; ");
    resetButton->setStyleSheet("QPushButton:pressed { "
                                        "border: 2px solid silver; "
                                        "border-radius: 5px; "
                                        "background-color: white; "
                                        "}");

    //setting-up Left Layout
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(searchProjectLabel);
    topLeftLayout->addWidget(searchProjectLineEdit);
    topLeftLayout->addSpacing(100);

    QHBoxLayout *LeftCenterLayout = new QHBoxLayout;
    LeftCenterLayout->addWidget(searchAuthorLabel);
    LeftCenterLayout->addWidget(searchAuthorLineEdit);
    LeftCenterLayout->addSpacing(100);


    QVBoxLayout *leftVerticalLayout = new QVBoxLayout;
    leftVerticalLayout->addLayout(topLeftLayout);
    leftVerticalLayout->addLayout(LeftCenterLayout);


    //setting-up Center Layout
    QHBoxLayout *centerLeftLayout = new QHBoxLayout;
    centerLeftLayout->addWidget(searchApplicationCheckBox);
    centerLeftLayout->addWidget(searchSystemCheckBox);

    QHBoxLayout *centerRightLayout = new QHBoxLayout;
    centerRightLayout->addWidget(searchLibraryCheckBox);
    centerRightLayout->addSpacing(27);
    centerRightLayout->addWidget(searchUtilityCheckBox);

    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->addLayout(centerLeftLayout);
    centerLayout->addLayout(centerRightLayout);
    centerLayout->addStretch();
    centerRightLayout->addStretch();
    centerLeftLayout->addStretch();

    //setting-up Right Layout
    QVBoxLayout *rightVerticalLayout = new QVBoxLayout;
    rightVerticalLayout->addWidget(searchLanguageLabel);
    rightVerticalLayout->addWidget(searchLanguageDropDown);
    rightVerticalLayout->addStretch();

    //setting-up main Layout
    QHBoxLayout *mainHorizontalLayout = new QHBoxLayout;
    mainHorizontalLayout->addLayout(leftVerticalLayout);
    mainHorizontalLayout->addLayout(centerLayout);
    mainHorizontalLayout->addLayout(rightVerticalLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(searchButton);
    buttonLayout->addSpacing(-200);
    buttonLayout->addWidget(resetButton);

    QVBoxLayout *mainVerticalLayout = new QVBoxLayout;
    mainVerticalLayout->addLayout(mainHorizontalLayout);
    mainVerticalLayout->addLayout(buttonLayout);
    setLayout(mainVerticalLayout);
}

/*--------------Public--------------*/

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void searchFunction::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void searchFunction::on_search() {
    if(searchProjectLineEdit->text() != "" && searchAuthorLineEdit->text() != "") {
        searchOptions.push_back(searchProjectLineEdit->text());
        searchOptions.push_back(searchAuthorLineEdit->text());
        QString type = "";
        if(searchApplicationCheckBox->isChecked())
            type = searchApplicationCheckBox->text();
        else if(searchLibraryCheckBox->isChecked())
            type = searchLibraryCheckBox->text();
        else if(searchSystemCheckBox->isChecked())
            type = searchSystemCheckBox->text();
        else if(searchUtilityCheckBox->isChecked())
            type = searchUtilityCheckBox->text();
        searchOptions.push_back(type);
        searchOptions.push_back(searchLanguageDropDown->currentText());
    }
    else if(searchProjectLineEdit->text() == "")
        QMessageBox::warning(0, "Error!", "Your forgot to specify the project's name");
    else
        QMessageBox::warning(0, "Error!", "Your forgot to specify the author");
}

QVector<QString> searchFunction::getOptions() {
    return searchOptions;
}
