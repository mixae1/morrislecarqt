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

    void set_default();

    void create_model();

private slots:

    std::pair<bool, std::vector<double>> get_values();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void add_chart(QChartView* chartview);

    bool qstod(const QString& qs, double& dest);

private:
    Ui::MainWindow *ui;
    MorrisLecar* model;
};

#endif // MAINWINDOW_H
