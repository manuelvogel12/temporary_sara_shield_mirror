// -*- lsst-c++ -*/
/**
 * @file path.h
 * @brief Defines the path class
 * @version 0.1
 * @copyright This file is part of SaRA-Shield.
 * SaRA-Shield is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 * SaRA-Shield is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with SaRA-Shield.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))
#include <array>
#include <iostream>

#ifndef PATH_H
#define PATH_H

namespace safety_shield {

/**
 * @brief A class that represents a path
 */
class Path {
 private:
  /**
   * @brief The three phases of the path with their end time (0 -> 2) and jerk (3 -> 5)
   */
  std::array<double, 6> phases_;

  /**
   * @brief The starting position
   */
  double pos_;

  /**
   * @brief The starting velocity
   */
  double vel_;

  /**
   * @brief The starting acceleration
   */
  double acc_;

  /**
   * @brief The starting jerk
   */
  double jerk_;

  /**
   * @brief Is the path the current one?
   */
  bool is_current_;

 public:
  /**
   * @brief empty path constructor
   * Initializes a path where every parameter is set to 0 except the velocity setted to 1
   */
  Path();

  /**
   * @brief A path destructor
   */
  ~Path() {}

  /**
   * @brief Returns the phases
   */
  inline std::array<double, 6> getPhases() {
    return phases_;
  }

  /**
   * @brief Prints the path as an array.
   *
   * Format : [phases, is_current, pos, vel, acc]
   */
  inline void printPath() {
    std::cout << phases_[0] << "," << phases_[1] << "," << phases_[2] << "," << phases_[3] << "," << phases_[4] << ","
              << phases_[5] << "," << is_current_ << "," << pos_ << "," << vel_ << "," << acc_ << std::endl;
  }

  /**
   * @brief Returns a given phase's end time
   *
   * @param i the phase number
   * @return the associated end time
   */
  inline double getPhase(int i) {
    return phases_[i - 1];
  }

  /**
   * @brief Returns a given phase's jerk
   *
   * @param phase the phase number
   * @return the associated jerk
   */
  inline double getJerk(int phase) {
    return phases_[phase + 3];
  }

  /**
   * @brief Returns the path starting position
   *
   * @return the starting position
   */
  inline double getPosition() {
    return pos_;
  }

  /**
   * @brief Returns the path starting velocity
   *
   * @return the starting velocity
   */
  inline double getVelocity() {
    return vel_;
  }

  /**
   * @brief Returns the path starting acceleration
   *
   * @return the starting acceleration
   */
  inline double getAcceleration() {
    return acc_;
  }

  /**
   * @brief Returns the path starting jerk
   *
   * @return the starting jerk
   */
  inline double getJerk() {
    return jerk_;
  }

  /**
   * @brief Returns the information about the current path
   *
   * @return is this path the current one ?
   */
  inline bool isCurrent() {
    return is_current_;
  }

  /**
   * @brief Sets the path phases
   *
   * @param phases the new phases
   */
  inline void setPhases(const std::array<double, 6>& phases) {
    for (int i = 0; i < 3; i++) {
      assertm(phases[i] >= 0, "Phase is smaller than zero");
    }
    phases_ = phases;
  }

  /**
   * @brief Sets the current path information
   *
   * @param is_current the new current path information
   */
  inline void setCurrent(bool is_current) {
    is_current_ = is_current;
  }

  /**
   * @brief Sets the starting position
   *
   * @param pos the new starting position
   */
  inline void setPosition(double pos) {
    pos_ = pos;
  }

  /**
   * @brief Sets the starting velocity
   *
   * @param vel the new starting velocity
   */
  inline void setVelocity(double vel) {
    vel_ = vel;
  }

  /**
   * @brief Sets the starting acceleration
   *
   * @param acc the new starting acceleration
   */
  inline void setAcceleration(double acc) {
    acc_ = acc;
  }

  /**
   * @brief Increments the path
   *
   * @param sample_time the incrementation path
   */
  void increment(double sample_time);

  /**
   * @brief Return the last position, velocity, and acceleration of the path.
   * @details Please note that the final jerk is always zero and therefore not returned.
   *
   * @param[out] final_pos last position
   * @param[out] final_vel last velocity
   * @param[out] final_acc last acceleration
   */
  void getFinalMotion(double& final_pos, double& final_vel, double& final_acc);

  /**
   * @brief computes s-values when Path falls under v_limit
   * @param[in] v_limit
   * @param[out] time
   * @param[out] position
   * @param[out] vel
   * @param[out] acc
   * @param[out] jerk
   */
  void getMotionUnderVel(double v_limit, double& time, double& position, double& vel, double& acc, double& jerk);

  /**
   * @brief Get the maximum velocity of the path.
   * 
   * @return double: maximium velocity
   */
  double getMaxVelocity();
};
}  // namespace safety_shield

#endif  // PATH_H