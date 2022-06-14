import numpy as np

class Mesh:
    """
    Mesh class containing the simulation volume for pySATUS. The Mesh class
    contains the `mesh` object, which is a (4, nx1, nx2) grid representing:

        mesh[0, :, :] --> Scattering coefficients for each grid location...
                          these differ depending on tissue or vessel
        mesh[1, :, :] --> Absorption coefficients for each grid location...
                          these differ depending on tissue or vessel
        mesh[2, :, :] --> Anisoptropy of scattering values...
                          determines isotropy of of scattered photons
        mesh[3, :, :] --> Grid containing binned photon counts at resolution
                          of nx1 X nx2 pixels (not normalized)

    In addition, it contains scale information and arrays... i.e. array of 
    x1 values and an array of x2 values.
    """

    def __init__(self, nx1, nx2, x1min, x1max, x2min, x2max) -> None:
        """
        Initializes values for Mesh. Required arguments:

        | Argument    |  Description                           |
        --------------------------------------------------------
        |   nx1       |  Number of grid points in x1 direction |
        --------------------------------------------------------
        |   nx2       |  Number of grid points in x1 direction |
        --------------------------------------------------------
        |   x1min     |  Minimum x1 value on grid (NEED UNITS) |
        --------------------------------------------------------
        |   x2min     |  Minimum x2 value on grid (NEED UNITS) |
        --------------------------------------------------------
        |   x1max     |  Maximum x1 value on grid (NEED UNITS) |
        --------------------------------------------------------
        |   x2max     |  Maximum x2 value on grid (NEED UNITS) |
        --------------------------------------------------------
        """
        self.nx1 = nx1
        self.nx2 = nx2

        self.x1max = x1max
        self.x2max = x2max
        self.x1min = x1min
        self.x2min = x2min

        self.dx1    = (x1max - x1min) / nx1
        self.dx2    = (x2max - x2min) / nx2

        self.mesh = np.zeros((4, nx1, nx2), dtype=np.float64)

        self.x1   = np.linspace(x1min, x1max, nx1)
        self.x2   = np.linspace(x2min, x2max, nx2)

    def FillMesh(self, ) -> None:
        return

    def SnapToMesh(self, photonPos) -> None:
        """
        Snaps photon positions to binned positions on simulation grid.

        Takes an array of photon positions, each element being an array
        with an x1 position as the first index and the second element 
        being an x2 position
        """
        for i in range(len(photonPos)):

            phot_x1 = photonPos[i][0]
            phot_x2 = photonPos[i][1]

            ind_x1  = (phot_x1 - self.x1min) / self.dx1
            ind_x2  = (phot_x2 - self.x2min) / self.dx2

            self.mesh[4, ind_x1, ind_x2] += 1.0

        return 

    def getMeshIndLoc(self, singlePos):
        """
        Get single indexed location values
        """
        phot_x1 = singlePos[0]
        phot_x2 = singlePos[1]

        ind_x1  = (phot_x1 - self.x1min) / self.dx1
        ind_x2  = (phot_x2 - self.x2min) / self.dx2

        return [ind_x1, ind_x2]
