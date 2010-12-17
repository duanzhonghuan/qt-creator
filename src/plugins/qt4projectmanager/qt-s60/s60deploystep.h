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

#ifndef S60DeployStep_H
#define S60DeployStep_H

#include <projectexplorer/buildstep.h>

#include <QtCore/QString>

QT_FORWARD_DECLARE_CLASS(QEventLoop)

namespace SymbianUtils {
class SymbianDevice;
}
namespace trk{
class Launcher;
}

namespace ProjectExplorer {
class IOutputParser;
}

namespace Qt4ProjectManager {
namespace Internal {

class BuildConfiguration;
class S60DeviceRunConfiguration;

class S60DeployStepFactory : public ProjectExplorer::IBuildStepFactory
{
    Q_OBJECT
public:
    explicit S60DeployStepFactory(QObject *parent = 0);
    virtual ~S60DeployStepFactory();

    // used to show the list of possible additons to a target, returns a list of types
    QStringList availableCreationIds(ProjectExplorer::BuildStepList *parent) const;
    // used to translate the types to names to display to the user
    QString displayNameForId(const QString &id) const;

    bool canCreate(ProjectExplorer::BuildStepList *parent, const QString &id) const;
    ProjectExplorer::BuildStep *create(ProjectExplorer::BuildStepList *parent, const QString &id);
    // used to recreate the runConfigurations when restoring settings
    bool canRestore(ProjectExplorer::BuildStepList *parent, const QVariantMap &map) const;
    ProjectExplorer::BuildStep *restore(ProjectExplorer::BuildStepList *parent, const QVariantMap &map);
    bool canClone(ProjectExplorer::BuildStepList *parent, ProjectExplorer::BuildStep *product) const;
    ProjectExplorer::BuildStep *clone(ProjectExplorer::BuildStepList *parent, ProjectExplorer::BuildStep *product);
};

class S60DeployStep : public ProjectExplorer::BuildStep
{
    Q_OBJECT
public:
    friend class S60DeployStepFactory;

    explicit S60DeployStep(ProjectExplorer::BuildStepList *parent);

    virtual ~S60DeployStep();

    virtual bool init();
    virtual void run(QFutureInterface<bool> &fi);
    virtual ProjectExplorer::BuildStepConfigWidget *createConfigWidget();

    void setReleaseDeviceAfterLauncherFinish(bool);

    virtual QVariantMap toMap() const;

protected:
    virtual bool fromMap(const QVariantMap &map);

protected slots:
    void deviceRemoved(const SymbianUtils::SymbianDevice &);

private slots:
    void connectFailed(const QString &errorMessage);
    void printCopyingNotice(const QString &fileName);
    void createFileFailed(const QString &filename, const QString &errorMessage);
    void writeFileFailed(const QString &filename, const QString &errorMessage);
    void closeFileFailed(const QString &filename, const QString &errorMessage);
    void printInstallingNotice(const QString &packageName);
    void installFailed(const QString &filename, const QString &errorMessage);
    void printInstallingFinished();
    void launcherFinished();
    void slotLauncherStateChanged(int);
    void slotWaitingForTrkClosed();
    void checkForCancel();

signals:
    void finished();
    void finishNow();

private:
    S60DeployStep(ProjectExplorer::BuildStepList *parent,
                  S60DeployStep *bs);
    void ctor();

    void start();
    void stop();
    void startDeployment();
    bool processPackageName(QString &errorMessage);
    void setupConnections();
    void appendMessage(const QString &error, bool isError);

    QString m_serialPortName;
    QString m_serialPortFriendlyName;
    QStringList m_packageFileNamesWithTarget; // Support for 4.6.1
    QStringList m_signedPackages;

    QTimer *m_timer;

    bool m_releaseDeviceAfterLauncherFinish;
    bool m_handleDeviceRemoval;

    QFutureInterface<bool> *m_futureInterface; //not owned

    trk::Launcher *m_launcher;

    QEventLoop *m_eventLoop;
    bool m_deployResult;
    char m_installationDrive;
    bool m_silentInstall;
};

class S60DeployStepWidget : public ProjectExplorer::BuildStepConfigWidget
{
    Q_OBJECT
public:
    S60DeployStepWidget();

    void init();
    QString summaryText() const;
    QString displayName() const;
};

} // Internal
} // Qt4ProjectManager

#endif // S60DeployStep_H
