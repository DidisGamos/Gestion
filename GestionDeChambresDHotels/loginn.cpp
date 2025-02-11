#include "loginn.h"
#include "ui_loginn.h"
#include "login.h"
#include "admin.h"
#include "client.h"
#include "baseDeDonnees.h"
#include "qdebug.h"
#include <QSqlQuery>
#include "qsqlerror.h"

Loginn::Loginn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginn)
{
    ui->setupUi(this);
    ui->usernameConEdit->setPlaceholderText("username");
    ui->passwordConEdit->setPlaceholderText("password");
    ui->usernameError->setVisible(false);
    ui->passwordError->setVisible(false);

}

Loginn::~Loginn()
{
    delete ui;
}

void Loginn::on_connectBtn_clicked()
{
    this->close();

    Login *loginDialog = new Login(this);
    loginDialog->show();
}


void Loginn::on_connBtn_clicked()
{
    Connection con;
       if (!con.openbdd()) {
           qDebug() << "Échec de la connexion à la base de données.";
           return;
       }

       QString username = ui->usernameConEdit->text();
       QString password = ui->passwordConEdit->text();

       if (username.isEmpty() || password.isEmpty()) {
           qDebug() << "Veuillez remplir tous les champs.";
           return;
       }

       // Préparer la requête pour vérifier si l'utilisateur existe et obtenir son rôle
       QSqlQuery query;
       query.prepare("SELECT role FROM utilisateurs WHERE username = :username AND pasword = :pasword");
       query.bindValue(":username", username);
       query.bindValue(":pasword", password);

       if (!query.exec()) {
           qDebug() << "Échec de la requête :" << query.lastError().text();
           return;
       }

       // Si l'utilisateur existe, récupérer son rôle
       if (query.next()) {
           QString role = query.value(0).toString();  // Récupérer le rôle

           // Rediriger en fonction du rôle de l'utilisateur
           if (role == "Admin") {
               qDebug() << "Connexion en tant qu'admin.";
               // Ouvrir la fenêtre Admin
               Admin *adminWindow = new Admin();
               adminWindow->show();
               this->close();  // Fermer la fenêtre de login
           } else if (role == "client") {
               qDebug() << "Connexion en tant que client.";
               // Ouvrir la fenêtre Client
               client *clientWindow = new client();
               clientWindow->show();
               this->close();  // Fermer la fenêtre de login
           } else {
               qDebug() << "Rôle non reconnu : " << role;
           }
       } else {
           qDebug() << "Nom d'utilisateur ou mot de passe incorrect.";
       }

       con.db.close();

       con.db.close();
}

