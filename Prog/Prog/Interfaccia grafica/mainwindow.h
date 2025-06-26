#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QStackedWidget *stackWidget, QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    QStackedWidget *stack;
};

#endif // MAINWINDOW_H
