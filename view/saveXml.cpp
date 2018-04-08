#include "saveXml.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

void saveXml::saveUserInfo(const QString &name, const QString &psw, const QString &email, const QString &prjUploaded,
                           const QString &type, bool newUser) {
    xmlUserWriter = new QXmlStreamWriter();
    //set output file and path
    //convert std::string to QString
    QString userFilePath = ("savedData/usersData/" + name + ".xml");
    QFile *userFile = new QFile(userFilePath);

    if (!userFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0, "Error!", "Error saving file");
    }
    else {
        xmlUserWriter->setDevice(userFile);
        xmlUserWriter->setAutoFormatting(true);
        xmlUserWriter->writeStartDocument();

        //account Element
        xmlUserWriter->writeStartElement("Account");
        //User info element
        xmlUserWriter->writeStartElement("userInfo");
        xmlUserWriter->writeTextElement("Name", name);
        xmlUserWriter->writeTextElement("Password", psw);
        xmlUserWriter->writeTextElement("Email", email);
        xmlUserWriter->writeTextElement("Uploaded-Projects", prjUploaded);
        xmlUserWriter->writeTextElement("Account-Type", type);
        xmlUserWriter->writeEndElement();
        //end document
        xmlUserWriter->writeEndDocument();
        userFile->close();

        //save user info for admin management
        if(newUser)
            saveAdminInfo(name, psw, email, prjUploaded, type);

    }
    delete userFile;
}

void saveXml::saveNewProjectInfo(const QString &prjName, const QString &prjAuthor,
                                 const QString &prjLang, const QString &prjType,
                                 const QString &prjLicense, const QString &user) {
    xmlUserWriter = new QXmlStreamWriter();
    //set output file and path
    //convert std::string to QString
    QString filePath = QString::fromStdString("savedData/applicationData/" + user.toStdString() + "ProjectList.xml");
    QFile file(filePath);
    if(file.exists())
        loadPrjInfo(user.toStdString());
    prjInfoList.push_back(prjName);
    prjInfoList.push_back(prjAuthor);
    prjInfoList.push_back(prjLang);
    prjInfoList.push_back(prjType);
    prjInfoList.push_back(prjLicense);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0, "Error!", "Error opening file_save_Project");
    }
     {
        xmlUserWriter->setDevice(&file);
        xmlUserWriter->setAutoFormatting(true);
        xmlUserWriter->writeStartDocument();
        xmlUserWriter->writeStartElement("Projects");
        for(auto i = 0; i < prjInfoList.size()/5; ++i) {
            //project element
            xmlUserWriter->writeTextElement("Project-Name", prjInfoList[i*5]);
            xmlUserWriter->writeTextElement("Project-Author", prjInfoList[1 + i*5]);
            xmlUserWriter->writeTextElement("Project-Language", prjInfoList[2 + i*5]);
            xmlUserWriter->writeTextElement("Project-Type", prjInfoList[3 + i*5]);
            xmlUserWriter->writeTextElement("Project-License", prjInfoList[4 + i*5]);
        }

        //end project
        xmlUserWriter->writeEndElement();
        xmlUserWriter->writeEndDocument();
        QMessageBox::information(0, "Success!", "Your project has been uploaded");
        file.close();
    }
}

void saveXml::updateProjectInfo(QVector<projectsListController::projectTableRow *> projectList, const QString &user, bool edit) {
    xmlUserWriter = new QXmlStreamWriter();
    //set output file and path
    QString filePath = QString::fromStdString("savedData/applicationData/" + user.toStdString() + "ProjectList.xml");
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0, "Error!", "Error opening file_save_Project");
    }
    xmlUserWriter->setDevice(&file);
    xmlUserWriter->setAutoFormatting(true);
    xmlUserWriter->writeStartDocument();
    xmlUserWriter->writeStartElement("Projects");
    for(auto i = 0; i < projectList.size(); ++i) {
        //project element
        xmlUserWriter->writeTextElement("Project-Name", projectList[i]->rowName->text());
        xmlUserWriter->writeTextElement("Project-Author", projectList[i]->rowAuthor->text());
        xmlUserWriter->writeTextElement("Project-Language", projectList[i]->rowLanguage->text());
        xmlUserWriter->writeTextElement("Project-Type", projectList[i]->rowType->text());
        xmlUserWriter->writeTextElement("Project-License", projectList[i]->rowLicense->text());
    }
    //end project
    xmlUserWriter->writeEndElement();
    xmlUserWriter->writeEndDocument();
    if(edit) {
        QMessageBox::information(0, "Success!", "Your project has been edited");
    }
    else
        QMessageBox::information(0, "Success!", "Your project has been removed");
    file.close();
}

void saveXml::loadPrjInfo(std::string user) {
    xmlReader = new QXmlStreamReader();
    QString filePath = QString::fromStdString("savedData/applicationData/" + user + "ProjectList.xml");
    QFile *file = new QFile(filePath);

    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0, "Error!", "Error opening file_load_Project");
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
                    prjInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Author") {
                    prjInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Language") {
                    prjInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-Type") {
                    prjInfoList.push_back(xmlReader->readElementText());
                }
                if(xmlReader->name() == "Project-License") {
                    prjInfoList.push_back(xmlReader->readElementText());
                }
            }
            xmlReader->readNext();
        }
        if (xmlReader->hasError()) {
            QMessageBox::warning(0, "XML Error!", "Parsing Error");
        }
    }
}

void saveXml::loadUserInfo(QFile *file) {
    xmlReader = new QXmlStreamReader(file);
    if(file->open(QIODevice::ReadWrite)) {
        //read till the end of the document
        while (!xmlReader->isEndDocument()) {
            //if is a start a start element
            if (xmlReader->isStartElement()) {
                //else if this is the userInfo element read it till the end
                if (xmlReader->name() == "User-List" || xmlReader->name() == "userInfo") {
                    xmlReader->readNext();
                }
                //read Projects info
                if (xmlReader->name() == "Name") {
                    usrInfoList.push_back(xmlReader->readElementText());
                }
                if (xmlReader->name() == "Password") {
                    usrInfoList.push_back(xmlReader->readElementText());
                }
                if (xmlReader->name() == "Email") {
                    usrInfoList.push_back(xmlReader->readElementText());
                }
                if (xmlReader->name() == "Uploaded-Projects") {
                    usrInfoList.push_back(xmlReader->readElementText());
                }
                if (xmlReader->name() == "Account-Type") {
                    usrInfoList.push_back(xmlReader->readElementText());
                }
            }
            xmlReader->readNext();
        }
        if (xmlReader->hasError()) {
            QMessageBox::warning(0, "XML Error!", "Parsing Error");
        }
        file->close();
    }
}

void saveXml::saveAdminInfo(const QString &name, const QString &psw, const QString &email, const QString &prjUploaded, const QString &accountType) {
    //set output file and path
    //convert std::string to QString
    QString userFilePath = ("savedData/adminData/userList.xml");
    QFile *adminFile = new QFile(userFilePath);
    //retrieve info
    loadUserInfo(adminFile);
    QFile *clearFile = new QFile(userFilePath);
    clearFile->remove();
    //insert current new user info
    usrInfoList.push_back(name);
    usrInfoList.push_back(psw);
    usrInfoList.push_back(email);
    usrInfoList.push_back(prjUploaded);
    usrInfoList.push_back(accountType);

    if (!adminFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0, "Error!", "Error saving file");
    }
    else {
        QXmlStreamWriter *xmlAdminWriter = new QXmlStreamWriter(adminFile);
        xmlAdminWriter->setAutoFormatting(true);
        xmlAdminWriter->writeStartDocument();

        //account Element
        xmlAdminWriter->writeStartElement("User-List");
        //User info element
        for (int i = 0; i < usrInfoList.size() / 5; ++i) {
            xmlAdminWriter->writeStartElement("userInfo");
            xmlAdminWriter->writeTextElement("Name", usrInfoList[i * 5]);
            xmlAdminWriter->writeTextElement("Password", usrInfoList[1 + i * 5]);
            xmlAdminWriter->writeTextElement("Email", usrInfoList[2 + i * 5]);
            xmlAdminWriter->writeTextElement("Email", usrInfoList[3 + i * 5]);
            xmlAdminWriter->writeTextElement("Account-Type", usrInfoList[4 + i * 5]);
            xmlAdminWriter->writeEndElement();
        }
        //end document
        xmlAdminWriter->writeEndDocument();
        adminFile->close();
        delete xmlAdminWriter;
    }
    delete adminFile;
    delete clearFile;
}

void saveXml::updateAccountProjects(const QString &name, bool decrease) {
    QString password, email, projectsUploaded, accountType;
    QString userFilePath = ("savedData/usersData/" + name + ".xml");
    QFile *userFile = new QFile(userFilePath);
    xmlReader = new QXmlStreamReader(userFile);

    if(userFile->open(QIODevice::ReadWrite)) {
        //read till the end of the document
        while (!xmlReader->isEndDocument()) {
            //if is a start a start element
            if (xmlReader->isStartElement()) {
                //else if this is the userInfo element read it till the end
                if (xmlReader->name() == "Account" || xmlReader->name() == "userInfo") {
                    xmlReader->readNext();
                }
                //read Projects info
                if (xmlReader->name() == "Password") {
                    password = xmlReader->readElementText();
                }
                if (xmlReader->name() == "Email") {
                    email = xmlReader->readElementText();
                }
                if (xmlReader->name() == "Uploaded-Projects") {
                    projectsUploaded = xmlReader->readElementText();
                    int changeValue = projectsUploaded.toInt();
                    if(decrease)
                        changeValue--;
                    else
                        changeValue++;
                    projectsUploaded = QString::number(changeValue);
                }
                if (xmlReader->name() == "Account-Type") {
                    accountType = xmlReader->readElementText();
                }
            }
            if (xmlReader->hasError()) {
                QMessageBox::warning(0, "XML Error!", "Parsing Error");
            }
            xmlReader->readNext();
        }
        userFile->close();
        delete xmlReader;
        saveUserInfo(name, password, email, projectsUploaded, accountType, false);
    }
}

void saveXml::updateAdminInfo(std::vector<Account *> updatedUserList) {
    QString userFilePath = ("savedData/adminData/userList.xml");
    QFile *clearFile = new QFile(userFilePath);
    clearFile->remove();
    QFile *adminFile = new QFile(userFilePath);

    if (!adminFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0, "Error!", "Error saving file");
    }
    else {
        QXmlStreamWriter *xmlAdminWriter = new QXmlStreamWriter(adminFile);
        xmlAdminWriter->setAutoFormatting(true);
        xmlAdminWriter->writeStartDocument();

        xmlAdminWriter->writeStartElement("User-List");

        //User info element
        for(int i = 0; i < updatedUserList.size(); ++i) {
            xmlAdminWriter->writeStartElement("userInfo");
            xmlAdminWriter->writeTextElement("Name", QString::fromStdString(updatedUserList[i]->getName()));
            xmlAdminWriter->writeTextElement("Password", QString::fromStdString(updatedUserList[i]->getPassword()));
            xmlAdminWriter->writeTextElement("Email", QString::fromStdString(updatedUserList[i]->getEmail()));
            xmlAdminWriter->writeTextElement("Uploaded-Projects", QString::number(updatedUserList[i]->getNumberOfProjects()));
            QString type = "FreeUser";
            if(updatedUserList[i]->isPremiumAccount()) {
                type = "PremiumUser";
            }
            xmlAdminWriter->writeTextElement("Account-Type", type);
            xmlAdminWriter->writeEndElement();
        }
        //end document
        xmlAdminWriter->writeEndDocument();
        adminFile->close();
        delete adminFile;
    }
}

void saveXml::deleteUser(const QString &name) {
    QString userFilePath = ("savedData/usersData/" + name + ".xml");
    QString userProjectFilePath = ("savedData/applicationData/" + name + "ProjectList.xml");
    QFile *userToDelete = new QFile(userFilePath);
    QFile *projectListToDelete = new QFile(userProjectFilePath);
    userToDelete->remove();
    projectListToDelete->remove();
    delete userToDelete;
}
