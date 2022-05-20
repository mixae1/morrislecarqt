#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include "morrislecar.h"

using namespace QtCharts;

int main(int argc, char *argv[])
{

/*

*/
    QApplication a(argc, argv);

    MainWindow window;

    MorrisLecar ml = MorrisLecar(100.);
    ml.calc_data(250);
    auto ret = ml.get_data();
    QLineSeries *series = new QLineSeries();
    for(int i = 0; i < ret.size(); i++){
        series->append(i*0.1, ret[i].first);
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("V\T");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
