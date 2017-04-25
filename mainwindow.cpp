#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QSplitter>

#include "gametypeconfigwidget.h"
#include "lanconfigwidget.h"
#include "maxplayersconfigwidget.h"
#include "mapconfigwidget.h"
#include "maxscoreconfigwidget.h"
#include "teamdamageconfigwidget.h"
#include "servernameconfigwidget.h"
#include "timelimitconfigwidget.h"
#include "passwordconfigwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Q_INIT_RESOURCE(teeworldsserver);

    
    installPath = QFileDialog::getExistingDirectory(this, QStringLiteral("Open teeworlds install directory"),
                                               QDir::homePath());


    if(installPath == "") {
        QMessageBox::warning(this, "No directory passed", "No teeworlds install directory specified, exiting");
        QApplication::quit();
    }

    // make sure it's good
    QString srvExe =
#ifdef Q_OS_WIN32
    installPath + "/teeworlds_srv.exe"
#else
    installPath + "/teeworlds_srv"
#endif
    ;
    
    QFileInfo info(srvExe);
    if(!info.exists()) {
        QMessageBox::warning(this, "Bad teeworlds install directory",
                             "Could not find \"" + srvExe + "\" in " + installPath);
        QApplication::quit();

    }

    auto splitter = new QSplitter;
    setCentralWidget(splitter);
    splitter->setOrientation(Qt::Vertical);

    output = new QPlainTextEdit;
    output->setReadOnly(true);


    auto mainWidget = new QWidget;
    auto mapView = new QLabel;
    mapView->setMinimumSize(splitter->sizeHint());
    
    splitter->addWidget(mainWidget);
    splitter->addWidget(output);
    
    splitter->setChildrenCollapsible(false);
    
    auto configHolder = new QWidget;
    
    auto hbox = new QHBoxLayout;
    mainWidget->setLayout(hbox);
    hbox->addWidget(configHolder);
    hbox->addWidget(mapView);
    
    auto layout = new QGridLayout;
    configHolder->setLayout(layout);
    
    addConfigWidget(new ServerNameConfigWidget, 0, layout);
    addConfigWidget(new PasswordConfigWidget, 1, layout);
    addConfigWidget(new LanConfigWidget, 2, layout);
    addConfigWidget(new GameTypeConfigWidget, 3, layout);
    auto mapConfigWidget = new MapConfigWidget(installPath);
    addConfigWidget(mapConfigWidget, 4, layout);
    addConfigWidget(new MaxPlayersConfigWidget, 5, layout);
    addConfigWidget(new MaxScoreConfigWidget, 6, layout);
    addConfigWidget(new TimeLimitConfigWidget, 7, layout);
    addConfigWidget(new TeamDamageConfigWidget, 8, layout);
    
    connect(mapConfigWidget, &MapConfigWidget::mapChanged, this, [this, mapView](QString map) {
        pixmapForMap = QPixmap(":/map/" + map + ".png");
        if(pixmapForMap.isNull()) {
            qDebug() << "Pixmap null: " << (":/map/" +  map + ".png");
        }
        mapView->setPixmap(pixmapForMap.scaled(600, 600, Qt::KeepAspectRatio));
    });
    mapConfigWidget->mapChanged("dm1");

    auto buttons = new QWidget;
    auto buttonslayout = new QHBoxLayout;
    buttons->setLayout(buttonslayout);
    goButton = new QPushButton;
    buttonslayout->addWidget(goButton);
    goButton->setText("Go!");
    connect(goButton, &QPushButton::clicked, this, [this, srvExe] {
        QString config;
        for(auto widget : configWidgets) {
            config += widget->getConfigString() + "\n";
        }
        auto configPath = 
#ifdef Q_OS_WIN32
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/../Teeworlds/server.cfg"
#else
            QDir::homePath() + "/.teeworlds/server.cfg"
#endif
            ;
        {
            QFile f(configPath);
            if(f.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&f);
                stream << config;
            } else {
                qDebug() << "Failed to write to " << configPath << " with error: " << f.errorString();
            }
        }
        serverProcess = new QProcess;
        serverProcess->start(srvExe, QStringList() << "-f" << "server.cfg");

        killButton->setEnabled(true);
        disablePickers();
        goButton->setEnabled(false);

        output->clear();

        connect(serverProcess, &QProcess::readyReadStandardOutput, this, [this]{
            output->appendPlainText(serverProcess->readAllStandardOutput().constData());
        });
        connect(serverProcess, &QProcess::readyReadStandardError, this, [this]{
            output->appendPlainText(serverProcess->readAllStandardError().constData());
        });
        connect(serverProcess, &QProcess::aboutToClose, this, [this] {
            enablePickers();
            killButton->setEnabled(false);
            goButton->setEnabled(true);
            delete serverProcess;
            serverProcess = nullptr;
        });

    });
    killButton = new QPushButton;
    buttonslayout->addWidget(killButton);
    killButton->setText("Kill Server");
    killButton->setEnabled(false);
    connect(killButton, &QPushButton::clicked, this, [this]{
        if(serverProcess) {
            serverProcess->kill();
            enablePickers();
            killButton->setEnabled(false);
            goButton->setEnabled(true);
            delete serverProcess;
            serverProcess = nullptr;
        }
    });


    layout->addWidget(buttons);
}

void MainWindow::addConfigWidget(ConfigWidget* widget, int row, QGridLayout* layout)
{
    layout->addWidget(new QLabel(widget->getLabel()), row, 0);
    layout->addWidget(widget, row, 1);
    
    configWidgets.push_back(widget);
}

void MainWindow::disablePickers()
{
    for(auto item : configWidgets) {
        item->setEnabled(false);
    }
}

void MainWindow::enablePickers()
{
    for(auto item : configWidgets) {
        item->setEnabled(true);
    }
}


MainWindow::~MainWindow()
{
    if(serverProcess) {
        serverProcess->kill();
    }
}
