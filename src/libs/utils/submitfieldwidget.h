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

#ifndef SUBMITFIELDWIDGET_H
#define SUBMITFIELDWIDGET_H

#include "utils_global.h"

#include  <QtGui/QWidget>

QT_BEGIN_NAMESPACE
class QCompleter;
QT_END_NAMESPACE

namespace Utils {

struct SubmitFieldWidgetPrivate;

/* A widget for editing submit message fields like "reviewed-by:",
 * "signed-off-by:". It displays them in a vertical row of combo/line edit fields
 * that is modeled after the target address controls of mail clients.
 * When choosing a different field in the combo, a new row is opened if text
 * has been entered for the current field. Optionally, a "Browse..." button and
 * completer can be added. */
class QTCREATOR_UTILS_EXPORT SubmitFieldWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList fields READ fields WRITE setFields DESIGNABLE true)
    Q_PROPERTY(bool hasBrowseButton READ hasBrowseButton WRITE setHasBrowseButton DESIGNABLE true)
    Q_PROPERTY(bool allowDuplicateFields READ allowDuplicateFields WRITE setAllowDuplicateFields DESIGNABLE true)

public:
    explicit SubmitFieldWidget(QWidget *parent = 0);
    virtual ~SubmitFieldWidget();

    QStringList fields() const;
    void setFields(const QStringList&);

    bool hasBrowseButton() const;
    void setHasBrowseButton(bool d);

    // Allow several entries for fields ("reviewed-by: a", "reviewed-by: b")
    bool allowDuplicateFields() const;
    void setAllowDuplicateFields(bool);

    QCompleter *completer() const;
    void setCompleter(QCompleter *c);

    QString fieldValue(int pos) const;
    void setFieldValue(int pos, const QString &value);

    QString fieldValues() const;

signals:
    void browseButtonClicked(int pos, const QString &field);

private slots:
    void slotRemove();
    void slotComboIndexChanged(int);
    void slotBrowseButtonClicked();

private:
    void removeField(int index);
    bool comboIndexChange(int fieldNumber, int index);
    void createField(const QString &f);

    SubmitFieldWidgetPrivate *m_d;
};

}

#endif // SUBMITFIELDWIDGET_H
