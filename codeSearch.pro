#-------------------------------------------------
#
# Project created by CLion 2017-05-02T17:25:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codeSearch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES = resources.qrc


SOURCES += main.cpp\
model/Project.cpp\
model/projectContainer.cpp \
model/Account.cpp \
model/FreeUser.cpp \
model/PremiumUser.cpp \
model/Administrator.cpp \
view/mainWindow.cpp \
view/toolbarButton.cpp \
view/mainApplication.cpp \
view/searchFunction.cpp \
view/projectsList.cpp \
view/uploadFunction.cpp \
view/accountFunction.cpp \
view/userListFunction.cpp \
controller/AccountController.cpp \
controller/UploadController.cpp \
view/saveXml.cpp \
view/loadXml.cpp \
controller/projectsListController.cpp \
view/loginWindow.cpp \
view/registerForm.cpp \
view/adminFunction.cpp \
view/userList.cpp \
controller/adminController.cpp \
view/premiumDialog.cpp \


HEADERS  += model/Project.h \
model/projectContainer.h \
model/Account.h \
model/FreeUser.h \
model/PremiumUser.h \
model/Administrator.h \
view/mainWindow.h \
view/toolbarButton.h \
view/mainApplication.h \
view/searchFunction.h \
view/projectsList.h \
view/uploadFunction.h \
view/accountFunction.h \
view/userListFunction.h \
controller/AccountController.h \
controller/UploadController.h \
view/saveXml.h \
view/loadXml.h \
controller/projectsListController.h \
view/loginWindow.h \
view/registerForm.h \
view/adminFunction.h \
view/userList.h \
controller/adminController.h \
view/premiumDialog.h \
