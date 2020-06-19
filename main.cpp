#include "mainwindow.h"
#include <QApplication>
/*!
 * \brief Wywołanie aplikacji
 *
 * Utworzone automatycznie.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
