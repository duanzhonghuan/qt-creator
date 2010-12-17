/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** No Commercial Usage
**
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtCore/QObject>

#define QMLDESIGNER_PLUGIN_INTERFACE "com.Nokia.QmlDesigner.IPlugin.v10"

namespace QmlDesigner {

// QmlDesigner "base" plugin with initialization method in which
// it can retriece the core via its static accessor and do magic.

class IPlugin
{
public:
    virtual ~IPlugin() {}

    virtual bool isInitialized() const = 0;

    virtual bool initialize(QString *errorMessage) = 0;
};

} // namespace QmlDesigner

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(QmlDesigner::IPlugin, QMLDESIGNER_PLUGIN_INTERFACE)
QT_END_NAMESPACE

#endif // IPLUGIN_H
