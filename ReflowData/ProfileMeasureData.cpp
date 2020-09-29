#include "ProfileMeasureData.h"

void ProfileMeasureData::addTemperatureSample(const double value)
{
    m_temperatureSampleMap[QDateTime::currentDateTime()] = value;
}
