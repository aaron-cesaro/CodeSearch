#ifndef CODESEARCH_UPLOADFUNCTION_H
#define CODESEARCH_UPLOADFUNCTION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>

#include "saveXml.h"

class uploadFunction : public QWidget {

    Q_OBJECT

public:
    uploadFunction(QWidget * = nullptr);
    void paintEvent(QPaintEvent *) override;
    QVector<QString> setSelectedOptions();
    void setUser(const QString &);
    //buttons
    QPushButton *uploadButton;
    QVector<QString> options;

    QLineEdit *uploadProjectLineEdit;
    QLineEdit *uploadAuthorLineEdit;
    QComboBox *uploadLanguageDropDown;

    QVector<QString> getUploadData();

private:
    //text-edit parameters
    QLabel *uploadNameLabel;
    QLabel *uploadProjectLabel;

    QLabel *uploadAuthorLabel;
    QLabel *uploadSpecifyAuthorLabel;

    //drop-down menus
    QLabel *uploadLanguageLabel;

    //checkboxes
    QLabel *uploadCheckBoxTypeLabel;
    QRadioButton *uploadSystemCheckBox;
    QRadioButton *uploadApplicationCheckBox;
    QRadioButton *uploadLibraryCheckBox;
    QRadioButton *uploadUtilityCheckBox;
    QLabel *uploadCheckBoxLicenseType;
    QRadioButton *uploadFreewareCheckBox;
    QRadioButton *uploadSharewareCheckBox;
    QRadioButton *uploadCopyleftCheckBox;
    QRadioButton *uploadOpenSourceCheckBox;
    QRadioButton *uploadAuthorMe;
    QRadioButton *uploadAuthorOther;
    //user name
    QString user;

};


#endif //CODESEARCH_UPLOADFUNCTION_H
