/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "%{APPNAMELC}.h"
#include <KLocalizedString>

%{APPNAME}::%{APPNAME}(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_nativeText(i18n("Text coming from C++ plugin"))
{
}

%{APPNAME}::~%{APPNAME}()
{
}

QString %{APPNAME}::nativeText() const
{
    return m_nativeText;
}

K_PLUGIN_CLASS_WITH_JSON(%{APPNAME}, "metadata.json")

#include "%{APPNAMELC}.moc"
