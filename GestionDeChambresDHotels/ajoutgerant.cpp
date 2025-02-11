#include "ajoutgerant.h"
#include "ui_ajoutgerant.h"
#include "baseDeDonnees.h"
#include "qdebug.h"

ajoutGerant::ajoutGerant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutGerant)
{
    ui->setupUi(this);

   //Ouvrir la connexion à la base de donnée
    Connection conn;
    conn.openbdd();

    //Remplir la liste déroulante avec l id de l hotel
    QSqlQuery query;
    query.prepare("SELECT idHotel, nomHotel FROM hotel");

    //si la requete s'est effectué avec succès
    if(query.exec()){
        //parcours du résultat du requete
        while(query.next()){
            //prendre les valeurs du requete
            QString idHotel = query.value(0).toString(); // recupère l'id de l'hotel
            QString nomHotel = query.value(1).toString();

            //on va concaténer les deux pour l'affichage dans la liste iny
            QString valConcat = QString("%1 - %2").arg(idHotel).arg(nomHotel);// ca sert juste à concaténer les deux
           //Ajouter l'idHotel au liste déroulante
            ui->hotelGerantEdit->addItem(valConcat);

        }
    }else{
        qDebug()<< "Erreur lors de la recupération de l'hotel" << query.lastError().text(); //concaténation en c++
    }
    //fermeture du connexion
    conn.closebdd();


}

ajoutGerant::~ajoutGerant()
{
    delete ui;
}

void ajoutGerant::on_confirmGerantBtn_clicked()
{

        QString username = ui->nomGerantEdit->text();
        QString hotel = ui->hotelGerantEdit->currentText();  // Le nom de l'hôtel sélectionné par l'utilisateur
        QString password = ui->passwordGerantEdit->text();
        QVariant idUser;
        QVariant idHotel;

        Connection conn;
        conn.openbdd();

        if(username.isEmpty() || hotel.isEmpty() || password.isEmpty()){
            qDebug() << "Veuillez remplir tous les champs";
            return;
        }


        //t'as plus besoin de cette étape car les données à prendre sont déjà dans la liste déroulante
        // Première étape : prendre l'idHotel dans la concaténation du liste déroulante

        QStringList hotelList = hotel.split('-'); //c'est pour séparer l'idHotel et le nomHotel

        if(hotelList.size()>0){ // si on a plus d'une caractère après la déconcaténation(idHotel et nomHotel)
            idHotel = hotelList[0].toInt(); //prendre le premier mot avant - (idHotel - nomHotel) du coup on a idHote
        }
        QSqlQuery query;
        // Deuxième requête pour insérer l'utilisateur (gérant) dans la table utilisateurs
        query.prepare("INSERT INTO utilisateurs (username, pasword, role) VALUES (:username, :password, 'gerant')");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'insertion de l'utilisateur : " << query.lastError().text();
            return;
        }

        // Récupérer l'ID de l'utilisateur nouvellement inséré
        idUser = query.lastInsertId();

        if (!idUser.isValid()) {
            qDebug() << "Échec de la récupération de l'ID de l'utilisateur.";
            return;
        }

        // Insertion dans la table gerant avec idUser et idHotel
        query.prepare("INSERT INTO gerant (idUser, idHotel) VALUES (:idUser, :idHotel)");
        query.bindValue(":idUser", idUser);
        query.bindValue(":idHotel", idHotel);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'insertion dans 'gerant' : " << query.lastError().text();
        } else {
            qDebug() << "Gérant ajouté avec succès.";
        }
        conn.closebdd();
        this->close();
    }
