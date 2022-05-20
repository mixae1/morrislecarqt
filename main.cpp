#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include "morrislecar.h"

using namespace QtCharts;

int main(int argc, char *argv[])
{

/*

*/
    QApplication a(argc, argv);

    MainWindow window;

    window.create_model();
    window.show();

    return a.exec();
}
