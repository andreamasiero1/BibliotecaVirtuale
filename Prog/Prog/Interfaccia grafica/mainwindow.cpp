#include "mainwindow.h"   // Header principale
#include <QMainWindow>    // Per QMainWindow
#include <QStackedWidget> // Per QStackedWidget
#include <QWidget>        // Per QWidget
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QToolBar>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), currentTabIndex(0){
    setupUI();
    setupToolbar();
    setupStatusBar();
    setupMediaList();
}
MainWindow::~MainWindow(){}

void MainWindow::setupUI() {
    //Crea uno splitter per dividere la finestra in due parti
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(splitter);
    // Parte sinistra: Lista dei media
    tabWidget = new QStackedWidget();
    splitter->addWidget(tabWidget);
    createLibriTab();
    createFilmTab();
    createMagazineTab();
    // Parte destra: Dettagli del media selezionato
    QWidget *detailsWidget = new QWidget();
    QVBoxLayout *datilsLayoiut = new QVBoxLayout(detailsWidget);
    QLabel *detailsLabel = new QLabel("Dettagli del media selezionato");
    detailsLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    // Immagine di copertina predefinita
    coverImageLabel = new Qlabel();
    coverImageLabel->setFixedSize(150, 200);
    coverImageLaber->setScaledContents(true);
    coverImageLabel-setStyleSheet("border: 1px solid gray; background-color: #f0f0f0;");
    coverImageLabel->setAlignment(Qt::AlignCenter);
    coverImageLabel->setText("Nessuna immagine");
    // Descrizione del media
    detailsTextEdit = new QTextEdit();
    detailsTextEdit->setReadOnly(true); // Rende il QTextEdit di sola lettura
    detailsTextEdit->setPlaceholderText("Seleziona un media per visualizzare i dettagli...");
    detailsTextEdit->setStyleSheet("font-size: 12px; color: #333;");
    // Aggiungi i widget al layout
    detailsLayout->addWidget(detailsLabel);
    datailsLayout->addWidget(coverImageLabel);
    detailsLayout->addWidget(detailsTextEdit);
    // Aggiungi il widget dei dettagli allo splitter
    splitter->addWidget(detailsWidget);
    splitter->setSizes({700,300}); // La dimensione iniziale è 70% per la tab e 30% per i dettagli
    // Collegamento evento cambio tab
    connect(tabWidget, &QStackedWidget::currentChanged, this, &MainWindow::onTabChanged);
    // Imposta il titolo della finestra e le dimensioni iniziali
    setWindowTitle("Biblioteca Multimediale");
    resize(1000, 600);
}

// Crea il tab per i libri
void MainWindow::createLibriTab(){
    libriWidget = new QWidget();
    QVBoxLayour *libriLayout = new QVBoxLayout(libriWIdget);
    //sezione di ricerca
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLibriEdit = new QLineEdit();
    searchLibriEdit->setPlaceholderText("Cerca libri...");
    searchLibriBtn = new QPushButton("Cerca");
    searchLayout->addWidget(searchLibriEdit);
    searchLayout->addWidget(searchLibriBtn);
    // Lista dei libri
    libriListWidget = new QListWidget();
    // Pulsanti di azione
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addLibriBtn = new QPushButton("Aggiungi media");
    removeLibriBtn = new QPushButton("Rimuovi libro");
    editLibriBtn = new QPushButton("Modifica libro");
    // Stile pulsanti
    addBookBtn->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border: none; border-radius: 4px; }");
    editBookBtn->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; border: none; border-radius: 4px; }");
    deleteBookBtn->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 8px; border: none; border-radius: 4px; }");
    // Aggiungi i widget al layout
    buttonLayout->addWidget(addlibriBtn);
    buttonLayout->addWidget(removeLibriBtn);
    buttonLayout->addWidget(editLibriBtn);
    buttonLayout->addStretch(); // Aggiunge uno spazio flessibile

    libriLayout->addLyout(searchLayout);
    libriLayout->addWidget(libriListWidget);
    libriLayout->addlayout(buttonLayout);
    // Aggiunta della tab
    tabWidget->addWidget(libriWidget, "Libri");
    // Collegamento dei segnali
    connect(searchLibriBtn, &QPushButton::clicked, this, &MainWindow::searchMedia);
    connect(libriListWidget, &QListWidget::itemClicked, this, &MainWindow::ShowMediaDetails);
    connect(addLibriBtn, &QPushButton::clicked, this, &MainWindow::addMedia);
    connect(removeLibriBtn; &QPushButton::clicked, this, &MainWindow::removeMedia);
    connect(editLibriBtn, &QPushButton::clicked, this, &MainWindow::editMedia);
}