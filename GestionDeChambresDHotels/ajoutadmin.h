#ifndef AJOUTADMIN_H
#define AJOUTADMIN_H

#include <QDialog>

namespace Ui {
class ajoutAdmin;
}

class ajoutAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutAdmin(QWidget *parent = nullptr);
    ~ajoutAdmin();

private slots:
    void on_pushButton_2_clicked();

    void on_CancelHotelBtn_clicked();

    void on_conformHotelBtn_clicked();

private:
    Ui::ajoutAdmin *ui;
};

#endif // AJOUTADMIN_H
