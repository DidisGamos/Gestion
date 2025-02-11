#include "account.h"
#include "ui_account.h"
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

account::account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account)
{
    ui->setupUi(this);

    QIcon defaultIcon(":/icon/C:/Users/PC-QUEREN/Downloads/connexion (4).png");  // Remplace par le chemin de ton icône par défaut
        ui->pdpBtn->setIcon(defaultIcon);
        ui->pdpBtn->setIconSize(QSize(100, 100));  // Taille de l'icône par défaut

        // Connecter le bouton pour changer la photo de profil
        connect(ui->pdpBtn, &QPushButton::clicked, this, &account::changeProfilePicture);
}

account::~account()
{
    delete ui;
}
void account::changeProfilePicture()
{
    // Ouvrir une boîte de dialogue pour sélectionner une image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir une photo de profil"), "",
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp);;All Files (*)"));

    // Vérifier si un fichier a été sélectionné
    if (!fileName.isEmpty()) {
        // Charger l'image sélectionnée
        QPixmap profilePic(fileName);

        // Vérifier si l'image est valide
        if (!profilePic.isNull()) {
            // Redimensionner l'image pour qu'elle s'adapte au bouton
            ui->pdpBtn->setIcon(QIcon(profilePic));
            ui->pdpBtn->setIconSize(QSize(100, 100));  // Ajuster la taille de l'image à afficher
        } else {
            // Afficher un message d'erreur si l'image ne peut pas être chargée
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image sélectionnée."));
        }
    }
}
void account::on_pdpBtn_clicked()
{

}

