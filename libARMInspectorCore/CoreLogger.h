/****************************************************************************
**
** Класс представляет интерфейс обработчика событий логирования.
**
****************************************************************************/

#ifndef CORELOGGER_H
#define CORELOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QTextStream>

class CoreLogger : public QObject
{
    Q_OBJECT

    /// Наблюдатель за файлом логирования.
    QFileSystemWatcher m_fileSystemWatcher;
    /// Путь к файлу логирования.
    QString m_sFilePath;
    /// Обработать системное сообщение.
    /// @param aMessageType Тип сообщения.
    /// @param aContext Контекст сообщения.
    /// @param asMessage Сообщение.
    static void messageHandler(QtMsgType aMessageType, const QMessageLogContext &aContext,
                               const QString & asMessage);

signals:
    /// Сигнал излучается в случае изменения пути к файлу логирования.
    /// @param asFilePath Путь к файлу логирования.
    void onFilePathChanged(const QString &asFilePath);

private slots:
    /// Создать файл логирования.
    /// @param asFilePath Путь к файлу логирования.
    void createLogFile(const QString &asFilePath);

public:
    /// Стандартный конструктор.
    /// @param parent Родитель.
    explicit CoreLogger(QObject *parent = nullptr);
    /// Установить путь к файлу логирования.
    /// @param asFilePath Путь к файлу логирования.
    void setLogFile(const QString& asFilePath);
};

#endif // CORELOGGER_H
