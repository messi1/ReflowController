#pragma once

#include <QString>
#include <array>

using PhaseData = std::array<int, 3>;
using PhaseDataArray = std::array<PhaseData, 4>;
enum PhaseIndex : size_t
{
  Time,
  Temperatur,
  Power
};

enum Phase : size_t
{
  Preheat,
  Soak,
  Reflow,
  Dwell
};

class ProfileConfigData final
{
public:
  explicit ProfileConfigData() = default;
  ~ProfileConfigData() = default;

  int data(const Phase phase, const PhaseIndex index) const;
  void setData(const Phase phase, const PhaseIndex index, const int value);

  PhaseData data(const Phase phase) const;
  void setData(const Phase phase, PhaseData data);

private:
  PhaseDataArray m_phaseConfigData;
};
