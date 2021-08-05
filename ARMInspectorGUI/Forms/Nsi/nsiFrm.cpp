/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   nsiFrm.cpp
 * Author: kazun_as
 *
 * Created on 26 апреля 2021 г., 08:40
 */

#include "nsiFrm.h"
#include "JsonSerializer.h"
#include "JsonSerializable.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

nsiFrm::nsiFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::nsiFrm) {
    widget_->setupUi(this);
    nsiEditFrm_ = new nsiEditForm(this);
    listnsi_ = new ModelList<Nsi>();
    proxyModel_ = new QSortFilterProxyModel(listnsi_);
}

///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

nsiFrm::~nsiFrm() {
    delete widget_;
    delete nsiEditFrm_;
    delete listnsi_;
    delete proxyModel_;
}

///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::nsiFrm* nsiFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void nsiFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            ItemContainer<Nsi> nsiContainer;
            JsonSerializer::parse(wrapper.getData(), nsiContainer);
            QList<Nsi> listnsi = nsiContainer.getItemsList();
            setModel(listnsi);
            emit ready();
        }
            break;
        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            Nsi nsi;
            JsonSerializer::parse(wrapper.getData(), nsi);
            showData(nsi);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            //QMessageBox::information(this, "АРМ Юриста", asWrapper);
            Nsi nsi;
            JsonSerializer::parse(wrapper.getData(), nsi);
            showEditData(nsi);
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            //Nsi nsi;
            //JsonSerializer::parse(wrapper.getData(), nsi);
            //QMessageBoxEx::information(Q_NULLPTR, wrapper.getHead(), wrapper.getMessage() +
            //        " <a style='color:royalblue'> " + nsi.getName() + "</a>");
            emit ready();
        }
            break;
        default:
            break;
    }
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void nsiFrm::setModel(const QList<Nsi>& nsi) {
    listnsi_->setListModel(nsi);
    proxyModel_->setSourceModel(listnsi_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    //emit ready();
    //this->getUI()->tableView->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///                 Установить размер таблицы
///          
///-----------------------------------------------------------------------------

void nsiFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->getUI()->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->getUI()->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->getUI()->tableView->setSortingEnabled(true);
    this->getUI()->tableView->verticalHeader()->hide();
    this->getUI()->tableView->setWordWrap(false);
    this->getUI()->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->getUI()->tableView->setShowGrid(false);
    this->getUI()->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->getUI()->tableView->horizontalHeader()->setHighlightSections(false);
    this->getUI()->tableView->setAlternatingRowColors(true); // alternative colors 
    this->getUI()->tableView->setFrameShape(QFrame::NoFrame);
    this->getUI()->tableView->setMinimumWidth(width);
    this->getUI()->tableView->setMinimumHeight(height);
    this->getUI()->tableView->setColumnWidth(0, 50);
    this->getUI()->tableView->setColumnWidth(1, width - 50);
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки добавления записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_addNsi_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addNsi_clicked");
    this->getUI()->tableView->model()->sort(-1);
    nsiEditForm frm;
    frm.setWindowTitle("Добавление новой записи");
    frm.getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    frm.getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (frm.exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        Nsi* nsi = new Nsi(Nsi::num_);
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        nsi->setName(frm.getUI()->lineEditName->text());
        QString nsiAsString = JsonSerializer::serialize(*nsi);
        QJsonObject param;
        param.insert(NSI_NUM, Nsi::num_);
        param.insert(DATA, nsiAsString);
        emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::Command::ADD_NEW_MODEL, param));
        emit waitReady();
        //showNewRecordData(*nsi);
        delete nsi;
    }
}
///-----------------------------------------------------------------------------
///
///         обработчик кнопки редактирования записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_editNsi_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editNsi_clicked");
    nsiEditForm frm;
    frm.setWindowTitle("Редактирование записи НСИ");
    frm.getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    frm.getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    Nsi nsi = listnsi_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
    frm.getUI()->lineEditName->setText(nsi.getName());
    if (frm.exec() == QDialog::Accepted) {
        ///        QMessageBox::information(this, "Редактирование записи НСИ", "QDialog::Accepted");
        nsi.setName(frm.getUI()->lineEditName->text());
        QString nsiAsString = JsonSerializer::serialize(nsi);
        QJsonObject param;
        param.insert(NSI_NUM, Nsi::num_);
        param.insert(DATA, nsiAsString);
        emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::Command::UPDATE_MODEL, param));
        emit waitReady();
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления записи НСИ
///          
///-----------------------------------------------------------------------------

void nsiFrm::on_pushButton_deleteNsi_clicked() {
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        Nsi nsi = listnsi_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = nsi.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление записи",
                "Вы действительно хотите удалить запись <br><br><a style='font-size:14px;color:red;'> " +
                nsi.getName() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert(ID_, id);
            param.insert(NSI_NUM, Nsi::num_);

            //emit deleteUser(id);
            emit runServerCmd(Functor<Nsi>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listnsi_->delModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        } else {
            qDebug() << "Yes was *not* clicked";
        }
    }
}

///-----------------------------------------------------------------------------
///
///         close event 
///          
///-----------------------------------------------------------------------------

void nsiFrm::closeEvent(QCloseEvent *event) {
    event->accept();
    QDialog::closeEvent(event);
}

///-----------------------------------------------------------------------------
///
///         показать данные новой записи
///          
///-----------------------------------------------------------------------------

void nsiFrm::showData(const Nsi& nsi) {
    Nsi nn = nsi;
    listnsi_->addModel(nn);
    this->getUI()->tableView->selectRow(listnsi_->rowCount() - 1);
    this->getUI()->tableView->scrollToBottom();
}


///-----------------------------------------------------------------------------
///
///         показать данные отредактированной  записи
///          
///-----------------------------------------------------------------------------

void nsiFrm::showEditData(const Nsi& nsi) {
    //QMessageBox::information(Q_NULLPTR, "showEditData", nsi.getName());

    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), nsi.getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), nsi.getName(), Qt::EditRole);

    //emit ready();
}
