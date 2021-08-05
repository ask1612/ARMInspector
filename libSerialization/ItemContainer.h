/****************************************************************************
 **
 **             Шаблон класса  контейнера.
 **
 ****************************************************************************/

#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H
#include "JsonSerializable.h"
class JsonSerializable;

template <class T>
class ItemContainer : public virtual JsonSerializable {
public:
    /// Записать все элементы контейнера в JSON объект.
    /// @param jsonObj JSON объект, куда помещаются данные из контейнера.
    void write(QJsonObject &jsonObj) const;

    /// Прочитать  JSON объект и записать его в контейнер .
    /// @param jsonObj JSON объект, из которого считываются данные.
    void read(const QJsonObject &jsonObj);

    /// Добавить объект класса Т  в контейнер. 
    /// @param p Ссылка  на объект класса Т.
    void add(T &p);

    /// Получить список элементов контейнера.
    /// return Список элементов. 
    QList<T> getItemsList() const;

private:
    /// Список объектов класса T. 
    QList<T> items_;

};

#include "ItemContainer_IMPL.h"
#endif /* ITEMCONTAINER_H */

