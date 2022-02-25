// #pragma once

// namespace ghostfragment {
// namespace detail_ {
// class NMerSystemPIMPL;
// class NMerSystemReferencePIMPL;
// } // namespace detail_

// template<typename PimplType = detail_::NMerSystemReferencePIMPL>
// class NMerSystemReference {
// public:
//     using system_type       = ;
//     using ao_basis_set_type = ;
//     using pimpl_type        = PimplType;
//     using pimpl_pointer     = std::unique_ptr<pimpl_type>;

//     ~NMerSystemReference() noexcept;

// protected:
//     friend class NMerSystem;
//     NMerSystemReference(pimpl_pointer p);

// private:
//     pimpl_pointer m_pimpl_;
// };

// /** @brief
//  *
//  */
// class NMerSystem {
// private:
//     using reference_pimpl_type = detail_::NMerSystemReferencePIMPL;

// public:
//     using reference = NMerSystemReference<>;

//     using const_reference =
//       NMerSystemReference<const detail_::NMerSystemReferencePIMPL>;
//     NMerSystem();
// };

// } // namespace ghostfragment
