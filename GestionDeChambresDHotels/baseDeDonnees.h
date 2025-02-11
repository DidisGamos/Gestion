#ifndef BASEDEDONNEES_H
#define BASEDEDONNEES_H
#include <QtSql>
#include "qdebug.h"
#include <QSqlError>

    class Connection{
        public:

            QSqlDatabase db;
            void closebdd(){
                db.close();
                db.removeDatabase(QSqlDatabase::defaultConnection);
            }
            bool openbdd(){
                Q_INIT_RESOURCE(ressource);

                closebdd();

                db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName("D:\\QUEREN\\INFORMATIQUE\\PROJETS_ENI24\\GestionDeChambresDHotels\\gestionDeChambres.db");
                if(!db.open()){
                    qDebug()<< "Erreur lors du connection à la base de donnée";
                     qDebug() << "Erreur d'ouverture de la base de données :" << db.lastError().text();
                    return false;
                }else{
                    qDebug()<< "Connection OK";
                    return true;
                }
            }
            bool beginTransaction() {
                if (db.transaction()) {
                    qDebug() << "Transaction started.";
                    return true;
                } else {
                    qDebug() << "Failed to start transaction:" << db.lastError();
                    return false;
                }
            }

            bool commitTransaction() {
                if (db.commit()) {
                    qDebug() << "Transaction committed.";
                    return true;
                } else {
                    qDebug() << "Failed to commit transaction:" << db.lastError();
                    return false;
                }
            }

            void rollbackTransaction() {
                db.rollback();
                qDebug() << "Transaction rolled back.";
            }
    };




#endif // BASEDEDONNEES_H
