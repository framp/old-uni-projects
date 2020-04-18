#include <QtGui/QApplication>
#include "calculator/calculatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorWindow w;
    w.show();

    return a.exec();
}
