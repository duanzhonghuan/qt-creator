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

#ifndef NODESVISITOR_H
#define NODESVISITOR_H

#include "projectexplorer_export.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

namespace ProjectExplorer {

class Node;
class FileNode;
class SessionNode;
class ProjectNode;
class FolderNode;

class NodesVisitor {
public:
    virtual ~NodesVisitor() {}

    virtual void visitSessionNode(SessionNode *) {}
    virtual void visitProjectNode(ProjectNode *) {}
    virtual void visitFolderNode(FolderNode *) {}
protected:
     NodesVisitor() {}
};

/* useful visitors */

class PROJECTEXPLORER_EXPORT FindNodesForFileVisitor : public NodesVisitor {
public:
    FindNodesForFileVisitor(const QString &fileToSearch);

    QList<Node*> nodes() const;

    void visitProjectNode(ProjectNode *node);
    void visitFolderNode(FolderNode *node);
private:
    QString m_path;
    QList<Node*> m_nodes;
};

class PROJECTEXPLORER_EXPORT FindAllFilesVisitor : public NodesVisitor {
public:
    QStringList filePaths() const;

    void visitProjectNode(ProjectNode *projectNode);
    void visitFolderNode(FolderNode *folderNode);
private:
    QStringList m_filePaths;
};

} // namespace ProjectExplorer

#endif // NODESVISITOR_H
