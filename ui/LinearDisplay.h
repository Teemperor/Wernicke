#ifndef WERNICKE_LINEARDISPLAY_H
#define WERNICKE_LINEARDISPLAY_H

#include <QtWidgets>
#include <Record.h>
#include <QApplication>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <qcustomplot.h>

class LinearDisplay : public QWidget {

    QCustomPlot* customPlot = nullptr;
    QPen pen;

    std::string graphName_;
    uint64_t limit_;
    uint64_t pos_;


public:
    LinearDisplay(std::string name, uint64_t limit = 64000) : graphName_(name), limit_(limit), pos_(limit) {
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

       layout->addWidget(customPlot);

       recreateGraph();
    }

    void addOverwriteData(const std::vector<double>& data, double factor = 1) {
        pos_ = 0;
        customPlot->graph(0)->clearData();
        for (double value : data) {
            customPlot->graph(0)->addData(pos_++, value * factor);
        }

        customPlot->graph(0)->keyAxis()->rescale(false);
        customPlot->replot();
    }

    void addData(const std::vector<double>& data) {
        for (double value : data) {
            customPlot->graph(0)->addData(pos_++, value);
        }

        if (pos_ > limit_) {
            customPlot->graph(0)->removeDataBefore(pos_ - limit_);
        }

        customPlot->graph(0)->keyAxis()->rescale(false);
        customPlot->replot();
    }

    void updateViewport() {
        customPlot->rescaleAxes();
        customPlot->replot();
    }

    void addData(const std::list<std::vector<double>>& dataSets) {

        for (auto& data : dataSets) {
            for (double value : data) {
                customPlot->graph(0)->addData(pos_++, value);
            }
        }

        if (pos_ > limit_) {
            customPlot->graph(0)->removeDataBefore(pos_ - limit_);
        }

        customPlot->graph(0)->keyAxis()->rescale(false);
        customPlot->replot();
    }

    void recreateGraph() {
        customPlot->clearGraphs();

        // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
        QVector<double> xContinious(limit_), data(limit_);

        for (std::size_t i = 0; i < limit_; i++) {
            xContinious[i] = i;
            data[i] = 0;
        }

        customPlot->addGraph();
        customPlot->graph(0)->setName(graphName_.c_str());
        customPlot->graph(0)->setPen(QPen(Qt::blue));
        customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
        customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 2));
        customPlot->graph(0)->setData(xContinious, data);

        customPlot->replot();
    }

    void setValueRange(double lower, double upper) {
        customPlot->graph(0)->valueAxis()->setRange(lower, upper);
    }

    void enableNavigation() {
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);
    }

};


#endif //WERNICKE_LINEARDISPLAY_H
