#include "ServerClient.h"
#include <QNetworkProxy>
#include <QMessageBox>

/// Стандартный конструктор.
/// @param parent Родитель.

ServerClient::ServerClient(QObject *parent) : QObject(parent) {
    QNetworkProxy proxy;
    QNetworkProxy::setApplicationProxy(proxy);

    // Initialization of the service connection socket
    m_pClientSocket = new UiSocket(this);
    // Signal-slot connection broadcasting service connection error
    connect(m_pClientSocket, static_cast<void(UiSocket::*)(UiSocketError)> (&UiSocket::error),
            this, &ServerClient::handleSocketError);
    // Signal-slot connection broadcasting signal of successful connection to the service
    connect(m_pClientSocket, SIGNAL(connected()), this, SLOT(handleConnectedToServer()));
    // Signal-slot connection transmitting a signal to disconnect from the service
    connect(m_pClientSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromServer()));
    // Signal-slot connection that reconnects to the service
    connect(&m_reconnectTimer, SIGNAL(timeout()), this, SLOT(reconnectToServer()));
}

/// Получить указатель на сокет клиент-серверного соединения.
/// @return Указатель на сокет клиент-серверного соединения.

UiSocket *ServerClient::getClientSocket() const {
    return m_pClientSocket;
}

/// Обработать соединение с сервером.

void ServerClient::handleConnectedToServer() {
    //qInfo() << "Connected to the server";
    m_launchAttemptCounter = 0;
    m_isServerConnected = true;
    stopReconnectingToServer();
    emit connected();
}

/// Запустить реконнект к серверу.

void ServerClient::startReconnectingToServer() {
    if (!m_reconnectTimer.isActive()) {
        //qInfo() << "Start trying to reconnect to server";
        m_reconnectTimer.start(RECONNECT_TIMEOUT_MS);
    }
}

/// Остановить реконнект к серверу.

void ServerClient::stopReconnectingToServer() {
    if (m_reconnectTimer.isActive()) {
        m_reconnectTimer.stop();
        //qInfo() << "Reconnect timer stopped";
    }
}

/// Обработать ошибку подключения к серверу.
/// @param aSocketEror Ошибка сокета.

void ServerClient::handleSocketError(UiSocketError aSocketEror) {
    qDebug() << m_pClientSocket->errorString();
    startReconnectingToServer();
    emit socketError(aSocketEror);
    emit socketErrorString(m_pClientSocket->errorString());
}

/// Переподключиться к серверу.

void ServerClient::reconnectToServer() {
    ++m_launchAttemptCounter;
    if (m_launchAttemptCounter == NUMBER_LAUNCH_ATTEMPTS) {
        qCritical() << "Server not running";
        //ARM_BRAND
        QMessageBoxEx::setCustomTextForButton(QMessageBox::Yes, "Да");
        QMessageBoxEx::critical(Q_NULLPTR, "АРМ Инспектора.",
        " Не возможно подключиться к серверу. Сервер не работает или отсутствует подключение к серверу."
        " Пожалуйста, обратитесь к системному администратору");
        exit(-1);
    } else {
        connectToServer();
    }
}

/// Подключиться к серверу.

void ServerClient::connectToServer() {
    if (m_pClientSocket->state() == QAbstractSocket::ConnectedState)
        return;

    qInfo() << QString("connectToServer(%1, %2)").arg("10.174.0.9").arg(7071);
    m_pClientSocket->connectToHost("10.174.0.9", 7071); // Windows
    //qInfo() << QString("connectToServer(%1, %2)").arg("127.0.0.1").arg(7071);
    //m_pClientSocket->connectToHost("127.0.0.1", 7071); // Linux
}



/// Отключиться от сервера .

void ServerClient::disconnectFromServer() {
    m_isServerConnected = true;
    startReconnectingToServer();
    emit disconnected();
}
