#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QChart>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();      // 连接串口
    void readSerialData();             // 读取串口数据
    void on_btnSetFan_clicked();       // 设置风扇转速
    void on_btnSave_clicked();         // 保存数据


private:
    Ui::MainWindow *ui;

    QSerialPort *serialPort;           // 串口对象
    QChart *chart;                     // 图表对象
    QLineSeries *series;           // 温度曲线
    QDateTimeAxis *axisX;              // 时间轴
    QValueAxis *axisY;                 // 温度轴
    QChartView *chartView;  // 手动创建QChartView
    QTimer *dataTimer;
    double timeCounter = 0;

    void initChart();                  // 初始化图表
    void updateChart();      // 更新图表
    void saveToCSV(float temp, float hum); // 保存数据
};
#endif // MAINWINDOW_H
