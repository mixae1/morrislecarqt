#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "morrislecar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_default(int);

    void create_model();

private slots:

    std::pair<bool, std::vector<double>> get_values();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void add_charts(QChartView* chartview, QChartView* chartview2);

    bool qstod(const QString& qs, double& dest);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    MorrisLecar* model;
};

#endif // MAINWINDOW_H
