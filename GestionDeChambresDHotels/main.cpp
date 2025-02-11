#include "Login.h"
#include "loginn.h"
#include "admin.h"
#include "client.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Loginn w;
    w.show();
    return a.exec();
}

