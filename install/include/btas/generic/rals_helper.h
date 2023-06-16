//
// Created by Karl Pierce on 11/3/18.
//

#ifndef BTAS_RALS_HELPER_H
#define BTAS_RALS_HELPER_H

#include <btas/generic/dot_impl.h>
namespace btas{
/**
    \brief A helper function for the RALS solver
    Stores a previous iteration of factor
    matrices to compute the nth iteration step size
    see https://doi.org/10.1063/1.4977994 for more details
 **/
  template <typename Tensor>
  class RALSHelper {
  public:
    using ind_t = typename Tensor::range_type::index_type::value_type;
    using ord_t = typename range_traits<typename Tensor::range_type>::ordinal_type;

    RALSHelper() = default;

    ~RALSHelper() = default;

    /// constructor of the helper function
    /// \param[in] prev an initial set of
    /// normalized factor matrices
    RALSHelper(std::vector<Tensor> prev) : prev_(prev) {
    }

    /// Operator to compute the nth iteration step size
    /// \param[in] mode which mode of the actual tensor
    /// is being updated
    /// \param[in] An the updated factor matrix
    double operator()(size_t mode, const Tensor &An) {
      ord_t size = An.size();
      auto change = An - prev_[mode];
      double denom = 0.0, s = 0.0;
      auto chg_ptr = change.data();
      auto an_ptr = An.data();
      for (ord_t i = 0; i < size; ++i) {
        auto val = *(chg_ptr + i);
        s += val * val;
        val = *(an_ptr + i);
        denom += val * val;
      }
      s = std::sqrt(s) / std::sqrt(denom);
      //double s = std::sqrt(btas::dot(change, change));
      //s /= std::sqrt(dot(An, An));

      prev_[mode] = An;
      return s;
    }

  private:
    std::vector<Tensor> prev_;  // stores a set normalized of factor matrices
  };

}

#endif //BTAS_RALS_HELPER_H
