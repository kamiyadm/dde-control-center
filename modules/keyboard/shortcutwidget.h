/*
 * Copyright (C) 2011 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include "contentwidget.h"
#include "shortcutmodel.h"
#include "settingsgroup.h"
#include "searchinput.h"
#include "settingshead.h"
#include <QList>
#include <com_deepin_daemon_search.h>

using namespace dcc::widgets;

using SearchInter=com::deepin::daemon::Search;
class QLineEdit;

namespace dcc {
namespace keyboard{
class ShortcutModel;
class ShortcutWidget : public ContentWidget
{
    Q_OBJECT

public:
    explicit ShortcutWidget(ShortcutModel *model, QWidget *parent = 0);

    void addShortcut(QList<ShortcutInfo*> list, ShortcutModel::InfoType type);

    SettingsHead* getHead();

protected:
    void modifyStatus(bool status);

signals:
    void shortcutChanged(bool valid, ShortcutInfo* info, const QString& shortcut);
    void customShortcut();
    void delShortcutInfo(ShortcutInfo* info);
    void requestDisableShortcut(ShortcutInfo* info);
    void shortcutEditChanged(ShortcutInfo* info);

public slots:
    void onSearch(const QString &text);
    void onCustomAdded(ShortcutInfo* info);
    void onDestroyItem(QObject* obj);
    void onSearchInfo(ShortcutInfo* info, const QString& key);
    void getKeyFinish(QDBusPendingCallWatcher* watch);
    void onSearchFinish(QDBusPendingCallWatcher* watch);
    void onTimeout();
    void onRemoveItem(const QString &id, int type);
    void onShortcutChanged(ShortcutInfo *info);

private:
    QWidget* m_searchWidget;
    QWidget* m_widget;
    QLineEdit* m_search;
    QString m_searchText;
    QVBoxLayout* m_layout;
    QVBoxLayout* m_searchLayout;
    QPushButton* m_addCustom;
    SettingsHead *m_head;
    SettingsGroup* m_systemGroup;
    SettingsGroup* m_windowGroup;
    SettingsGroup* m_workspaceGroup;
    SettingsGroup* m_customGroup;
    SettingsGroup* m_searchGroup;
    QMap<QString, ShortcutInfo*> m_searchInfos;
    SearchInter* m_searchInter;
    // 预留，如果用户太快，可以等带用户输入完成后才搜索
    QTimer* m_timer;
    ShortcutModel *m_model;
    QList<ShortcutItem *> m_allList;
    QList<ShortcutItem *> m_systemList;
    QList<ShortcutItem *> m_windowList;
    QList<ShortcutItem *> m_workspaceList;
    QList<ShortcutItem *> m_customList;
};

}
}
#endif // SHORTCUTWIDGET_H
