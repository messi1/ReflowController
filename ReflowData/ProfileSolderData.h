#pragma once

#include "ProfileConfigData.h"
#include "ProfileMeasureData.h"
#include <QDateTime>

class ProfileSolderData {
public:
  ProfileSolderData();
  ProfileSolderData(const QString &profileName);

  const QString &profileName(void) { return m_profileName; }
  void setProfileName(QString name) { m_profileName = name; }

private:
  QString m_profileName;
  QDateTime m_lastSavedDate;
  QDateTime m_measureStarted;
  QDateTime m_measureStopped;
  ProfileConfigData m_configData;
  ProfileMeasureData m_measureData;
  int mTempOffset;
};
