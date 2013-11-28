#ifndef D_LOGGER_H
#define D_LOGGER_H

#include <QObject>
#include <QTextEdit>

enum LogLevel {
    DEBUG,
    WARNING,
    SERIOUS_ERROR,
    FATAL_ERROR
};

void dLog(QString msg, LogLevel lvl = DEBUG);

class DLogger : public QObject
{
    Q_OBJECT

public:
    virtual ~DLogger();

    static DLogger& getInstance();
    static void initialize(QTextEdit* output);

public slots:
    void dLog(QString msg, LogLevel lvl = DEBUG);

private:
    DLogger(QTextEdit* output);
    static DLogger* singleton;
    QTextEdit* output;
};

#endif // D_LOGGER_H
