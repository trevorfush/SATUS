import numpy as np

class Photon:
    """
    Class representing a photon agent in the simulation. The photon
    possess many important characteristics:

            x1  -> Position along the x1 axis
            x2  -> Position along the x2 axis
            phi -> Orientation angle relative to the positive x1 axis
            dr  -> Step length per iteration for each photon

    Photon contains many crucial methods for evolving the sim:

            probAbsorb -> Return probability that the photon is absorbed
            probScatter -> Returns probability of scatter
            getNewDir   -> Alters direction of photon if scattered
            Move        -> Moves photon for one iteration

    """
    def __init__(self, x10, x20, indx1, indx2, phi0, dr) -> None:
        
        self.x1    = x10
        self.x2    = x20
        self.phi   = phi0

        self.dr    = dr

        self.indx1 = indx1
        self.indx2 = indx2

        self.alive = True

    def probAbsorb(self, abs_coef_ij):
        return (1-np.exp(-abs_coef_ij * self.dr))

    def probScatter(self, sct_coef_ij):
        return (1-np.exp(-sct_coef_ij * self.dr))

    def getNewDir(self, scatter, g_ij) -> None:
        # Scatter is bool, True or False
        if scatter == True:
            s2 = np.random.uniform(-1.0,1.0)
            self.phi += s2 * np.cos(g_ij)
        elif scatter == False:
            self.phi = self.phi

    def Move(self) -> None:
        self.x1 += self.dr * np.cos(self.phi)
        self.x2 += self.dr * np.sin(self.phi)
