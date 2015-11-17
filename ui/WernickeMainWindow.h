#ifndef WERNICKE_WERNICKEMAINWINDOW_H
#define WERNICKE_WERNICKEMAINWINDOW_H

#include <QtWidgets>
#include <iostream>
#include "Recorder.h"
#include "RecordDialog.h"
#include "LinearDisplay.h"

class WernickeMainWindow : public QApplication {
    Q_OBJECT

    Recorder recorder = Recorder(16000);
    LinearDisplay * display = nullptr;

    QMainWindow* window_ = nullptr;

public slots:
    void record()
    {
        for (auto segment : recorder.dataSegments()) {
            display->addData(segment);
        }

        recorder.dataSegments().clear();

        QTimer::singleShot(100, this, SLOT(record()));
    }


public:
    WernickeMainWindow(int argc, char **argv) : QApplication(argc, argv) {
        window_ = new QMainWindow();

        display = new LinearDisplay();

        window_->setCentralWidget(display);
        window_->showMaximized();

        recorder.record();
    }

    int start() {
        QTimer::singleShot(500, this, SLOT(record()));
        return exec();
    }

};


#endif //WERNICKE_WERNICKEMAINWINDOW_H
