/****************************************************************************
**
**                      Интерфейс  сериализации.
**
****************************************************************************/

#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H
#include "JsonSerializer.h"


class JsonSerializable {
public:
    /// Деструктор
   virtual ~JsonSerializable() {}
   
   /// Прочитать данные JSON объекта и записать их в объект класса.
   /// @param jsonObj JSON объект.
    virtual void read(const QJsonObject &jsonObj) = 0;
    
    /// Записать данные объекта класса в JSON объект.
    /// @param jsonObj
    virtual void write(QJsonObject &jsonObj) const = 0;
};

#endif /* JSONSERIALIZABLE_H */

