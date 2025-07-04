#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QStackedWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QSplitter>
#include <QListWidgetItem>
#include "../Modello logico/Biblioteca.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QStackedWidget *stackWidget, QWidget *parent = nullptr);
    ~MainWindow() = default;
private slots:
    void addMedia();
    void removeMedia();
    void editMedia();
    void searchMedia();
    void showMediaDetails();
    void closeLibrary();
    void loadLibrary();
    void saveLibrary();
    void onTabChanged(int index);

private:
    void setupUI();
    void setupBottomBar();
    void createLibriTab();
    void createFilmTab();
    void createMagazineTab();
    void updateMediaList();
    QListWidget *getCurrentListWidget() const;
    void clearMediaList();
    void clearDetails();
    Media *getSelectedMedia() const;
    void populateMediaList(const QLista<Media *> &mediaList);
    void close();
    Biblioteca biblioteca;
    QTabWidget *tabWidget; // Tab widget per i media

    // Tab per i libri
    QWidget *libriWidget;
    QLineEdit *searchLibriEdit;
    QPushButton *searchLibriBtn;
    QListWidget *libriListWidget;
    QPushButton *addLibriBtn;
    QPushButton *removeLibriBtn;
    QPushButton *editLibriBtn;

    // Tab per i film
    QWidget *filmWidget;
    QLineEdit *searchFilmEdit;
    QPushButton *searchFilmBtn;
    QListWidget *filmListWidget;
    QPushButton *addFilmBtn;
    QPushButton *removeFilmBtn;
    QPushButton *editFilmBtn;

    // Tab per le riviste
    QWidget *magazineWidget;
    QLineEdit *searchMagazineEdit;
    QPushButton *searchMagazineBtn;
    QListWidget *magazineListWidget;
    QPushButton *addMagazineBtn;
    QPushButton *removeMagazineBtn;
    QPushButton *editMagazineBtn;

    // dettagli del media selezionato
    QTextEdit *detailsTextEdit;
    QLabel *coverImageLabel;

    int currentTabIndex; // Indice del tab corrente
};

#endif // MAINWINDOW_H
