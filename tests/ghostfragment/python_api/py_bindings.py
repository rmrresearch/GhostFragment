from simde import simde, chemist, pluginplay
import ghostfragment as gf
from test_ghostfragment import *

mm = pluginplay.ModuleManager()
gf.ghostfragment.load_modules(mm)

class MySTO3G(pluginplay.ModuleBase):
    def __init__(self):
        super().__init__(self)
        self.satisfies_property_type[simde.AtomicOrbitals]()

    def run_(self, inputs, submods):
        [mol] = simde.AtomicOrbitals.unwrap_inputs(inputs)
        aos = simde.AOSpaceD(sto3g(mol))
        rv = self.results()
        return simde.AtomicOrbitals.wrap_results(rv, aos)


class TestEgy(pluginplay.ModuleBase):
    def __init__(self):
        super().__init__(self)
        self.satisfies_property_type[simde.AOEnergy]()

    def run_(self, inputs, submods):
        [aos, mol] = simde.AOEnergy.unwrap_inputs(inputs)
        print(mol)
        rv = self.results()
        return simde.AOEnergy.wrap_results(rv, 3.14)



mm.add_module("STO-3G", MySTO3G())
mm.add_module("Fake egy", TestEgy())
mm.change_submod("FragmentedSystem Driver", "Cap Basis", "STO-3G")
mm.change_submod("Fragment Based Method", "energy method", "Fake egy")
mod = mm.at("Fragment Based Method")
n = 2
mol = water_nmer(n)
sys = chemist.ChemicalSystem(mol, n * 10)
bs  = sto3g(mol)
aos = chemist.orbital_space.AOSpaceD(bs)

mod.change_input["unsigned int"]("GMBE truncation order", 1)
[e] = mod.run_as[simde.AOEnergy](aos, sys)

print(e)
