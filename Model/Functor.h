/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functor.h
 * Author: kazun_as
 *
 * Created on 5 мая 2021 г., 11:10
 */

#ifndef FUNCTOR_H
#define FUNCTOR_H
#include "ModelWrapper.h"
#include <QJsonObject>
#include "User/User.h"



template <class T> class Functor {
public:
    static QString produce(ModelWrapper::Command, const T&);
    static QString producePrm(ModelWrapper::Command, const QJsonObject&);
private:
};

#include "Functor_IMPL.h"
#endif /* FUNCTOR_H */

