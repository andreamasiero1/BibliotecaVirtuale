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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentTabIndex(0)
{
    setupUI();
    setupBottomBar();
    setupMediaList();
}
MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    // Crea uno splitter per dividere la finestra in due parti
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
    coverImageLabel - setStyleSheet("border: 1px solid gray; background-color: #f0f0f0;");
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
    splitter->setSizes({700, 300}); // La dimensione iniziale è 70% per la tab e 30% per i dettagli
    // Collegamento evento cambio tab
    connect(tabWidget, &QStackedWidget::currentChanged, this, &MainWindow::onTabChanged);
    // Imposta il titolo della finestra e le dimensioni iniziali
    setWindowTitle("Biblioteca Multimediale");
    resize(1000, 600);
}

// Crea il tab per i libri
void MainWindow::createLibriTab()
{
    libriWidget = new QWidget();
    QVBoxLayour *libriLayout = new QVBoxLayout(libriWIdget);
    // sezione di ricerca
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
    addLibriBtn = new QPushButton("Aggiungi Libro");
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

// Crea il tab per i film
void MainWindow::createFilmTab()
{
    film Widget = new QWidget();
    QVBoxLayout *filmLayout = new QVBoxLayout(filmWidget);
    // sezione di ricerca
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchFilmEdit = new QLineEdit();
    searchFilmEdit->setPlacholderText("Cerca film...");
    searchFilmBtn = new QPushButton("Cerca");
    searchLayout->addWidget(searchFilmEdit);
    searchLayout->addWidget(searchFilmBtn);
    // lista dei film
    filmListWIdget = new QListWidget();
    // pulsanti di azione
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addFilmBtn = new QPushButton("Aggiungi film");
    removeFilmBtn = new QPushBotton("RUmuovi film");
    editFilmBtn = new QPushButton("Modifica film");
    // stile pulsanti
    addFilmBtn->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border: none; border-radius: 4px; }");
    editFilmBtn->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; border: none; border-radius: 4px; }");
    deleteFilmBtn->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 8px; border: none; border-radius: 4px; }");
    // Aggiungi i widget al layout
    buttonLayout->addWidget(addFilmBtn);
    buttonLayout->addWidget(editFilmBtn);
    buttonLayout->addWidget(removeFilmBtn);
    buttonLayout->addStretch();

    filmLayout->addLayout(searchLayout);
    filmLayout->addWidget(filmListWidget);
    filmLayout->addLayout(buttonLayout);
    // Aggiunta della tab
    tabWidget->addWidget(filmWidget, "Film");
    // collegamento dei segnali
    connect(searchFilmBtn, &QPushButton::clicked, this, &MainWindow::searchMedia);
    connect(filmListWidget, &QListWidget::itemClicked, this, &MainWindow::showMediaDetails);
    connect(addFilmBtn, &QPushButton::clicked, this, &MainWindow::addMedia);
    connect(removeFilmBtn, &QPushButton::clicked, this, &MainWindow::removeMedia);
    connect(editFilmBtn, &QPushButton::clicked, this, &MainWindow::editMedia);
}

// Crea il tab per le riviste
void MainWindow::createMagazineTab()
{
    magazineWidget = new QWidget();
    QVBoxLayout *magazineLayout = new QVBoxLayout(magazineWidget);
    // sezione di ricerca
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchMagazineEdit = new QLineEdit();
    searchMagazineEdit->setPlaceholderText("Cerca riviste...");
    searchMagazineBtn = new QPushButton("Cerca");
    searchLayout->addWidget(searchMagazineEdit);
    serachLayout->addWidget(searchMagazineBtn);
    // lista delle riviste
    magazineListWidget = new QListWidget();
    // pulsanti di azione
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addMagazineBtn = new QPushButton("Aggiungi rivista");
    removeMagazineBtn = new QPushButton("Rimuovi rivista");
    editMagazineBtn = new QPushButton("Modifica rivista");
    // stile pulsanti
    addMagazineBtn->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 8px; border: none; border-radius: 4px; }");
    editMagazineBtn->setStyleSheet("QPushButton { background-color: #2196F3; color: white; padding: 8px; border:    none; border-radius: 4px; }");
    deleteMagazineBtn->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 8px; border: none; border-radius: 4px; }");
    // Aggiungi i widget al layout
    buttonLayout->addWidget(addMagazineBtn);
    buttonLayout->addWidget(editMagazineBtn);
    buttonLayout->addWidget(removeMagazineBtn);
    buttonLayout->addStretch();
    magazineLayout->addLayout(searchLayout);
    magazineLayout->addWidget(magazineListWidget);
    magazineçayput->addLayout(buttonLayout);
    // Aggiunta della tab
    tabWidget->addWidget(magazineWidget, "Riviste");
    // Collegamento dei segnali
    connect(searchMagazineBtn, &QPushButton::clicked, this, &MainWindow::searchMedia);
    connect(magazineListWidget, &QListWidget::itemClicked, this, &MainWindow::showMediaDetails);
    conncet(addMagazineBtn, &QPushButton::clicked, this, &MainWindow::addMedia);
    connect(removeMagazineBtn, &QPushButton::clicked, this, &MainWindow::removeMedia);
    connect(editMagazineBtn, &QPushButton::clicked, this, &MainWindow::editMedia);
}

void MainWindow::setupBottomBar()
{
    // setta il messaggio di stato iniziale
    QStatusBar *sb = statusBar();
    sb->setStyleSheet("QStatusBar { background-color:rgb(82, 82, 82); color: #f0f0f0; font-size: 12px; }");
    sb->showMessage("Biblioteca Multimediale pronta");
    // crea i tre pulsanti
    QPushButton *loadButton = new QPushButton("Carica Biblioteca", this);
    QPushButton *saveButton = new QPushButton("Salva Biblioteca", this);
    QPushButton *closeButton = new QPushButton("Chiudi Biblioteca", this);
    // tootip
    loadButton->setToolTip("Carica i dati della biblioteca da un file");
    saveButton->setToolTip("Salva i dati della biblioteca su un file");
    closeButton->setToolTip("Chiude la finestra della biblioteca");
    // aggiunta dei pulsanti alla barra degli strumenti
    sb->addPermanentWidget(loadButton);
    sb->addPermanentWidget(saveButton);
    sb->addPermanentWidget(closeButton);
    // collegamento dei segnali
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadLibrary);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveLibrary);
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeLibrary);
}

void MainWindow::addMedia()
{
    AddMediaVisitor *addMediaDialog = new AddMediaVisitor(this);
    if (AddMediaDialod->exec() == QDialog::Accepted)
    {
        updateMediaList();
        statusBar()->showMessage("Media aggiunto con successo", 2000);
    }
    delete addMediaDialog;
}

void MainWindow::removeMedia()
{
    Media *selectedMedia = getSelectedMedia();
    if (!selectedMedia)
    {
        QMessageBox::warning(this, "Rimozione media", "Nessun media selezionato per la rimozione.");
        return;
    }
    int risposta = QMessageBox::question(this, "Rimozione media", QString("Sei sicuro di voler rimuovere questo media "), QMessageBox::Yes | QMessageBox::No);
    if (risposta == QMessageBox::Yes)
    {
        // rimuovi il media
        DeleteMediaVisitor deleteVisitor(biblioteca, this);
        selectedMedia->accept(deleteVisitor);
        updateMediaList();
        statusBar()->showMessage("Media rimosso con successo", 2000);
        clearDetails();
    }
}

void MainWindow::editMedia()
{
    Media *selectedMedia = getSelectedMedia();
    if (!selectedMedia)
    {
        QMessageBox::warning(this, "Modifica media", "Nessun media selezionato per la modifica.");
        return;
    }
    EditMediaVisitor *editMediaDialog = new EditMediaVisitor(biblioteca, selectedMedia, this);
    if (editMediaDialog->exec() == QDialog::Accepted)
    {
        updateMediaList();
        showMediaDetails();
        statusBar()->showMessage("Media modificato con successo", 2000);
    }
    delete editMediaDialog;
}

void MainWindow::searchMedia()
{
    QString searchText;
    if (currentTabIndex == 0)
    { // libri
        searchText = searchLibriEdit->text();
    }
    else if (currentTabIndex == 1)
    { // film
        searchText = searchFilmEdit->text()
    }
    else if (currentTabIndex == 2)
    { // riviste
        searchText = searchMagazineEdit->text();
    }
    if (searchText.isEmpty())
    {
        updateMediaList(); // mostra tutti i media se il campo di ricerca è vuoto
        return;
    }
    // Filtra la lista dei media in base al testo di ricerca
    QList<Media *> searchResults = biblioteca.cercaPerTitolo(searchText); //
    popolateMediaList(searchResults);
}

void MainWindow::showMediaDetails()
{
    Media *selectedMedia = getSelectedMedia();
    if (selectedMedia)
    {
        detailsTextEdit->setTect(selectedMedia->visualizzaDettagli());
        QString imagePath = selecteMedia->getCoverImagePath();
        if (!imagePath.isEmpty() && QFileInfo::exists(imagePath))
        {
            QPixmap pixmap(imagePath);
            coverImageLabel->setPixmap(pixmap.scaled(coverImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            coverIamgeLabel->clear();
            coverImageLabel->setText("Nessuna immagine disponibile");
        }
    }
}

void MainWindow::saveLibrary()
{
    QString filename = QFileDialog::getSaveFileName(this, "Salva Biblioteca", "", "Biblioteca (*.json)");
    if (!filename.isEmpty())
    {
        if (JsonManager::saveLibrary(biblioteca, filename))
        {
            statusBar()->showMessage("Biblioteca salvata con successo", 2000);
        }
        else
        {
            QMessageBox::warning(this, "Errore", "Impossibile salvare la biblioteca.");
        }
    }
}

void MainWindow::close()
{
    int risposta = QMessageBox::question(this, "Chiudi Biblioteca", "Sei sicuro di voler chiudere la biblioteca: i dati non salvati andranno persi?", QMessageBox::Yes | QMessageBox::No);
    if (risposta == QMessageBox::Yes)
    {
        QMainWindow::close();
    }
}

void MainWindow::loadLibrary()
{
    QString filename = QFileDialog::getOpenFileName(this, "Carica Biblioteca", "", "Biblioteca (*.json)");
    if (!filename.isEmpty())
    {
        if (JsonManager::loadLibrary(biblioteca, filename))
        {
            upadteMediaList();
            statusBar()->showMessage("Biblioteca caricata con successo", 2000);
        }
        else
        {
            QMessageBox::warning(this, "Errore", "Impossibile caricare la biblioteca.");
        }
    }
}

void MainWindow::onTabChanged(int index) // Slot chiamato quando cambia il tab
{
    currentTabIndex = index;
    clearMediaList();
    updateMediaList();
    clearDetails();
}

void MainWindow::updateMediaList()
{
    QList<Media *> mediaList;
    if (currentTabIndex == 0)
    {
        mediaList = biblioteca.getLibri();
    }
    else if (currentTabIndex == 1)
    {
        mediaList = biblioteca.getFilm();
    }
    else if (currentTabIndex == 2)
    {
        mediaList = biblioteca.getRiviste();
    }
}

QListWidget *MainWindow::getCurrentListWidget() const
{
    if (currentTabIndex == 0)
    {
        return libriListWidget;
    }
    else if (currentTabIndex == 1)
    {
        return filmListWidget;
    }
    else if (currentTabIndex == 2)
    {
        return magazineListWidget;
    }
}

void MainWindow::PopulateMediaList(const QList<Media *> &mediaList)
{
    clearMediaList();
    QListWidget *currentList = getCurrentListWidget();
    if (!currentList)
    {
        return;
    }
    for (Media *media = mediaList.begin(); media != mediaList.end(); ++media)
    {
        QListWidgetItem *item = new QListWidgetItem(("%1 (%2)").arg(media->getTitolo()).arg(media->getAnnoPubblicazione()));
        item->setData(Qt::UserRole, QVariant::fromValue(static_cast<void*>(media))); // Salva il puntatore al media nell'item
        currentList->addItem(item);
    }
}

void MainWindow::clearMediaList(){
    if(currentTabIndex==0){
        libriListWidget->clear();
    }else if(currentTabIndex==1){
        filmListWidget->clear();
    } else if(currentTabIndex==2){
        magazineListWidget->clear();
    }
}

void MainWindow::clearDetails(){
    detailsTextEdit->clear();
    coverImageLabel->clear();
    coverImageLabel->setText("Nessuna immagine");
}

