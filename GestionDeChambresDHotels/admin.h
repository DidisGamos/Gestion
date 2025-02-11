#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "ajoutadmin.h"
#include "ajoutgerant.h"
#include <QStandardItemModel>
#include "modifhotel.h"

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    ajoutAdmin *ajout = new ajoutAdmin();
    modifHotel *modif = new modifHotel();
    ajoutGerant *ajoutG = new ajoutGerant();



private slots:
    void on_ajoutAdminBtn_clicked();
    void showHotel();


    void on_hotelView_clicked(const QModelIndex &index);

    void on_rechercheHotelEdit_textChanged(const QString &arg1);

    void on_disconnectAdminBtn_clicked();

    void on_rechercheHotelEdit_2_textChanged(const QString &arg1);

    void on_ajoutGerantBtn_clicked();

private:
    QString id;
    QString nom;
    QString localisation;
    QString etoiles;

    Ui::Admin *ui;
    QStandardItemModel *modele;

};

#endif // ADMIN_H
