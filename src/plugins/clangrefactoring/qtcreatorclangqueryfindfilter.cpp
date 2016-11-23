/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "qtcreatorclangqueryfindfilter.h"

#include <cpptools/cppmodelmanager.h>
#include <cpptools/projectinfo.h>

#include <projectexplorer/session.h>

namespace ClangRefactoring {

QtCreatorClangQueryFindFilter::QtCreatorClangQueryFindFilter(ClangBackEnd::RefactoringServerInterface &server,
                                                             SearchInterface &searchInterface,
                                                             RefactoringClient &refactoringClient)
    : ClangQueryProjectsFindFilter(server, searchInterface, refactoringClient)
{
}

void QtCreatorClangQueryFindFilter::findAll(const QString &queryText, Core::FindFlags findFlags)
{
    prepareFind();

    ClangQueryProjectsFindFilter::findAll(queryText, findFlags);
}

namespace {
std::vector<CppTools::ProjectPart::Ptr>
convertProjectParts(const QList<CppTools::ProjectPart::Ptr> &projectPartList)
{
    std::vector<CppTools::ProjectPart::Ptr> projectPartVector;
    projectPartVector.reserve(projectPartList.size());

    std::copy(projectPartList.begin(), projectPartList.end(), std::back_inserter(projectPartVector));

    return projectPartVector;
}

}

void QtCreatorClangQueryFindFilter::prepareFind()
{
   ProjectExplorer::Project *currentProject = ProjectExplorer::SessionManager::startupProject();

    const CppTools::ProjectInfo projectInfo = CppTools::CppModelManager::instance()->projectInfo(currentProject);

    setProjectParts(convertProjectParts(projectInfo.projectParts()));
}

} // namespace ClangRefactoring
