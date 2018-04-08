#ifndef CODESEARCH_TOOLBARACTION_H
#define CODESEARCH_TOOLBARACTION_H

#include <QPushButton>

class toolbarButton : public QPushButton {

    Q_OBJECT

public:
    toolbarButton(const QString &, QWidget *parent = nullptr);
    void setNormalStatus();

public slots:
    void changeSelected();

private:
    QString text;
    bool active;
    bool isActive();
    void setActive(bool value);

};


#endif //CODESEARCH_TOOLBARACTION_H
