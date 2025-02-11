#ifndef MODIFHOTEL_H
#define MODIFHOTEL_H

#include <QDialog>

namespace Ui {
class modifHotel;
}

class modifHotel : public QDialog
{
    Q_OBJECT

public:
    explicit modifHotel(QWidget *parent = nullptr);
    ~modifHotel();
    void recupDonnees(QString nom, QString localisation, QString etoiles);
    QString idHotel;
    QString recupId(QString id);

private slots:
    void on_CancelHotelBtn_clicked();

    void on_confirmHotelBtn_clicked();

private:
    Ui::modifHotel *ui;
};

#endif // MODIFHOTEL_H
