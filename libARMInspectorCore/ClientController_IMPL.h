/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientController_IMPL.h
 * Author: kazun_as
 *
 * Created on 3 мая 2021 г., 11:07
 */

#ifndef CLIENTCONTROLLER_IMPL_H
#define CLIENTCONTROLLER_IMPL_H
// Nothing changed here

///-----------------------------------------------------------------------------
///
///             Получить список моделей.
///
///-----------------------------------------------------------------------------

/// Выполнить Sql запрос для объекта класса Т. T - шаблон модели для которй 
/// выполняется запрос. Результат работы запроса упаковывается в секцию данных
/// командной обёртки m_pModellWrapper.

template<typename T> void ClientController::addModel(const T& model) {
    //QMessageBox::information(0, "Добавление нового пользовтеля", QString(user.getFio()));
    //Создать командную обёртку.
    ModelWrapper wrapper(ModelWrapper::Command::ADD_NEW_MODEL);
    wrapper.setEnumModel(T::model_);
    //Установить идентификатор сессии.
    wrapper.setSessionID(m_aSessionID);
    //Установить модель.    
    //Сериализовать модель User.Передать данные о пользователе.
    QString userAsString = JsonSerializer::serialize(model);
    wrapper.setData(userAsString);
    //Упаковать  весь запрос в строку
    QString query = JsonSerializer::serialize(wrapper);
    //Переслать его на сервер.
    m_pCommandController->requestServer(query);

}
#endif /* CLIENTCONTROLLER_IMPL_H */

