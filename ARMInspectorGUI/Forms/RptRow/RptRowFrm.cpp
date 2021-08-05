/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RptRowFrm.cpp
 * Author: kazun_as
 *
 * Created on 15 мая 2021 г., 14:45
 */

#include "RptRowFrm.h"
#include "ItemContainer.h"
#include "Nsi/Nsi.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

RptRowFrm::RptRowFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::RptRowFrm) {
    widget_->setupUi(this);
    listrptrow_ = new ModelList<RptRow>();
    proxyModel_ = new QSortFilterProxyModel(listrptrow_);
    rptrow_ = new RptRow();
    rptrowEditFrm_ = new RptRowEditForm(this);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

RptRowFrm::~RptRowFrm() {
    delete widget_;
    delete listrptrow_;
    delete proxyModel_;
    delete rptrow_;
    delete rptrowEditFrm_;

}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::RptRowFrm* RptRowFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void RptRowFrm::setModel(const QList<RptRow>& rptrow) {
    listrptrow_->setListModel(rptrow);
    proxyModel_->setSourceModel(listrptrow_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    //emit ready();
    //this->getUI()->tableView_Mro->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void RptRowFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            ItemContainer<RptRow> rptrowContainer;
            JsonSerializer::parse(wrapper.getData(), rptrowContainer);
            QList<RptRow> listrptrow = rptrowContainer.getItemsList();
            //QMessageBox::information(this, "RptRowFrm::worker", listrptrowview[0].getArticle());
            setModel(listrptrow);
            emit ready();
        }
            break;
        case ModelWrapper::Command::GET_MODEL:
        {
            RptRow rptrow;
            JsonSerializer::parse(wrapper.getData(), rptrow);
            fillEditFrm(rptrow);
            emit ready();
        }
            break;

        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            RptRow rptrow;
            JsonSerializer::parse(wrapper.getData(), rptrow);
            showData(rptrow);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            RptRow rptrow;
            JsonSerializer::parse(wrapper.getData(), rptrow);
            showEditData(rptrow);
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            //Сервер вернул результат команды "DEL_MODEL"     
            //RptRow rptrow;
            //JsonSerializer::parse(wrapper.getData(), rptrow);
            //emit dialog_->showUserData(user);
            //QMessageBoxEx::information(Q_NULLPTR, wrapper.getHead(), wrapper.getMessage() +
            //        " <a style='color:royalblue'> " + rptrow.getArticle() + "</a>");

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

void RptRowFrm::setSizeTbl(const int& width, const int& height) {
    //frm.getUI()->tableView_Mro->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //frm.getUI()->tableView_Mro->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //frm.getUI()->tableView_Mro->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    this->getUI()->tableView->setColumnWidth(0, 85);
    this->getUI()->tableView->setColumnWidth(1, 35);
    this->getUI()->tableView->setColumnWidth(2, ((width - 160)* 3) / 4);
    this->getUI()->tableView->setColumnWidth(3, (width - 160) / 4);
    this->getUI()->tableView->setColumnWidth(4, 40);
}
///-----------------------------------------------------------------------------
///
///      обработчик кнопки добавления записи МРО
///          
///-----------------------------------------------------------------------------

void RptRowFrm::on_pushButton_Add_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addMro_clicked()");
    this->getUI()->tableView->model()->sort(-1);
    //mroEditForm frm;
    rptrowEditFrm_->setWindowTitle("Добавление новой записи");
    rptrowEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    rptrowEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (rptrowEditFrm_->exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        RptRow* rptrow = new RptRow();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        rptrow->setNpp(rptrowEditFrm_->getUI()->lineEdit_Npp->text());
        rptrow->setName(rptrowEditFrm_->getUI()->textEdit_Name->toPlainText());
        rptrow->setFormula(rptrowEditFrm_->getUI()->lineEdit_Formula->text());
        rptrow->setRow(rptrowEditFrm_->getUI()->lineEdit_Row->text().toInt());

        //QString mroAsString = JsonSerializer::serialize(*mro);
        //QJsonObject param;
        //param.insert(DATA, mroAsString);
        emit runServerCmd(Functor<RptRow>::produce(ModelWrapper::Command::ADD_NEW_MODEL, *rptrow));
        emit waitReady();
        //showNewRecordData(*mro);
        delete rptrow;
    }
}

///-----------------------------------------------------------------------------
///
///       обработчик кнопки редактирования записи  МРО
///          
///-----------------------------------------------------------------------------

void RptRowFrm::on_pushButton_Edit_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editMro_clicked()");
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        RptRow rptrowV = listrptrow_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = rptrowV.getId();
        QJsonObject param;
        param.insert(ID_, id);
        emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::Command::GET_MODEL, param));
        emit waitReady();
        rptrowEditFrm_->setWindowTitle("Редактирование");
        rptrowEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        rptrowEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
        if (rptrowEditFrm_->exec() == QDialog::Accepted) {
            RptRow* rptrow = new RptRow();
            rptrow->setId(id);
            rptrow->setNpp(rptrowEditFrm_->getUI()->lineEdit_Npp->text());
            rptrow->setName(rptrowEditFrm_->getUI()->textEdit_Name->toPlainText());
            rptrow->setFormula(rptrowEditFrm_->getUI()->lineEdit_Formula->text());
            rptrow->setRow(rptrowEditFrm_->getUI()->lineEdit_Row->text().toInt());
            emit runServerCmd(Functor<RptRow>::produce(ModelWrapper::Command::UPDATE_MODEL, *rptrow));
            emit waitReady();
            delete rptrow;
        }
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  записи  МРО
///          
///-----------------------------------------------------------------------------

void RptRowFrm::on_pushButton_Remove_clicked() {
    //Question MessageBox
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        RptRow rptrow = listrptrow_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = rptrow.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление записи",
                "Вы действительно хотите удалить запись<br><br><a style='font-size:14px;color:red;'> " +
                rptrow.getName() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert(ID_, id);
            emit runServerCmd(Functor<RptRow>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listrptrow_->delModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
            //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_removeMro_clicked()");
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

void RptRowFrm::showData(const RptRow& asRptRow) {
    RptRow rptrow = asRptRow;
    listrptrow_->addModel(rptrow);
    this->getUI()->tableView->selectRow(listrptrow_->rowCount() - 1);
    this->getUI()->tableView->scrollToBottom();
}

///-----------------------------------------------------------------------------
///
///         показать данные выбранной записи 
///          
///-----------------------------------------------------------------------------

void RptRowFrm::showEditData(const RptRow& rptrow) {
    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), rptrow.getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), rptrow.getNpp(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 2), rptrow.getName(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 3), rptrow.getFormula(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 4), rptrow.getRow(), Qt::EditRole);
}


///-----------------------------------------------------------------------------
///
///         заполнить форму редактирования
///          
///-----------------------------------------------------------------------------

void RptRowFrm::fillEditFrm(const RptRow& rptrow) {
    rptrowEditFrm_->getUI()->lineEdit_Npp->setText(rptrow.getNpp());
    rptrowEditFrm_->getUI()->textEdit_Name->setText(rptrow.getName());
    rptrowEditFrm_->getUI()->lineEdit_Formula->setText(rptrow.getFormula());
    rptrowEditFrm_->getUI()->lineEdit_Row->setText(QString::number(rptrow.getRow()));
};

