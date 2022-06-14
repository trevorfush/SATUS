from lib2to3.pgen2 import pgen
import numpy as np
from Mesh import Mesh
from Photon import Photon
from IO import WriteData
import sys
from pgen import *

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

    def Initialize(self):

        if self.sim_args["problem"] == "initialtest":
            pgenfunc = pgen.initialtest.ProblemGen
        else:
            sys.exit("Input problem not recognized, please use a correct simulation implementation")

        return