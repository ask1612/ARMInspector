/****************************************************************************
 **
 **                 Реализация методов класса  контейнера  
 **
 ****************************************************************************/
#ifndef ITEMCONTAINER_IMPL_H
#define ITEMCONTAINER_IMPL_H

#include <QJsonArray>
#include "JsonSerializable.h"
#include "ItemContainer.h"

/// Записать все элементы контейнера в JSON объект.
/// @param jsonObj JSON объект, куда помещаются данные из контейнера.

template <class T> void ItemContainer<T>::write(QJsonObject& jsonObj) const {
    QJsonArray jsonArray;

    for(T p:this->items_) {
        QJsonObject jsonT;
        p.write(jsonT);
        jsonArray.append(jsonT);
    }

    jsonObj["data"] = jsonArray;
}

/// Прочитать  JSON объект и записать его в контейнер.
/// @param jsonObj JSON объект, из которого считываются данные.

template <class T> void ItemContainer<T>::read(const QJsonObject &jsonObj) {
    QJsonArray jsonArray = jsonObj["data"].toArray();

    for (auto jsonItem : jsonArray) {
        T p;
        p.read(jsonItem.toObject());
        this->items_.append(p);
    }
}

/// Добавить объект класса Т  в контейнер. 
/// @param p Ссылка  на объект класса Т.

template <class T> void ItemContainer<T>::add(T& p) {

    this->items_.append(p);
}

/// Получить список элементов контейнера.
/// return Список элементов. 

template <class T> QList<T> ItemContainer<T>::getItemsList() const {

    return this->items_;
};

#endif /* ITEMCONTAINER_IMPL_H */
