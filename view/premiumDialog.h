#ifndef CODESEARCH_PREMIUMDIALOG_H
#define CODESEARCH_PREMIUMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class premiumDialog : public QDialog {

    Q_OBJECT

public:
    premiumDialog(QWidget *);
    QPushButton *getPremiumConfirmButton() const;
    QLineEdit *getinsertCodeText() const;

private:
    QLabel *insertCode;
    QLineEdit *insertCodeText;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    //layout
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

};


#endif //CODESEARCH_PREMIUMDIALOG_H
