#ifndef NAVIRE_H
#define NAVIRE_H

#include <QString>

class Navire
{
private:
    QString nom;
    QString immatriculation;
    int capacite;
    QString statut; // "À quai", "En mer", "Interdit"

public:
    Navire();
    Navire(QString nom, QString immat, int cap, QString stat);

    // Getters
    QString getNom() const { return nom; }
    QString getImmatriculation() const { return immatriculation; }
    int getCapacite() const { return capacite; }
    QString getStatut() const { return statut; }

    // Setters
    void setNom(QString n) { nom = n; }
    void setImmatriculation(QString i) { immatriculation = i; }
    void setCapacite(int c) { capacite = c; }
    void setStatut(QString s) { statut = s; }
};

#endif
