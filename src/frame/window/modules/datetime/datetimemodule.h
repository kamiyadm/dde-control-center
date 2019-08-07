/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     wubw <wubowen_cm@deepin.com>
 *
 * Maintainer: wubw <wubowen_cm@deepin.com>
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
#pragma once

#include "window/interface/moduleinterface.h"

#include <QObject>
#include <types/zoneinfo.h>

namespace dcc {
namespace datetime {
class DatetimeWork;
class DatetimeModel;
class TimeZoneChooser;
}
}

namespace DCC_NAMESPACE {
namespace datetime {
class TimezoneList;

class DatetimeModule : public QObject, public ModuleInterface
{
    Q_OBJECT
public:
    enum datetimeType {
        DEFAULT = -1,
        TIMEZONELIST,
        SYSTEMTIMEZONE,
        TIMESETTING,
        COUNT
    };


public:
    DatetimeModule(FrameProxyInterface *frameProxy, QObject *parent = nullptr);

    virtual void initialize() override;
    virtual void reset() override;
    virtual const QString name() const override;
    virtual void showPage(const QString &pageName) override;
    virtual QWidget *moduleWidget() override;
    virtual void contentPopped(QWidget *const w) override;

    void createWidget(int index);

private:
    void showTimezoneList();
    void showSystemTimezone();
    void showTimeSetting();
    void ensureZoneChooserDialog();

private:
    dcc::datetime::DatetimeWork *m_work;
    dcc::datetime::DatetimeModel *m_model;
    QPointer<dcc::datetime::TimeZoneChooser> m_dialog;
    QPointer<TimezoneList> m_timezonelist;//timezonelist in other page, need exchangle data from this page

Q_SIGNALS:
    void requestAddUserTimeZone(const QString &zone);
    void requestRemoveUserTimeZone(const ZoneInfo &zone);
    void requestSetTimeZone(const QString &zone);

public Q_SLOTS:
    void onPushWidget(const int &index);
    void onPopWidget();
    void updateSystemTimezone(const QString &timezone);

};

}// namespace datetime
}// namespace DCC_NAMESPACE