#ifndef DIALOGNAVIRE_H
#define DIALOGNAVIRE_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include "navire.h"

class DialogNavire : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNavire(QWidget *parent = nullptr, Navire *navire = nullptr, bool adminMode = false);
    Navire getNavire() const;

private slots:
    void valider();
    void supprimer();

private:
    QLineEdit *lineNom;
    QLineEdit *lineImmatriculation;
    QSpinBox *spinCapacite;
    QComboBox *comboStatut;
    QPushButton *btnEnregistrer;
    QPushButton *btnAnnuler;
    QPushButton *btnSupprimer;

    bool modeModification;
    bool modeAdmin;

    void configurerInterface();
    void appliquerStyles();
};

#endif
