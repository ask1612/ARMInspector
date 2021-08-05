
/******************************************************************************* 
 * 
 *      Реализация методов класса ModelWrapper.    
 * 
 ******************************************************************************/

#include "ModelWrapper.h"

///Конструктор

ModelWrapper::ModelWrapper() : head_(QString("")), sessionID_(0),
command_(Command::NOP), model_(Model::Unknown), data_(QString("")), success_(false), message_(QString("")) {
}
///Конструктор

ModelWrapper::ModelWrapper(const Command& cmd) {
    head_ = ListCommand[cmd];
    command_ = cmd;
    model_ = Model::Unknown;
    data_ = QString("");
    success_ = false;
    message_ = QString("");

}
/// Деструктор.

ModelWrapper::~ModelWrapper() {
}

///Установить заголовок.
///@param head Шапка (заголовок) командной обёртки.

void ModelWrapper::setHead(const QString& head) {
    head_ = head;
};



///Записать данные.
/// @param data Данные.

void ModelWrapper::setData(const QString& data) {
    data_ = data;
};

///Записать результат.
/// @param success Результат выполнения операции(успех или неуспех).

void ModelWrapper::setSuccess(const bool& success) {
    success_ = success;
};
///Записать сообщение.
/// @param message Сообщение.

void ModelWrapper::setMessage(const QString& message) {
    message_ = message;

};

///Получить заголовок.
/// @return Заголовок. 

const QString& ModelWrapper::getHead() const {
    return head_;
}

///Получить данные.
/// @return Данные. 

const QString& ModelWrapper::getData() const {
    return data_;

};

///Получить результат запроса.
/// @return Успех или неуспех запроса. 

const bool& ModelWrapper::getSuccess() const {
    return success_;
};

///Получить  сообщение.
/// @return Сообщение. 

const QString& ModelWrapper::getMessage() const {
    return message_;
};

///Инициализировать идентификатор сессии.
/// @param asSessionID Идентификатор сессии.

void ModelWrapper::setSessionID(const int& asSessionID) {
    sessionID_ = asSessionID;
}
///Получить  идентификатор сессии.
/// @return Идентификатор сессии. 

const int& ModelWrapper::getSessionID() const {
    return sessionID_;
}

///Установить команду.
///Используется при сериализации объекта.
/// @param cmd Команда в виде строки.

void ModelWrapper::setCommand(const QString &cmd) {
    const QMetaObject &mo = ModelWrapper::staticMetaObject;
    int index = mo.indexOfEnumerator("Command");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(cmd));
    command_ = static_cast<Command> (value);
}


///Получить команду.
///Используется при сериализации объекта.
///@return Возвращает команду в виде строки.

const QString ModelWrapper::getCommand() const {
    const QMetaObject &mo = ModelWrapper::staticMetaObject;
    int index = mo.indexOfEnumerator("Command");
    QMetaEnum metaEnum = mo.enumerator(index);
    return metaEnum.valueToKey(command_);
}

///Получить команду.
///@return Возвращает команду  в виде элемента перечисления Enum.  

ModelWrapper::Command ModelWrapper::getEnumCommand() const {
    return command_;
}
///Установить команду.
///@param cmd Комманда в виде элемента перечисления Enum.

void ModelWrapper::setCmd(ModelWrapper::Command cmd) {
    command_ = cmd;
}








///Получить команду.
///return Возвращает model  в виде элемента перечисления Enum.  

ModelWrapper::Model ModelWrapper::getEnumModel() const {
    return model_;

}

///Установить команду.
///@param mdl Модель в виде элемента перечисления Enum.

void ModelWrapper::setEnumModel(ModelWrapper::Model mdl) {
    model_ = mdl;
}


///Установить команду.
///Используется при сериализации объекта.
/// @param mdl Модель в виде строки.

void ModelWrapper::setModel(const QString &mdl) {
    const QMetaObject &mo = ModelWrapper::staticMetaObject;
    int index = mo.indexOfEnumerator("Model");
    QMetaEnum metaEnum = mo.enumerator(index);
    int value = metaEnum.keyToValue(qPrintable(mdl));
    model_ = static_cast<Model> (value);
}

///Получить модель.
///Используется при сериализации объекта.
///return Возвращает модель в виде строки.

const QString ModelWrapper::getModel() const {
    const QMetaObject &mo = ModelWrapper::staticMetaObject;
    int index = mo.indexOfEnumerator("Model");
    QMetaEnum metaEnum = mo.enumerator(index);
    return metaEnum.valueToKey(model_);
}






///Считать данные JSON объекта в объект модели.

void ModelWrapper::read(const QJsonObject &jsonObj) {
    //Шапка.
    this->setHead(jsonObj["head"].toString());
    //Идентификатор сессии.
    this->setSessionID(jsonObj["sessionID"].toInt());
    //Команда.
    this->setCommand(jsonObj["command"].toString());
    //Модель.
    this->setModel(jsonObj["model"].toString());
    //Данные.
    this->setData(jsonObj["data"].toString());
    //Результат выполнения.
    this->setSuccess(jsonObj["success"].toBool());
    //Сообщение
    this->setMessage(jsonObj["message"].toString());
};

///Записать  данные объекта модели в JSON объект. 

void ModelWrapper::write(QJsonObject &jsonObj) const {
    //Шапка.
    jsonObj["head"] = this->getHead();
    //Идентификатор сессии.
    jsonObj["sessionID"] = this->getSessionID();
    //Команда.
    jsonObj["command"] = this->getCommand();
    //Модель.
    jsonObj["model"] = this->getModel();
    //Данные.
    jsonObj["data"] = this->getData();
    //Результат выполнения.
    jsonObj["success"] = this->getSuccess();
    //Сообщение
    jsonObj["message"] = this->getMessage();
};
