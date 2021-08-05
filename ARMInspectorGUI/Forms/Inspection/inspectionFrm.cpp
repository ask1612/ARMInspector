/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   inspectionFrm.cpp
 * Author: kazun_as
 *
 * Created on 14 мая 2021 г., 15:40
 */

#include "inspectionFrm.h"
#include "ItemContainer.h"

///-----------------------------------------------------------------------------
///
///         Конструктор.
///          
///-----------------------------------------------------------------------------

inspectionFrm::inspectionFrm(QWidget *parent) :
QDialog(parent), widget_(new Ui::inspectionFrm) {
    widget_->setupUi(this);
    listinspection_ = new ModelList<InspectionView>();
    proxyModel_ = new QSortFilterProxyModel(listinspection_);
    inspectionview_ = new InspectionView();
    inspectionEditFrm_ = new inspectionEditForm(this);

}
///-----------------------------------------------------------------------------
///
///         Деструктор.
///          
///-----------------------------------------------------------------------------

inspectionFrm::~inspectionFrm() {
    delete widget_;
    delete listinspection_;
    delete proxyModel_;
    delete inspectionview_;
    delete inspectionEditFrm_;

}


///-----------------------------------------------------------------------------
///
///         Получить ссылку на виджет.
///          
///-----------------------------------------------------------------------------

Ui::inspectionFrm* inspectionFrm::getUI() {
    return widget_;
}


///-----------------------------------------------------------------------------
///
///         определить модель вывода данных
///          
///-----------------------------------------------------------------------------

void inspectionFrm::setModel(const QList<InspectionView>& inspection) {
    listinspection_->setListModel(inspection);
    proxyModel_->setSourceModel(listinspection_);
    this->getUI()->tableView->setSortingEnabled(true); // enable sortingEnabled
    this->getUI()->tableView->setModel(proxyModel_);
    emit ready();
    //this->getUI()->tableView_Mro->setSpan(0,1,2,2);
}

///-----------------------------------------------------------------------------
///
///         Обработать ответ сервера.
///          
///-----------------------------------------------------------------------------

void inspectionFrm::worker(const QString& asWrapper) {
    ModelWrapper wrapper;
    //Разворачиваем командную обёртку.
    JsonSerializer::parse(asWrapper, wrapper);
    ModelWrapper::Command command = wrapper.getEnumCommand();
    ModelWrapper::Model model = wrapper.getEnumModel();
    switch (command) {
        case ModelWrapper::Command::GET_LIST_MODELS:
        {
            switch (model) {
                case ModelWrapper::Model::Mro:
                {
                    ItemContainer<Mro> mroContainer;
                    JsonSerializer::parse(wrapper.getData(), mroContainer);
                    QList<Mro> listmro = mroContainer.getItemsList();
                    setListMro(listmro);
                    //QMessageBox::information(this, "inspectionFrm::worker", listmro[0].getName());
                    //setModel(listmro);
                    emit ready();
                }
                    break;
                case ModelWrapper::Model::InspectionView:
                {
                    ItemContainer<InspectionView> inspectionContainer;
                    JsonSerializer::parse(wrapper.getData(), inspectionContainer);
                    QList<InspectionView> listinspection = inspectionContainer.getItemsList();
                    //QMessageBox::information(this, "inspectionFrm::worker", listmro[0].getName());
                    setModel(listinspection);
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
            Inspection inspection;
            JsonSerializer::parse(wrapper.getData(), inspection);
            fillEditFrm(inspection);
            emit ready();
        }
            break;

        case ModelWrapper::Command::ADD_NEW_MODEL:
        {
            Inspection inspection;
            JsonSerializer::parse(wrapper.getData(), inspection);
            showData(inspection);
            emit ready();
        }
            break;
        case ModelWrapper::Command::UPDATE_MODEL:
        {
            Inspection inspection;
            JsonSerializer::parse(wrapper.getData(), inspection);
            showEditData(inspection);
            emit ready();
        }
            break;
        case ModelWrapper::Command::DEL_MODEL:
        {
            //Сервер вернул результат команды "DEL_MODEL"     
            Inspection inspection;
            JsonSerializer::parse(wrapper.getData(), inspection);
            //emit dialog_->showUserData(user);
            //QMessageBoxEx::information(0, wrapper.getHead(), wrapper.getMessage() +
            //        "МРО  <a style='color:royalblue'> " + inspection.getName() + "</a>");

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

void inspectionFrm::setSizeTbl(const int& width, const int& height) {
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
    this->getUI()->tableView->setColumnWidth(1, (width - 85) / 2);
    this->getUI()->tableView->setColumnWidth(2, (width - 85) / 2);
}
///-----------------------------------------------------------------------------
///
///      обработчик кнопки добавления записи МРО
///          
///-----------------------------------------------------------------------------

void inspectionFrm::on_pushButton_Add_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_addMro_clicked()");
    this->getUI()->tableView->model()->sort(-1);
    //mroEditForm frm;
    inspectionEditFrm_->setWindowTitle("Добавление новой записи");
    inspectionEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Добавить"));
    inspectionEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
    if (inspectionEditFrm_->exec() == QDialog::Accepted) {
        //QMessageBox::information(this, "Добавление записи НСИ", "QDialog::Accepted");
        Inspection* inspection = new Inspection();
        //QMessageBox::information(this, "Добавление новой записи НСИ", Nsi::num_);
        inspection->setName(inspectionEditFrm_->getUI()->lineEdit->text());
        inspection->setMro(inspectionEditFrm_->getListMro()[inspectionEditFrm_->getUI()->comboBox->currentIndex()].getId());

        //QString mroAsString = JsonSerializer::serialize(*mro);
        //QJsonObject param;
        //param.insert(DATA, mroAsString);
        emit runServerCmd(Functor<Inspection>::produce(ModelWrapper::Command::ADD_NEW_MODEL, *inspection));
        emit waitReady();
        //showNewRecordData(*mro);
        delete inspection;
    }
}

///-----------------------------------------------------------------------------
///
///       обработчик кнопки редактирования записи  МРО
///          
///-----------------------------------------------------------------------------

void inspectionFrm::on_pushButton_Edit_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_editMro_clicked()");
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        InspectionView inspectionV = listinspection_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = inspectionV.getId();
        QJsonObject param;
        param.insert(ID_, id);
        emit runServerCmd(Functor<Inspection>::producePrm(ModelWrapper::Command::GET_MODEL, param));
        emit waitReady();
        inspectionEditFrm_->setWindowTitle("Редактирование");
        inspectionEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
        inspectionEditFrm_->getUI()->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));
        if (inspectionEditFrm_->exec() == QDialog::Accepted) {
            Inspection* inspection = new Inspection();
            inspection->setId(id);
            inspection->setName(inspectionEditFrm_->getUI()->lineEdit->text());
            inspection->setMro(inspectionEditFrm_->getListMro()[inspectionEditFrm_->getUI()->comboBox->currentIndex()].getId());
            emit runServerCmd(Functor<Inspection>::produce(ModelWrapper::Command::UPDATE_MODEL, *inspection));
            emit waitReady();
            delete inspection;
        }
    }
}

///-----------------------------------------------------------------------------
///
///         обработчик кнопки удаления  записи  МРО
///          
///-----------------------------------------------------------------------------

void inspectionFrm::on_pushButton_Remove_clicked() {
    //QMessageBox::information(this, "АРМ Юриста", "on_pushButton_removeMro_clicked()");
    //Question MessageBox
    int rowidx = proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()).row();
    if (rowidx >= 0) {
        InspectionView inspection = listinspection_->getModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
        auto id = inspection.getId();
        QMessageBoxEx::StandardButton reply;
        reply = QMessageBoxEx::question(this, "Удаление записи",
                "Вы действительно хотите удалить РЭГИ <br><br><a style='font-size:14px;color:red;'> " +
                inspection.getName() + "</a> ?<br>",
                QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            QJsonObject param;
            param.insert(ID_, id);
            //emit deleteUser(id);
            emit runServerCmd(Functor<Inspection>::producePrm(ModelWrapper::DEL_MODEL, param));
            emit waitReady();
            listinspection_->delModel(proxyModel_->mapToSource(this->getUI()->tableView->currentIndex()));
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

void inspectionFrm::showData(const Inspection& asInspection) {
    Inspection inspection = asInspection;
    inspectionview_->setId(inspection.getId());
    inspectionview_->setName(inspection.getName());
    inspectionview_->setMro(inspectionEditFrm_->mapMro()[inspection.getMro()]);

    listinspection_->addModel(*inspectionview_);
    this->getUI()->tableView->selectRow(listinspection_->rowCount() - 1);
    this->getUI()->tableView->scrollToBottom();
}

///-----------------------------------------------------------------------------
///
///         показать отредактированные данные 
///          
///-----------------------------------------------------------------------------

void inspectionFrm::showEditData(const Inspection& inspection) {
    inspectionview_->setId(inspection.getId());
    inspectionview_->setName(inspection.getName());
    inspectionview_->setMro(inspectionEditFrm_->mapMro()[inspection.getMro()]);
    QItemSelectionModel *select = this->getUI()->tableView->selectionModel();
    int rowidx = select->currentIndex().row();
    this->getUI()->tableView->scrollTo(select->currentIndex());
    select->model()->setData(select->model()->index(rowidx, 0), inspectionview_->getId(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 1), inspectionview_->getName(), Qt::EditRole);
    select->model()->setData(select->model()->index(rowidx, 2), inspectionview_->getMro(), Qt::EditRole);
}

///-----------------------------------------------------------------------------
///
///         Инициализировать список инспекций  в окнах ввода и 
///         редактированиядля пользователя  
///          
///-----------------------------------------------------------------------------

void inspectionFrm::setListMro(const QList<Mro>& listmro) {
    //QMessageBox::information(0, "Information Box", inspections[1].getName());
    inspectionEditFrm_->setListMro(listmro);
}

///-----------------------------------------------------------------------------
///
///         заполнить форму редактирования МРО
///          
///-----------------------------------------------------------------------------

void inspectionFrm::fillEditFrm(const Inspection& inspection) {
    inspectionEditFrm_->getUI()->lineEdit->setText(inspection.getName());
    inspectionEditFrm_->getUI()->comboBox->setCurrentText(inspectionEditFrm_->mapMro()[inspection.getMro()]);
}

