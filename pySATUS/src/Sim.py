import numpy as np
import sys
sys.path.append("..")
from .Mesh import Mesh
from .Photon import Photon
from .IO import WriteData
from .pgen import initialtest
from tqdm import tqdm

############### TO DO ####################
# - need to figure out how to link params to pgen function
# - need to work in CL args and make them link to pgen
# - Simulation run
# - Implement initialtest with a simple example
# - Create a simple testing visualization environment

class Simulation:
    """
    Simulation class to organize all the inputs and outputs for
    a given simulation. Main inputs are:

        sim_params --> Dictionary containing parameters for simulation
                       (see main.py, params.yml)
        sim_args   --> Dictionary containing CL args for simulation
                       these consist of .yml file to use, outfile and
                       output directory, data save frequency... (etc.)
    """

    def __init__(self, sim_params, sim_args):

        self.sim_params = sim_params
        self.sim_args   = sim_args

        self.mesh       = Mesh(sim_params["nx1"], sim_params["nx2"], sim_params["x1min"],
                               sim_params["x1max"], sim_params["x2min"], sim_params["x2max"])

        self.photonArray = []

    def Initialize(self):

        if self.sim_args.problem == "initialtest":
            pgenfunc = initialtest.ProblemGen
        else:
            sys.exit("Input problem not recognized, please use a correct simulation implementation")

        pgenfunc(self.sim_params, self.mesh, self.photonArray)

        return

    def generateNewPhotons(self):
        
        for i in range(self.sim_params["Nphotons"]):
        
            x20 = self.mesh.x2min
            x10 = np.random.normal(0.0, self.sim_params["w0"]/2)

            phi0 = np.pi/2

            ind0 = self.mesh.getSingleMeshLoc(x10, x20)

            self.photonArray.append(Photon(x10, x20, ind0[0], ind0[1], phi0, self.sim_params["dr"]))

    def Run(self) -> None:

        maxiter = self.sim_params["maxiter"]
        saveiter = 0

        for T in tqdm(range(maxiter)):

            self.mesh.mesh[3,:,:] = 0.0

            if T < self.sim_params["pulselength"]:
                self.generateNewPhotons()
                
            self.mesh.SnapToMesh(self.photonArray)

            for i, photon in enumerate(self.photonArray):
                
                if photon.alive:
                    p_abs = photon.probAbsorb(self.mesh.mesh[1,photon.indx1,photon.indx2])

                    if np.random.random() < p_abs:
                        photon.alive = False
                        continue

                    p_scat = photon.probScatter(self.mesh.mesh[0,photon.indx1,photon.indx2])

                    if np.random.random() < p_scat:
                        scatter = True
                    else:
                        scatter = False

                    photon.getNewDir(scatter, self.mesh.mesh[3,photon.indx1,photon.indx2])
                    photon.Move()
                
                else:
                    del self.photonArray[i]

            if T % self.sim_args.savefreq == 0:

                fname = f"{self.sim_args.outpath}/{self.sim_args.outfile}_{str(saveiter).zfill(4)}.h5"

                WriteData(fname, self.mesh, self.photonArray)

                print(f"Saved data to {fname} for iteration {str(T).zfill(7)}")
                saveiter += 1

        return
