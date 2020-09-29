#include "ProfileConfigData.h"
#include <QDateTime>

int ProfileConfigData::data(const Phase phase, const PhaseIndex index) const {
  return m_phaseConfigData[phase].at(index);
}

void ProfileConfigData::setData(const Phase phase, const PhaseIndex index,
                                const int value) {
  m_phaseConfigData[phase].at(index) = value;
}

PhaseData ProfileConfigData::data(const Phase phase) const {
  return m_phaseConfigData[phase];
}

void ProfileConfigData::setData(const Phase phase, PhaseData data) {
  m_phaseConfigData[phase] = data;
}
