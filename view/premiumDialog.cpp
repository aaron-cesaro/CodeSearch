
#include "premiumDialog.h"

premiumDialog::premiumDialog(QWidget *parent) : QDialog(parent) {
    setGeometry(730,250,280,100);
    setWindowTitle("Go Premium");
    setStyleSheet("background-color:white; ");

    insertCode = new QLabel("Insert Premium code", this);
    insertCodeText = new QLineEdit(this);
    confirmButton = new QPushButton("Confirm",this);
    confirmButton->setMaximumWidth(100);
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setMaximumWidth(100);
    confirmButton->setStyleSheet("width: 50px;");

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addSpacing(80);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(insertCode);
    mainLayout->addWidget(insertCodeText);
    mainLayout->addSpacing(15);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

QPushButton *premiumDialog::getPremiumConfirmButton() const {
    return confirmButton;
}

QLineEdit *premiumDialog::getinsertCodeText() const {
    return insertCodeText;
}
