#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>

#include "configwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    void addConfigWidget(ConfigWidget* widget, int row, QGridLayout* layout);
    
    bool disablePickers();
    bool enablePickers();

    QPixmap pixmapForMap;
    std::vector<ConfigWidget*> configWidgets;
    QString installPath;
    QProcess* serverProcess;
    QPushButton* killButton, *goButton;
    QPlainTextEdit* output;
};

#endif // MAINWINDOW_H
