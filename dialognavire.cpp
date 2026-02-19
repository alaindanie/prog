#include "dialognavire.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>

DialogNavire::DialogNavire(QWidget *parent, Navire *navire, bool adminMode)
    : QDialog(parent), modeModification(navire != nullptr), modeAdmin(adminMode)
{
    configurerInterface();
    appliquerStyles();

    // Remplir les données si mode modification
    if (modeModification && navire) {
        lineNom->setText(navire->getNom());
        lineImmatriculation->setText(navire->getImmatriculation());
        lineImmatriculation->setReadOnly(true);
        spinCapacite->setValue(navire->getCapacite());
        comboStatut->setCurrentText(navire->getStatut());
    }
}

void DialogNavire::configurerInterface()
{
    if (modeModification) {
        setWindowTitle("⚓ Modifier le Navire");
    } else {
        setWindowTitle("🚢 Ajouter un Navire");
    }

    resize(550, 450);

    // En-tête
    QLabel *enTete = new QLabel(this);
    enTete->setObjectName("enTeteDialog");

    QString texteEnTete = modeModification ? "⚓ Modifier le Navire" : "🚢 Ajouter un Navire";
    QLabel *titreDialog = new QLabel(texteEnTete, enTete);
    titreDialog->setObjectName("titreDialog");
    titreDialog->setAlignment(Qt::AlignCenter);
    titreDialog->setMinimumHeight(80);

    // Formulaire
    QWidget *zoneFormulaire = new QWidget(this);
    zoneFormulaire->setObjectName("zoneFormulaire");

    lineNom = new QLineEdit(this);
    lineNom->setPlaceholderText("Transporteur");
    lineNom->setObjectName("champForm");

    lineImmatriculation = new QLineEdit(this);
    lineImmatriculation->setPlaceholderText("235066595");
    lineImmatriculation->setObjectName("champForm");

    spinCapacite = new QSpinBox(this);
    spinCapacite->setSuffix(" tonnes");
    spinCapacite->setRange(1, 999999);
    spinCapacite->setValue(25);
    spinCapacite->setObjectName("spinForm");

    comboStatut = new QComboBox(this);
    comboStatut->addItems({"À quai", "En mer", "Interdit"});
    comboStatut->setObjectName("comboForm");

    // Layout formulaire
    QFormLayout *formLayout = new QFormLayout(zoneFormulaire);
    formLayout->addRow("Nom:", lineNom);
    formLayout->addRow("Immatriculation:", lineImmatriculation);
    formLayout->addRow("Capacité:", spinCapacite);
    formLayout->addRow("Statut:", comboStatut);
    formLayout->setSpacing(20);
    formLayout->setContentsMargins(40, 30, 40, 30);
    formLayout->setLabelAlignment(Qt::AlignRight);

    // Boutons
    QWidget *zoneBoutons = new QWidget(this);
    zoneBoutons->setObjectName("zoneBoutons");

    btnAnnuler = new QPushButton("Annuler", this);
    btnAnnuler->setObjectName("btnAnnuler");
    btnAnnuler->setCursor(Qt::PointingHandCursor);

    btnEnregistrer = new QPushButton("Enregistrer", this);
    btnEnregistrer->setObjectName("btnEnregistrer");
    btnEnregistrer->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *btnLayout = new QHBoxLayout(zoneBoutons);

    // Si mode admin ET modification, afficher bouton Supprimer
    if (modeAdmin && modeModification) {
        btnSupprimer = new QPushButton("Supprimer", this);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setCursor(Qt::PointingHandCursor);
        btnLayout->addWidget(btnSupprimer);
        connect(btnSupprimer, &QPushButton::clicked, this, &DialogNavire::supprimer);
    }

    btnLayout->addStretch();
    btnLayout->addWidget(btnAnnuler);
    btnLayout->addWidget(btnEnregistrer);
    btnLayout->setContentsMargins(40, 15, 40, 25);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(enTete);
    mainLayout->addWidget(zoneFormulaire);
    mainLayout->addWidget(zoneBoutons);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Connexions
    connect(btnEnregistrer, &QPushButton::clicked, this, &DialogNavire::valider);
    connect(btnAnnuler, &QPushButton::clicked, this, &QDialog::reject);
}

void DialogNavire::valider()
{
    if (lineNom->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom est obligatoire.");
        return;
    }

    if (lineImmatriculation->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'immatriculation est obligatoire.");
        return;
    }

    if (spinCapacite->value() <= 0) {
        QMessageBox::warning(this, "Erreur", "La capacité doit être supérieure à 0.");
        return;
    }

    accept();
}

void DialogNavire::supprimer()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        "Voulez-vous vraiment supprimer ce navire ?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        done(2); // Code 2 = Suppression
    }
}

Navire DialogNavire::getNavire() const
{
    Navire n;
    n.setNom(lineNom->text().trimmed());
    n.setImmatriculation(lineImmatriculation->text().trimmed());
    n.setCapacite(spinCapacite->value());
    n.setStatut(comboStatut->currentText());
    return n;
}

void DialogNavire::appliquerStyles()
{
    QString styles = R"(
        QDialog {
            background-color: #f0f4f8;
        }

        #enTeteDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #2c5282, stop:1 #4299e1);
            min-height: 80px;
        }

        #titreDialog {
            color: white;
            font-size: 24px;
            font-weight: bold;
        }

        #zoneFormulaire {
            background-color: white;
        }

        QLabel {
            color: #2d3748;
            font-size: 15px;
            font-weight: 600;
        }

        #champForm, #spinForm {
            padding: 12px 15px;
            border: 2px solid #cbd5e0;
            border-radius: 8px;
            background-color: white;
            font-size: 14px;
            min-height: 20px;
        }

        #champForm:focus, #spinForm:focus {
            border: 2px solid #4299e1;
        }

        #comboForm {
            padding: 12px 15px;
            border: 2px solid #cbd5e0;
            border-radius: 8px;
            background-color: white;
            font-size: 14px;
            min-height: 45px;
        }

        #comboForm:hover {
            border: 2px solid #4299e1;
        }

        #zoneBoutons {
            background-color: #f7fafc;
            border-top: 2px solid #e2e8f0;
        }

        #btnAnnuler {
            background-color: white;
            color: #4a5568;
            padding: 14px 35px;
            border: 2px solid #cbd5e0;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
            min-width: 130px;
        }

        #btnAnnuler:hover {
            background-color: #f7fafc;
            border: 2px solid #a0aec0;
        }

        #btnEnregistrer {
            background-color: #2c5282;
            color: white;
            padding: 14px 35px;
            border: none;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
            min-width: 130px;
        }

        #btnEnregistrer:hover {
            background-color: #2a4365;
        }

        #btnSupprimer {
            background-color: #c53030;
            color: white;
            padding: 14px 35px;
            border: none;
            border-radius: 8px;
            font-size: 15px;
            font-weight: 600;
            min-width: 130px;
        }

        #btnSupprimer:hover {
            background-color: #9b2c2c;
        }
    )";

    setStyleSheet(styles);
}
