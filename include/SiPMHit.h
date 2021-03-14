/** @class sipm::SiPMHit SimSiPM/SimSiPM/SiPMHit.h SiPMHit.h
 *
 * @brief Class storing informations relative to a single SiPM hitted cell.
 *
 * This class is used mainly to store informations relative to a single hit on a
 * SiPM cell. Informations stored in thiss class will be used to generate the
 * signal for each SiPM cell.
 *
 *  @author Edoardo Proserpio
 *  @date 2020
 */
#include <stdint.h>

#ifndef SIPM_SIPMHITS_H
#define SIPM_SIPMHITS_H

namespace sipm {

class SiPMHit {
public:
  /** @enum HitType
   * Used to distinguish between hits generated by different processes
   */
  enum class HitType {
    kPhotoelectron,     ///< Hit generated by a photoelectron
    kDarkCount,         ///< Hit generated by a dark count
    kOpticalCrosstalk,  ///< Hit generated by an optical crosstalk
    kAfterPulse         ///< Hit generated by an afterpulse
  };

  /** @brief Constructor of SiPMHit */
  SiPMHit(const double time, const double amp, const uint32_t r, const uint32_t c, const HitType type) noexcept :
   m_Time(time),
   m_Amplitude(amp),
   m_Row(r),
   m_Col(c),
   m_Id(makePair(r,c)),
   m_HitType(type) {}
  /// @brief Operator used to sort hits
  /**
   * Hits are sorted based on theyr time parameter:
   * @f[Hit_1 < Hit_2 \Leftrightarrow Hit_1.time < Hit_2.time @f]
   */
  const bool operator<(const SiPMHit& aHit) const noexcept { return m_Time < aHit.m_Time; }

  /// @brief Returns hit time
  const double time() const { return m_Time; }
  /// @brief Returns row of hitted cell
  const uint32_t row() const { return m_Row; }
  /// @brief Returns column of hitted cell
  const uint32_t col() const { return m_Col; }
  /// @brief Returns a unique id to identify a hitted cell
  const uint32_t id() const { return m_Id; }
  /// @brief Returns amplitude of the signal produced by the hit
  const double amplitude() const { return m_Amplitude; }
  /// @brief Used to modify the amplitude if needed
  double& amplitude() { return m_Amplitude; }
  /// @brief Returns hit type to identify the hits
  const HitType& hitType() const { return m_HitType; }

private:
  /// @brief Creates an unique id from two integers (based on Cantor pairing
  /// function)
  static const uint32_t makePair(const uint32_t x, const uint32_t y) { return ((x + y + 1) * (x + y) << 1) + y; }

  double m_Time;
  double m_Amplitude;
  uint32_t m_Row;
  uint32_t m_Col;
  HitType m_HitType;
  uint32_t m_Id;
};

}  // namespace sipm
#endif /* SIPM_SIPMHITS_H */