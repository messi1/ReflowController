#pragma once

#include <QDateTime>
#include <QMap>
#include <QString>

using SampleMap = QMap<QDateTime, double>;

class ProfileMeasureData final
{
  public:
    explicit ProfileMeasureData() = default;
    ~ProfileMeasureData() = default;
    void addTemperatureSample(const double value);

  private:
    SampleMap m_temperatureSampleMap;
};
