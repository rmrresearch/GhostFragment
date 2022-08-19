from simde import simde, chemist, pluginplay
import ghostfragment as gf

#TODO: When simde.chemist is a submodule do: from simde.chemist import Atom
Atom = chemist.Atom

mm = pluginplay.ModuleManager()
gf.ghostfragment.load_modules(mm)

def water_nmer(n, dz = 3.0):

    mol = chemist.Molecule()

    zO = Atom.AtomicNumber(8)
    zH = Atom.AtomicNumber(1)

    for i in range(n):
        z = i * dz
        rO0 = Atom.coord_type([0.00000000000000, -0.07579039945857, z])
        rH0 = Atom.coord_type([0.86681456860648, 0.60144316994806, z])
        rH1 = Atom.coord_type([-0.86681456860648, 0.60144316994806, z])
        mol.push_back(Atom("O", zO, rO0))
        mol.push_back(Atom("H", zH, rH0))
        mol.push_back(Atom("H", zH, rH1))

    return mol

def sto3g(mol):
    ao_basis_set     = chemist.AOBasisSet["double"]
    atomic_basis_set = ao_basis_set.value_type
    shell_type       = atomic_basis_set.value_type

    # Taken from hard-coded basis sets in NWX
    # O
    c0_o = [0.15432897, 0.53532814, 0.44463454]
    a0_o = [130.7093200, 23.8088610, 6.4436083]
    c1 = [ -0.09996723, 0.39951283, 0.70011547]
    c2 = [0.15591627, 0.60768372, 0.39195739]
    a1 = [5.0331513, 1.1695961, 0.3803890]

    # H
    c0 = [0.1543289673, 0.5353281423, 0.4446345422]
    a0 = [3.425250914, 0.6239137298, 0.1688554040]

    pure = chemist.ShellType.pure

    bs = ao_basis_set()
    for atom_i in mol:
        x = atom_i.coords()[0]
        y = atom_i.coords()[1]
        z = atom_i.coords()[2]
        c = atomic_basis_set("STO-3G", atom_i.Z(), x, y, z)
        if atom_i.Z() == 1:
            c.add_shell(pure, 0, c0, a0)
        elif atom_i.Z() == 8:
            c.add_shell(pure, 0, c0_o, a0_o)
            c.add_shell(pure, 0, c1, a1)
            c.add_shell(pure, 1, c2, a1)
        else:
            raise runtime_error("No data for atomic number")
        bs.add_center(c)

    return bs

mod = mm.at("Fragment Based Method")
n = 2
mol = water_nmer(n)
sys = chemist.ChemicalSystem(mol, n * 10)
bs  = sto3g(mol)
aos = chemist.orbital_space.AOSpaceD(bs)

mod.change_input["unsigned int"]("GMBE truncation order", 1)
my_pt = "simde::AOEnergy"
ao_type = "const simde::chemist::orbital_space::AOSpaceD"
sys_type = "const simde::ChemicalSystem"
[e] = mod.run_as[simde.AOEnergy, ao_type, sys_type](aos, sys)

print(e)
