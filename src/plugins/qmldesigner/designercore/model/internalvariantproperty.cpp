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

#include "internalvariantproperty.h"

namespace QmlDesigner {
namespace Internal {

InternalVariantProperty::InternalVariantProperty(const QString &name, const InternalNodePointer &node)
        : InternalProperty(name, node)
{
}

InternalVariantProperty::Pointer InternalVariantProperty::create(const QString &name, const InternalNodePointer &propertyOwner)
{
    InternalVariantProperty *newPointer(new InternalVariantProperty(name, propertyOwner));
    InternalVariantProperty::Pointer smartPointer(newPointer);

    newPointer->setInternalWeakPointer(smartPointer);

    return smartPointer;
}

QVariant InternalVariantProperty::value() const
{
    return m_value;
}

void InternalVariantProperty::setValue(const QVariant &value)
{
    m_value = value;
}

bool InternalVariantProperty::isVariantProperty() const
{
    return true;
}

void InternalVariantProperty::setDynamicValue(const QString &type, const QVariant &value)
{
     setValue(value);
     setDynamicTypeName(type);
}

bool InternalVariantProperty::isValid() const
{
    return InternalProperty::isValid() && isVariantProperty();
}

} // namespace Internal
} // namespace QmlDesigner
