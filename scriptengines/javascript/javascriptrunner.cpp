/*
 *   Copyright 2008 Richard J. Moore <rich@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
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

#include "javascriptrunner.h"

#include <QFile>

#include <Plasma/AbstractRunner>
#include <Plasma/QueryMatch>

#include "authorization.h"
#include "scriptenv.h"

typedef const Plasma::RunnerContext* ConstRunnerContextStar;
typedef const Plasma::QueryMatch* ConstSearchMatchStar;

Q_DECLARE_METATYPE(Plasma::QueryMatch*)
Q_DECLARE_METATYPE(Plasma::RunnerContext*)
Q_DECLARE_METATYPE(ConstRunnerContextStar)
Q_DECLARE_METATYPE(ConstSearchMatchStar)

JavaScriptRunner::JavaScriptRunner(QObject *parent, const QVariantList &args)
    : RunnerScript(parent),
      m_engine(new ScriptEnv(this))
{
    Q_UNUSED(args);
    connect(m_engine, SIGNAL(reportError(ScriptEnv*,bool)), this, SLOT(reportError(ScriptEnv*,bool)));
}

JavaScriptRunner::~JavaScriptRunner()
{
}

Plasma::AbstractRunner* JavaScriptRunner::runner() const
{
    return RunnerScript::runner();
}

bool JavaScriptRunner::init()
{
    setupObjects();

    Authorization auth;
    if (!m_engine->importExtensions(description(), m_self, auth)) {
        return false;
    }

    QFile file(mainScript());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        kWarning() << "Unable to load script file";
        return false;
    }

    QString script = file.readAll();
    kDebug() << "Script says" << script;

    m_engine->evaluate(script);
    if (m_engine->hasUncaughtException()) {
        reportError(m_engine, true);
        return false;
    }

    return true;
}

void JavaScriptRunner::match(Plasma::RunnerContext &search)
{
    QScriptValue fun = m_self.property("match");
    if (!fun.isFunction()) {
        kDebug() << "Script: match is not a function, " << fun.toString();
        return;
    }

    QScriptValueList args;
    args << m_engine->toScriptValue(&search);

    QScriptContext *ctx = m_engine->pushContext();
    ctx->setActivationObject(m_self);
    fun.call(m_self, args);
    m_engine->popContext();

    if (m_engine->hasUncaughtException()) {
        reportError(m_engine, false);
    }
}

void JavaScriptRunner::exec(const Plasma::RunnerContext *search, const Plasma::QueryMatch *action)
{
    QScriptValue fun = m_self.property("exec");
    if (!fun.isFunction()) {
        kDebug() << "Script: exec is not a function, " << fun.toString();
        return;
    }

    QScriptValueList args;
    args << m_engine->toScriptValue(search);
    args << m_engine->toScriptValue(action);

    QScriptContext *ctx = m_engine->pushContext();
    ctx->setActivationObject(m_self);
    fun.call(m_self, args);
    m_engine->popContext();

    if (m_engine->hasUncaughtException()) {
        reportError(m_engine, false);
    }
}

void JavaScriptRunner::setupObjects()
{
    QScriptValue global = m_engine->globalObject();

    // Expose the runner
    m_self = m_engine->newQObject(this);
    m_self.setScope(global);

    global.setProperty("runner", m_self);
}

void JavaScriptRunner::reportError(ScriptEnv *engine, bool fatal)
{
    Q_UNUSED(fatal)
    kDebug() << "Error: " << engine->uncaughtException().toString()
             << " at line " << engine->uncaughtExceptionLineNumber() << endl;
    kDebug() << engine->uncaughtExceptionBacktrace();
}

#include "javascriptrunner.moc"
