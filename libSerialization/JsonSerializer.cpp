/****************************************************************************
 **
 **          Реализация методов класса    сериализации.
 **
 ****************************************************************************/

#include <QJsonDocument>
#include <QJsonObject>
#include "JsonSerializer.h"
#include "JsonSerializable.h"

///Стандартный конструктор

JsonSerializer::JsonSerializer() {
}
/// Сериализовать объект класса.
/// @param obj Ссылка на объект сериализации.
/// @return Возвращет сериализованный объект в виде строки QString.

QString JsonSerializer::serialize(const JsonSerializable &obj) {
    QJsonObject jsonObj;
    obj.write(jsonObj);
    QJsonDocument doc(jsonObj);
    QString result(doc.toJson(QJsonDocument::Indented));
    return result;
}

/// Проверить  JSON объект , представленный в виде  строки QString. 
/// В случае успеха записать его данные в  объект класса.
/// @param json JSON объект, кторый проверяется.
/// @param jsonSerializable Объект , в который записывается JSON объект.      

void JsonSerializer::parse(const QString &json, JsonSerializable &jsonSerializable) {
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObj = document.object();
    jsonSerializable.read(jsonObj);

}

/// Ковертировать  JSON объект в строку.
/// @param obj Ссылка JSON объект.
/// @return Возвращет сериализованный объект в виде строки QString.

QString JsonSerializer::json_encode(const QJsonObject & obj) {
    QJsonDocument doc(obj);
    QString result(doc.toJson(QJsonDocument::Indented));
    return result;
}


/// Ковертировать  строку в  JSON объект.
/// @param json строка сериализованного JSON объекта.
/// @param &obj Объект , в который записывается JSON объект.      

void JsonSerializer::json_decode(const QString &json, QJsonObject &obj) {
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    obj = document.object();

}

