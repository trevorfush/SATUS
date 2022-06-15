import numpy as np
import sys
sys.path.append("..")
from ..Photon import Photon

def ProblemGen(sim_params, simMesh, photonArray) -> None:

    nx1 = sim_params["nx1"]
    nx2 = sim_params["nx2"]

    x1min = sim_params["x1min"]
    x1max = sim_params["x1max"]
    x2min = sim_params["x2min"]
    x2max = sim_params["x2max"]

    Nphotons = sim_params["Nphotons"]
    dr       = sim_params["dr"]
    w0       = sim_params["w0"]

    x1  = simMesh.x1
    x2  = simMesh.x2
    RadL = 1.0 # mm
    RadS = 0.75 # mm

    # Code to initialize grid...

    for i in range(nx1):
        for j in range(nx2):

            simMesh.mesh[0,i,j] = 1.0  # mm^-1
            simMesh.mesh[1,i,j] = 0.0  # mm^-1
            simMesh.mesh[2,i,j] = 0.8  # dimensionless

            if (x1[i] ** 2) + (x2[j] ** 2) <= RadL**2:

                simMesh.mesh[0,i,j] = 78.0   # mm^-1
                simMesh.mesh[1,i,j] = 0.0415 # mm^-1
                simMesh.mesh[2,i,j] = 0.95   # dimensionless

            if ((x1[i]-2.5) ** 2) + ((x2[j]-2.5) ** 2) <= RadS**2:

                simMesh.mesh[0,i,j] = 78.0   # mm^-1
                simMesh.mesh[1,i,j] = 0.0415 # mm^-1
                simMesh.mesh[2,i,j] = 0.95   # dimensionless

            if ((x1[i]+2.5) ** 2) + ((x2[j]-2.5) ** 2) <= RadS**2:

                simMesh.mesh[0,i,j] = 78.0   # mm^-1
                simMesh.mesh[1,i,j] = 0.0415 # mm^-1
                simMesh.mesh[2,i,j] = 0.95   # dimensionless

            if ((x1[i]-2.5) ** 2) + ((x2[j]+2.5) ** 2) <= RadS**2:

                simMesh.mesh[0,i,j] = 78.0   # mm^-1
                simMesh.mesh[1,i,j] = 0.0415 # mm^-1
                simMesh.mesh[2,i,j] = 0.95   # dimensionless

            if ((x1[i]+2.5) ** 2) + ((x2[j]+2.5) ** 2) <= RadS**2:

                simMesh.mesh[0,i,j] = 78.0   # mm^-1
                simMesh.mesh[1,i,j] = 0.0415 # mm^-1
                simMesh.mesh[2,i,j] = 0.95   # dimensionless

    # Code to initialize array of photons
    for i in range(Nphotons):
        
        x20 = x2min
        x10 = np.random.normal(0.0, w0/2)

        phi0 = np.pi/2

        ind0 = simMesh.getSingleMeshLoc(x10, x20)

        photonArray.append(Photon(x10, x20, ind0[0], ind0[1], phi0, dr))

    return
