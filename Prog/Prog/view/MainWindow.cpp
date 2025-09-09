#include "MainWindow.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/MagazineArticle.h"
#include "../persistence/JsonSerializer.h"
#include <QPixmap>
#include <QFileInfo>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QDir>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    loadDefaultLibrary();
    updateMediaDisplay();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    QLabel *filterLabel = new QLabel("Tipo Media:");
    QComboBox *mediaTypeFilter = new QComboBox();
    mediaTypeFilter->addItem("Tutti", "all");
    mediaTypeFilter->addItem("📚 Libri", "book");
    mediaTypeFilter->addItem("🎬 Film", "film");
    mediaTypeFilter->addItem("📄 Articoli", "article");

    // barra di ricerca
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Cerca media ...");
    QPushButton *searchBtn = new QPushButton("🔍 Cerca");

    // action buttons
    QPushButton *addBtn = new QPushButton("➕ Aggiungi");
    QPushButton *editBtn = new QPushButton("✏️ Modifica");
    QPushButton *deleteBtn = new QPushButton("🗑️ Elimina");
    QPushButton *detailsBtn = new QPushButton("👁️ Dettagli");

    toolbarLayout->addWidget(filterLabel);
    toolbarLayout->addWidget(mediaTypeFilter);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(searchEdit);
    toolbarLayout->addWidget(searchBtn);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(addBtn);
    toolbarLayout->addWidget(editBtn);
    toolbarLayout->addWidget(deleteBtn);
    toolbarLayout->addWidget(detailsBtn);

    // Media display
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *contentWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(contentWidget);

    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumHeight(600);

    mainLayout->addLayout(toolbarLayout);
    mainLayout->addWidget(scrollArea);

    this->mediaTypeFilter = mediaTypeFilter;
    this->searchEdit = searchEdit;
    this->gridLayout = gridLayout;
    this->contentWidget = contentWidget;
    this->scrollArea = scrollArea;

    connect(mediaTypeFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFilterChanged);
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::searchMedia);
    connect(searchEdit, &QLineEdit::returnPressed, this, &MainWindow::searchMedia);
    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addMedia);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editMedia);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteMedia);
    connect(detailsBtn, &QPushButton::clicked, this, &MainWindow::showMediaDetails);

    setWindowTitle("Biblioteca Virtuale");
    resize(1200, 800);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&Carica Biblioteca", QKeySequence::Open, this, &MainWindow::loadLibrary);
    fileMenu->addAction("&Salva Biblioteca", QKeySequence::Save, this, &MainWindow::saveLibrary);
    fileMenu->addSeparator();
    fileMenu->addAction("&Esci", QKeySequence::Quit, this, &MainWindow::close);

    QMenu *mediaMenu = menuBar->addMenu("&Media");
    mediaMenu->addAction("&Aggiungi", QKeySequence::New, this, &MainWindow::addMedia);
    mediaMenu->addAction("&Modifica", this, &MainWindow::editMedia);
    mediaMenu->addAction("&Elimina", QKeySequence::Delete, this, &MainWindow::deleteMedia);
    mediaMenu->addSeparator();
    mediaMenu->addAction("&Cerca", QKeySequence::Find, this, &MainWindow::searchMedia);
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Pronto", 2000);
}

void MainWindow::updateMediaDisplay()
{
    clearMediaDisplay();

    QList<Media *> mediaToDisplay = getFilteredMedia();
    populateDisplayWithMedia(mediaToDisplay);
}

void MainWindow::clearMediaDisplay()
{
    clearLayout(gridLayout);
}

QList<Media *> MainWindow::getFilteredMedia() const
{
    QString currentFilter = mediaTypeFilter->currentData().toString();
    QString searchTerm = searchEdit->text().trimmed();

    QList<Media *> allMedia;

    if (currentFilter == "all")
    {
        allMedia = biblioteca.getTuttiMedia();
    }
    else if (currentFilter == "book")
    {
        allMedia = biblioteca.collectMediaByType(MediaFilter::FilterType::BOOKS_ONLY);
    }
    else if (currentFilter == "film")
    {
        allMedia = biblioteca.collectMediaByType(MediaFilter::FilterType::FILMS_ONLY);
    }
    else if (currentFilter == "article")
    {
        allMedia = biblioteca.collectMediaByType(MediaFilter::FilterType::ARTICLES_ONLY);
    }

    if (!searchTerm.isEmpty())
    {
        QList<Media *> searchResults;
        for (Media *media : allMedia)
        {
            if (media->getTitle().contains(searchTerm, Qt::CaseInsensitive))
            {
                searchResults.append(media);
            }
        }
        return searchResults;
    }

    return allMedia;
}

void MainWindow::populateDisplayWithMedia(const QList<Media *> &mediaList)
{
    int columns = 4;
    int currentRow = gridLayout->rowCount();
    int currentCol = 0;

    for (Media *media : mediaList)
    {
        addMediaWidgetToGrid(media, currentRow, currentCol);
        currentCol++;

        if (currentCol >= columns)
        {
            currentCol = 0;
            currentRow++;
        }
    }
}

void MainWindow::addMediaWidgetToGrid(Media *media, int row, int col)
{
    MediaWidgetVisitor visitor(false);
    media->accept(visitor);
    QWidget *widget = visitor.getWidget();

    widget->setProperty("media", QVariant::fromValue(static_cast<void *>(media)));
    widget->setProperty("clickable", true);
    widget->installEventFilter(this);

    gridLayout->addWidget(widget, row, col);
}

void MainWindow::clearLayout(QLayout *layout)
{
    if (!layout)
        return;

    while (QLayoutItem *item = layout->takeAt(0))
    {
        if (QWidget *widget = item->widget())
        {
            widget->removeEventFilter(this);

            widget->setProperty("media", QVariant());
            widget->setProperty("clickable", QVariant());

            disconnect(widget, nullptr, this, nullptr);

            widget->deleteLater();
        }
        delete item;
    }
}

void MainWindow::onFilterChanged()
{
    updateMediaDisplay();
    selectedMedia = nullptr;
}

void MainWindow::showMediaDetails()
{
    if (!selectedMedia)
    {
        QMessageBox::information(this, "Informazione", "Seleziona un media per visualizzare i dettagli.");
        return;
    }

    QString details = selectedMedia->visualizzaDettagli();
    QMessageBox::information(this, "Dettagli Media", details);
}

void MainWindow::addMedia()
{

    QStringList mediaTypes;
    mediaTypes << "Libro" << "Film" << "Articolo di Rivista";

    bool ok;
    QString selectedType = QInputDialog::getItem(this, "Aggiungi Media",
                                                 "Seleziona il tipo di media:",
                                                 mediaTypes, 0, false, &ok);

    if (!ok || selectedType.isEmpty())
    {
        return;
    }

    // Crea il media temporaneo per il visitor
    Media *tempMedia = nullptr;
    if (selectedType == "Libro")
    {
        tempMedia = new Book("", 2024, "", "", "", "");
    }
    else if (selectedType == "Film")
    {
        tempMedia = new Film("", 2024, "", 0, "", "");
    }
    else if (selectedType == "Articolo di Rivista")
    {
        tempMedia = new MagazineArticle("", 2024, "", "", "", "");
    }

    if (!tempMedia)
    {
        return;
    }

    MediaVisitor *visitor = new MediaWidgetVisitor(true);
    tempMedia->accept(*visitor);
    QWidget *widget = (static_cast<MediaWidgetVisitor *>(visitor))->getWidget();

    // Crea il dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Aggiungi " + selectedType);
    dialog.setModal(true);

    QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);
    dialogLayout->addWidget(widget);

    // Bottoni
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okBtn = new QPushButton("Aggiungi");
    QPushButton *cancelBtn = new QPushButton("Annulla");

    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);

    dialogLayout->addLayout(buttonLayout);

    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        // Crea il nuovo media con i dati inseriti
        MediaWidgetVisitor *editVisitor = static_cast<MediaWidgetVisitor *>(visitor);

        Media *newMedia = nullptr;
        if (selectedType == "Libro")
        {
            newMedia = new Book(editVisitor->getTitle(), editVisitor->getYear(),
                                editVisitor->getAuthor(), editVisitor->getIsbn(),
                                editVisitor->getPublisher(), editVisitor->getCoverImagePath());
        }
        else if (selectedType == "Film")
        {
            newMedia = new Film(editVisitor->getTitle(), editVisitor->getYear(),
                                editVisitor->getDirector(), editVisitor->getDuration(),
                                editVisitor->getGenere(), editVisitor->getCoverImagePath());
        }
        else if (selectedType == "Articolo di Rivista")
        {
            newMedia = new MagazineArticle(editVisitor->getTitle(), editVisitor->getYear(),
                                           editVisitor->getArticleAuthor(), editVisitor->getMagazine(),
                                           editVisitor->getDoi(), editVisitor->getCoverImagePath());
        }

        if (newMedia)
        {
            newMedia->setCopiesAvailable(editVisitor->getCopiesAvailable());
            biblioteca.aggiungiMedia(newMedia);
            updateMediaDisplay();
            statusBar()->showMessage("Media aggiunto con successo", 2000);
        }
    }

    delete tempMedia;
    delete visitor;
}

void MainWindow::editMedia()
{
    if (!selectedMedia)
    {
        QMessageBox::warning(this, "Attenzione", "Seleziona un media da modificare.");
        return;
    }

    QList<Media *> currentMedia = biblioteca.getTuttiMedia();
    if (!currentMedia.contains(selectedMedia))
    {
        QMessageBox::critical(this, "Errore", "L'elemento selezionato non è più valido. Prova a selezionarlo di nuovo.");
        selectedMedia = nullptr;
        updateMediaDisplay();
        return;
    }

    MediaVisitor *visitor = new MediaWidgetVisitor(true);
    selectedMedia->accept(*visitor);
    QWidget *widget = (static_cast<MediaWidgetVisitor *>(visitor))->getWidget();

    MediaWidgetVisitor *editVisitor = static_cast<MediaWidgetVisitor *>(visitor);
    editVisitor->populateFields(selectedMedia);

    QDialog dialog(this);
    dialog.setWindowTitle("Modifica Media");
    dialog.setModal(true);

    QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);
    dialogLayout->addWidget(widget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okBtn = new QPushButton("Salva");
    QPushButton *cancelBtn = new QPushButton("Annulla");

    buttonLayout->addStretch();
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);

    dialogLayout->addLayout(buttonLayout);

    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        selectedMedia->setTitle(editVisitor->getTitle());
        selectedMedia->setYear(editVisitor->getYear());
        selectedMedia->setCoverImagePath(editVisitor->getCoverImagePath());
        selectedMedia->setCopiesAvailable(editVisitor->getCopiesAvailable());

        if (Book *book = dynamic_cast<Book *>(selectedMedia))
        {
            book->setAuthor(editVisitor->getAuthor());
            book->setIsbn(editVisitor->getIsbn());
            book->setPublisher(editVisitor->getPublisher());
        }
        else if (Film *film = dynamic_cast<Film *>(selectedMedia))
        {
            film->setDirector(editVisitor->getDirector());
            film->setDuration(editVisitor->getDuration());
            film->setGenere(editVisitor->getGenere());
        }
        else if (MagazineArticle *article = dynamic_cast<MagazineArticle *>(selectedMedia))
        {
            article->setAuthor(editVisitor->getArticleAuthor());
            article->setMagazine(editVisitor->getMagazine());
            article->setDoi(editVisitor->getDoi());
        }

        updateMediaDisplay();
        statusBar()->showMessage("Media modificato con successo", 2000);
    }

    delete visitor;
}

void MainWindow::deleteMedia()
{
    if (!selectedMedia)
    {
        QMessageBox::warning(this, "Attenzione", "Seleziona un media da eliminare.");
        return;
    }

    QList<Media *> currentMedia = biblioteca.getTuttiMedia();
    if (!currentMedia.contains(selectedMedia))
    {
        QMessageBox::critical(this, "Errore", "L'elemento selezionato non è più valido. Prova a selezionarlo di nuovo.");
        selectedMedia = nullptr;
        updateMediaDisplay();
        return;
    }

    int ret = QMessageBox::question(this, "Conferma",
                                    QString("Sei sicuro di voler eliminare \"%1\"?").arg(selectedMedia->getTitle()),
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
        biblioteca.rimuoviMedia(selectedMedia);
        selectedMedia = nullptr;
        updateMediaDisplay();
        statusBar()->showMessage("Media eliminato con successo", 2000);
    }
}

void MainWindow::searchMedia()
{
    updateMediaDisplay();

    QString searchTerm = searchEdit->text().trimmed(); // trimmed serve a rimuovere spazi vuoti
    if (!searchTerm.isEmpty())
    {
        QList<Media *> results = getFilteredMedia();
        statusBar()->showMessage(QString("Trovati %1 risultati per \"%2\"").arg(results.size()).arg(searchTerm), 3000); // 3000 serve per mostrare il messaggio per 3 secondi
    }
    else
    {
        statusBar()->showMessage("Visualizzati tutti i media", 2000);
    }
}

namespace
{
    static QString librariesDir()
    {
        QDir base(QCoreApplication::applicationDirPath());
#ifdef Q_OS_MAC
        // Se è un app bundle: Contents/MacOS -> risali al parent della .app
        if (base.dirName() == "MacOS")
        {
            base.cdUp(); // Contents
            base.cdUp(); // .app
            base.cdUp(); // cartella che contiene la .app
        }
#endif
        return base.filePath("data/bibliotecas");
    }
}

void MainWindow::saveLibrary()
{
    QString defaultDir = librariesDir();
    QDir().mkpath(defaultDir);

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Salva Biblioteca",
                                                    defaultDir + "/biblioteca.json",
                                                    "JSON Files (*.json);;All Files (*)");
    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith(".json", Qt::CaseInsensitive))
        {
            fileName += ".json";
        }

        JsonSerializer serializer;
        if (serializer.salvaBiblioteca(biblioteca, fileName))
        {
            statusBar()->showMessage(QString("Biblioteca salvata: %1").arg(QFileInfo(fileName).fileName()), 3000);
            QMessageBox::information(this, "Salvataggio Completato",
                                     QString("La biblioteca è stata salvata con successo in:\n%1").arg(fileName));
        }
        else
        {
            QMessageBox::critical(this, "Errore di Salvataggio",
                                  "Impossibile salvare la biblioteca.\nVerifica i permessi di scrittura del file.");
        }
    }
}

void MainWindow::loadLibrary()
{
    QString defaultDir = librariesDir();
    QDir().mkpath(defaultDir);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Carica Biblioteca",
                                                    defaultDir,
                                                    "JSON Files (*.json);;All Files (*)");
    if (!fileName.isEmpty())
    {
        if (biblioteca.dimensione() > 0)
        {
            int ret = QMessageBox::question(this, "Conferma Caricamento",
                                            QString("La biblioteca attuale contiene %1 elementi.\n"
                                                    "Caricando una nuova biblioteca, tutti i dati attuali andranno persi.\n\n"
                                                    "Vuoi continuare?")
                                                .arg(biblioteca.dimensione()),
                                            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                            QMessageBox::No);

            if (ret != QMessageBox::Yes)
            {
                return;
            }
        }

        try
        {
            JsonSerializer serializer;
            Biblioteca loadedLibrary;

            serializer.caricaBiblioteca(loadedLibrary, fileName);
            selectedMedia = nullptr;
            clearMediaDisplay();

            // forzo la pulizia degli eventi in coda
            QCoreApplication::processEvents();

            biblioteca = loadedLibrary;

            // permette di attendere un momento prima di aggiornare il display
            QTimer::singleShot(100, this, [this]()
                               { updateMediaDisplay(); });

            statusBar()->showMessage(QString("Biblioteca caricata: %1 elementi").arg(biblioteca.dimensione()), 3000);
            QMessageBox::information(this, "Caricamento Completato",
                                     QString("La biblioteca è stata caricata con successo!\n"
                                             "Elementi caricati: %1\n"
                                             "File: %2")
                                         .arg(biblioteca.dimensione())
                                         .arg(QFileInfo(fileName).fileName()));
        }
        catch (const FileNotFoundException &e)
        {
            QMessageBox::critical(this, "File non trovato",
                                  QString("Il file selezionato non può essere aperto:\n%1")
                                      .arg(QString::fromStdString(e.what())));
        }
        catch (const JsonParseException &e)
        {
            QMessageBox::critical(this, "Errore nel formato del file",
                                  QString("Il file JSON non è valido o è corrotto:\n%1")
                                      .arg(QString::fromStdString(e.what())));
        }
        catch (const BibliotecaException &e)
        {
            QMessageBox::critical(this, "Errore di caricamento",
                                  QString("Si è verificato un errore durante il caricamento:\n%1")
                                      .arg(QString::fromStdString(e.what())));
        }
        catch (...)
        {
            QMessageBox::critical(this, "Errore imprevisto",
                                  "Si è verificato un errore imprevisto durante il caricamento della biblioteca.");
        }
    }
}

void MainWindow::loadDefaultLibrary()
{
    const QString dir = librariesDir();
    QString exampleFile = QDir(dir).filePath("biblioteca_esempio.json");
    QFileInfo fileInfo(exampleFile);

    if (fileInfo.exists() && fileInfo.isReadable())
    {
        JsonSerializer serializer;
        Biblioteca loadedLibrary;
        if (serializer.caricaBiblioteca(loadedLibrary, exampleFile))
        {
            biblioteca = loadedLibrary;
            selectedMedia = nullptr; // Reset selection
            statusBar()->showMessage(QString("Biblioteca di esempio caricata (%1 elementi)").arg(biblioteca.dimensione()), 2000);
        }
    }
    else
    {
        QString backupFile = QDir::currentPath() + "/data/bibliotecas/ultima_sessione.json";
        QFileInfo backupInfo(backupFile);

        if (backupInfo.exists() && backupInfo.isReadable())
        {
            JsonSerializer serializer;
            Biblioteca loadedLibrary;
            if (serializer.caricaBiblioteca(loadedLibrary, backupFile))
            {
                biblioteca = loadedLibrary;
                selectedMedia = nullptr;
                statusBar()->showMessage(QString("Ultima sessione ripristinata (%1 elementi)").arg(biblioteca.dimensione()), 2000);
            }
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QWidget *widget = qobject_cast<QWidget *>(obj);
        if (widget && widget->property("clickable").toBool())
        {
            QVariant mediaVariant = widget->property("media");
            if (mediaVariant.isValid() && !mediaVariant.isNull())
            {
                Media *media = static_cast<Media *>(mediaVariant.value<void *>());
                QList<Media *> currentMedia = biblioteca.getTuttiMedia();
                if (media && currentMedia.contains(media))
                {
                    selectedMedia = media;
                    QString title = media->getTitle();
                    if (!title.isNull())
                    {
                        statusBar()->showMessage(QString("Selezionato: %1").arg(title), 20000);
                    }
                    else
                    {
                        statusBar()->showMessage("Elemento selezionato", 10000);
                    }
                }
                else
                {
                    widget->setProperty("media", QVariant());
                    widget->setProperty("clickable", QVariant());
                    return QMainWindow::eventFilter(obj, event);
                }
            }
            else
            {
                return QMainWindow::eventFilter(obj, event);
            }
        }
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

// salva automaticamente la seesione prima di chiuderla
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (biblioteca.dimensione() > 0)
    {
        QString backupDir = QDir::currentPath() + "/data/bibliotecas";
        QDir().mkpath(backupDir);
        QString backupFile = backupDir + "/ultima_sessione.json";

        JsonSerializer serializer;
        if (serializer.salvaBiblioteca(biblioteca, backupFile))
        {
            statusBar()->showMessage("Sessione salvata automaticamente.", 2000);
        }
    }
    event->accept();
}