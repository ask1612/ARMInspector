#ifndef SERVERCLIENTNATIVEABSTRACT_H
#define SERVERCLIENTNATIVEABSTRACT_H

#include <QTimer>
#include <QDebug>

enum class ServerError {
    NO_ERRORS,
    USER_COMMAND_ABORT,
    SERVER_NOT_FOUND,
    UNKNOWN_ERROR
};

class ServerClientNativeAbstract {
public:
    ServerClientNativeAbstract();
};

#endif // SERVERCLIENTNATIVEABSTRACT_H
