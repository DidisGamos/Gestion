#include "ajoutadmin.h"
#include "ui_ajoutadmin.h"
#include "baseDeDonnees.h"
#include "qdebug.h"
#include <QMessageBox>

ajoutAdmin::ajoutAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutAdmin)
{
    ui->setupUi(this);
}

ajoutAdmin::~ajoutAdmin()
{
    delete ui;
}

void ajoutAdmin::on_pushButton_2_clicked()
{
    this->close();
}


void ajoutAdmin::on_CancelHotelBtn_clicked()
{
    this->close();
}

void ajoutAdmin::on_conformHotelBtn_clicked()
{
    QString nom = ui->nomHotelEdit->text();
    QString localisation = ui->localisationHotelEdit->text();
    QString etoiles = ui->nbEtoilesEdit->text();

    Connection conn;
    conn.openbdd();


    if(nom == "" || localisation == "" || etoiles == ""){
        qDebug()<< "Veuillez remplir tous les champs";
    }else{
        QSqlQuery query;
        query.prepare("INSERT INTO hotel (nomHotel, localisationHotel, nbEtoiles) VALUES (:nom, :loca, :nbetoiles)");
        query.bindValue(":nom",nom);
        query.bindValue(":loca",localisation);
        query.bindValue(":nbetoiles",etoiles);

        if (query.exec()) {
                    // Confirmation message
                    QMessageBox::information(this, "Confirmation", "L'hôtel a été ajouté avec succès !");
                } else {
                    qDebug() << "Erreur lors de l'ajout de l'hôtel :" << query.lastError().text();
                }
        conn.closebdd();
        ui->nomHotelEdit->setText("");
        ui->localisationHotelEdit->setText("");
        ui->nbEtoilesEdit->setText("");
        this->close();
    }
}

