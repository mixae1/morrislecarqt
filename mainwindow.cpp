#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
#include "morrislecar.h"
#include <QMessageBox>
#include <QString>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new MorrisLecar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::qstod(const QString& qs, double& dest){
    bool ok(false);
    double d = qs.toDouble(&ok);
    if (ok) {
        dest = d;
    }
    return ok;
}

std::pair<bool, std::vector<double>> MainWindow::get_values(){
    std::vector<double> ret = std::vector<double>(15);

    if(!qstod(ui->lineEdit->text(), ret[0]) ||
            !qstod(ui->lineEdit_1->text(), ret[1]) ||
            !qstod(ui->lineEdit_2->text(), ret[2]) ||
            !qstod(ui->lineEdit_3->text(), ret[3]) ||
            !qstod(ui->lineEdit_4->text(), ret[4]) ||
            !qstod(ui->lineEdit_5->text(), ret[5]) ||
            !qstod(ui->lineEdit_6->text(), ret[6]) ||
            !qstod(ui->lineEdit_7->text(), ret[7]) ||
            !qstod(ui->lineEdit_8->text(), ret[8]) ||
            !qstod(ui->lineEdit_9->text(), ret[9]) ||
            !qstod(ui->lineEdit_10->text(), ret[10]) ||
            !qstod(ui->lineEdit_11->text(), ret[11]) ||
            !qstod(ui->lineEdit_12->text(), ret[12]) ||
            !qstod(ui->lineEdit_13->text(), ret[13]) ||
            !qstod(ui->lineEdit_14->text(), ret[14])){
        QMessageBox::warning(this, "Warning","A field is incorrect.");
        return std::make_pair(false, ret);
    }

    return std::make_pair(true, ret);
}

//calc
void MainWindow::on_pushButton_clicked(){
    auto values = get_values();
    if(!values.first){
        QMessageBox::warning(this, "Warning","Something went wrong.");
        return;
    }
    if(values.second.size() != 15){
        QMessageBox::warning(this, "Warning","Something went wrong.");
        return;
    }

    model->load_values(values.second);
    model->calc_data();

    auto ret = model->get_data();
    QLineSeries *series = new QLineSeries();
    for(int i = 0; i < ret.size(); i++){
        series->append(i/model->get_accuracy(), ret[i].first);
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("V\T");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->stackedWidget->addWidget(chartView);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::set_default() {
    ui->lineEdit->setText(QString::number(model->_V_Ca));
    ui->lineEdit_1->setText(QString::number(model->_V_K));
    ui->lineEdit_2->setText(QString::number(model->_V_L));
    ui->lineEdit_3->setText(QString::number(model->_V_1));
    ui->lineEdit_4->setText(QString::number(model->_V_2));
    ui->lineEdit_5->setText(QString::number(model->_V_3));
    ui->lineEdit_6->setText(QString::number(model->_V_4));
    ui->lineEdit_7->setText(QString::number(model->_g_Ca));
    ui->lineEdit_8->setText(QString::number(model->_g_K));
    ui->lineEdit_9->setText(QString::number(model->_g_L));
    ui->lineEdit_10->setText(QString::number(model->_C));
    ui->lineEdit_11->setText(QString::number(model->_phi));
    ui->lineEdit_12->setText(QString::number(model->_I_ext));
    ui->lineEdit_13->setText(QString::number(model->_time));
    ui->lineEdit_14->setText(QString::number(model->_accuracy));
}

void MainWindow::on_pushButton_2_clicked() {
    set_default();
}

void MainWindow::add_charts(QChartView* chartview, QChartView* chartview2){
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->stackedWidget->addWidget(chartview);
    ui->stackedWidget->addWidget(chartview2);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::create_model(){
    model = new MorrisLecar();
    model->calc_data();
    auto ret = model->get_data();

    // 1
    QLineSeries *series = new QLineSeries();
    for(int i = 0; i < ret.size(); i++){
        series->append(i/model->get_accuracy(), ret[i].first);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("V / T");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 2
    QLineSeries *series2 = new QLineSeries();
    for(int i = 0; i < ret.size(); i++){
        series2->append(ret[i].first, ret[i].second);
    }

    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->createDefaultAxes();
    chart2->setTitle("N / V");
    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    //QComboBox *pageComboBox = new QComboBox;
    //pageComboBox->addItem(tr("Page 1"));
    //pageComboBox->addItem(tr("Page 2"));
    //connect(pageComboBox, QOverload<int>::of(&QComboBox::activated), ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    add_charts(chartView, chartView2);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
