#include "toolbarButton.h"
#include "mainWindow.h"

toolbarButton::toolbarButton(const QString &text, QWidget *parent) :
        QPushButton(text, parent), active(false) {
    setFont(QFont("italic", 14, QFont::Normal));
    setStyleSheet("padding:10px; border: none");
}

//-------------Public SLOTS---------------

void toolbarButton::changeSelected() {
    if(!isActive()) {
        setFont(QFont("italic", 14, QFont::StyleNormal));
        setStyleSheet("background-color: #DCDCDC;"
                      "padding:10px; "
                      "border: 1px solid silver;"
                      "border-top-left-radius: 10px;"
                      "border-top-right-radius: 10px; ");
        setActive(true);
    }
}

bool toolbarButton::isActive() {
    return active;
}

void toolbarButton::setActive(bool value) {
    active = value;
}

void toolbarButton::setNormalStatus() {
    setFont(QFont("italic", 14, QFont::StyleNormal));
    setStyleSheet("padding:10px; "
                  "border: none");
    setActive(false);
}




