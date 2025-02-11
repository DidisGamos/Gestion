#ifndef MAINWINDOWGERANT_H
#define MAINWINDOWGERANT_H

#include <QMainWindow>

namespace Ui {
class MainWindowGerant;
}

class MainWindowGerant : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowGerant(QWidget *parent = nullptr);
    ~MainWindowGerant();

private:
    Ui::MainWindowGerant *ui;
};

#endif // MAINWINDOWGERANT_H
