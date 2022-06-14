import numpy as np

class Photon:
    """
    
    """
    def __init__(self, x10, x20, theta0, dr) -> None:
        
        self.x1    = x10
        self.x2    = x20
        self.theta = theta0

        self.dr    = dr

    def probAbsorb(self, abs_coef_ij):
        return np.exp(-abs_coef_ij * self.dr)

    def probScatter(self, sct_coef_ij):
        return (1 - np.exp(-sct_coef_ij * self.dr))

    def getNewDir(self, scatter, g_ij):
        # Scatter is bool, true or false
        if scatter == True:
            s1 = np.random.random()
            s2 = np.random.uniform(-1.0,1.0)
            self.theta += s1 * s2 * np.cos(g_ij)
        return 
