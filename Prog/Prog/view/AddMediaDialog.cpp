#include "AddMediaDialog.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/MagazineArticle.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPixmap>
#include <QDir>
#include <QFileInfo>

AddMediaDialog::AddMediaDialog(Biblioteca &biblioteca, QWidget *parent) : QDialog(parent), biblioteca(biblioteca)
{
    setupUI();
    setWindowTitle("Aggiungi Nuovo Media");
}

AddMediaDialog::~AddMediaDialog()
{
}

void AddMediaDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *commonFormLayout = new QFormLayout();
    titleEdit = new QLineEdit();
    yearSpinBox = new QSpinBox();
    yearSpinBox->setRange(1000, 2100);
    yearSpinBox->setValue(QDate::currentDate().year());
    copiesSpinBox = new QSpinBox();
    copiesSpinBox->setRange(1, 10000);
    copiesSpinBox->setValue(1);
    coverImagePathEdit = new QLineEdit();
    coverImagePathEdit->setReadOnly(true);
    QPushButton *selectImageBtn = new QPushButton("Seleziona Immagine");
    connect(selectImageBtn, &QPushButton::clicked, this, &AddMediaDialog::selectCoverImage);
    commonFormLayout->addRow("Titolo:", titleEdit);
    commonFormLayout->addRow("Anno:", yearSpinBox);
    commonFormLayout->addRow("Copie disponibili:", copiesSpinBox);
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(coverImagePathEdit);
    imageLayout->addWidget(selectImageBtn);
    commonFormLayout->addRow("Copertina:", imageLayout);
    // Anteprima rimossa su richiesta: nessuna QLabel per preview
    mainLayout->addLayout(commonFormLayout);

    QComboBox *mediaTypeComboBox = new QComboBox();
    mediaTypeComboBox->addItem("Libro");
    mediaTypeComboBox->addItem("Film");
    mediaTypeComboBox->addItem("Articolo di Rivista");
    connect(mediaTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddMediaDialog::onMediaTypeChanged);
    mainLayout->addWidget(mediaTypeComboBox);

    stackedWidget = new QStackedWidget();
    createBookForm();
    createFilmForm();
    createMagazineArticleForm();
    mainLayout->addWidget(stackedWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddMediaDialog::addMediaConfirmed);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddMediaDialog::reject);
    mainLayout->addWidget(buttonBox);

    onMediaTypeChanged(0);
}

void AddMediaDialog::createBookForm()
{
    QWidget *bookPage = new QWidget();
    QFormLayout *formLayout = new QFormLayout(bookPage);
    bookAuthorEdit = new QLineEdit();
    bookIsbnEdit = new QLineEdit();
    bookPublisherEdit = new QLineEdit();
    formLayout->addRow("Autore:", bookAuthorEdit);
    formLayout->addRow("ISBN:", bookIsbnEdit);
    formLayout->addRow("Editore:", bookPublisherEdit);
    stackedWidget->addWidget(bookPage);
}

void AddMediaDialog::createFilmForm()
{
    QWidget *filmPage = new QWidget();
    QFormLayout *formLayout = new QFormLayout(filmPage);
    filmDirectorEdit = new QLineEdit();
    filmDurationSpinBox = new QSpinBox();
    filmDurationSpinBox->setRange(1, 1000);
    filmGenreEdit = new QLineEdit();
    formLayout->addRow("Regista:", filmDirectorEdit);
    formLayout->addRow("Durata (min):", filmDurationSpinBox);
    formLayout->addRow("Genere:", filmGenreEdit);
    stackedWidget->addWidget(filmPage);
}

void AddMediaDialog::createMagazineArticleForm()
{
    QWidget *articlePage = new QWidget();
    QFormLayout *formLayout = new QFormLayout(articlePage);
    articleAuthorEdit = new QLineEdit();
    articleMagazineEdit = new QLineEdit();
    articleDoiEdit = new QLineEdit();
    formLayout->addRow("Autore:", articleAuthorEdit);
    formLayout->addRow("Rivista:", articleMagazineEdit);
    formLayout->addRow("DOI:", articleDoiEdit);
    stackedWidget->addWidget(articlePage);
}

void AddMediaDialog::onMediaTypeChanged(int index)
{
    stackedWidget->setCurrentIndex(index);
}

void AddMediaDialog::selectCoverImage()
{
    QString defaultDir = QDir::currentPath() + "/data/images";
    QDir().mkpath(defaultDir);
    QString imagePath = QFileDialog::getOpenFileName(this, "Seleziona Immagine di Copertina", defaultDir, "Immagini (*.png *.jpg *.jpeg *.gif)");
    if (!imagePath.isEmpty())
    {
        selectedCoverImagePath = imagePath;
        coverImagePathEdit->setText(QFileInfo(imagePath).fileName());
    }
}

void AddMediaDialog::addMediaConfirmed()
{
    QString title = titleEdit->text();
    int year = yearSpinBox->value();
    int copies = copiesSpinBox->value();
    QString coverImagePath = selectedCoverImagePath;

    try
    {
        Media *newMedia = nullptr;
        int currentIndex = stackedWidget->currentIndex();

        if (currentIndex == 0)
        {
            QString author = bookAuthorEdit->text();
            QString isbn = bookIsbnEdit->text();
            QString publisher = bookPublisherEdit->text();
            newMedia = MediaFactory::createBook(title, year, author, isbn, publisher, coverImagePath);
        }
        else if (currentIndex == 1)
        {
            QString director = filmDirectorEdit->text();
            int duration = filmDurationSpinBox->value();
            QString genre = filmGenreEdit->text();
            newMedia = MediaFactory::createFilm(title, year, director, duration, genre, coverImagePath);
        }
        else if (currentIndex == 2)
        {
            QString author = articleAuthorEdit->text();
            QString magazine = articleMagazineEdit->text();
            QString doi = articleDoiEdit->text();
            newMedia = MediaFactory::createMagazineArticle(title, year, author, magazine, doi, coverImagePath);
        }

        if (newMedia)
        {
            newMedia->setCopiesAvailable(copies);
            biblioteca.aggiungiMedia(newMedia);
            QMessageBox::information(this, "Successo", "Media aggiunto con successo!");
            accept();
        }
    }
    catch (const InvalidDataException &e)
    {
        QMessageBox::warning(this, "Dati non validi", QString::fromStdString(e.what()));
    }
    catch (const DuplicateMediaException &e)
    {
        QMessageBox::warning(this, "Media duplicato", QString::fromStdString(e.what()));
    }
    catch (const BibliotecaException &e)
    {
        QMessageBox::critical(this, "Errore", QString::fromStdString(e.what()));
    }
    catch (...)
    {
        QMessageBox::critical(this, "Errore", "Si è verificato un errore imprevisto.");
    }
}
