#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include <QList>
#include "navire.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void afficherTableauBord();
    void afficherGestionNavires();
    void ajouterNavireClient();
    void modifierNavireAdmin();
    void supprimerNavireAdmin();
    void rechercherNavire(const QString &texte);

private:
    void configurerInterface();
    void configurerTableauBord();
    void configurerGestionNavires();
    void appliquerStyles();
    void mettreAJourStatistiques();
    void chargerNaviresAdmin();
    QFrame* creerCarteStatistique(QString titre, QString valeur, QString icone, QString couleur);

    // Composants UI
    QFrame *menuLateral;
    QStackedWidget *stackedWidget;

    // Pages
    QWidget *pageTableauBord;
    QWidget *pageGestionNavires;

    // Boutons menu
    QPushButton *btnTableauBord;
    QPushButton *btnGestionNavires;

    // Page Tableau de Bord
    QTableWidget *tableNaviresAdmin;
    QLineEdit *lineRechercheAdmin;
    QPushButton *btnModifierAdmin;
    QPushButton *btnSupprimerAdmin;
    QLabel *labelNbTotal;
    QLabel *labelNbQuai;
    QLabel *labelNbMer;
    QLabel *labelNbInterdit;

    // Page Gestion Navires - Formulaire
    QPushButton *btnAjouterClient;
    QLineEdit *champNomNavire;
    QLineEdit *champImmatNavire;
    QComboBox *comboCapaciteNavire;
    QComboBox *comboStatutNavire;

    // Données
    QList<Navire> listeNavires;
};

#endif // MAINWINDOW_H
