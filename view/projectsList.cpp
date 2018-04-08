#include "projectsList.h"

#include <QHeaderView>
#include <QPainter>

projectsList::projectsList(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {
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
    tableHeader << "Name" << "Author" << "Language" << "Type" << "License";
    setHorizontalHeaderLabels(tableHeader);

    //set Header Style
    verticalHeader()->hide();
    setColumnWidth(0,300);
    setColumnWidth(1,300);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setSectionsClickable(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);

}

/*--------------Public functions--------------*/
