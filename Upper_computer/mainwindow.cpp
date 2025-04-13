#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splite->setFixedWidth(2); // 宽度为 2px（垂直分界线）
    ui->splite->setStyleSheet("background-color: #CCCCCC;"); // 颜色

    //初始化串口
    serialPort = new QSerialPort(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboPort->addItem(info.portName());
    }

    //初始化图表
    initChart();

    // 临时测试代码（可在构造函数中添加）
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &MainWindow::updateChart);
    dataTimer->start(100); // 100ms更新一次


    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::on_btnSave_clicked);
}

//初始化图表
void MainWindow::initChart(){

    // 初始化图表
    QChart *chart = new QChart();
//    chart->setTitle("模拟数据曲线");

    // 创建曲线对象
    QLineSeries *series = new QLineSeries();
    series->setName("温度数据");
    chart->addSeries(series);

    // 配置坐标轴
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTitleText("时间");
    axisX->setFormat("hh:mm:ss");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("温度 (°C)");
    axisY->setRange(0, 50);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 将图表绑定到提升的QChartView
    QChartView *chartView = qobject_cast<QChartView*>(ui->widgetChartContainer);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // 抗锯齿

    QChart *chart2 = new QChart();
//    chart2->setTitle("模拟数据曲线");

    QLineSeries *series2 = new QLineSeries();
    series2->setName("湿度数据");
    chart2->addSeries(series2);

    QDateTimeAxis *axisX2 = new QDateTimeAxis();
    axisX2->setTitleText("时间");
    axisX2->setFormat("hh:mm:ss");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    series2->attachAxis(axisX2);

    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("湿度 (%)");
    axisY2->setRange(0, 50);
    chart2->addAxis(axisY2, Qt::AlignLeft);
    series2->attachAxis(axisY2);

    QChartView *chartView2 = qobject_cast<QChartView*>(ui->widgetChartContainer_2);
    chartView2->setChart(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing); // 抗锯齿
}


// 连接/断开串口
void MainWindow::on_btnConnect_clicked() {
    if (serialPort->isOpen()) {
        serialPort->close();
        ui->btnConnect->setText("连接");
 //       ui->statusBar->showMessage("串口已关闭");
    } else {
        serialPort->setPortName(ui->comboPort->currentText());
        serialPort->setBaudRate(QSerialPort::Baud9600);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);

        if (serialPort->open(QIODevice::ReadWrite)) {
            connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
            ui->btnConnect->setText("断开");
            readSerialData();
  //          ui->statusBar->showMessage("已连接: " + ui->comboPort->currentText());
        } else {
            QMessageBox::critical(this, "错误", "无法打开串口！");
        }
    }
}

// 在类定义中添加成员变量用于存储数据
QString temperatureString;
QString humidityString;
QList<QPair<float, float>> sensorDataHistory;  // 可选：用于存储历史数据
float value =0;
float value2 =0;
// 读取串口数据
void MainWindow::readSerialData() {
    static QByteArray buffer;
    buffer += serialPort->readAll();

    // 按行解析数据（格式示例：TEMP:25.5,HUM:60）
    int idx = buffer.indexOf('\n');
    while (idx != -1) {
        QByteArray line = buffer.left(idx).trimmed();
        buffer = buffer.mid(idx + 1);

        QString str(line);
        if (str.startsWith("T:")) {
            bool parseSuccess = false;
            float temp = 0, hum = 0;

            // 更健壮的解析逻辑
            QStringList parts = str.split(",");
            if (parts.size() >= 2) {
                // 解析温度
                QString tempPart = parts[0].trimmed();
                if (tempPart.startsWith("T:")) {
                    temp = tempPart.mid(2).trimmed().toFloat(&parseSuccess);
                    value =temp;
                }

                // 解析湿度
                if (parseSuccess && parts[1].startsWith(" H:")) {
                    QString humPart = parts[1].trimmed();
                    hum = humPart.mid(2).replace("%", "").trimmed().toFloat(&parseSuccess);
                    value2 = hum;
                }
            }

            if (parseSuccess) {
                // 存储到字符串变量
                temperatureString = QString::number(temp, 'f', 1) + " °C";
                humidityString = QString::number(hum, 'f', 1) + " %";

                // 存储历史数据（可选）
                sensorDataHistory.append(qMakePair(temp, hum));

                // 调试输出（可替换为其他存储方式）
                qDebug() << "Temperature:" << temperatureString;
                qDebug() << "Humidity:" << humidityString;

                // 如果需要保留界面更新可以取消注释
                 ui->labelTemp->setText(temperatureString);
                 ui->labelHum->setText(humidityString);


            } else {
                qWarning() << "Invalid data format:" << str;
            }
        }
        idx = buffer.indexOf('\n');
    }
}

// 设置风扇转速
void MainWindow::on_btnSetFan_clicked() {
    if (!serialPort->isOpen()) {
        QMessageBox::warning(this, "警告", "请先连接串口！");
        return;
    }

    int speed = ui->spinFanSpeed->value();
    QString cmd = QString("SET_FAN:%1\n").arg(speed);
    serialPort->write(cmd.toUtf8());
}

// 保存数据到CSV
void MainWindow::saveToCSV(float temp, float hum) {
    QFile file("data.csv");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
               << "," << temp << "," << hum << "\n";
        file.close();
    }
}

void MainWindow::on_btnSave_clicked(){
    // 实现保存逻辑（即使暂时留空）
    qDebug() << "Save button clicked";
}

void MainWindow::updateChart() {

    if(sensorDataHistory.empty()) return;
    //温度
    QChartView *chartView = qobject_cast<QChartView*>(ui->widgetChartContainer);
    QChart *chart = chartView->chart();
    QLineSeries *series = qobject_cast<QLineSeries*>(chart->series().at(0));
    //湿度
    QChartView *chartView2 = qobject_cast<QChartView*>(ui->widgetChartContainer_2);
    QChart *chart2 = chartView2->chart();
    QLineSeries *series2 = qobject_cast<QLineSeries*>(chart2->series().at(0));

    timeCounter += 0.1; // 控制波形速度               // 温度范围0-50°C
    QDateTime currentTime = QDateTime::currentDateTime();

    // 添加数据点
    series->append(currentTime.toMSecsSinceEpoch(),value);
    series2->append(currentTime.toMSecsSinceEpoch(),value2);
    // 自动滚动显示最近30秒数据
    chart->axisX()->setRange(currentTime.addSecs(-30), currentTime);
    chart->axisY()->setRange(10, 40); // 固定Y轴范围

    chart2->axisX()->setRange(currentTime.addSecs(-30), currentTime);
    chart2->axisY()->setRange(20, 80); // 固定Y轴范围

}

MainWindow::~MainWindow()
{
    delete ui;
}
