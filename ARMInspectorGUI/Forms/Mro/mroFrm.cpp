/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   mroFrm.cpp
 * Author: kazun_as
 *
 * Created on 4 мая 2021 г., 16:28
 */

#include "mroFrm.h"
#include "ItemContainer.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

mroFrm::mroFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::mroFrm) {
    widget_->setupUi(this);
    listmro_ = new ModelList<MroView>();
    proxyModel_ = new QSortFilterProxyModel(listmro_);
    mroview_ = new MroView();
    mroFrm_ = new mroEditForm(this);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

mroFrm::~mroFrm() {
    delete widget_;
    delete listmro_;
    delete proxyModel_;
    delete mroview_;
    delete mroFrm_;

}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::mroFrm* mroFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void mroFrm::setModel(const QList<MroView>& mro) {
    listmro_->setListModel(mro);
    proxyModel_->setSourceModel(listmro_);
    this->getUI()->tableView_Mro->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView_Mro->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView_Mro->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void mroFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            switch (model) {
                case ModelWrapper::Model::Inspection:
                {
                    ItemContainer<Inspection> inspectionContainer;
                    JsonSerializer::parse(wrapper.getData(), inspectionContainer);
                    QList<Inspection> listInspection = inspectionContainer.getItemsList();
                    setListInspections(listInspection);
                    //QMessageBox::information(this, "mroFrm::worker", listmro[0].getName());
                    //setModel(listmro);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::MroView:
                {
                    ItemContainer<MroView> mroContainer;
                    JsonSerializer::parse(wrapper.getData(), mroContainer);
                    QList<MroView> listmro = mroContainer.getItemsList();
                    //QMessageBox::information(this, "mroFrm::worker", listmro[0].getName());
                    setModel(listmro);
                    emit ready();
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case ModelWrapper::Command::GET_MODEL:
        {
            Mro mro;
            JsonSerializer::parse(wrapper.getData(), mro);
            fillEditFrm(mro);
            emit ready();
        }
            break;

        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            Mro mro;
            JsonSerializer::parse(wrapper.getData(), mro);
            showData(mro);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            Mro mro;
            JsonSerializer::parse(wrapper.getData(), mro);
            showEditData(mro);
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            //Сервер вернул результат команды "DEL_MODEL"     
            Mro mro;
            JsonSerializer::parse(wrapper.getData(), mro);
            //emit dialog_->showUserData(user);
            QMessageBoxEx::information(0, wrapper.getHead(), wrapper.getMessage() +
                    "МРО  <a style='color:royalblue'> " + mro.getName() + "</a>");

            emit ready();
        }
            break;
        default:
            break;
    }
}
///-----------------------------------------------------------------------------
///
///                 Установить размер таблицы
///          
///-----------------------------------------------------------------------------

void mroFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView_Mro->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView_Mro->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView_Mro->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->getUI()->tableView_Mro->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->getUI()->tableView_Mro->setSelectionMode(QAbstractItemView::SingleSelection);
    this->getUI()->tableView_Mro->setSortingEnabled(true);
    this->getUI()->tableView_Mro->verticalHeader()->hide();
    this->getUI()->tableView_Mro->setWordWrap(false);
    this->getUI()->tableView_Mro->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView_Mro->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView_Mro->setShowGrid(false);
    this->getUI()->tableView_Mro->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->getUI()->tableView_Mro->horizontalHeader()->setHighlightSections(false);
    this->getUI()->tableView_Mro->setAlternatingRowColors(true); // alternative colors 
    this->getUI()->tableView_Mro->setFrameShape(QFrame::NoFrame);
    this->getUI()->tableView_Mro->setMinimumWidth(width);
    this->getUI()->tableView_Mro->setMinimumHeight(height);
    this->getUI()->tableView_Mro->setColumnWidth(0, 85);
    this->getUI()->tableView_Mro->setColumnWidth(1, (width - 85) / 2);
    this->getUI()->tableView_Mro->setColumnWidth(2, (width - 85) / 2);
}
///-----------------------------------------------------------------------------
///
///      обработчик кнопки добавления записи МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_AddMro_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addMro_clicked()");
    this->getUI()->tableView_Mro->model()->sort(-1);
    //mroEditForm frm;
    mroFrm_->setWindowTitle("Добавление новой записи");
    mroFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    mroFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (mroFrm_->exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        Mro* mro = new Mro();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        mro->setName(mroFrm_->getUI()->lineEditName->text());
        mro->setInspection(mroFrm_->getInspections()[mroFrm_->getUI()->comboBoxInspection->currentIndex()].getId());

        //QString mroAsString = JsonSerializer::serialize(*mro);
        //QJsonObject param;
        //param.insert(DATA, mroAsString);
        emit runServerCmd(Functor<Mro>::produce(ModelWrapper::Command::ADD_NEW_MODEL, *mro));
        emit waitReady();
        //showNewRecordData(*mro);
        delete mro;
    }
}

///-----------------------------------------------------------------------------
///
///       обработчик кнопки редактирования записи  МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_EditMro_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editMro_clicked()");
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView_Mro->currentIndex()).row();
    if (rowidx >= 0) {
        MroView mroV = listmro_->getModel(proxyModel_->mapToSource(this->getUI()->tableView_Mro->currentIndex()));
        auto id = mroV.getId();
        QJsonObject param;
        param.insert("ID", id);
        emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::Command::GET_MODEL, param));
        emit waitReady();
        mroFrm_->setWindowTitle("Редактирование записи");
        mroFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        mroFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
        if (mroFrm_->exec() == QDialog::Accepted) {
            Mro* mro = new Mro();
            mro->setId(id);
            mro->setName(mroFrm_->getUI()->lineEditName->text());
            mro->setInspection(mroFrm_->getInspections()[mroFrm_->getUI()->comboBoxInspection->currentIndex()].getId());
            //emit updateUser(*user);
            emit runServerCmd(Functor<Mro>::produce(ModelWrapper::Command::UPDATE_MODEL, *mro));
            emit waitReady();
            delete mro;
        }
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  записи  МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::on_pushButton_RemoveMro_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_removeMro_clicked()");
    //Question MessageBox
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView_Mro->currentIndex()).row();
    if (rowidx >= 0) {
        MroView mro = listmro_->getModel(proxyModel_->mapToSource(this->getUI()->tableView_Mro->currentIndex()));
        auto id = mro.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление записи",
                "Вы действительно хотите удалить МРО <br><br><a style='font-size:14px;color:red;'> " +
                mro.getName() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert(ID_, id);
            //emit deleteUser(id);
            emit runServerCmd(Functor<Mro>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listmro_->delModel(proxyModel_->mapToSource(this->getUI()->tableView_Mro->currentIndex()));
        } else {
            qDebug() << "Yes was *not* clicked";
        }
    }
}

///-----------------------------------------------------------------------------
///
///         показать данные новой записи
///          
///-----------------------------------------------------------------------------

void mroFrm::showData(const Mro& asMro) {
    Mro mro = asMro;
    mroview_->setId(mro.getId());
    mroview_->setName(mro.getName());
    mroview_->setInspection(mroFrm_->mapInspections()[mro.getInspection()]);

    listmro_->addModel(*mroview_);
    this->getUI()->tableView_Mro->selectRow(listmro_->rowCount() - 1);
    this->getUI()->tableView_Mro->scrollToBottom();
}

///-----------------------------------------------------------------------------
///
///         показать отредактированные данные 
///          
///-----------------------------------------------------------------------------

void mroFrm::showEditData(const Mro& mro) {
    mroview_->setId(mro.getId());
    mroview_->setName(mro.getName());
    mroview_->setInspection(mroFrm_->mapInspections()[mro.getInspection()]);
    QItemSelectionModel *select = this->getUI()->tableView_Mro->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView_Mro->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), mroview_->getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), mroview_->getName(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 2), mroview_->getInspection(), Qt::EditRole);
}

///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций  в окнах ввода и 
///         редактированиядля пользователя  
///          
///-----------------------------------------------------------------------------

void mroFrm::setListInspections(const QList<Inspection>& inspections) {
    //QMessageBox::information(0, "Information Box", inspections[1].getName());
    mroFrm_->setInspections(inspections);
}

///-----------------------------------------------------------------------------
///
///         заполнить форму редактирования МРО
///          
///-----------------------------------------------------------------------------

void mroFrm::fillEditFrm(const Mro& mro) {
    mroFrm_->getUI()->lineEditName->setText(mro.getName());
    for (int i = 0; i < mroFrm_->getInspections().size(); i++) {
        if (mroFrm_->getInspections()[i].getId() == mro.getInspection()) {
            mroFrm_->getUI()->comboBoxInspection->setCurrentIndex(i);
            break;
        }
    }
}

