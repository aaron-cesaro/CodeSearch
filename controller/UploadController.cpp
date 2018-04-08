#include <QtWidgets/QMessageBox>
#include "UploadController.h"
#include "adminController.h"
#include "../model/PremiumUser.h"
#include "../model/FreeUser.h"
#include <typeinfo>
#include <QDebug>

UploadController::UploadController(uploadFunction *view, AccountController *accountController) :
                                   uploadFunctionView(view), userAccountController(accountController) {
    //create upload view
    uploadFunctionView = new uploadFunction;
    uploadFunctionView->setUser(QString::fromStdString(userAccountController->getAccountModel()->getName()));

    connect(uploadFunctionView->uploadButton, SIGNAL(clicked()), this, SLOT(on_upload()));
}

uploadFunction *UploadController::setUploadFunctionView() {
    return uploadFunctionView;
}

void UploadController::on_upload() {
    Account *userAccount = userAccountController->getAccountModel();
    if(userAccount && ((dynamic_cast<PremiumUser *>(userAccount)) ||
                      (dynamic_cast<FreeUser *>(userAccount) && userAccount->getNumberOfProjects() < 10))) {
        //get project info
        QVector<QString> selectedOptions = uploadFunctionView->getUploadData();
    	if(selectedOptions[0] != "" && selectedOptions[1] != "") {

        	//add project to account project list
        	userAccount->addProject(new Project(selectedOptions[0].toStdString(), selectedOptions[1].toStdString(),
            	                                selectedOptions[2].toStdString(), selectedOptions[3].toStdString(),
            	                                selectedOptions[4].toStdString()));

        	//save new Project to file
        	saveXml *saveUploadedProject = new saveXml;
        	saveUploadedProject->saveNewProjectInfo(selectedOptions[0], selectedOptions[1], selectedOptions[2],
            	                                    selectedOptions[3], selectedOptions[4],
                	                                QString::fromStdString(userAccount->getName()));
        	saveUploadedProject->updateAccountProjects(QString::fromStdString(userAccount->getName()), false);

        	Administrator *auxAdmin = nullptr;
        	adminController *auxAdminController = new adminController(auxAdmin, nullptr, nullptr);
        	auxAdminController->adminView->hide();
        	auxAdminController->adminModel->getUser(userAccount->getName(), userAccount->getEmail())->increaseNumberOfProjects();
        	saveUploadedProject->updateAdminInfo(auxAdminController->adminModel->getAccountList());

        	//clean all
        	delete saveUploadedProject;
        	delete auxAdmin;
        	delete auxAdminController;
        	uploadFunctionView->uploadProjectLineEdit->setText("");
        	uploadFunctionView->uploadAuthorLineEdit->setText("");
       		uploadFunctionView->uploadLanguageDropDown->clearEditText();
    	}
    	else {
    		QMessageBox::warning(0, "Error!", "Please insert a valid project name and author");
    	}
    }
    else {
        QMessageBox::warning(0, "Error!", "Your number of project has been exceeded, Upgrade to Premium to upload more projects");
    }
}
