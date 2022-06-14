import numpy as np

def ProblemGen(sim_params, simMesh) -> None:

    nx1 = sim_params["nx1"]
    nx2 = sim_params["nx2"]

    x1min = sim_params["x1min"]
    x1max = sim_params["x1max"]
    x2min = sim_params["x2min"]
    x2max = sim_params["x2max"]

    # Code to initialize grid...
