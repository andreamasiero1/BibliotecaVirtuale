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

MainWindow::MainWindow(QStackedWidget *stackWidget, QWidget *parent) : QMainWindow(parent), stack(stackWidget)
{
    // Set the title of the window
    setWindowTitle("Media Library");
    // Set the size of the window
    setMinimumSize(800, 600);
    // Create a logPage widget
    QWidget *logPage = new QWidget(this);
    // Create a layout for the logPage
    QVBoxLayout *logLayout = new QVBoxLayout(logPage);
    // Create a label for the logPage
    QLabel *logLabel = new QLabel("Log Page", logPage);
    // Create a line edit for the logPage
    QLineEdit *logLineEdit = new QLineEdit(logPage);
    // Create a button for the logPage
    QPushButton *logButton = new QPushButton("Log In", logPage);
}