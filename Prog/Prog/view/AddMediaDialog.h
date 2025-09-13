#ifndef ADDMEDIADIALOG_H
#define ADDMEDIADIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "Biblioteca.h"
#include "MediaFactory.h"
#include "Exceptions.h"

class AddMediaDialog : public QDialog
{
    Q_OBJECT

public:
    AddMediaDialog(Biblioteca &biblioteca, QWidget *parent = nullptr);
    ~AddMediaDialog();

private slots:
    void onMediaTypeChanged(int index);
    void selectCoverImage();
    void addMediaConfirmed();

private:
    Biblioteca &biblioteca;
    QStackedWidget *stackedWidget;
    QLineEdit *titleEdit;
    QSpinBox *yearSpinBox;
    QLineEdit *coverImagePathEdit;
    QString selectedCoverImagePath;
    QSpinBox *copiesSpinBox;

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
};

#endif // ADDMEDIADIALOG_H
