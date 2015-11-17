#ifndef SPEECHREG_RECORDDIALOG_H
#define SPEECHREG_RECORDDIALOG_H


#include <QtWidgets/qprogressdialog.h>
#include <future>
#include "Record.h"
#include "Recorder.h"

class RecordDialog : public QProgressDialog {

    static void startRecordStatic(RecordDialog* dialog) {
        dialog->startRecord();
    }

    std::vector<Record> records_;
    unsigned int recordTries = 5;
    unsigned int currentRecordTries = 0;
    bool recording = false;

protected:
    void startRecord() {
        Recorder recorder(16000);
        //Record record = *recorder.record();
        //records_.push_back(record);
        close();
    }

public:
    RecordDialog() {

    }

    void run() {
        setModal(true);

        for (currentRecordTries = 0; currentRecordTries < recordTries; currentRecordTries++) {
            recording = true;
            setLabelText(QString::fromStdString(std::string("Recording ") + std::to_string(currentRecordTries)));
            std::future<void> foo = std::async (std::launch::async, &RecordDialog::startRecordStatic, this);

            exec();
        }
    }

};


#endif //SPEECHREG_RECORDDIALOG_H
