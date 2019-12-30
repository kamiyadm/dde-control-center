/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     lq <longqi_cm@deepin.com>
 *
 * Maintainer: lq <longqi_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "advancedpage.h"
#include "window/utils.h"

#include "widgets/settingsgroup.h"
#include "widgets/titlelabel.h"
#include "modules/sound/portitem.h"
#include "modules/sound/soundmodel.h"

#include <QScrollArea>

using namespace dcc::sound;
using namespace dcc::widgets;
using namespace DCC_NAMESPACE::sound;
DWIDGET_USE_NAMESPACE

Q_DECLARE_METATYPE(const dcc::sound::Port *)

AdvancedPage::AdvancedPage(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
{
    m_layout->setMargin(0);

    auto scrollarea = new QScrollArea;
    scrollarea->setWidgetResizable(true);
    scrollarea->setFrameStyle(QFrame::NoFrame);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollarea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    scrollarea->setContentsMargins(ThirdPageContentsMargins);

    auto contentWidget = new QWidget;
    auto contentLayout = new QVBoxLayout;
    contentLayout->setMargin(0);
    contentWidget->setLayout(contentLayout);
    scrollarea->setWidget(contentWidget);

    m_layout->addWidget(scrollarea);
    setLayout(m_layout);

    const int titleLeftMargin = 15;
///    //~ contents_path /sound/Advanced
    TitleLabel *label = new TitleLabel(tr("Output"));
    label->setContentsMargins(titleLeftMargin, 0, 0, 0);
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    contentLayout->addWidget(label);

    auto setListFucn = [](DListView * listView) {
        listView->setEditTriggers(DListView::NoEditTriggers);
        listView->setAutoScroll(false);
        listView->setSelectionMode(QAbstractItemView::NoSelection);
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setBackgroundType(DStyledItemDelegate::ClipCornerBackground);
        listView->setSizeAdjustPolicy(DListView::AdjustToContentsOnFirstShow);
        listView->setSpacing(1);
    };

    m_outputList = new DListView;
    setListFucn(m_outputList);
    contentLayout->addWidget(m_outputList);
    contentLayout->addSpacing(10);

///    //~ contents_path /sound/Advanced
    label = new TitleLabel(tr("Input"));
    label->setContentsMargins(titleLeftMargin, 0, 0, 0);
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    contentLayout->addWidget(label);
    m_inputList = new DListView;
    setListFucn(m_inputList);
    contentLayout->addWidget(m_inputList);

    connect(m_inputList, &DListView::clicked, this, [this](const QModelIndex & idx) {
        this->requestSetPort(m_inputList->model()->data(idx, Qt::WhatsThisPropertyRole).value<const Port *>());
    });
    connect(m_outputList, &DListView::clicked, this, [this](const QModelIndex & idx) {
        this->requestSetPort(m_outputList->model()->data(idx, Qt::WhatsThisPropertyRole).value<const Port *>());
    });
}

AdvancedPage::~AdvancedPage()
{
}

void AdvancedPage::setModel(dcc::sound::SoundModel *model)
{
    m_model = model;

    connect(m_model, &SoundModel::portAdded, this, &AdvancedPage::addPort);
    connect(m_model, &SoundModel::portRemoved, this, &AdvancedPage::removePort);

    initList();
}

void AdvancedPage::initList()
{
    m_inputModel = new QStandardItemModel(m_inputList);
    m_inputList->setModel(m_inputModel);
    m_outputModel = new QStandardItemModel(m_outputList);
    m_outputList->setModel(m_outputModel);

    auto ports = m_model->ports();
    for (auto port : ports) {
        addPort(port);
    }
}

void AdvancedPage::addPort(const Port *port)
{
    DStandardItem *pi = new DStandardItem;
    pi->setText(port->name());

    DViewItemActionList actionList;
    auto cardAction = new DViewItemAction(Qt::AlignVCenter, QSize(30, 30));
    cardAction->setFontSize(DFontSizeManager::T8);
    cardAction->setTextColorRole(DPalette::TextTips);
    cardAction->setText(tr("Sound Card:") + port->cardName());
    actionList << cardAction;
    pi->setTextActionList(actionList);
    pi->setData(QVariant::fromValue<const Port *>(port), Qt::WhatsThisPropertyRole);

    connect(port, &Port::nameChanged, this, [ = ](const QString str) {
        pi->setText(str);
    });
    connect(port, &Port::cardNameChanged, cardAction, &DViewItemAction::setText);
    connect(port, &Port::isActiveChanged, this, [ = ](bool isActive) {
        pi->setCheckState(isActive ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    });

    if (port->isActive())
        pi->setCheckState(Qt::CheckState::Checked);

    if (port->direction() == Port::Out) {
        m_outputModel->appendRow(pi);
    } else {
        m_inputModel->appendRow(pi);
    }
}

void AdvancedPage::removePort(const QString &portId, const uint &cardId)
{
    auto rmFunc = [ = ](QStandardItemModel * model) {
        for (int i = 0; i < model->rowCount();) {
            auto item = model->item(i);
            auto port = item->data(Qt::WhatsThisPropertyRole).value<const Port *>();
            if (port->id() == portId && cardId == port->cardId()) {
                model->removeRow(i);
            } else {
                ++i;
            }
        }
    };

    rmFunc(m_inputModel);
    rmFunc(m_outputModel);
}
