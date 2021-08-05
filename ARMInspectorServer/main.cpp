#include "MainWindow.h"
#include <QApplication>
#include <QHostAddress>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>

#include "ServerController.h"

#include "CoreLogger.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    /// Создание обработчика событий логирования.
    CoreLogger coreLogger;
#if defined(Q_OS_LINUX)
    coreLogger.setLogFile(QString("/opt/ARMInspector/log/%1Server.log").arg(ARM_BRAND));
#elif defined (Q_OS_WIN)
    coreLogger.setLogFile(QString("%1/%2Server.log").arg(QCoreApplication::applicationDirPath()).arg(ARM_BRAND));
#endif

    /// Контроллер-обработчик RPC-протокола.
    ServerController serverController;
    serverController.start();

    MainWindow w;
    w.show();

    return a.exec();
}
