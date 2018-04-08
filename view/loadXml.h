#ifndef CODESEARCH_LOADXML_H
#define CODESEARCH_LOADXML_H

#include <QXmlStreamReader>
#include <string>
#include "../model/Account.h"

class loadXml {

public:
    void loadAccountInfo(std::string);
    int loadAdminInfo();
    void loadProjectInfo(std::string);
    QString nameStore;
    QString passwordStore;
    QString emailStore;
    QString numberOfProjectsStore;
    QString accountType;
    QVector<QString> userProjectsInfoList;
    QVector<QString> userList;


private:
    QXmlStreamReader *xmlReader;
    void clearUserList();
};


#endif //CODESEARCH_LOADXML_H
