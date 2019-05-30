#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDir>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

void MainWidget::load() {

    ColladaParser parser;
    string s = "resources\\human_walk.dae";
    Model m = parser.loadColladaFile(s);
    for(int i = 0; i < m.getBones().size(); i++) {
        std::cout << m.getBones()[i].getId() << " " <<m.getBones()[i].getTransform().data()[0] << "\n";
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}
