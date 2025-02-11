#include "admin.h"
#include "ui_admin.h"
#include "qdebug.h"
#include "login.h"
#include "loginn.h"
#include <QPushButton>
#include "baseDeDonnees.h"
#include <QIcon>
#include <QMessageBox>



Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    showHotel();
    ui->rechercheHotelEdit->setPlaceholderText("rechercher");
    ui->rechercheHotelEdit_2->setPlaceholderText("rechercher");
    ui->hotelView->setColumnWidth(0, 30);  // Colonne 'Nom' à 200 pixels
    ui->hotelView->setColumnWidth(1, 150);
    ui->hotelView->setColumnWidth(2, 180);
    ui->hotelView->setColumnWidth(3, 80);
    ui->hotelView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);  // La dernière colonne sera étirée
    ui->hotelView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);  // La dernière colonne sera étirée
    ui->hotelView->setIconSize(QSize(30, 25));  // Taille d'icône 32x32 pixels


}


Admin::~Admin()
{
    delete ui;
}

void Admin::on_ajoutAdminBtn_clicked()
{
    ajout->setModal(true);
    ajout->exec();
    showHotel();
}

void Admin::showHotel(){
    Connection conn;
    conn.openbdd();
    QSqlQuery query;
    int ligne(0);
    query.exec("select count (*) from hotel");
    while(query.next()){
        ligne=query.value(0).toInt();
    }
    query.clear();
    modele = new QStandardItemModel(ligne, 3);
    int row(0);
    query.exec("select * from hotel");
    while(query.next()){
        QStandardItem *editItem = new QStandardItem(QIcon(":/icon/edit"), "");
        modele->setItem(row, 4, editItem);
        QStandardItem *deleteItem = new QStandardItem(QIcon(":/icon/tras"), "");
        modele->setItem(row, 5, deleteItem);

        for(int j=0;j<4;j++){
            QStandardItem *item=new QStandardItem(query.value(j).toString());
            modele->setItem(row,j,item);
        }
        row++;
    }

    modele->setHeaderData(0,Qt::Horizontal,"Identifiant");
    modele->setHeaderData(1,Qt::Horizontal,"Nom");
    modele->setHeaderData(2,Qt::Horizontal,"Localisation");
    modele->setHeaderData(3,Qt::Horizontal,"Etoiles");
    modele->setHeaderData(4,Qt::Horizontal, "Modifier");
    modele->setHeaderData(5,Qt::Horizontal, "Supprimer");

    ui->hotelView->setModel(modele);
    query.clear();
    //QMessageBox::warning(this,"help", QString::number(ligne));
    query.clear();
    conn.closebdd();

}


void Admin::on_hotelView_clicked(const QModelIndex &index)
{

    int rowSelected = index.row();
    id = ui->hotelView->model()->data(ui->hotelView->model()->index(rowSelected,0)).toString();
    nom = ui->hotelView->model()->data(ui->hotelView->model()->index(rowSelected,1)).toString();
    localisation = ui->hotelView->model()->data(ui->hotelView->model()->index(rowSelected,2)).toString();
    etoiles = ui->hotelView->model()->data(ui->hotelView->model()->index(rowSelected,3)).toString();

    //action pour le bouton modifier
    if(index.column()==4){
        modif->setModal(true);
        modif->recupDonnees(this->nom, this->localisation, this->etoiles);
        modif->idHotel = modif->recupId(this->id);
        modif->exec();
    }
    //action pour le bouton supprimer
    else if(index.column()==5){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Confirmation");
        msgBox.setText("Voulez-vous supprimer cet hôtel ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, "Oui");
        msgBox.setButtonText(QMessageBox::No, "Non");

        if (msgBox.exec() == QMessageBox::Yes) {
            Connection con;
            con.openbdd();
            QSqlQuery q;
            q.prepare("DELETE FROM hotel WHERE idHotel=:id");
            q.bindValue(":id", id);
            qDebug() << q.exec();
            qDebug() << q.lastError();
        }

    }
    showHotel();

}


void Admin::on_rechercheHotelEdit_textChanged(const QString &arg1)
{
    Connection conn;
    conn.openbdd();
    QSqlQuery query;
    int ligne(0);

    // Comptage des lignes
    query.exec("SELECT COUNT(*) FROM hotel");
    query.clear();
    if(query.next()){
        ligne = query.value(0).toInt();
    }

    // Correction du nombre de colonnes à 6 (Identifiant, Nom, Localisation, Etoiles, Modifier, Supprimer)
    modele = new QStandardItemModel(ligne, 6);
    int row(0);
    QString requeteprepare;

    // Construction de la requête préparée
    if(ui->rechercheHotelEdit->text().isEmpty()){
        requeteprepare = "SELECT * FROM hotel";
        query.prepare(requeteprepare);
    } else {
        requeteprepare = "SELECT * FROM hotel WHERE idHotel = :idHotel OR nomHotel LIKE :nomHotel";
        query.prepare(requeteprepare);
        query.bindValue(":idHotel", arg1);  // Recherche par idHotel
        query.bindValue(":nomHotel", "%" + arg1 + "%");  // Recherche par nomHotel partiel
    }

    // Exécution de la requête
    if(query.exec()){
        // Remplissage du modèle avec les données de la base de données
        while(query.next()){
            // Colonnes de données (Identifiant, Nom, Localisation, Etoiles)
            for(int j = 0; j < 4; j++){
                QStandardItem *item = new QStandardItem(query.value(j).toString());
                modele->setItem(row, j, item);
            }

            // Colonne Modifier (colonne 4)
            QStandardItem *editItem = new QStandardItem(QIcon(":/icon/edit"), "");
            editItem->setSizeHint(QSize(50, 50));  // Taille personnalisée de l'icône
            modele->setItem(row, 4, editItem);

            // Colonne Supprimer (colonne 5)
            QStandardItem *deleteItem = new QStandardItem(QIcon(":/icon/trash"), "");
            modele->setItem(row, 5, deleteItem);

            row++;
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête: " << query.lastError();
    }

    // Configuration des en-têtes de colonnes
    modele->setHeaderData(0, Qt::Horizontal, "Identifiant");
    modele->setHeaderData(1, Qt::Horizontal, "Nom");
    modele->setHeaderData(2, Qt::Horizontal, "Localisation");
    modele->setHeaderData(3, Qt::Horizontal, "Etoiles");
    modele->setHeaderData(4, Qt::Horizontal, "Modifier");
    modele->setHeaderData(5, Qt::Horizontal, "Supprimer");

    // Affectation du modèle à la vue
    ui->hotelView->setModel(modele);

    // Fermeture de la connexion à la base de données
    query.clear();
    conn.closebdd();
}


    void Admin::on_disconnectAdminBtn_clicked()
    {
        this->close();

        Loginn *loginDialog = new Loginn(this);
        loginDialog->show();
    }


void Admin::on_rechercheHotelEdit_2_textChanged(const QString &arg1)
{
    Connection conn;
    conn.openbdd();
    QSqlQuery query;
    int ligne(0);

    // Comptage des lignes
    query.exec("SELECT COUNT(*) FROM gerant AND hotel");
    if(query.next()){
        ligne = query.value(0).toInt();
    }

    // nombre de colonnes
    modele = new QStandardItemModel(ligne, 6);
    int row(0);
    QString requeteprepare;

    // Construction de la requête préparée
    if(ui->rechercheHotelEdit->text().isEmpty()){
        requeteprepare = "SELECT * FROM gerant";
        query.prepare(requeteprepare);
    } else {
        requeteprepare = "SELECT * FROM gerant WHERE idGerant = :idHotel OR nomHotel LIKE :nomHotel";
        query.prepare(requeteprepare);
        query.bindValue(":idHotel", arg1);  // Recherche par idHotel
        query.bindValue(":nomHotel", "%" + arg1 + "%");  // Recherche par nomHotel partiel
    }

    // Exécution de la requête
    if(query.exec()){
        // Remplissage du modèle avec les données de la base de données
        while(query.next()){
            // Colonnes de données (Identifiant, Nom, Localisation, Etoiles)
            for(int j = 0; j < 4; j++){
                QStandardItem *item = new QStandardItem(query.value(j).toString());
                modele->setItem(row, j, item);
            }

            // Colonne Modifier (colonne 4)
            QStandardItem *editItem = new QStandardItem(QIcon(":/icon/edit"), "");
            editItem->setSizeHint(QSize(50, 50));  // Taille personnalisée de l'icône
            modele->setItem(row, 4, editItem);

            // Colonne Supprimer (colonne 5)
            QStandardItem *deleteItem = new QStandardItem(QIcon(":/icon/trash"), "");
            modele->setItem(row, 5, deleteItem);

            row++;
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête: " << query.lastError();
    }

    // Configuration des en-têtes de colonnes
    modele->setHeaderData(0, Qt::Horizontal, "");
    modele->setHeaderData(1, Qt::Horizontal, "");
    modele->setHeaderData(2, Qt::Horizontal, "");


    // Affectation du modèle à la vue
    ui->hotelView->setModel(modele);

    // Fermeture de la connexion à la base de données
    query.clear();
    conn.closebdd();
}


void Admin::on_ajoutGerantBtn_clicked()
{
    ajoutG->setModal(true);
    ajoutG->exec();
    showHotel();
}

