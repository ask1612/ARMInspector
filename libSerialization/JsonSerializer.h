/****************************************************************************
 **
 **          Класс    сериализации.
 **
 ****************************************************************************/

#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H
class JsonSerializable;

class JsonSerializer {
public:
    /// Сериализовать объект класса.
    /// @param obj Ссылка на объект сериализации.
    /// @return Возвращет сериализованный объект в виде строки QString.
    static QString serialize(const JsonSerializable &obj);

    /// Проверить  JSON объект , представленный в виде  строки QString. 
    /// В случае успеха записать его данные в  объект.
    /// @param json JSON объект, кторый проверяется.
    /// @param jsonSerializable Объект , в который записывается JSON объект.      
    static void parse(const QString &json, JsonSerializable &jsonSerializable);

    /// Конвертировать  JSON объект в строку.
    /// @param obj Ссылка JSON объект.
    /// @return Возвращет сериализованный объект в виде строки QString.
    static QString json_encode(const QJsonObject &obj);

    /// Конвертировать  строку в  JSON объект.
    /// @param json строка сериализованного JSON объекта.
    /// @param &obj Объект , в который записывается JSON объект.      
    static void json_decode(const QString &json, QJsonObject &obj);

private:
    ///Стандартный конструктор
    JsonSerializer();

};

#endif /* JSONSERIALIZER_H */

