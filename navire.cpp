#include "navire.h"

Navire::Navire() : capacite(0) {}

Navire::Navire(QString nom, QString immat, int cap, QString stat)
    : nom(nom), immatriculation(immat), capacite(cap), statut(stat) {}
