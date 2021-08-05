/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functor.cpp
 * Author: kazun_as
 * 
 * Created on 5 мая 2021 г., 11:10
 */


///-----------------------------------------------------------------------------
///
///             exec
///
///-----------------------------------------------------------------------------

template<typename T> QString Functor<T>::produce(ModelWrapper::Command cmd, const T& model) {
    //QMessageBox::information(0, "Добавление нового пользовтеля", QString(user.getFio()));
    //Создать командную обёртку.
    ModelWrapper wrapper(cmd);
    wrapper.setEnumModel(T::model_);
    //Установить идентификатор сессии.
    //wrapper.setSessionID(m_aSessionID);
    //Установить модель.    
    //Сериализовать модель User.Передать данные о пользователе.
    QString userAsString = JsonSerializer::serialize(model);
    wrapper.setData(userAsString);
    //Упаковать  весь запрос в строку
    return JsonSerializer::serialize(wrapper);
}

///-----------------------------------------------------------------------------
///
///         execPrm
///
///-----------------------------------------------------------------------------

template<typename T> QString Functor<T>::producePrm(ModelWrapper::Command cmd, const QJsonObject& param) {
    //QMessageBox::information(0, "Добавление нового пользовтеля", QString(user.getFio()));
    //Создать командную обёртку.
    ModelWrapper wrapper(cmd);
    wrapper.setEnumModel(T::model_);
    //Установить идентификатор сессии.
    //wrapper.setSessionID(m_aSessionID);
    //Сериализовать модель User.Передать данные о пользователе.
    QString query = JsonSerializer::json_encode(param);
    wrapper.setData(query);
    //Упаковать  весь запрос в строку
     return  JsonSerializer::serialize(wrapper);
}
