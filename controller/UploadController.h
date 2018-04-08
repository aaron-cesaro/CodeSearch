#ifndef CODESEARCH_UPLOADCONTROLLER_H
#define CODESEARCH_UPLOADCONTROLLER_H

#include "../model/Project.h"
#include "../model/Account.h"
#include "../view/uploadFunction.h"
#include "../view/loadXml.h"

class UploadController: public QObject {

    Q_OBJECT

public:
    UploadController(uploadFunction *, AccountController *);
    uploadFunction *setUploadFunctionView();

public slots:
    void on_upload();

private:
    AccountController *userAccountController;
    uploadFunction *uploadFunctionView;
};


#endif //CODESEARCH_UPLOADCONTROLLER_H
