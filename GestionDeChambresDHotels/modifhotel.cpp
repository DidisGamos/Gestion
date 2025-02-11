#include "modifhotel.h"
#include "ui_modifhotel.h"
#include "baseDeDonnees.h"
#include <QSqlError>

modifHotel::modifHotel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifHotel)
{
    ui->setupUi(this);
}

modifHotel::~modifHotel()
{
    delete ui;

}

void modifHotel::on_CancelHotelBtn_clicked()
{
    this->close();
}

QString modifHotel::recupId(QString id){
    return id;
}

void modifHotel::recupDonnees(QString nom, QString localisation, QString etoiles){
    ui->nomModifHotelEdit->setText(nom);
    ui->localisationModifHotelEdit->setText(localisation);
    ui->nbEtoilesModifEdit->setText(etoiles);

}
void modifHotel::on_confirmHotelBtn_clicked()
{
    Connection conn;
    conn.openbdd();
    QString nom = ui->nomModifHotelEdit->text();
    QString localisation = ui->localisationModifHotelEdit->text();
    QString etoiles = ui->nbEtoilesModifEdit->text();
    qDebug()<< nom+" "+localisation+" "+etoiles+" "+ idHotel;
    if(nom =="" || localisation =="" || etoiles == ""){
        qDebug()<< "Veuillez remplir tous les champs";
    }else{
        QSqlQuery Q;
        Q.prepare("UPDATE hotel SET nomHotel=:nom, localisationHotel=:localisation, nbEtoiles=:etoiles WHERE idHotel=:id");
        Q.bindValue(":nom",nom);
        Q.bindValue(":localisation",localisation);
        Q.bindValue(":etoiles",etoiles);
        Q.bindValue(":id",idHotel);
        qDebug()<<Q.exec();
        qDebug()<<Q.lastError();
        conn.closebdd();
        this->close();

}

}
