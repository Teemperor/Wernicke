#ifndef WERNICKE_TWODIMENSIONDISPLAY_H
#define WERNICKE_TWODIMENSIONDISPLAY_H

#include <QtWidgets>
#include <Record.h>
#include <QApplication>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <qcustomplot.h>


class TwoDimensionDisplay  : public QWidget {

    QCustomPlot* customPlot = nullptr;
    QPen pen;

public:
    TwoDimensionDisplay() {
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

    void addData(const std::vector<std::vector<float>>& data) {
        // set up the QCPColorMap:
        QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
        customPlot->addPlottable(colorMap);
        int nx = data.size();
        int ny = data[0].size();
        colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
        colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
        // now we assign some data, by accessing the QCPColorMapData instance of the color map:
        double x, y, z;
        for (int xIndex=0; xIndex<nx; ++xIndex)
        {
            for (int yIndex=0; yIndex<ny; ++yIndex)
            {
                colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
                colorMap->data()->setCell(xIndex, yIndex, data[nx][ny]);
            }
        }

        // add a color scale:
        QCPColorScale *colorScale = new QCPColorScale(customPlot);
        customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
        colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
        colorMap->setColorScale(colorScale); // associate the color map with the color scale
        colorScale->axis()->setLabel("Magnetic Field Strength");

        // set the color gradient of the color map to one of the presets:
        colorMap->setGradient(QCPColorGradient::gpPolar);
        // we could have also created a QCPColorGradient instance and added own colors to
        // the gradient, see the documentation of QCPColorGradient for what's possible.

        // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
        colorMap->rescaleDataRange();

        // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
        QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
        customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
        colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

        // rescale the key (x) and value (y) axes so the whole color map is visible:
        customPlot->rescaleAxes();

        customPlot->replot();
    }

    void recreateGraph() {
        //customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
        customPlot->axisRect()->setupFullAxesBox(true);
        customPlot->xAxis->setLabel("x");
        customPlot->yAxis->setLabel("y");

    }

};


#endif //WERNICKE_TWODIMENSIONDISPLAY_H
