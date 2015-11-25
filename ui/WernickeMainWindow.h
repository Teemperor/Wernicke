#ifndef WERNICKE_WERNICKEMAINWINDOW_H
#define WERNICKE_WERNICKEMAINWINDOW_H

#include <QtWidgets>
#include <iostream>
#include "Recorder.h"
#include "RecordDialog.h"
#include "LinearDisplay.h"
#include "RecordDisplay.h"

class WernickeMainWindow : public QApplication {
    Q_OBJECT

    Recorder recorder = Recorder(16000);
    LinearDisplay *linearDisplay = nullptr;

    QMainWindow* window_ = nullptr;

public slots:
    void record()
    {
        linearDisplay->addData(recorder.dataSegments());

        recorder.dataSegments().clear();

        QTimer::singleShot(100, this, SLOT(record()));
    }

public:
    WernickeMainWindow(int argc, char **argv) : QApplication(argc, argv) {

        QCoreApplication::setApplicationName("wernickeui");
        QCoreApplication::setApplicationVersion("0.1");

        QCommandLineParser parser;
        parser.setApplicationDescription("User interface for wernicke");
        parser.addHelpOption();
        parser.addVersionOption();

        parser.addPositionalArgument("file", "File to analyze.");

        // Process the actual command line arguments given by the user
        parser.process(*this);

        const QStringList args = parser.positionalArguments();

        window_ = new QMainWindow();

        if (args.size() != 0) {
            std::string file = args.at(0).toStdString();

            Record* record = Record::fromRawFile(file);

            auto display = new RecordDisplay(record);
            window_->setCentralWidget(display);

        } else {
            linearDisplay = new LinearDisplay("Amplitudes");
            window_->setCentralWidget(linearDisplay);
            recorder.record();
        }

        window_->showMaximized();

    }

    int start() {
        if (linearDisplay)
            QTimer::singleShot(500, this, SLOT(record()));
        return exec();
    }

};


#endif //WERNICKE_WERNICKEMAINWINDOW_H
