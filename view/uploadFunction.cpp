#include "uploadFunction.h"
#include <QString>
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>
#include <QtWidgets/QButtonGroup>

/*--------------Public--------------*/

uploadFunction::uploadFunction(QWidget *parent) : QWidget(parent) {
    setVisible(false);
    setStyleSheet("background-color: #f7f8f8; "
                  "border: 1px solid silver; "
                  "border-radius: 5px");

    //initializing functionality
    uploadNameLabel = new QLabel("Project Info:");
    uploadNameLabel->setStyleSheet("border: none; "
                                   "text-decoration: underline;");

    uploadProjectLabel = new QLabel("Project Name:");
    uploadProjectLabel->setStyleSheet("border: none; ");

    uploadProjectLineEdit = new QLineEdit(this);
    uploadProjectLineEdit->setStyleSheet("border-radius: none; "
                                         "background-color: white; ");
    uploadProjectLabel->setBuddy(uploadProjectLineEdit);

    uploadAuthorLabel = new QLabel("Author:");
    uploadAuthorLabel->setStyleSheet("border: none;"
                                     "text-decoration: underline; ");
    QButtonGroup *groupAuthor = new QButtonGroup(this);
    uploadAuthorMe = new QRadioButton("Me");
    uploadAuthorMe->setStyleSheet("border: none; ");
    uploadAuthorOther = new QRadioButton("Other");
    uploadAuthorOther->setStyleSheet("border: none; ");
    groupAuthor->addButton(uploadAuthorMe);
    groupAuthor->addButton(uploadAuthorOther);

    uploadSpecifyAuthorLabel = new QLabel("Author Name:");
    uploadSpecifyAuthorLabel->setStyleSheet("border: none; ");
    uploadAuthorLineEdit = new QLineEdit(this);
    uploadAuthorLineEdit->setEnabled(false);
    uploadAuthorLineEdit->setStyleSheet("border-radius: none; "
                                        "background-color: white; ");
    uploadAuthorLabel->setBuddy(uploadAuthorLineEdit);

    //if other is checked it is possible to enter the author name
    connect(uploadAuthorOther, SIGNAL(toggled(bool)), uploadAuthorLineEdit, SLOT(setEnabled(bool)));

    QButtonGroup *groupType = new QButtonGroup(this);
    uploadCheckBoxTypeLabel = new QLabel("Project Type:");
    uploadCheckBoxTypeLabel->setStyleSheet("border: none; "
                                           "text-decoration: underline; ");
    uploadApplicationCheckBox = new QRadioButton("Application");
    uploadApplicationCheckBox->setStyleSheet("border: none; ");
    uploadSystemCheckBox = new QRadioButton("System");
    uploadSystemCheckBox->setStyleSheet("border: none; ");
    uploadLibraryCheckBox = new QRadioButton("Library");
    uploadLibraryCheckBox->setStyleSheet("border: none; ");
    uploadUtilityCheckBox = new QRadioButton("Utility");
    uploadUtilityCheckBox->setStyleSheet("border: none; ");
    groupType->addButton(uploadApplicationCheckBox);
    groupType->addButton(uploadSystemCheckBox);
    groupType->addButton(uploadLibraryCheckBox);
    groupType->addButton(uploadUtilityCheckBox);

    QButtonGroup *groupLicense = new QButtonGroup(this);
    uploadCheckBoxLicenseType = new QLabel("License");
    uploadCheckBoxLicenseType->setStyleSheet("border: none; "
                                             "text-decoration: underline; ");
    uploadFreewareCheckBox = new QRadioButton("FreeWare");
    uploadFreewareCheckBox->setStyleSheet("border: none; ");
    uploadSharewareCheckBox = new QRadioButton("ShareWare");
    uploadSharewareCheckBox->setStyleSheet("border: none; ");
    uploadCopyleftCheckBox = new QRadioButton("Copy-Left");
    uploadCopyleftCheckBox->setStyleSheet("border: none; ");
    uploadOpenSourceCheckBox = new QRadioButton("Open-Source");
    uploadOpenSourceCheckBox->setStyleSheet("border: none; ");
    groupLicense->addButton(uploadFreewareCheckBox);
    groupLicense->addButton(uploadSharewareCheckBox);
    groupLicense->addButton(uploadCopyleftCheckBox);
    groupLicense->addButton(uploadOpenSourceCheckBox);

    uploadLanguageLabel = new QLabel("Project Language:");
    uploadLanguageLabel->setStyleSheet("border: none;"
                                       "text-decoration: underline; ");
    uploadLanguageDropDown = new QComboBox(this);
    uploadLanguageDropDown->setStyleSheet("border-radius: none; "
                                            "width: 100px; "
                                            "selection-background-color: LightGrey; "
                                            "selection-color: black; ");
    uploadLanguageDropDown->setMaximumWidth(127);
    uploadLanguageDropDown->addItem("C++");
    uploadLanguageDropDown->addItem("Java");
    uploadLanguageDropDown->addItem("Python");
    uploadLanguageDropDown->addItem("Scala");

    uploadButton = new QPushButton("Upload");
    uploadButton->setMinimumHeight(50);
    uploadButton->setMaximumWidth(100);
    uploadButton->setCheckable(true);
    uploadButton->setStyleSheet("QPushButton {"
                                "background-color: white; "
                                "}");
    uploadButton->setStyleSheet("QPushButton:pressed {"
                                "background-color: #FFFFFF; "
                                "border: 2px solid #DCDCDC"
                                "}");

    //setting-up top Layout
    QHBoxLayout *topFirstUploadLayout = new QHBoxLayout;
    topFirstUploadLayout->addWidget(uploadProjectLabel);
    topFirstUploadLayout->addWidget(uploadProjectLineEdit);
    topFirstUploadLayout->addSpacing(150);

    QHBoxLayout *topSecondUploadLayout = new QHBoxLayout;
    topSecondUploadLayout->addWidget(uploadAuthorMe);
    topSecondUploadLayout->addSpacing(-880);
    topSecondUploadLayout->addWidget(uploadAuthorOther);

    QHBoxLayout *topThirdUploadLayout = new QHBoxLayout;
    topThirdUploadLayout->addWidget(uploadSpecifyAuthorLabel);
    topThirdUploadLayout->addWidget(uploadAuthorLineEdit);
    topThirdUploadLayout->addSpacing(150);

    QVBoxLayout *topVerticalUploadLayout = new QVBoxLayout;
    topVerticalUploadLayout->addLayout(topFirstUploadLayout);
    topVerticalUploadLayout->addSpacing(10);
    topVerticalUploadLayout->addWidget(uploadAuthorLabel);
    topVerticalUploadLayout->addLayout(topSecondUploadLayout);
    topVerticalUploadLayout->addSpacing(10);
    topVerticalUploadLayout->addLayout(topThirdUploadLayout);


    //setting-up Center Layout
    QHBoxLayout *centerLeftFirstUploadLayout = new QHBoxLayout;
    centerLeftFirstUploadLayout->addWidget(uploadApplicationCheckBox);
    centerLeftFirstUploadLayout->addWidget(uploadSystemCheckBox);

    QHBoxLayout *centerLeftSecondUploadLayout = new QHBoxLayout;
    centerLeftSecondUploadLayout->addWidget(uploadLibraryCheckBox);
    centerLeftSecondUploadLayout->addSpacing(27);
    centerLeftSecondUploadLayout->addWidget(uploadUtilityCheckBox);

    QHBoxLayout *centerRightFirstUploadLayout = new QHBoxLayout;
    centerRightFirstUploadLayout->addWidget(uploadFreewareCheckBox);
    centerRightFirstUploadLayout->addWidget(uploadSharewareCheckBox);

    QHBoxLayout *centerRightSecondUploadLayout = new QHBoxLayout;
    centerRightSecondUploadLayout->addWidget(uploadCopyleftCheckBox);
    centerRightSecondUploadLayout->addSpacing(21);
    centerRightSecondUploadLayout->addWidget(uploadOpenSourceCheckBox);

    QVBoxLayout *centerVerticalLeftUploadLayout = new QVBoxLayout;

    centerVerticalLeftUploadLayout->addLayout(centerLeftFirstUploadLayout);
    centerVerticalLeftUploadLayout->addLayout(centerLeftSecondUploadLayout);
    centerLeftSecondUploadLayout->addStretch();
    centerLeftFirstUploadLayout->addStretch();

    QVBoxLayout *centerVerticalRightUploadLayout = new QVBoxLayout;

    centerVerticalRightUploadLayout->addLayout(centerRightFirstUploadLayout);
    centerVerticalRightUploadLayout->addLayout(centerRightSecondUploadLayout);
    centerLeftSecondUploadLayout->addStretch();
    centerLeftFirstUploadLayout->addStretch();

    QHBoxLayout *uploadCenterLayout = new QHBoxLayout;
    uploadCenterLayout->addLayout(centerVerticalLeftUploadLayout);
    uploadCenterLayout->addLayout(centerVerticalRightUploadLayout);
    uploadCenterLayout->addStretch();

    QHBoxLayout *uploadCenterLabelLayout = new QHBoxLayout;
    uploadCenterLabelLayout->addWidget(uploadCheckBoxTypeLabel);
    uploadCenterLabelLayout->addSpacing(-230);
    uploadCenterLabelLayout->addWidget(uploadCheckBoxLicenseType);

    //setting-up bottom Layout
    QVBoxLayout *bottomVerticalUploadLayout = new QVBoxLayout;
    bottomVerticalUploadLayout->addWidget(uploadLanguageLabel);
    bottomVerticalUploadLayout->addSpacing(5);
    bottomVerticalUploadLayout->addWidget(uploadLanguageDropDown);
    bottomVerticalUploadLayout->addStretch();

    QHBoxLayout *bottomUploadButtonLayout = new QHBoxLayout;
    bottomUploadButtonLayout->addWidget(uploadButton);

    //setting-up main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //adding top label layout
    mainLayout->addWidget(uploadNameLabel);
    //adding top layout
    mainLayout->addLayout(topVerticalUploadLayout);
    mainLayout->addSpacing(25);
    //Adding center label layout
    mainLayout->addLayout(uploadCenterLabelLayout);
    //adding center layout
    mainLayout->addLayout(uploadCenterLayout);
    mainLayout->addSpacing(25);
    //adding bottom layout
    mainLayout->addLayout(bottomVerticalUploadLayout);
    mainLayout->addLayout(bottomUploadButtonLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

//this solve the hidden visibility problem with QObject-QWidget derivative classes
void uploadFunction::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QVector<QString> uploadFunction::getUploadData() {
    QString type, license, language;
    if(uploadApplicationCheckBox->isChecked()) {
        type = uploadApplicationCheckBox->text();
        uploadApplicationCheckBox->setChecked(false);
    }
    else if(uploadSystemCheckBox->isChecked()) {
        type = uploadSystemCheckBox->text();
        uploadSystemCheckBox->setChecked(false);
    }
    else if(uploadLibraryCheckBox->isChecked()) {
        type = uploadLibraryCheckBox->text();
        uploadLibraryCheckBox->setChecked(false);
    }
    else {
        type = uploadUtilityCheckBox->text();
        uploadUtilityCheckBox->setChecked(false);
    }
    if(uploadFreewareCheckBox->isChecked()) {
        license = uploadFreewareCheckBox->text();
        uploadFreewareCheckBox->setChecked(false);
    }
    else if(uploadSharewareCheckBox->isChecked()) {
        license = uploadSharewareCheckBox->text();
        uploadSharewareCheckBox->setChecked(false);
    }
    else if(uploadCopyleftCheckBox->isChecked()) {
        license = uploadCopyleftCheckBox->text();
        uploadCopyleftCheckBox->setChecked(false);
    }
    else {
        license = uploadOpenSourceCheckBox->text();
        uploadOpenSourceCheckBox->setChecked(false);
    }

    QVector<QString> options;
    options.push_back(uploadProjectLineEdit->text());
    if(uploadAuthorMe->isChecked()) {
        options.push_back(user);
    }
    else {
        options.push_back(uploadAuthorLineEdit->text());
    }
    options.push_back(uploadLanguageDropDown->currentText());
    options.push_back(type);
    options.push_back(license);

    return options;
}

QVector<QString> uploadFunction::setSelectedOptions() {
    QVector<QString> auxVector;
    auxVector = options;
    options.clear();
    return auxVector;
}

void uploadFunction::setUser(const QString &usr) {
    user = usr;
}

