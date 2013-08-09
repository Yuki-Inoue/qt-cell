#include "mainwindow.hpp"
#include "ui_mainwindow.hpp"
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    timer->start(10);

    setFixedSize(1100,600);
    ui->setupUi(this);

    life = new Automaton(40,
			 255,
			 ui->k1DoubleSpinBox->value(),
			 ui->k2DoubleSpinBox->value(),
			 ui->gDoubleSpinBox->value(),
                         this);

    graphics = new Graphics(ui->glView->width(),
                            ui->glView->height(),
                            this);



    initConnections();
    initComponents();
}

void MainWindow::initConnections()
{
    connect(ui->gDoubleSpinBox, SIGNAL(valueChanged(double)),
	    this->life, SLOT(setG(double)));

    connect(ui->k1DoubleSpinBox, SIGNAL(valueChanged(double)),
	    this->life, SLOT(setK1(double)));

    connect(ui->k2DoubleSpinBox, SIGNAL(valueChanged(double)),
	    this->life, SLOT(setK2(double)));

    connect(ui->randomizeButton,SIGNAL(clicked()),
            this->life, SLOT(Randomize()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            this->life, SLOT(ChangeSpeed(int)));

    connect(timer,SIGNAL(timeout()),
            this->life,SLOT(Update()));

    connect(ui->clearButton,SIGNAL(clicked()),
            this->life, SLOT(Clear()));

    connect(this->life,SIGNAL(updated()),
            ui->glView,SLOT(updateGL()));

    connect(ui->glView, SIGNAL(pauseAutomaton()),
            this->life, SLOT(stop()));

    connect(ui->glView, SIGNAL(startAutomaton()),
            this->life, SLOT(start()));

    connect(ui->startButton, SIGNAL(clicked()),
	    this, SLOT(startGame()));

    connect(ui->stopButton, SIGNAL(clicked()),
            this, SLOT(stopGame()));

    connect(this->life, SIGNAL(statusChanged(QString,int)),
            ui->statusBar, SLOT(showMessage(QString,int)));
}

void MainWindow::startGame(){
    life->start();
    ui->gDoubleSpinBox->setReadOnly(true);
    ui->k1DoubleSpinBox->setReadOnly(true);
    ui->k2DoubleSpinBox->setReadOnly(true);
}

void MainWindow::stopGame(){
    life->stop();
    ui->gDoubleSpinBox->setReadOnly(false);
    ui->k1DoubleSpinBox->setReadOnly(false);
    ui->k2DoubleSpinBox->setReadOnly(false);
}

void MainWindow::initComponents()
{
    ui->glView->setAutomaton(life);
    ui->glView->setGraphics(graphics);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space: {
        life->Update();
        break;
    }
    case Qt::Key_R: {
        life->Randomize();
        break;
    }
    case Qt::Key_S: {
	(life->isRunning()? ui->stopButton: ui->startButton)
	    -> click();
	break;
    }
    default: break;
    }
}
