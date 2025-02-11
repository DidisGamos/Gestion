#include "client.h"
#include "ui_client.h"
#include "account.h"
#include <QIcon>

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    QIcon icon(":/icon/C:/Users/PC-QUEREN/Downloads/connexion (4).png");  // Charger l'icône
    ui->accountBtn->setIcon(icon);  // Appliquer l'icône au bouton
    ui->accountBtn->setIconSize(QSize(34, 34));  // Ajuster la taille de l'icône
    ui->accountBtn->setText("");



}
client::~client()
{
    delete ui;
}

void client::on_accountBtn_clicked()
{
    this->close();

    account *accountwndow = new account(this);
    accountwndow->show();
}

