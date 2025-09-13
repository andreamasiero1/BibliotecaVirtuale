#ifndef EDITMEDIADIALOG_H
#define EDITMEDIADIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "Biblioteca.h"
#include "../model/Media.h"

class EditMediaDialog : public QDialog {
    Q_OBJECT

public:
    EditMediaDialog(Biblioteca& biblioteca, Media* mediaToEdit, QWidget *parent = nullptr);
    ~EditMediaDialog();

private slots:
    void selectCoverImage();
    void editMediaConfirmed();

private:
    Biblioteca& biblioteca;
    Media* currentMedia;
    QStackedWidget *stackedWidget;
    QLineEdit *titleEdit;
    QSpinBox *yearSpinBox;
    QLineEdit *coverImagePathEdit;
    QLabel *coverImagePreview;
    QString selectedCoverImagePath;

    QLineEdit *bookAuthorEdit;
    QLineEdit *bookIsbnEdit;
    QLineEdit *bookPublisherEdit;

    QLineEdit *filmDirectorEdit;
    QSpinBox *filmDurationSpinBox;
    QLineEdit *filmGenreEdit;

    QLineEdit *articleAuthorEdit;
    QLineEdit *articleMagazineEdit;
    QLineEdit *articleDoiEdit;

    void setupUI();
    void createBookForm();
    void createFilmForm();
    void createMagazineArticleForm();
    void populateFields();
};

#endif // EDITMEDIADIALOG_H

