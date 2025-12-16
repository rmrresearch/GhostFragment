#include "../integration_tests.hpp"

using pt     = simde::AOEnergy;
using ao_pt  = simde::MolecularBasisSet;
using mol_pt = simde::MoleculeFromString;
using tensorwrapper::operations::approximately_equal;

TEST_CASE("VMFC") {
    auto mm = testing::initialize();

    const auto vmfc_key = "VMFC Driver";
    const auto mol_key  = "XYZ to Molecule";

    mm.change_submod(vmfc_key, "Energy method", "SCF Driver");
    mm.change_input(mol_key, "Unit scaling factor", 1.8897261246);

    std::stringstream ss;
    ss << "9\n";
    ss << "This is a comment line\n";
    ss << "O -2.59739269 -0.16216846 0.51842668\n";
    ss << "H -3.11237273 0.59155925 0.21414681\n";
    ss << "H -2.99148972 -0.91697774 0.06994740\n";
    ss << "O 0.00000000 0.00000000 -0.87103097\n";
    ss << "H 0.76709965 0.02523635 -0.28381455\n";
    ss << "H -0.76709965 -0.02523635 -0.28381455\n";
    ss << "O 2.59739269 0.16216846 0.51842668\n";
    ss << "H 3.11237273 -0.59155925 0.21414681\n";
    ss << "H 2.99148972 0.91697774 0.06994740\n";

    auto mol = mm.run_as<mol_pt>(mol_key, ss.str());
    auto aos = mm.run_as<ao_pt>("STO-3G", mol);
    simde::type::chemical_system sys(mol);

    double e_0 = -74.9637;
    double e_1 = -74.9638;
    double e_2 = -74.9637;
    double de1 = e_0 + e_1 + e_2;

    double e_0_01  = -74.9693;
    double e_1_01  = -74.9639;
    double e_0_02  = -74.9637;
    double e_2_02  = -74.9637;
    double e_1_12  = -74.9639;
    double e_2_12  = -74.9693;
    double e_01_01 = -149.936;
    double e_02_02 = -149.927;
    double e_12_12 = -149.936;
    double de_01   = e_01_01 - e_0_01 - e_1_01;
    double de_02   = e_02_02 - e_0_02 - e_2_02;
    double de_12   = e_12_12 - e_1_12 - e_2_12;
    double de2     = de_01 + de_02 + de_12;

    double e_0_012     = -74.9693;
    double e_1_012     = -74.964;
    double e_2_012     = -74.9693;
    double e_01_012    = -149.936;
    double e_02_012    = -149.938;
    double e_12_012    = -149.936;
    double e_012_012   = -224.906;
    double e3_monomers = e_0_012 + e_1_012 + e_2_012;
    double e3_dimers   = e_01_012 + e_02_012 + e_12_012;
    double de3         = e_012_012 - e3_dimers + e3_monomers;

    // TODO: better precision by adding more decimal places to values above
    simde::type::tensor e1_corr(de1);
    simde::type::tensor e2_corr(de1 + de2);
    simde::type::tensor e3_corr(de1 + de2 + de3);

    SECTION("n == 1") {
        mm.change_input(vmfc_key, "Truncation order", std::size_t{1});
        auto e = mm.run_as<pt>(vmfc_key, aos, sys);
        REQUIRE(approximately_equal(e, e1_corr, 1e-4));
    }

    SECTION("n == 2") {
        mm.change_input(vmfc_key, "Truncation order", std::size_t{2});
        auto e = mm.run_as<pt>(vmfc_key, aos, sys);
        REQUIRE(approximately_equal(e, e2_corr, 1e-3));
    }

    SECTION("n == 3") {
        mm.change_input(vmfc_key, "Truncation order", std::size_t{3});
        auto e = mm.run_as<pt>(vmfc_key, aos, sys);
        REQUIRE(approximately_equal(e, e3_corr, 1e-2));
    }
}