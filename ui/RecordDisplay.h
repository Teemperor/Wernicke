#ifndef WERNICKE_RECORDDISPLAY_H
#define WERNICKE_RECORDDISPLAY_H


#include <QtWidgets>
#include <Record.h>
#include <QApplication>
#include <QMainWindow>
#include <QtPrintSupport/QPrinter>
#include <qcustomplot.h>
#include <RecordPart.h>
#include <unistd.h>
#include "TwoDimensionDisplay.h"
#include "LinearDisplay.h"

class RecordDisplay : public QWidget {

    TwoDimensionDisplay* frequencies_;
    LinearDisplay* amplitudes_;
    LinearDisplay* wholeRangeFrequencies_;

public:
    RecordDisplay(Record* record) {
        QHBoxLayout* layout = new QHBoxLayout();

        setLayout(layout);

        RecordPart part(record);

        //frequencies_ = new TwoDimensionDisplay();
        amplitudes_ = new LinearDisplay("Amplitudes", record->altitudes().size());
        wholeRangeFrequencies_ = new LinearDisplay("Frequencies", part.frequencies().size());

        //layout->addWidget(frequencies_);
        layout->addWidget(amplitudes_);
        layout->addWidget(wholeRangeFrequencies_);

        amplitudes_->addOverwriteData(record->altitudes());
        amplitudes_->setValueRange(-1, 1);

        wholeRangeFrequencies_->addOverwriteData(part.frequencies(), 1);
        wholeRangeFrequencies_->updateViewport();

    }

};


#endif //WERNICKE_RECORDDISPLAY_H
