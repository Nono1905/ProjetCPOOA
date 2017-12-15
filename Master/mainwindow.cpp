#include <QtDebug>
#include <QStringListModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Plateforme &p) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    plateforme(&p),
    adapter(p)
{
    ui->setupUi(this);
    //évite de nous retrouver sur le mauvais widget a cause de l'uidesigner
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::setPlateforme(Plateforme &p)
{
    plateforme = &p;
}


void MainWindow::seConnecter()
{
    std::string login = ui->lineLogin->text().toStdString();
    std::string mdp = ui->lineMdp->text().toStdString();

    if (plateforme->containsUser(login) && plateforme->getEtudiantParLogin(login).verifMDP(mdp) ) {
        //Passe a la page suivante
        QString home = QString::fromStdString("Bienvenue " + login + " !");
        ui->label_3->setText(home);

        // Afficher les cours suivis
        Etudiant e = plateforme->getEtudiantParLogin(login);
        listeModelCoursSuivis.setStringList(adapter.ListeCoursSuivis(e));
        ui->listCoursSuivis->setModel(&listeModelCoursSuivis);

        // Affiche la liste des cours validés
        listeModelCours.setStringList(adapter.ListeCoursValide());
        ui->listCours->setModel(&listeModelCours);

        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Login ou mot de passe incorrect"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonDeconnexion_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionexit_triggered()
{
    close();
}

void MainWindow::on_pushButtonAccueil_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_listCoursSuivis_doubleClicked(const QModelIndex &index)
{
    // On récupère le nom du cours en fonction de l'index
    QString nomCours = listeModelCoursSuivis.data(index,0).toString();
    coursSelectionne = &plateforme->getCoursParNom(nomCours.toStdString());

    // Donne le nom du cours au label
    QString labelText = "Cours : " + nomCours;
    ui->labelNomCours->setText(labelText);

    // Affiche le nom de l'enseignant
    QString labelNomEnseignant = "Enseignant : " + QString::fromStdString(coursSelectionne->getLoginEnseignant());
    ui->label_NomEnseigant->setText(labelNomEnseignant);

    // Affiche la liste des ressources
    listeModelRessources.setStringList(adapter.mapRessourceToQStringList(coursSelectionne->getRessources()));
    ui->listRessources->setModel(&listeModelRessources);

    // Affiche la liste principale des étudiants
    listeModelEtudiantsPrincipal.setStringList(adapter.ListeEtudiantToQStringList(coursSelectionne->getListeEtudiantP()));
    ui->listPrincipaleEtudiant->setModel(&listeModelEtudiantsPrincipal);

    // Affiche la liste d'attente des étudiants
    listeModelEtudiantsSecondaire.setStringList(adapter.ListeEtudiantToQStringList(coursSelectionne->getListeEtudiantA()));
    ui->listAttenteEtudiant->setModel(&listeModelEtudiantsSecondaire);

    // Affiche le nombre de place
    labelText = QString("Nombre de places : %1").arg(coursSelectionne->getNbPlace());
    ui->labelNombrePlace->setText(labelText);

    // Affiche la bonne page
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_listCours_doubleClicked(const QModelIndex &index)
{
    std::string login = ui->lineLogin->text().toStdString();
    Etudiant& e = plateforme->getEtudiantParLogin(login);

    QString nomCours = listeModelCours.data(index,0).toString();
    coursSelectionne = &plateforme->getCoursParNom(nomCours.toStdString());

    if(!e.inscrire(*coursSelectionne)){
        listeModelCoursSuivis.setStringList(adapter.ListeCoursSuivis(e));
        ui->listCoursSuivis->setModel(&listeModelCoursSuivis);
    }
}

void MainWindow::on_SeDesinscrire_clicked()
{
    std::string login = ui->lineLogin->text().toStdString();
    Etudiant& e = plateforme->getEtudiantParLogin(login);

    e.desinscrire(*coursSelectionne);

    listeModelCoursSuivis.setStringList(adapter.ListeCoursSuivis(e));
    ui->listCoursSuivis->setModel(&listeModelCoursSuivis);

    ui->stackedWidget->setCurrentIndex(1);
}
