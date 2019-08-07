/*
 * Copyright (C) 2017 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     andywang <andywang_cm@deepin.com>
 *
 * Maintainer: andywang <andywang_cm@deepin.com>
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
#include "bluetoothmodule.h"
#include "bluetoothwidget.h"
#include "detailpage.h"
#include "modules/bluetooth/bluetoothmodel.h"
#include "modules/bluetooth/bluetoothworker.h"
#include "modules/bluetooth/pincodedialog.h"
#include <QDebug>

using namespace DCC_NAMESPACE;
using namespace DCC_NAMESPACE::bluetooth;
using namespace dcc;
using namespace dcc::bluetooth;
BluetoothModule::BluetoothModule(FrameProxyInterface *frame, QObject *parent)
    : QObject(parent),
      ModuleInterface(frame),
      m_bluetoothView(nullptr),
      m_bluetoothModel(nullptr),
      m_bluetoothWorker(nullptr)
{

}

void BluetoothModule::preInitialize()
{
    m_bluetoothWorker = &BluetoothWorker::Instance();
    m_bluetoothModel = m_bluetoothWorker->model();
    m_bluetoothModel->moveToThread(qApp->thread());
    m_bluetoothWorker->moveToThread(qApp->thread());

    auto updateModuleVisible = [=] {
        m_frameProxy->setModuleVisible(this, m_bluetoothModel->adapters().size());
    };

    connect(m_bluetoothModel, &BluetoothModel::adpaterListChanged, this, updateModuleVisible);

    updateModuleVisible();
}

void BluetoothModule::initialize()
{
    connect(m_bluetoothWorker, &BluetoothWorker::requestConfirmation, this, &BluetoothModule::showPinCode);
    connect(m_bluetoothWorker, &BluetoothWorker::pinCodeCancel, this, &BluetoothModule::closePinCode);
}

void BluetoothModule::reset()
{
}

QWidget *BluetoothModule::moduleWidget()
{
    m_bluetoothView = new BluetoothWidget(m_bluetoothModel);

    connect(m_bluetoothView, &BluetoothWidget::requestSetToggleAdapter, m_bluetoothWorker, &BluetoothWorker::setAdapterPowered);
    connect(m_bluetoothView, &BluetoothWidget::requestConnectDevice, m_bluetoothWorker, &BluetoothWorker::connectDevice);
    connect(m_bluetoothView, &BluetoothWidget::requestSetAlias, m_bluetoothWorker, &BluetoothWorker::setAlias);
    connect(m_bluetoothView, &BluetoothWidget::showDeviceDetail, this, &BluetoothModule::showDeviceDetail);

    connect(m_bluetoothView, &BluetoothWidget::requestModuleVisible, [this](const bool visible) {
        m_frameProxy->setModuleVisible(this, visible);
    });
    return m_bluetoothView;
}

const QString BluetoothModule::name() const
{
    return QStringLiteral("bluetooth");
}

void BluetoothModule::contentPopped(QWidget *const w)
{
    Q_UNUSED(w);
}

void BluetoothModule::showDeviceDetail(const Adapter *adapter, const Device *device)
{
    DCC_NAMESPACE::bluetooth::DetailPage *page = new DCC_NAMESPACE::bluetooth::DetailPage(adapter, device);

    connect(page, &DetailPage::requestIgnoreDevice, m_bluetoothWorker, &BluetoothWorker::ignoreDevice);
    connect(page, &DetailPage::requestDisconnectDevice, m_bluetoothWorker, &BluetoothWorker::disconnectDevice);
    connect(page, &DetailPage::requestIgnoreDevice, this, &BluetoothModule::popPage);
    connect(page, &DetailPage::requestDisconnectDevice, this, &BluetoothModule::popPage);
    connect(page, &DetailPage::requestBack, this, &BluetoothModule::popPage);
    connect(page, &DetailPage::requestSetDevAlias, m_bluetoothWorker, &BluetoothWorker::setDeviceAlias);

    m_frameProxy->pushWidget(this, page);
}

void BluetoothModule::popPage()
{
    m_frameProxy->popWidget(this);
}

void BluetoothModule::showPinCode(const QDBusObjectPath &device, const QString &code)
{
    qDebug() << "request confirmation: " << device.path() << code;

    PinCodeDialog *dialog = PinCodeDialog::instance(code);
    m_dialogs[device] = dialog;
    if (!dialog->isVisible()) {
        int ret = dialog->exec();
        closePinCode(device);
        m_bluetoothWorker->pinCodeConfirm(device, bool(ret));
    }
}

void BluetoothModule::closePinCode(const QDBusObjectPath &device)
{
    PinCodeDialog *dialog = m_dialogs[device];
    m_dialogs.remove(device);
    QMetaObject::invokeMethod(dialog, "deleteLater", Qt::QueuedConnection);
}