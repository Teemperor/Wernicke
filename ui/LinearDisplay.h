#ifndef WERNICKE_RECORDDISPLAY_H
#define WERNICKE_RECORDDISPLAY_H

#include <QtWidgets>
#include <Record.h>
#include <QApplication>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <qcustomplot.h>

class LinearDisplay : public QWidget {

    std::vector<double> data_;
    QCustomPlot* customPlot = nullptr;
    QPen pen;

public:
    LinearDisplay() {
       QVBoxLayout* layout = new QVBoxLayout();

       setLayout(layout);

       customPlot = new QCustomPlot();
       customPlot->legend->setVisible(true);
       customPlot->legend->setFont(QFont("Helvetica",9));
       // set locale to english, so we get english decimal separator:
       customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
       // add confidence band graphs:

       pen.setStyle(Qt::DotLine);
       pen.setWidth(1);
       pen.setColor(QColor(180,180,180));

       // setup look of bottom tick labels:
       customPlot->xAxis->setTickLabelRotation(30);
       customPlot->xAxis->setAutoTickCount(9);
       customPlot->xAxis->setNumberFormat("ebc");
       customPlot->xAxis->setNumberPrecision(1);
       customPlot->xAxis->moveRange(-10);
       // make top right axes clones of bottom left axes. Looks prettier:
       customPlot->axisRect()->setupFullAxesBox();

       customPlot->setInteraction(QCP::iRangeDrag, true);
       customPlot->setInteraction(QCP::iRangeZoom, true);

       layout->addWidget(customPlot);
    }

    void addData(const std::vector<double>& data) {
        for (double value : data)
            data_.push_back(value);
        updateDisplay();
    }

    void updateDisplay() {
        customPlot->clearGraphs();

        unsigned xFactor = 100;

        // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
        QVector<double> xContinious(data_.size()), data(data_.size());
        for (int i = 0; i < data_.size(); i++)
        {
          xContinious[i] = i * xFactor;
          data[i] = data_[i];
        }

        // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:

        customPlot->addGraph();
        customPlot->graph(0)->setName("Altitudes");
        customPlot->graph(0)->setPen(QPen(Qt::blue));
        customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
        customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 2));
        customPlot->graph(0)->setData(xContinious, data);
        customPlot->graph(0)->rescaleAxes();
        customPlot->graph(0)->rescaleAxes(true);

        customPlot->replot();
    }

};


#endif //WERNICKE_RECORDDISPLAY_H
