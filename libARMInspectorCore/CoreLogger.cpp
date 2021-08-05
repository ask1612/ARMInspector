#include "CoreLogger.h"

/// Файл логирования.
static QFile m_logFile;

/// Стандартный конструктор.
/// @param parent Родитель.
CoreLogger::CoreLogger(QObject *parent) : QObject(parent)
{
    qInstallMessageHandler(messageHandler);
    // Сигнально-слотовое соединение, иницирующее создание файла при изменении пути к нему
    connect(this, SIGNAL(onFilePathChanged(QString)), this, SLOT(createLogFile(QString)));
    // Сигнально-слотовое соединение, позволяющее создать новый файл логирования после его
    // удаления в процессе работы приложения
    connect(&m_fileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, [=]
    {
        createLogFile(m_sFilePath);
    });
}

/// Обработать системное сообщение.
/// @param aMessageType Тип сообщения.
/// @param aContext Контекст сообщения.
/// @param asMessage Сообщение.
void CoreLogger::messageHandler(QtMsgType aMessageType,
                               const QMessageLogContext &aContext,
                               const QString & asMessage)
{
    QTextStream out(&m_logFile);
    // Дата события
    QString datetime = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz]");
    out << datetime;
    fprintf(stdout, "%s", datetime.toLocal8Bit().data());
    // Тип сообщения
    QString messagetype;
    switch (aMessageType)
    {
        case QtInfoMsg:
        {
            out << "[INF]";
            fprintf(stdout, "\x1b[32;2m[INF]");
            break;
        }
        case QtDebugMsg:
        {
            out << "[DBG]";
            fprintf(stdout, "\x1b[37;2m[DBG]");
            break;
        }
        case QtWarningMsg:
        {
            out << "[WRN]";
            fprintf(stdout, "\x1b[33;2m[WRN]");
            break;
        }
        case QtCriticalMsg:
        {
            out << "[ERR]";
            fprintf(stdout, "\x1b[31m[ERR]");
            break;
        }
        case QtFatalMsg:
        {
            out << "[FTL]";
            fprintf(stdout, "\x1b[1;5;31m[FTL]");
            break;
        }
    }
    printf("\x1b[0m");
    // Место возникновения события
    QString messagePlace;
    if(aContext.file)
    {
        char prefixBuffer[128];
        const char *fileName = strrchr(aContext.file, '/');
        fileName = (fileName == Q_NULLPTR ? aContext.file : fileName + 1);
        strcpy(prefixBuffer, fileName);
        messagePlace = QString("%1 %2 ").arg(prefixBuffer).arg(aContext.line);
    }
    // Сообщение
    out << messagePlace << asMessage << endl;
    fprintf(stdout, "%s", QString("%1 %2\n").arg(messagePlace).arg(asMessage).toLocal8Bit().data());
    fflush(stdout);
    out.flush();
}

/// Создать файл логирования.
/// @param asFilePath Путь к файлу логирования.
void CoreLogger::createLogFile(const QString &asFilePath)
{
    QFileInfo fileInfo(asFilePath);
    m_logFile.close();
    m_logFile.open(QFile::Append | QFile::Text);
    m_fileSystemWatcher.addPath(fileInfo.absolutePath());
}

/// Установить путь к файлу логирования.
/// @param asFilePath Путь к файлу логирования.
void CoreLogger::setLogFile(const QString& asFilePath)
{
    m_sFilePath = asFilePath;
    m_logFile.setFileName(asFilePath);
    emit onFilePathChanged(m_sFilePath);
}
