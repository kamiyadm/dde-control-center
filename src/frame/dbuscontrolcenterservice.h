/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *             listenerri <listenerri@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *             listenerri <listenerri@gmail.com>
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

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp dde-center -a dbuscontrolcenter -c DBusControlCenter -l Frame
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DBUSCONTROLCENTER_H_1439447183
#define DBUSCONTROLCENTER_H_1439447183

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.deepin.dde.ControlCenter
 */
class Frame;
class DBusControlCenterService: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dde.ControlCenter")

public:
    explicit DBusControlCenterService(Frame *parent);
    virtual ~DBusControlCenterService();

    inline Frame *parent() const;

public: // PROPERTIES
    Q_PROPERTY(bool ShowInRight READ showInRight)
    Q_PROPERTY(QRect Rect READ rect NOTIFY rectChanged)

    bool showInRight() const;

//    Q_PROPERTY(int X READ x)
//    int x() const;
    const QRect rect() const;

public Q_SLOTS: // METHODS
    void Hide();
    void HideImmediately();
    void Show();
    void ShowImmediately();
    void ShowHome();
    void ShowModule(const QString &module);
    void ShowPage(const QString &module, const QString &page);
    void SetAutoHide(const bool autoHide);
    void Toggle();
    void ToggleInLeft();
    bool isNetworkCanShowPassword();

Q_SIGNALS: // SIGNALS
    void rectChanged(const QRect &rect);
    void destRectChanged(const QRect &rect);

private:
    bool m_toggleProcessed;
};

#endif