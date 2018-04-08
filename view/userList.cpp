#include "userList.h"

#include <QHeaderView>
#include <QtGui/QPainter>

userList::userList(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {
    //setting Widget style
    setStyleSheet("background-color: white; "
                          "selection-background-color: #ECECEC; "
                          "selection-color: black; "
                          "border-radius: 5px; "
                          "border: none; "
                          "border-color: silver; "
                          "QTableWidget::item:focus{border:none;}");

    //set Header
    QStringList tableHeader;
    tableHeader << "Name" << "Password" << "Email" << "Number of projects" << "Account Type";
    setHorizontalHeaderLabels(tableHeader);

    //set Header Style
    verticalHeader()->hide();
    setColumnWidth(0,250);
    setColumnWidth(1,250);
    setColumnWidth(2,180);
    setColumnWidth(3,180);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setSectionsClickable(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);

}
