/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/****************************************************************************
 **
 **             Интерфейс класса модели.
 **
 ****************************************************************************/

/* 
 * File:   Model.h
 * Author: kazun_as
 *
 * Created on 29 марта 2021 г., 14:21
 */

#ifndef MODEL_H
#define MODEL_H

class Model  {
public:
    virtual ~Model(){};
    virtual  const QVariant getData(const int& ) const = 0;
    virtual  void setData(const int&, const QVariant& ) = 0;
private:

};

#endif /* MODEL_H */

