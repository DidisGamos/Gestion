#include "login.h"
#include "ui_Login.h"
#include "client.h"
#include "baseDeDonnees.h"
#include <QSqlQuery>
#include "qdebug.h"
#include "qsqlerror.h"
#include "loginn.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->usernameEdit->setPlaceholderText("username");
    ui->passwordEdit->setPlaceholderText("password");
    ui->dateEdit->setPlaceholderText("YY-MM-DD");



}

Login::~Login()
{
    delete ui;
}
void Login::on_connectBtn_clicked()
{
    this->close();

      // Ouvrir le dialogue d'inscription
      Loginn *inscriptionDialog = new Loginn(this);
      inscriptionDialog->show();

}

void Login::on_inscBtn_clicked()
{
    Connection con;
      if (!con.openbdd()) return;

      QString username = ui->usernameEdit->text();
      QString password = ui->passwordEdit->text();
      QString dateNaissance = ui->dateEdit->text();

      // Cacher le label d'erreur au démarrage

      if (username.isEmpty() || password.isEmpty() || dateNaissance.isEmpty()) {
          qDebug() << "Veuillez remplir tous les champs ";
          // Cacher le label d'erreur au démarrage


          return;
      }

      // Vérifiez si une transaction est déjà active
      if (con.db.transaction()) {
          qDebug() << "Transaction démarrée.";
      } else {
          qDebug() << "Échec du démarrage de la transaction :" << con.db.lastError();
          return; // Retour anticipé si le démarrage de la transaction échoue
      }

      QSqlQuery query;
      query.prepare("INSERT INTO utilisateurs(username, pasword, role) VALUES (:username, :pasword, 'client');");
      query.bindValue(":username", username);
      query.bindValue(":pasword", password);

      if (query.exec()) {
          int userId = query.lastInsertId().toInt(); // Récupérer le dernier ID inséré

          QSqlQuery q;
          q.prepare("INSERT INTO client(dateNaissance, dateInscription, idUser) VALUES (:datenais, '2023-09-26 ', :idUser);");
          q.bindValue(":datenais", dateNaissance);
          q.bindValue(":idUser", userId);
          if (q.exec()) {
              // Validez si les deux insertions sont réussies
              if (con.db.commit()) {
                  qDebug() << "Les deux insertions ont réussi.";
              } else {
                  qDebug() << "Échec de la validation de la transaction :" << con.db.lastError();
                  con.rollbackTransaction(); // Annulez si la validation échoue
              }
          } else {
              qDebug() << "Échec de la deuxième insertion :" << q.lastError();
              con.rollbackTransaction(); // Annulez si la deuxième insertion échoue
          }
      } else {
          qDebug() << "Échec de la première insertion :" << query.lastError();
          con.rollbackTransaction(); // Annulez si la première insertion échoue
      }
      client *clientWindow = new client();
      clientWindow->show();
      this->close();
}



