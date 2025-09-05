#ifndef MEDIAWIDGETVISITOR_H
#define MEDIAWIDGETVISITOR_H

#include "MediaVisitor.h"
#include "../model/Media.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QFileInfo>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

class MediaWidgetVisitor : public QObject, public MediaVisitor
{
    Q_OBJECT

public:
    MediaWidgetVisitor(bool isEditMode = false);
    ~MediaWidgetVisitor();

    QWidget *visit(Book *book) override;
    QWidget *visit(Film *film) override;
    QWidget *visit(MagazineArticle *article) override;

    QWidget *getWidget() const;

    QString getTitle() const;
    int getYear() const;
    QString getCoverImagePath() const;
    int getCopiesAvailable() const;

    QString getAuthor() const;
    QString getISBN() const;
    QString getPublisher() const;
    QString getDirector() const;
    int getDuration() const;
    QString getGenere() const;

    QString getArticleAuthor() const;
    QString getMagazine() const;
    QString getDoi() const;

    void populateFields(Media *media);

private slots:
    void selectCoverImage();

private:
    bool editMode;
    QWidget *currentWidget;

    QLineEdit *titleEdit;
    QSpinBox *yearSpin;
    QLineEdit *coverImageEdit;
    QPushButton *browseImageBtn;
    QSpinBox *copiesSpin;

    QLineEdit *authorEdit;
    QLineEdit *isbnEdit;
    QLineEdit *publisherEdit;

    QLineEdit *directorEdit;
    QSpinBox *durationSpin;
    QLineEdit *genreEdit;

    QLineEdit *articleAuthorEdit;
    QLineEdit *magazineEdit;
    QLineEdit *doiEdit;

    QWidget *createBaseWidget(const QString &title, int year, const QString &coverImagePath);
    void addBookSpecificInfo(QWidget *widget, const QString &author, const QString &isbn, const QString &publisher);
    void addFilmSpecificInfo(QWidget *widget, const QString &director, int duration, const QString &genre);
    void addMagazineArticleSpecificInfo(QWidget *widget, const QString &author, const QString &magazine, const QString &doi);

    void createCommonFields(QFormLayout *layout);
    void setupImageSelection();
};

#endif
