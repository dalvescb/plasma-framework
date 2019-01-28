/*
*   Copyright 2011 by Aaron Seigo <aseigo@kde.org>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Library General Public License version 2,
*   or (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details
*
*   You should have received a copy of the GNU Library General Public
*   License along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef PLASMA_DIALOGSHADOWS_H
#define PLASMA_DIALOGSHADOWS_H

#include <QSet>
#include <KWindowEffects>

#include "plasma/framesvg.h"
#include "plasma/svg.h"

class DialogShadows : public Plasma::Svg
{
    Q_OBJECT

public:
    explicit DialogShadows(QObject *parent = nullptr, const QString &prefix = QStringLiteral("dialogs/background"));
    ~DialogShadows();

    static DialogShadows *self();

    void addWindow(QWindow *window, Plasma::FrameSvg::EnabledBorders enabledBorders = Plasma::FrameSvg::AllBorders);
    void removeWindow(QWindow *window);
    void updateShadows();
private:
    KWindowEffects::ShadowData m_shadow;
};

#endif

