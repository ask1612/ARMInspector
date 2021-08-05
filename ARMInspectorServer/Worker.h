
/****************************************************************************
 **
 **     Вспомогательный класс Worker для организации отдельного потока 
 **     и работы  с базой данных.
 **
 ****************************************************************************/
#ifndef WORKER_H
#define WORKER_H
#include <QtCore>
#include "DBManager.h"
#include "ModelWrapper.h"

class Worker : public QObject {
    Q_OBJECT

public:

    /// Стандартный конструктор.
    /// @param apParent Родитель.
    Worker(QObject *apParent = nullptr);
    ///Деструктор
    ~Worker();
    /// Инициализировать строку командной обёртки.
    /// @param asWrapperString Строка инициализации командной обёртки
    void setModelWrapperString(const QString& asWrapperString);
    /// Получить строку командной обёртки.
    /// @return Возвращает строку командной обёртки.
    const QString& getModelWrapperString() const;
    DBManager* getDBManager();
    static QMutex mutex_;

public slots:
    ///Основная функция потока
    void process();

signals:
    ///Сигнал завершения работы.
    /// @param asResult Результат выполнения запроса 
    void finished(QString asResult);
    void error(QString asError);

private:
    ///Командная обёртка в форме строки.
    QString m_aModelWrapperString;
    DBManager *m_pDBManager;
};

#endif /* WORKER_H */

