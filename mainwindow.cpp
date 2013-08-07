#include "mainwindow.hpp"
#include "ui_mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this);
    timer->start(10);

    setFixedSize(1100,600);
    ui->setupUi(this);

    life = new Automaton(40,
			 255, 10, 1, 10,
                         this);

    graphics = new Graphics(ui->glView->width(),
                            ui->glView->height(),
                            this);



    initConnections();
    initComponents();
}

void MainWindow::initConnections()
{
    connect(ui->pushButton,SIGNAL(clicked()),
            this->life, SLOT(Randomize()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            this->life, SLOT(ChangeSpeed(int)));

    connect(timer,SIGNAL(timeout()),
            this->life,SLOT(Update()));

    connect(ui->pushButton_2,SIGNAL(clicked()),
            this->life, SLOT(Clear()));

    connect(this->life,SIGNAL(updated()),
            ui->glView,SLOT(updateGL()));

    connect(ui->glView, SIGNAL(pauseAutomaton()),
            this->life, SLOT(stop()));

    connect(ui->glView, SIGNAL(startAutomaton()),
            this->life, SLOT(start()));

    connect(ui->pushButton_5, SIGNAL(clicked()),
            this->life, SLOT(stop()));

    connect(ui->pushButton_4, SIGNAL(clicked()),
            this->life, SLOT(start()));

    connect(this->life, SIGNAL(statusChanged(QString,int)),
            ui->statusBar, SLOT(showMessage(QString,int)));
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
    default: break;
    }
}
