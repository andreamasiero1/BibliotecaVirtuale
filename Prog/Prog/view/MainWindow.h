#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QTimer>
#include <QCoreApplication>
#include "Biblioteca.h"
#include "Exceptions.h"
#include "../persistence/JsonSerializer.h"
#include "MediaWidgetVisitor.h"

Q_DECLARE_METATYPE(void *)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addMedia();
    void editMedia();
    void deleteMedia();
    void searchMedia();
    void saveLibrary();
    void loadLibrary();
    void onFilterChanged();
    void showMediaDetails();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void updateMediaDisplay();
    void clearMediaDisplay();
    void populateDisplayWithMedia(const QList<Media *> &mediaList);
    void clearLayout(QLayout *layout);
    void addMediaWidgetToGrid(Media *media, int row, int col);
    QList<Media *> getFilteredMedia() const;
    void loadDefaultLibrary();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Biblioteca biblioteca;

    QComboBox *mediaTypeFilter;
    QLineEdit *searchEdit;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QGridLayout *gridLayout;

    Media *selectedMedia;
};

#endif // MAINWINDOW_H
