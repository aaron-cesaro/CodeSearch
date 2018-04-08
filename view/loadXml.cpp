#include "loadXml.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

void loadXml::loadAccountInfo(std::string user) {
    xmlReader = new QXmlStreamReader();
    //set output file and path
    //convert std::string to QString
    QString filePath = QString::fromStdString("savedData/usersData/" + user + ".xml");
    QFile *file = new QFile(filePath);

    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0, "Error!", "Error opening file load_account_info_error");
    }
    else {
        xmlReader->setDevice(file);
        xmlReader->readNext();
        //read till the end of the document
        while(!xmlReader->isEndDocument()) {
            //if is a start a start element
            if(xmlReader->isStartElement()) {
                //check if this is the outer element and if it's the case skip it
                if(xmlReader->name() == "Account") {
                    xmlReader->readNext();
                }
                //else if this is the userInfo element read it till the end
                if(xmlReader->name() == "userInfo" || xmlReader->name() == "Projects") {
                    xmlReader->readNext();
                }
                //read user info
                if(xmlReader->name() == "Name") {
                    nameStore = xmlReader->readElementText();
                }
                if(xmlReader->name() == "Password") {
                    passwordStore = xmlReader->readElementText();
                }
                if(xmlReader->name() == "Email") {
                    emailStore = xmlReader->readElementText();
                }
                if(xmlReader->name() == "Uploaded-Projects") {
                    numberOfProjectsStore = xmlReader->readElementText();
                }
                if(xmlReader->name() == "Account-Type") {
                    accountType = xmlReader->readElementText();
                }
            }
            xmlReader->readNext();
        }
        if (xmlReader->hasError()) {
                QMessageBox::warning(0, "XML Error!", "Parsing Error");
        }
    }
}

void loadXml::loadProjectInfo(std::string user) {
    xmlReader = new QXmlStreamReader();
    //set output file and path
    //convert std::string to QString
    QString filePath = QString::fromStdString("savedData/applicationData/" + user + "ProjectList.xml");
    QFile *file = new QFile(filePath);

    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0, "Error!", "Error opening file load_project_info_error");
    }
    else {
        xmlReader->setDevice(file);
        xmlReader->readNext();
        //read till the end of the document
        while(!xmlReader->isEndDocument()) {
            //if is a start a start element
            if(xmlReader->isStartElement()) {
                //else if this is the userInfo element read it till the end
                if(xmlReader->name() == "Projects") {
                    xmlReader->readNext();
                }
                //read Projects info
                if(xmlReader->name() == "Project-Name") {
                    userProjectsInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Author") {
                    userProjectsInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Language") {
                    userProjectsInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Type") {
                    userProjectsInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-License") {
                    userProjectsInfoList.push_back(xmlReader->readElementText());
                }
            }
            xmlReader->readNext();
        }
        if (xmlReader->hasError()) {
            QMessageBox::warning(0, "XML Error!", "Parsing Error");
        }
        file->close();
        delete file;
    }
}

int loadXml::loadAdminInfo() {
    xmlReader = new QXmlStreamReader();
    int i = 0;
    //set output file and path
    //convert std::string to QString
    QString filePath;
    filePath = QString::fromStdString("savedData/adminData/userList.xml");
    QFile *file = new QFile(filePath);

    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0, "Error!", "Error opening file load_admin_error");
    }
    else {
        if(!userList.isEmpty())
            userList.clear();
        xmlReader->setDevice(file);
        xmlReader->readNext();
        //read till the end of the document
        while(!xmlReader->isEndDocument()) {
            //if is a start a start element
            if(xmlReader->isStartElement()) {
                //check if this is the outer element and if it's the case skip it

                //else if this is the userInfo element read it till the end
                if(xmlReader->name() == "User-List" || xmlReader->name() == "userInfo") {
                    xmlReader->readNext();
                }
                //read user info
                if(xmlReader->name() == "Name") {
                    userList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Password") {
                    userList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Email") {
                    userList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Uploaded-Projects") {
                    userList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Account-Type") {
                    userList.push_back(xmlReader->readElementText());
                    i++;
                }
            }
            xmlReader->readNext();
        }
        if (xmlReader->hasError()) {
            QMessageBox::warning(0, "XML Error!", "Parsing Error");
        }
    }
    file->close();
    return i;
}

