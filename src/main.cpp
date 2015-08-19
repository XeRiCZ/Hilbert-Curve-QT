#include "Curve.h"
#include "HilbertCurve.h"
#include "Drawer.h"
#include "Vector2.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
