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

#ifndef GITSUBMITEDITOR_H
#define GITSUBMITEDITOR_H

#include <vcsbase/vcsbasesubmiteditor.h>

#include <QtCore/QStringList>

namespace VCSBase {
    class SubmitFileModel;
}

namespace Git {
namespace Internal {

class GitSubmitEditorWidget;
struct CommitData;
struct GitSubmitEditorPanelData;

class GitSubmitEditor : public VCSBase::VCSBaseSubmitEditor
{
    Q_OBJECT
public:
    explicit GitSubmitEditor(const VCSBase::VCSBaseSubmitEditorParameters *parameters, QWidget *parent);

    void setCommitData(const CommitData &);
    GitSubmitEditorPanelData panelData() const;

signals:
    void diff(const QStringList &unstagedFiles, const QStringList &stagedFiles);

private slots:
    void slotDiffSelected(const QStringList &);

private:
    inline GitSubmitEditorWidget *submitEditorWidget();

    VCSBase::SubmitFileModel *m_model;
};

} // namespace Internal
} // namespace Git

#endif // GITSUBMITEDITOR_H
