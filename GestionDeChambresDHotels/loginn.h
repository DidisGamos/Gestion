#ifndef LOGINN_H
#define LOGINN_H

#include <QDialog>

namespace Ui {
class Loginn;
}

class Loginn : public QDialog
{
    Q_OBJECT

public:
    explicit Loginn(QWidget *parent = nullptr);
    ~Loginn();

private slots:
    void on_connectBtn_clicked();

    void on_connBtn_clicked();

private:
    Ui::Loginn *ui;
};

#endif // LOGINN_H
