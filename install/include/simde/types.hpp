/*
 * Copyright 2022 NWChemEx-Project
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
#include <chemist/chemist.hpp>

/** @file types.hpp
 *
 *  These are typedefs of the fundamental types used in the property types.
 *  Property types are encouraged to use these typedefs to stay in sync with
 *  the remainder of the library.
 */
namespace simde::type {

using namespace chemist::type;

// --------------------- Fundamental Types -------------------------------------

/// Typedef of the class used to describe a molecule
using molecule = chemist::Molecule;

/// Typedef of the class which models a nucleus
using atom = typename molecule::atom_type;

/// Typedef of the class which models an atomic symbol
using atomic_symbol = typename atom::name_type;

/// Typedef of the class which models an atomic number
using atomic_number = typename atom::size_type;

/// Typedef of the class which describes an entire chemical system
using chemical_system = chemist::ChemicalSystem;

/// Typedef of the AO Basis Set
using ao_basis_set = chemist::AOBasisSetD;

/// Typedef of an Atomic Basis Set
using atomic_basis_set = chemist::AtomicBasisSet<double>;

/// Typedef of an electron
using el = chemist::Electron;

/// Typedef of many electrons
using many_electrons = chemist::ManyElectrons;

/// Typedef of the electron density
using el_density        = chemist::OneElectronDensity;
using decomp_el_density = chemist::Decomposable1EDensity;

// ------------------------------ Orbital Spaces -------------------------------

/// Typedef of class describing an AO space
using ao_space = chemist::orbital_space::AOSpaceD;

/// Typedef of orbital space obtained by transforming an ao_space
using derived_space = chemist::orbital_space::DerivedSpaceD;

using tot_derived_space = chemist::orbital_space::ToTDerivedSpace;

/// Typedef of an orbital space with orbitals that diagonalize the Fock matrix
using canonical_space = chemist::orbital_space::CanonicalSpaceD;

using canonical_tot_space = chemist::orbital_space::CanonicalToTSpace;

// using independent_space = chemist::orbital_space::CanonicalIndSpace;

// ---------------------- Tensors ---------------------------------------------

using tensor = chemist::type::tensor;

using tensor_of_tensors = chemist::type::tensor_of_tensors;

using sparse_map = chemist::type::sparse_map;

// -----------------------------------------------------------------------------
// ----------------------------- Operators -------------------------------------
// -----------------------------------------------------------------------------

using core_hamiltonian = chemist::operators::CoreHamiltonian;

using el_dipole = chemist::operators::ElectricDipole;

using el_el_coulomb = chemist::operators::ElectronRepulsion;

using el_el_delta = chemist::operators::ElectronElectronDelta;

using el_el_f12_commutator = chemist::operators::ElectronElectronF12Commutator;

using el_el_stg = chemist::operators::ElectronElectronSTG;

using el_el_yukawa = chemist::operators::ElectronElectronYukawa;

using el_identity = chemist::operators::ElectronIdentity;

using el_identity_nuc = chemist::operators::ElectronIdentity_Nuclear;

using el_kinetic = chemist::operators::ElectronKinetic;

using el_nuc_coulomb = chemist::operators::ElectronNuclearAttraction;

using el_octupole = chemist::operators::ElectricOctupole;

using el_quadrupole = chemist::operators::ElectricQuadrupole;

using el_scf_j = chemist::operators::ElectronEDensityCoulomb;

using el_scf_k = chemist::operators::ElectronEDensityExchange;

using el_lscf_k = chemist::operators::ElectronDecomposableEDensity;

using el_scf_xc = chemist::operators::ExchangeCorrelation;

using els_hamiltonian = chemist::operators::ElectronicHamiltonian;

using els_coulomb = chemist::operators::NElectronRepulsion;

using els_kinetic = chemist::operators::NElectronKinetic;

using els_nuc_coulomb = chemist::operators::NElectronNuclearAttraction;

using fock = chemist::operators::Fock;

using hamiltonian = chemist::operators::Hamiltonian;

using nuc_coulomb = chemist::operators::NuclearRepulsion;

// -----------------------------------------------------------------------------
// ---------------------------- Wavefunctions ----------------------------------
// -----------------------------------------------------------------------------

using noncanonical_reference = chemist::wavefunction::Reference;

using canonical_reference = chemist::wavefunction::CanonicalReference;

// using local_reference = chemist::wavefunction::SparseReference;

// using local_tot_reference = chemist::wavefunction::SparseToTReference;

using many_body = chemist::wavefunction::ManyBodyWf;

using canonical_many_body = chemist::wavefunction::CanonicalManyBodyWf;

// using local_many_body = chemist::wavefunction::SparseManyBodyWf;

// using local_tot_many_body = chemist::wavefunction::SparseToTManyBodyWf;

// ---------------------------- Other ------------------------------------------

/// Typedef of the class used for connectivity information
using connectivity_table = chemist::topology::ConnectivityTable;

/// Typedef of the class used for molecular topology
using topology = chemist::topology::Topology;

/// Typedef of an integral factory
using integral_factory = chemist::IntegralFactory;

/// Typedef of a full atomic electronic configuration
using full_elec_conf = std::map<std::pair<size, size>, size>;

} // namespace simde::type
