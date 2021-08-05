#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore>
#include <QLocale>
#include <QTranslator>
#include "ServerClient.h"
#include "ClientController.h"
#include "CoreLogger.h"
#include "JsonSerializer.h"
#include "ModelWrapper.h"
#include "Login/myForm.h"
#include "MainWindow.h"
#include "Main/reportForm.h"
#include "QMessageBoxEx.cpp"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    //QQmlApplicationEngine engine;

    //const QUrl url(QStringLiteral("qrc:/main.qml"));
    //QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    //        &app, [url](QObject *obj, const QUrl & objUrl) {
    //            if (!obj && url == objUrl)
    //                QCoreApplication::exit(-1);
    //        }, Qt::QueuedConnection);
    //engine.load(url);

    QString style = R"(
QPushButton {
color: white;
background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);
border-width: 1px;
border-color: #339;
border-style: solid;
border-radius: 7;
padding: 3px;
font-size: 10px;
padding-left: 5px;
padding-right: 5px;
min-width: 50px;
max-width: 50px;
min-height: 13px;
max-height: 13px;
}
               )";
    app.setStyleSheet(style);
    QTranslator translator_my;
    translator_my.load("i18n/i18n_" + QLocale::system().name() + ".qm");
    //translator_my.load('i18n/i18n_ru_Ru.qm')
    QCoreApplication::installTranslator(&translator_my);
    //app.installTranslator(&translator_my);

    QTranslator translator_qt;
    translator_qt.load("i18n/qt_" + QLocale::system().name()[2] + ".qm");
    //translator_qt.load('i18n/qt_ru.qm')
    QCoreApplication::installTranslator(&translator_qt);
    //app.installTranslator(&translator_qt);




    /// Создание обработчика событий логирования.
    CoreLogger coreLogger;
#if defined(Q_OS_LINUX)
    coreLogger.setLogFile(QString("/opt/ARMInspector/log/%1GUI.log").arg(ARM_BRAND));
#elif defined (Q_OS_WIN)
    coreLogger.setLogFile(QString("%1/%2GUI.log").arg(QCoreApplication::applicationDirPath()).arg(ARM_BRAND));
#endif

    /// Клиент.
    ServerClient serverClient;
    /// Контроллер-обработчик RPC-протокола.
    ClientController &clientController = ClientController::getInstance();
    clientController.init(&serverClient);
    /// Подключение к серверу.
    serverClient.connectToServer();
    ///Ждать сигнала установления соединения с сервером и присвоения ID клиенту .
    clientController.waitReady();
    ///Сигнал получен. 
    ///На сервере клиенту создана сессия.
    ///Можно на сервере  выполнять операции с данными и
    ///получать результат обработки.
    QApplication::setQuitOnLastWindowClosed(true);
    myForm form;
    form.initClient(&clientController);
    //form.initApp(&app);
    form.show();
    clientController.waitReady();
    form.hide();
    if (!clientController.getLogged()) {
        return 0;
    }

    User user = clientController.getSessionUser();

    /// ПРИМЕР ИСПОЛЬЗОВАНИЯ
    //clientController.getListModels("Select * from pass_list", ModelWrapper::Model::PassList);QApplication app(argc, argv);
    if (user.getName() == "admin") {
        //QMessageBox::information(0, "Информация о пользователе", user.getName());
        MainWindow w;
        w.setWindowState(Qt::WindowMaximized);
        w.initClient(&clientController);
        w.show();
        return app.exec();
    } else {
        reportForm frm;
        frm.initClient(&clientController);
        frm.setUser(user);
        frm.setMenuByUserRole();
        //clientController.getListMRO();
        //QMenuBar * menuBar = frm.getMenuBar();
        frm.setWindowTitle("АРМ юриста");
        frm.setWindowState(Qt::WindowMaximized);
        frm.hideControlsFrm();
        frm.show();
        return app.exec();
    }
}
