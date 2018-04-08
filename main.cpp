#include <QApplication>
#include "view/loginWindow.h"

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    loginWindow *login = new loginWindow(nullptr);
    app->exec();
    return 0;
}