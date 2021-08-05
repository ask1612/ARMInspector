#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>
#include <QTimer>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTcpServer>
#include "QMessageBoxEx.h"

typedef QTcpSocket UiSocket;
typedef QTcpServer UiServer;
typedef QTcpSocket::SocketError UiSocketError;

class ServerClient : public QObject {

    Q_OBJECT
    Q_DISABLE_COPY(ServerClient)

    /// Время реконнекта клиента к серверу.
    const int RECONNECT_TIMEOUT_MS {
        5000
    };
    /// Количество попыток реконнекта клиента к серверу.
    const size_t NUMBER_LAUNCH_ATTEMPTS{3};
    /// Текущее количество попыток реконнекта клиента к серверу.
    size_t m_launchAttemptCounter{0};
    /// Таймер реконнекта клиента к серверу.
    QTimer m_reconnectTimer;
    /// Сокет клиент-серверного соединения.
    UiSocket *m_pClientSocket{nullptr};
    /// Флаг состояния клиент-сервреного соединения.
    bool m_isServerConnected{false};

public:
    /// Стандартный конструктор.
    /// @param parent Родитель.
    explicit ServerClient(QObject *parent = nullptr);
    /// Получить указатель на сокет клиент-серверного соединения.
    /// @return Указатель на сокет клиент-серверного соединения.
    UiSocket *getClientSocket() const;

signals:
    /// Сигнал излучается в случае успешного соединения клиента с сервером.
    void connected();
    /// Сигнал излучается в случае успешного отключения клиента от сервера.
    void disconnected();
    /// Сигнал излучается в случае возникновения ошибки в клиент-серверном соединении.
    /// @param asErrorMessage Ошибка сокета.
    void socketErrorString(const QString& asErrorMessage);
    /// Сигнал излучается в случае возникновения ошибки в клиент-серверном соединении.
    /// @param aSocketEror Ошибка сокета.
    void socketError(UiSocketError aSocketEror);

protected slots:
    /// Обработать соединение с сервером.
    void handleConnectedToServer();
    /// Запустить реконнект к серверу.
    void startReconnectingToServer();
    /// Остановить реконнект к серверу.
    void stopReconnectingToServer();
    /// Обработать ошибку подключения к серверу.
    /// @param aSocketEror Ошибка сокета.
    void handleSocketError(UiSocketError aSocketEror);
    /// Переподключиться к серверу.
    void reconnectToServer();

public slots:
    /// Подключиться к серверу.
    void connectToServer();
    /// Отключиться от сервера.
    void disconnectFromServer();
};
#endif // SERVERCLIENT_H
