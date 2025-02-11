#ifndef AJOUTGERANT_H
#define AJOUTGERANT_H

#include <QDialog>

namespace Ui {
class ajoutGerant;
}

class ajoutGerant : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutGerant(QWidget *parent = nullptr);
    ~ajoutGerant();

private slots:
    void on_confirmGerantBtn_clicked();

private:
    Ui::ajoutGerant *ui;
};

#endif // AJOUTGERANT_H
