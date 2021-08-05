#include "CommandController.h"

/// Переопределенный конструктор.
/// @param apIODevice Устройство ввода/вывода (QTcpSocket).
/// @param apParent Родительский класс.

CommandController::CommandController(QIODevice *apIODevice, QObject *apParent) : QObject(apParent) {
    // Инициализация сокета
    m_RpcSocket = new RpcSocket(apIODevice, this);
    // Сигнально-слотовое соединение, реализующее обработку сообщения, полученного от сервера
    connect(m_RpcSocket, SIGNAL(messageReceived(RpcMessage)), SLOT(messageProcessing(RpcMessage)));
    // Регистрация сервера
    //    addService(this);
}

/// Обработать входящее сообщение.
/// @param asMessage Входящее сообщение.

void CommandController::messageProcessing(const RpcMessage &asMessage) {
    qInfo() << "messageProcessing(...)";
    RpcSocket *socket = static_cast<RpcSocket*> (sender());
    if (!socket) {
        qDebug() << "Отсутствует соединение с сервером";
        return;
    }

    //qDebug() << "received message: " << QString::fromLocal8Bit(asMessage.method().toStdString().c_str());
    QString result = QString(asMessage.method().toStdString().c_str());
    if (!result.isEmpty()) {
        emit onProcessRequestServer(result);
    } 
}

/// Сделать  запрос к серверу.
/// @param asQuery запрос.

void CommandController::requestServer(const QString &asQuery) {
    //Выполнить удалённый вызов процедуры execServerCommand на сервере, к которому подключен клиент. 
    //RpcServiceReply *reply = 
    m_RpcSocket->invokeRemoteMethod("RPCServer.execServerCommand", asQuery);
    // Сигнально-слотовое соединение, реализующее обработку сообщения о завершении
    //работы удалённой процедуры, выполняющей  запрос к серверу.
    //connect(reply, SIGNAL(finished()), this, SLOT(processRequestServer()));
}


/// Обработать результат  выполнения запроса к серверу. 

/*void CommandController::processRequestServer() {
    //qInfo() << "processCommandResult()";
    ///Получить данные.
    RpcServiceReply *reply = static_cast<RpcServiceReply *> (sender());
    if (!reply) {
        qWarning() << "Ошибка получения от сервера результата выполнения комнады";
        return;
    }
    //Преобразовать в строку.
    QString result = reply->response().result().toString();
    //Сообщить  о готовности данных. 
    emit onProcessRequestServer(result);
}*/
