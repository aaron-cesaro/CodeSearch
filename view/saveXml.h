#ifndef CODESEARCH_SAVEXML_H
#define CODESEARCH_SAVEXML_H

#include <QXmlStreamWriter>
#include <QtCore/QFile>
#include "../controller/projectsListController.h"

class saveXml {

public:
    void saveUserInfo(const QString &, const QString &, const QString &, const QString &, const QString &, bool);
    void loadPrjInfo(std::string);
    void loadUserInfo(QFile *);
    void saveNewProjectInfo(const QString &, const QString &, const QString &, const QString &, const QString &,
                            const QString &);
    void saveAdminInfo(const QString &, const QString &, const QString &, const QString &, const QString &);
    void updateAccountProjects(const QString &, bool);
    void updateProjectInfo(QVector<projectsListController::projectTableRow *>, const QString &, bool = false);
    void updateAdminInfo(std::vector<Account *>);
    void deleteUser(const QString &);

private:
    QXmlStreamWriter *xmlUserWriter;
    QXmlStreamReader *xmlReader;
    QVector<QString> prjInfoList;
    QVector<QString> usrInfoList;

};


#endif //CODESEARCH_SAVEXML_H
