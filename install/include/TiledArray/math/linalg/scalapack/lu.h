/*
 *  This file is a part of TiledArray.
 *  Copyright (C) 2020 Virginia Tech
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  David Williams-Young
 *  Computational Research Division, Lawrence Berkeley National Laboratory
 *
 *  lu.h
 *  Created:    19 June, 2020
 *
 */
#ifndef TILEDARRAY_MATH_LINALG_SCALAPACK_LU_H__INCLUDED
#define TILEDARRAY_MATH_LINALG_SCALAPACK_LU_H__INCLUDED

#include <TiledArray/config.h>
#if TILEDARRAY_HAS_SCALAPACK

#include <TiledArray/math/linalg/scalapack/util.h>

#include <scalapackpp/factorizations/getrf.hpp>
#include <scalapackpp/linear_systems/gesv.hpp>
#include <scalapackpp/matrix_inverse/getri.hpp>

namespace TiledArray::math::linalg::scalapack {

/**
 *  @brief Solve a linear system via LU factorization
 */
template <typename ArrayA, typename ArrayB>
auto lu_solve(const ArrayA& A, const ArrayB& B,
              TiledRange x_trange = TiledRange(),
              size_t NB = default_block_size(),
              size_t MB = default_block_size()) {
  using value_type = typename ArrayA::element_type;
  static_assert(std::is_same_v<value_type, typename ArrayB::element_type>);

  auto& world = A.world();
  auto world_comm = world.mpi.comm().Get_mpi_comm();
  blacspp::Grid grid = blacspp::Grid::square_grid(world_comm);

  world.gop.fence();  // stage ScaLAPACK execution
  auto A_sca = scalapack::array_to_block_cyclic(A, grid, MB, NB);
  auto B_sca = scalapack::array_to_block_cyclic(B, grid, MB, NB);
  world.gop.fence();  // stage ScaLAPACK execution

  auto [M, N] = A_sca.dims();
  if (M != N) TA_EXCEPTION("A must be square for LU Solve");
  auto [B_N, NRHS] = B_sca.dims();
  if (B_N != N) TA_EXCEPTION("A and B dims must agree");

  auto [A_Mloc, A_Nloc] = A_sca.dist().get_local_dims(N, N);
  auto desc_a = A_sca.dist().descinit_noerror(N, N, A_Mloc);

  auto [B_Mloc, B_Nloc] = B_sca.dist().get_local_dims(N, NRHS);
  auto desc_b = B_sca.dist().descinit_noerror(N, NRHS, B_Mloc);

  std::vector<int64_t> IPIV(A_Mloc + MB);

  auto info =
      scalapackpp::pgesv(N, NRHS, A_sca.local_mat().data(), 1, 1, desc_a,
                         IPIV.data(), B_sca.local_mat().data(), 1, 1, desc_b);
  if (info) TA_EXCEPTION("LU Solve Failed");

  if (x_trange.rank() == 0) x_trange = B.trange();

  world.gop.fence();
  auto X = scalapack::block_cyclic_to_array<ArrayB>(B_sca, x_trange);
  world.gop.fence();

  return X;
}

/**
 *  @brief Invert a matrix via LU
 */
template <typename Array>
auto lu_inv(const Array& A, TiledRange ainv_trange = TiledRange(),
            size_t NB = default_block_size(),
            size_t MB = default_block_size()) {
  auto& world = A.world();
  auto world_comm = world.mpi.comm().Get_mpi_comm();
  blacspp::Grid grid = blacspp::Grid::square_grid(world_comm);

  world.gop.fence();  // stage ScaLAPACK execution
  auto A_sca = scalapack::array_to_block_cyclic(A, grid, MB, NB);
  world.gop.fence();  // stage ScaLAPACK execution

  auto [M, N] = A_sca.dims();
  if (M != N) TA_EXCEPTION("A must be square for LU Inverse");

  auto [A_Mloc, A_Nloc] = A_sca.dist().get_local_dims(N, N);
  auto desc_a = A_sca.dist().descinit_noerror(N, N, A_Mloc);

  std::vector<int64_t> IPIV(A_Mloc + MB);

  {
    auto info = scalapackpp::pgetrf(N, N, A_sca.local_mat().data(), 1, 1,
                                    desc_a, IPIV.data());
    if (info) TA_EXCEPTION("LU Failed");
  }

  {
    auto info = scalapackpp::pgetri(N, A_sca.local_mat().data(), 1, 1, desc_a,
                                    IPIV.data());
    if (info) TA_EXCEPTION("LU Inverse Failed");
  }

  if (ainv_trange.rank() == 0) ainv_trange = A.trange();

  world.gop.fence();
  auto Ainv = scalapack::block_cyclic_to_array<Array>(A_sca, ainv_trange);
  world.gop.fence();

  return Ainv;
}

}  // namespace TiledArray::math::linalg::scalapack

#endif  // TILEDARRAY_HAS_SCALAPACK
#endif  // TILEDARRAY_MATH_LINALG_SCALAPACK_LU_H__INCLUDED
