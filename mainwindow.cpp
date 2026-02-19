#include "mainwindow.h"
#include "dialognavire.h" // Correction du nom de fichier
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QFrame>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    listeNavires.append(Navire("Transporteur", "2765987658", 291, "À quai"));
    listeNavires.append(Navire("Neptune", "123456789", 291, "En mer"));
    listeNavires.append(Navire("Atlantis", "589543217", 291, "En mer"));
    listeNavires.append(Navire("Falboot", "n/auteur", 291, "Interdit"));

    configurerInterface();
    appliquerStyles();
}

MainWindow::~MainWindow() {}

void MainWindow::configurerInterface()
{
    setWindowTitle("Fishtech ");
    resize(1400, 850);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    menuLateral = new QFrame(this);
    menuLateral->setObjectName("menuLateral");
    menuLateral->setFixedWidth(240);

    QWidget *enTeteMenu = new QWidget(menuLateral);
    enTeteMenu->setObjectName("enTeteMenu");


    QLabel *nomApp = new QLabel("Fishtech", enTeteMenu);
    nomApp->setObjectName("nomAppMenu");

    QHBoxLayout *logoLayout = new QHBoxLayout(enTeteMenu);
    logoLayout->addWidget(nomApp);
    logoLayout->addStretch();
    logoLayout->setContentsMargins(15, 20, 15, 20);
    logoLayout->setSpacing(10);

    btnTableauBord = new QPushButton("Tableau de bord", menuLateral);
    btnGestionNavires = new QPushButton("Navires", menuLateral);
    QPushButton *btnStats = new QPushButton("Statistiques", menuLateral);
    QPushButton *btnParams = new QPushButton("Parametres", menuLateral);

    btnTableauBord->setObjectName("btnMenu");
    btnGestionNavires->setObjectName("btnMenu");
    btnStats->setObjectName("btnMenu");
    btnParams->setObjectName("btnMenu");

    btnTableauBord->setCursor(Qt::PointingHandCursor);
    btnGestionNavires->setCursor(Qt::PointingHandCursor);
    btnStats->setCursor(Qt::PointingHandCursor);
    btnParams->setCursor(Qt::PointingHandCursor);

    btnTableauBord->setMinimumHeight(45);
    btnGestionNavires->setMinimumHeight(45);
    btnStats->setMinimumHeight(45);
    btnParams->setMinimumHeight(45);

    QWidget *footerMenu = new QWidget(menuLateral);
    footerMenu->setObjectName("footerMenu");

    QLabel *avatar = new QLabel("User", footerMenu);
    avatar->setObjectName("avatar");


    QVBoxLayout *footerLayout = new QVBoxLayout(footerMenu);
    footerLayout->addWidget(avatar, 0, Qt::AlignCenter);
    footerLayout->setSpacing(5);
    footerLayout->setContentsMargins(15, 15, 15, 15);

    QVBoxLayout *menuLayout = new QVBoxLayout(menuLateral);
    menuLayout->addWidget(enTeteMenu);
    menuLayout->addSpacing(20);
    menuLayout->addWidget(btnTableauBord);
    menuLayout->addWidget(btnGestionNavires);
    menuLayout->addWidget(btnStats);
    menuLayout->addWidget(btnParams);
    menuLayout->addStretch();
    menuLayout->addWidget(footerMenu);
    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(2);

    stackedWidget = new QStackedWidget(this);

    configurerTableauBord();
    configurerGestionNavires();

    stackedWidget->addWidget(pageTableauBord);
    stackedWidget->addWidget(pageGestionNavires);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(menuLateral);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    connect(btnTableauBord, &QPushButton::clicked, this, &MainWindow::afficherTableauBord);
    connect(btnGestionNavires, &QPushButton::clicked, this, &MainWindow::afficherGestionNavires);

    afficherTableauBord();
}

void MainWindow::configurerTableauBord()
{
    pageTableauBord = new QWidget(this);
    pageTableauBord->setObjectName("pageTableauBord");

    QWidget *enTete = new QWidget(pageTableauBord);
    enTete->setObjectName("enTetePage");

    QLabel *titre = new QLabel("Tableau de Bord", enTete);
    titre->setObjectName("titrePage");

    QLabel *notif = new QLabel("Bell", enTete);
    notif->setObjectName("iconNotif");

    QLabel *avatarUser = new QLabel("User", enTete);
    avatarUser->setObjectName("avatarUser");


    QHBoxLayout *enTeteLayout = new QHBoxLayout(enTete);
    enTeteLayout->addWidget(titre);
    enTeteLayout->addStretch();
    enTeteLayout->addWidget(notif);
    enTeteLayout->addSpacing(15);
    enTeteLayout->addWidget(avatarUser);
    enTeteLayout->setContentsMargins(0, 0, 0, 20);

    QFrame *carteTotal = creerCarteStatistique("Total Navires", "0", "Ship", "#4a7ba7");
    QFrame *carteQuai = creerCarteStatistique("A Quai", "0", "Anchor", "#f59e0b");
    QFrame *carteMer = creerCarteStatistique("En Mer", "0", "Wave", "#10b981");
    QFrame *carteInterdit = creerCarteStatistique("Interdit", "0", "Stop", "#ef4444");

    labelNbTotal = carteTotal->findChild<QLabel*>("valeurStat");
    labelNbQuai = carteQuai->findChild<QLabel*>("valeurStat");
    labelNbMer = carteMer->findChild<QLabel*>("valeurStat");
    labelNbInterdit = carteInterdit->findChild<QLabel*>("valeurStat");

    QHBoxLayout *cartesLayout = new QHBoxLayout;
    cartesLayout->addWidget(carteTotal);
    cartesLayout->addWidget(carteQuai);
    cartesLayout->addWidget(carteMer);
    cartesLayout->addWidget(carteInterdit);
    cartesLayout->setSpacing(20);

    QWidget *zoneActions = new QWidget(pageTableauBord);

    QLineEdit *lineRecherche = new QLineEdit(zoneActions);
    lineRecherche->setPlaceholderText("Rechercher...");
    lineRecherche->setObjectName("champRecherche");
    lineRecherche->setFixedWidth(350);
    lineRechercheAdmin = lineRecherche;

    QPushButton *btnDropdown = new QPushButton("V", zoneActions);
    btnDropdown->setObjectName("btnDropdown");
    btnDropdown->setFixedSize(40, 40);

    btnModifierAdmin = new QPushButton("Modifier", zoneActions);
    btnSupprimerAdmin = new QPushButton("Supprimer", zoneActions);

    btnModifierAdmin->setObjectName("btnModifier");
    btnSupprimerAdmin->setObjectName("btnSupprimer");
    btnModifierAdmin->setCursor(Qt::PointingHandCursor);
    btnSupprimerAdmin->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *actionsLayout = new QHBoxLayout(zoneActions);
    actionsLayout->addWidget(lineRecherche);
    actionsLayout->addWidget(btnDropdown);
    actionsLayout->addStretch();
    actionsLayout->addWidget(btnModifierAdmin);
    actionsLayout->addWidget(btnSupprimerAdmin);
    actionsLayout->setSpacing(10);
    actionsLayout->setContentsMargins(0, 20, 0, 15);

    tableNaviresAdmin = new QTableWidget(pageTableauBord);
    tableNaviresAdmin->setObjectName("tableAdmin");
    tableNaviresAdmin->setColumnCount(4);
    tableNaviresAdmin->setHorizontalHeaderLabels({"Nom", "Immatriculation", "Capacite", "Statut"});

    tableNaviresAdmin->setColumnWidth(0, 350);
    tableNaviresAdmin->setColumnWidth(1, 300);
    tableNaviresAdmin->setColumnWidth(2, 200);
    tableNaviresAdmin->setColumnWidth(3, 200);

    tableNaviresAdmin->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableNaviresAdmin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableNaviresAdmin->setAlternatingRowColors(false);
    tableNaviresAdmin->horizontalHeader()->setStretchLastSection(true);
    tableNaviresAdmin->verticalHeader()->setVisible(false);
    tableNaviresAdmin->setShowGrid(false);

    QVBoxLayout *layoutTDB = new QVBoxLayout(pageTableauBord);
    layoutTDB->addWidget(enTete);
    layoutTDB->addLayout(cartesLayout);
    layoutTDB->addWidget(zoneActions);
    layoutTDB->addWidget(tableNaviresAdmin);
    layoutTDB->setContentsMargins(35, 25, 35, 25);
    layoutTDB->setSpacing(0);

    connect(btnModifierAdmin, &QPushButton::clicked, this, &MainWindow::modifierNavireAdmin);
    connect(btnSupprimerAdmin, &QPushButton::clicked, this, &MainWindow::supprimerNavireAdmin);
    connect(lineRechercheAdmin, &QLineEdit::textChanged, this, &MainWindow::rechercherNavire);
}

void MainWindow::configurerGestionNavires()
{
    pageGestionNavires = new QWidget(this);
    pageGestionNavires->setObjectName("pageClient");

    QWidget *enTete = new QWidget(pageGestionNavires);

    QLabel *titre = new QLabel("Gestion des Navires");
    titre->setObjectName("titrePage");

    QLabel *sousTitre = new QLabel("Ajout de navire");
    sousTitre->setObjectName("sousTitrePage");

    QLabel *avatarUser = new QLabel("Admin");
    avatarUser->setObjectName("avatarUserClient");

    QVBoxLayout *titresLayout = new QVBoxLayout;
    titresLayout->addWidget(titre);
    titresLayout->addWidget(sousTitre);
    titresLayout->setSpacing(4);

    QHBoxLayout *enTeteLayout = new QHBoxLayout(enTete);
    enTeteLayout->addLayout(titresLayout);
    enTeteLayout->addStretch();
    enTeteLayout->addWidget(avatarUser);
    enTeteLayout->setContentsMargins(0, 0, 0, 30);

    QFrame *carte = new QFrame();
    carte->setObjectName("carteFormulaire");
    carte->setMaximumWidth(600);

    QLabel *titreFormulaire = new QLabel("Ajouter un Navire");
    titreFormulaire->setObjectName("titreFormulaire");
    titreFormulaire->setAlignment(Qt::AlignCenter);

    QLabel *labelNom = new QLabel("Nom du navire");
    labelNom->setObjectName("labelChamp");

    champNomNavire = new QLineEdit();
    champNomNavire->setObjectName("champFormulaire");
    champNomNavire->setPlaceholderText("");
    champNomNavire->setMinimumHeight(45);

    QLabel *labelImmat = new QLabel("Immatriculation");
    labelImmat->setObjectName("labelChamp");

    champImmatNavire = new QLineEdit();
    champImmatNavire->setObjectName("champFormulaire");
    champImmatNavire->setPlaceholderText("");
    champImmatNavire->setMinimumHeight(45);

    QLabel *labelCapacite = new QLabel("Capacite (t)");
    labelCapacite->setObjectName("labelChamp");

    comboCapaciteNavire = new QComboBox();
    comboCapaciteNavire->setObjectName("comboFormulaire");
    comboCapaciteNavire->addItem("50");
    comboCapaciteNavire->addItem("100");
    comboCapaciteNavire->addItem("150");
    comboCapaciteNavire->addItem("200");
    comboCapaciteNavire->addItem("250");
    comboCapaciteNavire->addItem("291");
    comboCapaciteNavire->addItem("300");
    comboCapaciteNavire->setMinimumHeight(45);

    QLabel *labelStatut = new QLabel("Selectionnez le statut");
    labelStatut->setObjectName("labelChamp");

    comboStatutNavire = new QComboBox();
    comboStatutNavire->setObjectName("comboFormulaire");
    comboStatutNavire->addItem("A quai");
    comboStatutNavire->addItem("En mer");
    comboStatutNavire->addItem("Interdit");
    comboStatutNavire->setMinimumHeight(45);

    btnAjouterClient = new QPushButton("Ajouter le navire");
    btnAjouterClient->setObjectName("btnAjouterFormulaire");
    btnAjouterClient->setCursor(Qt::PointingHandCursor);
    btnAjouterClient->setMinimumHeight(50);

    QVBoxLayout *layoutFormulaire = new QVBoxLayout(carte);
    layoutFormulaire->addWidget(titreFormulaire);
    layoutFormulaire->addSpacing(30);
    layoutFormulaire->addWidget(labelNom);
    layoutFormulaire->addWidget(champNomNavire);
    layoutFormulaire->addSpacing(15);
    layoutFormulaire->addWidget(labelImmat);
    layoutFormulaire->addWidget(champImmatNavire);
    layoutFormulaire->addSpacing(15);
    layoutFormulaire->addWidget(labelCapacite);
    layoutFormulaire->addWidget(comboCapaciteNavire);
    layoutFormulaire->addSpacing(15);
    layoutFormulaire->addWidget(labelStatut);
    layoutFormulaire->addWidget(comboStatutNavire);
    layoutFormulaire->addSpacing(30);
    layoutFormulaire->addWidget(btnAjouterClient);
    layoutFormulaire->setContentsMargins(40, 35, 40, 40);

    QHBoxLayout *centreLayout = new QHBoxLayout();
    centreLayout->addStretch();
    centreLayout->addWidget(carte);
    centreLayout->addStretch();

    QVBoxLayout *layoutClient = new QVBoxLayout(pageGestionNavires);
    layoutClient->addWidget(enTete);
    layoutClient->addLayout(centreLayout);
    layoutClient->addStretch();
    layoutClient->setContentsMargins(35, 25, 35, 25);

    connect(btnAjouterClient, &QPushButton::clicked, this, &MainWindow::ajouterNavireClient);
}

QFrame* MainWindow::creerCarteStatistique(QString titre, QString valeur, QString icone, QString couleur)
{
    QFrame *carte = new QFrame();
    carte->setObjectName("carteStat");
    carte->setMinimumHeight(140);

    QLabel *labelIcone = new QLabel(icone);
    labelIcone->setObjectName("iconeCarte");

    QLabel *labelValeur = new QLabel(valeur);
    labelValeur->setObjectName("valeurStat");
    labelValeur->setStyleSheet("color: " + couleur + ";");

    QLabel *labelTitre = new QLabel(titre);
    labelTitre->setObjectName("titreCarte");

    QVBoxLayout *layout = new QVBoxLayout(carte);
    layout->addWidget(labelIcone, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(labelValeur, 0, Qt::AlignCenter);
    layout->addWidget(labelTitre, 0, Qt::AlignCenter);
    layout->setContentsMargins(20, 20, 20, 20);

    return carte;
}

void MainWindow::afficherTableauBord()
{
    mettreAJourStatistiques();
    chargerNaviresAdmin();
    stackedWidget->setCurrentWidget(pageTableauBord);

    btnTableauBord->setProperty("actif", true);
    btnGestionNavires->setProperty("actif", false);
    style()->polish(btnTableauBord);
    style()->polish(btnGestionNavires);
}

void MainWindow::afficherGestionNavires()
{
    stackedWidget->setCurrentWidget(pageGestionNavires);

    btnTableauBord->setProperty("actif", false);
    btnGestionNavires->setProperty("actif", true);
    style()->polish(btnTableauBord);
    style()->polish(btnGestionNavires);
}

void MainWindow::mettreAJourStatistiques()
{
    int total = listeNavires.size();
    int quai = 0, mer = 0, interdit = 0;

    for (const Navire &n : std::as_const(listeNavires) ){
        if (n.getStatut() == "À quai") quai++;
        else if (n.getStatut() == "En mer") mer++;
        else if (n.getStatut() == "Interdit") interdit++;
    }

    labelNbTotal->setText(QString::number(total));
    labelNbQuai->setText(QString::number(quai));
    labelNbMer->setText(QString::number(mer));
    labelNbInterdit->setText(QString::number(interdit));
}

void MainWindow::chargerNaviresAdmin()
{
    tableNaviresAdmin->setRowCount(0);

    for (const Navire &n : std::as_const(listeNavires)) {
        int row = tableNaviresAdmin->rowCount();
        tableNaviresAdmin->insertRow(row);

        QWidget *cellNom = new QWidget();
        QLabel *icone = new QLabel("Ship");
        QLabel *texte = new QLabel(n.getNom());
        QHBoxLayout *layout = new QHBoxLayout(cellNom);
        layout->addWidget(icone);
        layout->addWidget(texte);
        layout->addStretch();
        layout->setContentsMargins(10, 5, 5, 5);
        tableNaviresAdmin->setCellWidget(row, 0, cellNom);

        QTableWidgetItem *itemImmat = new QTableWidgetItem(n.getImmatriculation());
        QTableWidgetItem *itemCap = new QTableWidgetItem(QString::number(n.getCapacite()) + " t");

        tableNaviresAdmin->setItem(row, 1, itemImmat);
        tableNaviresAdmin->setItem(row, 2, itemCap);

        QWidget *cellStatut = new QWidget();
        QLabel *badge = new QLabel(n.getStatut());
        badge->setObjectName("badge");
        badge->setAlignment(Qt::AlignCenter);
        badge->setFixedWidth(120);
        badge->setFixedHeight(28);

        if (n.getStatut() == "À quai") {
            badge->setStyleSheet("background-color: #fef3c7; color: #92400e; border-radius: 14px; font-weight: 600; font-size: 12px; padding: 5px 15px;");
        } else if (n.getStatut() == "En mer") {
            badge->setStyleSheet("background-color: #d1fae5; color: #065f46; border-radius: 14px; font-weight: 600; font-size: 12px; padding: 5px 15px;");
        } else if (n.getStatut() == "Interdit") {
            badge->setStyleSheet("background-color: #fee2e2; color: #991b1b; border-radius: 14px; font-weight: 600; font-size: 12px; padding: 5px 15px;");
        }

        QHBoxLayout *badgeLayout = new QHBoxLayout(cellStatut);
        badgeLayout->addWidget(badge);
        badgeLayout->addStretch();
        badgeLayout->setContentsMargins(10, 5, 5, 5);
        tableNaviresAdmin->setCellWidget(row, 3, cellStatut);

        tableNaviresAdmin->setRowHeight(row, 55);
    }
}

void MainWindow::ajouterNavireClient()
{
    QString nom = champNomNavire->text().trimmed();
    QString immat = champImmatNavire->text().trimmed();
    int capacite = comboCapaciteNavire->currentText().toInt();
    QString statut = comboStatutNavire->currentText();

    if (nom.isEmpty() || immat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs!");
        return;
    }

    for (const Navire &navire : std::as_const(listeNavires)) {
        if (navire.getImmatriculation() == immat) {
            QMessageBox::warning(this, "Erreur", "Cette immatriculation existe deja!");
            return;
        }
    }

    if (statut == "A quai") {
        statut = "À quai";
    }

    Navire n(nom, immat, capacite, statut);
    listeNavires.append(n);

    champNomNavire->clear();
    champImmatNavire->clear();
    comboCapaciteNavire->setCurrentIndex(0);
    comboStatutNavire->setCurrentIndex(0);

    QMessageBox::information(this, "Succes", "Navire ajoute avec succes!");
}

void MainWindow::modifierNavireAdmin()
{
    int row = tableNaviresAdmin->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Attention", "Selectionnez un navire.");
        return;
    }

    QString immat = tableNaviresAdmin->item(row, 1)->text();
    int index = -1;

    for (int i = 0; i < listeNavires.size(); i++) {
        if (listeNavires[i].getImmatriculation() == immat) {
            index = i;
            break;
        }
    }

    if (index >= 0) {
        Navire navire = listeNavires[index];
        DialogNavire dialog(this, &navire, true);

        int result = dialog.exec();

        if (result == QDialog::Accepted) {
            listeNavires[index] = dialog.getNavire();
            chargerNaviresAdmin();
            mettreAJourStatistiques();
            QMessageBox::information(this, "Succes", "Navire modifie!");
        } else if (result == 2) {
            listeNavires.removeAt(index);
            chargerNaviresAdmin();
            mettreAJourStatistiques();
            QMessageBox::information(this, "Succes", "Navire supprime!");
        }
    }
}

void MainWindow::supprimerNavireAdmin()
{
    int row = tableNaviresAdmin->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Attention", "Selectionnez un navire.");
        return;
    }

    if (QMessageBox::question(this, "Confirmation", "Supprimer ce navire ?") == QMessageBox::Yes) {
        QString immat = tableNaviresAdmin->item(row, 1)->text();

        for (int i = 0; i < listeNavires.size(); i++) {
            if (listeNavires[i].getImmatriculation() == immat) {
                listeNavires.removeAt(i);
                break;
            }
        }

        chargerNaviresAdmin();
        mettreAJourStatistiques();
        QMessageBox::information(this, "Succes", "Navire supprime!");
    }
}

void MainWindow::rechercherNavire(const QString &texte)
{
    for (int i = 0; i < tableNaviresAdmin->rowCount(); ++i) {
        bool match = false;

        QTableWidgetItem *item1 = tableNaviresAdmin->item(i, 1);
        QTableWidgetItem *item2 = tableNaviresAdmin->item(i, 2);

        if ((item1 && item1->text().contains(texte, Qt::CaseInsensitive)) ||
            (item2 && item2->text().contains(texte, Qt::CaseInsensitive))) {
            match = true;
        }

        tableNaviresAdmin->setRowHidden(i, !match);
    }
}

void MainWindow::appliquerStyles()
{
    QString styles =
        "QMainWindow {"
        "    background-color: #f1f5f9;"
        "    font-family: 'Segoe UI';"
        "}"
        ""
        "#menuLateral {"
        "    background-color: #1e3a8a;"
        "}"
        ""
        "#iconeLogo {"
        "    font-size: 34px;"
        "    color: white;"
        "}"
        ""
        "#nomAppMenu {"
        "    color: white;"
        "    font-size: 22px;"
        "    font-weight: 700;"
        "}"
        ""
        "#btnMenu {"
        "    background-color: transparent;"
        "    color: #bfdbfe;"
        "    text-align: left;"
        "    padding: 14px 22px;"
        "    border: none;"
        "    border-radius: 8px;"
        "    margin: 4px 10px;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "}"
        ""
        "#btnMenu:hover {"
        "    background-color: rgba(147, 197, 253, 0.15);"
        "    color: white;"
        "}"
        ""
        "#footerMenu {"
        "    background-color: rgba(255,255,255,0.05);"
        "    border-top: 1px solid rgba(255,255,255,0.08);"
        "}"
        ""
        "#nomUser {"
        "    color: white;"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "}"
        ""
        "#deconnexion {"
        "    color: #bfdbfe;"
        "    font-size: 11px;"
        "}"
        ""
        "#titrePage {"
        "    color: #1e293b;"
        "    font-size: 28px;"
        "    font-weight: 800;"
        "}"
        ""
        "#sousTitrePage {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "}"
        ""
        "#avatarUserClient {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "    padding: 8px 16px;"
        "    border-radius: 20px;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "}"
        ""
        "#carteStat {"
        "    background-color: white;"
        "    border-radius: 16px;"
        "    border: 1px solid #e2e8f0;"
        "    padding: 20px;"
        "}"
        ""
        "#iconeCarte {"
        "    font-size: 42px;"
        "}"
        ""
        "#valeurStat {"
        "    font-size: 38px;"
        "    font-weight: 800;"
        "    color: #0f172a;"
        "}"
        ""
        "#titreCarte {"
        "    color: #64748b;"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "}"
        ""
        "#champRecherche {"
        "    padding: 12px 16px;"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "}"
        ""
        "#champRecherche:focus {"
        "    border: 1px solid #3b82f6;"
        "}"
        ""
        "#btnDropdown {"
        "    background-color: white;"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "}"
        ""
        "#btnModifier {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "    padding: 12px 26px;"
        "    border-radius: 10px;"
        "    font-weight: 600;"
        "}"
        ""
        "#btnModifier:hover {"
        "    background-color: #2563eb;"
        "}"
        ""
        "#btnSupprimer {"
        "    background-color: #ef4444;"
        "    color: white;"
        "    padding: 12px 26px;"
        "    border-radius: 10px;"
        "    font-weight: 600;"
        "}"
        ""
        "#btnSupprimer:hover {"
        "    background-color: #dc2626;"
        "}"
        ""
        "#carteFormulaire {"
        "    background-color: white;"
        "    border-radius: 16px;"
        "    border: 1px solid #e2e8f0;"
        "    padding: 40px;"
        "}"
        ""
        "#titreFormulaire {"
        "    font-size: 22px;"
        "    font-weight: 800;"
        "    color: #1e293b;"
        "}"
        ""
        "#labelChamp {"
        "    color: #475569;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    margin-bottom: 8px;"
        "}"
        ""
        "#champFormulaire {"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "    padding: 12px 16px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "    color: #1e293b;"
        "}"
        ""
        "#champFormulaire:focus {"
        "    border: 2px solid #3b82f6;"
        "    outline: none;"
        "}"
        ""
        "#comboFormulaire {"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "    padding: 12px 16px;"
        "    background-color: white;"
        "    font-size: 14px;"
        "    color: #1e293b;"
        "}"
        ""
        "#comboFormulaire:focus {"
        "    border: 2px solid #3b82f6;"
        "}"
        ""
        "#btnAjouterFormulaire {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "    font-size: 15px;"
        "    font-weight: 700;"
        "    padding: 14px 40px;"
        "    border-radius: 10px;"
        "    border: none;"
        "}"
        ""
        "#btnAjouterFormulaire:hover {"
        "    background-color: #2563eb;"
        "}"
        ""
        "#btnAjouterFormulaire:pressed {"
        "    background-color: #1d4ed8;"
        "}"
        ""
        "#tableAdmin {"
        "    background-color: white;"
        "    border: 1px solid #e2e8f0;"
        "    border-radius: 16px;"
        "    gridline-color: #f1f5f9;"
        "}"
        ""
        "QTableWidget::item {"
        "    padding: 16px;"
        "}"
        ""
        "QTableWidget::item:selected {"
        "    background-color: #eff6ff;"
        "}"
        ""
        "QHeaderView::section {"
        "    background-color: #1e293b;"
        "    color: white;"
        "    padding: 18px;"
        "    border: none;"
        "    font-weight: 600;"
        "    font-size: 13px;"
        "}"
        ""
        "QLineEdit {"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "    padding: 8px;"
        "    background-color: white;"
        "}"
        ""
        "QLineEdit:focus {"
        "    border: 1px solid #3b82f6;"
        "}"
        ""
        "QComboBox {"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 10px;"
        "    padding: 8px;"
        "    background-color: white;"
        "}"
        ""
        "QComboBox:focus {"
        "    border: 1px solid #3b82f6;"
        "}";

    setStyleSheet(styles);
}
