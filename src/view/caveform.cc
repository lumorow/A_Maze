#include "caveform.h"

#include "cavescene.h"
#include "ui_caveform.h"

CaveForm::CaveForm(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CaveForm) {
  mode = 0;
  ui->setupUi(this);
  ui->widgetcave->SetController(controller);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(on_Step_clicked()));
}

CaveForm::~CaveForm() { delete ui; }

void CaveForm::on_pushButton_clicked() {
  QString str =
      QFileDialog::getOpenFileName(this, "open file", "/src/", "*.txt");
  if (!str.isEmpty()) {
    ui->widgetcave->DrawCave(str);
    QList<QString> name = str.split('/');
    ui->label->setText(name.last());
  }
  update();
}

void CaveForm::on_Step_clicked() {
  ui->widgetcave->setLimitsBD(ui->BirthLimit->value(), ui->DeathLimit->value());
  update();
}

void CaveForm::on_Generate_clicked() {
  timer->stop();
  mode = false;
  ui->widgetcave->generateRandomMap(ui->Height->value(), ui->Width->value(),
                                    ui->BirthChanch->value());
  update();
}

void CaveForm::on_Auto_clicked() {
  if (!mode) {
    timer->start(ui->Time->value() * 1000);
    mode = true;
  } else {
    timer->stop();
    mode = false;
  }
}
