/***************************************************************************
 *   Copyright 2010 Marco Martin <mart@kde.org>                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/
#ifndef THEME_PROXY_P
#define THEME_PROXY_P

#include <QObject>

#include <QUrl>
#include <QFont>
#include <QColor>

class ThemeProxy : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY themeChanged)
    Q_PROPERTY(QFont font READ font NOTIFY themeChanged)
    Q_PROPERTY(bool translucent READ windowTranslucencyEnabled NOTIFY themeChanged)
    Q_PROPERTY(QUrl homepage READ homepage NOTIFY themeChanged)

    // colors
    Q_PROPERTY(QColor textColor READ textColor NOTIFY themeChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor NOTIFY themeChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY themeChanged)
    Q_PROPERTY(QColor buttonTextColor READ buttonTextColor NOTIFY themeChanged)
    Q_PROPERTY(QColor buttonBackgroundColor READ buttonBackgroundColor NOTIFY themeChanged)
    Q_PROPERTY(QColor linkColor READ linkColor NOTIFY themeChanged)
    Q_PROPERTY(QColor visitedLinkColor READ visitedLinkColor NOTIFY themeChanged)
    Q_PROPERTY(QColor visitedLinkColor READ visitedLinkColor NOTIFY themeChanged)
    Q_PROPERTY(QColor buttonHoverColor READ buttonHoverColor NOTIFY themeChanged)
    Q_PROPERTY(QColor buttonFocusColor READ buttonFocusColor NOTIFY themeChanged)
    Q_PROPERTY(QColor viewTextColor READ viewTextColor NOTIFY themeChanged)
    Q_PROPERTY(QColor viewBackgroundColor READ viewBackgroundColor NOTIFY themeChanged)
    Q_PROPERTY(QColor viewHoverColor READ viewHoverColor NOTIFY themeChanged)
    Q_PROPERTY(QColor viewFocusColor READ viewFocusColor NOTIFY themeChanged)

public:
    ThemeProxy(QObject *parent = 0);
    ~ThemeProxy();

    QString name() const;
    QFont font() const;
    bool windowTranslucencyEnabled() const;
    QUrl homepage() const;

    QColor textColor() const;
    QColor highlightColor() const;
    QColor backgroundColor() const;
    QColor buttonTextColor() const;
    QColor buttonBackgroundColor() const;
    QColor linkColor() const;
    QColor visitedLinkColor() const;
    QColor buttonHoverColor() const;
    QColor buttonFocusColor() const;
    QColor viewTextColor() const;
    QColor viewBackgroundColor() const;
    QColor viewHoverColor() const;
    QColor viewFocusColor() const;

Q_SIGNALS:
    void themeChanged();
};

#endif
