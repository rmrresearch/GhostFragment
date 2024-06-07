# Copyright 2024 GhostFragment
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import nwchemex as nwx
import parallelzone as pz
import simde
import chemist
import pluginplay
import ghostfragment
import unittest
import ctypes


class TestFragmentBasedMethod(unittest.TestCase):

    def test_1b_water_dimer_hf_aug_cc_pvdz(self):
        mod_key = 'Fragment Based Method'
        method = 'NWChem : SCF'
        basis = 'aug-cc-pvdz'
        self.mm.change_input(method, 'basis set', basis)
        sys = chemist.ChemicalSystem(self.water2)

        self.mm.change_submod(mod_key, 'Energy method', method)
        egy = self.mm.run_as(simde.TotalEnergy(), mod_key, sys)
        self.assertAlmostEqual(egy, -152.084758403538)

    def test_1b_water_trimer_hf_sto_3g(self):
        mod_key = 'Fragment Based Method'
        method = 'NWChem : SCF'
        basis = 'sto-3g'
        self.mm.change_input(method, 'basis set', basis)
        sys = chemist.ChemicalSystem(self.water3)

        self.mm.change_submod(mod_key, 'Energy method', method)
        egy = self.mm.run_as(simde.TotalEnergy(), mod_key, sys)
        self.assertAlmostEqual(egy, -224.881189393868)

    def test_2b_water_trimer_hf_sto_3g(self):
        mod_key = 'N-mer Based Method'
        method = 'NWChem : SCF'
        basis = 'sto-3g'
        trunc_order = 2
        self.mm.change_input(method, 'basis set', basis)
        self.mm.change_input('All nmers', 'n', trunc_order)
        sys = chemist.ChemicalSystem(self.water3)

        self.mm.change_submod(mod_key, 'Energy method', method)
        egy = self.mm.run_as(simde.TotalEnergy(), mod_key, sys)
        self.assertAlmostEqual(egy, -224.90189366802105)

    def setUp(self):
        self.mm = pluginplay.ModuleManager()
        nwx.load_modules(self.mm)
        ghostfragment.load_modules(self.mm)

        mol_pt = simde.MoleculeFromString()
        sys_maker_key = 'ChemicalSystem via QCElemental'

        mol_str = """
        H       -1.958940   -0.032063    0.725554
        H       -0.607485    0.010955    0.056172
        O       -1.538963    0.004548   -0.117331
        H        1.727607    0.762122   -0.351887
        H        1.704312   -0.747744   -0.399151
        O        1.430776   -0.003706    0.113495
        """
        self.water2 = self.mm.run_as(mol_pt, sys_maker_key, mol_str)

        mol_str = """
        O          -0.167787    1.645761    0.108747
        H           0.613411    1.102620    0.113724
        H          -0.093821    2.209720   -0.643619
        O           1.517569   -0.667424   -0.080674
        H           1.989645   -1.098799    0.612047
        H           0.668397   -1.091798   -0.139744
        O          -1.350388   -0.964879   -0.092208
        H          -1.908991   -1.211298    0.626207
        H          -1.263787   -0.018107   -0.055536
        """
        self.water3 = self.mm.run_as(mol_pt, sys_maker_key, mol_str)
