/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <array>

namespace ghostfragment::topology {

/** @brief  Returns the covalent radius (in Bohr) of the specified element.
 *
 *  @param[in] z The atomic number of the element. @p z is 1-based, *i.e.*,
 *               @p z = 1 is hydrogen, @p z = 2 is helium, etc.
 *
 *  @return The requested covalent radius.
 */
inline double covalent_radius(std::size_t z) {
    /// Data is generated with Mathematica 10.0 (only available up to Z=96)
    std::array<double, 96> cov_radii{
      0.585815, 0.529123, 2.418849, 1.814137, 1.606267, 1.436192, 1.341706,
      1.247219, 1.077144, 1.096041, 3.136945, 2.664514, 2.286569, 2.097596,
      2.022007, 1.984212, 1.927521, 2.003110, 3.836144, 3.325918, 3.212534,
      3.023562, 2.891281, 2.626719, 2.626719, 2.494438, 2.381055, 2.343260,
      2.494438, 2.305466, 2.305466, 2.267671, 2.248774, 2.267671, 2.267671,
      2.192082, 4.157397, 3.684966, 3.590480, 3.307021, 3.099151, 2.910178,
      2.777897, 2.759000, 2.683411, 2.626719, 2.740103, 2.721206, 2.683411,
      2.626719, 2.626719, 2.607822, 2.626719, 2.645617, 4.610932, 4.062911,
      3.911733, 3.855041, 3.836144, 3.798350, 3.760555, 3.741658, 3.741658,
      3.703863, 3.666069, 3.628274, 3.628274, 3.571582, 3.590480, 3.533788,
      3.533788, 3.307021, 3.212534, 3.061356, 2.853486, 2.721206, 2.664514,
      2.570028, 2.570028, 2.494438, 2.740103, 2.759000, 2.796795, 2.645617,
      2.834589, 2.834589, 4.913288, 4.176295, 4.062911, 3.892836, 3.779452,
      3.703863, 3.590480, 3.533788, 3.401507, 3.193637};
    return cov_radii[z - 1];
}

} // namespace ghostfragment::connectivity
