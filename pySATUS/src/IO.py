import h5py
import numpy as np

def WriteData(fname, simmesh, photonarr):

    h5file = h5py.File(fname, "w")
    
    # Group for mesh data
    h5group = h5file.create_group("MeshData")

    # Scattering Coeff data
    scatcoef = h5group.create_dataset("ScatCoeff", simmesh.mesh[0,:,:].shape, type(simmesh.mesh[0,0,0]))
    scatcoef[:,:] = simmesh.mesh[0,:,:]

    # Absorption Coeff data
    abscoef = h5group.create_dataset("AbsCoeff", simmesh.mesh[1,:,:].shape, type(simmesh.mesh[1,0,0]))
    abscoef[:,:] = simmesh.mesh[1,:,:]

    # Anisotropy Coeff data
    aniscoef = h5group.create_dataset("AnisoCoeff", simmesh.mesh[3,:,:].shape, type(simmesh.mesh[3,0,0]))
    aniscoef[:,:] = simmesh.mesh[3,:,:]

    # Photon count data
    photcount = h5group.create_dataset("PhotCnt", simmesh.mesh[4,:,:].shape, type(simmesh.mesh[4,0,0]))
    photcount[:,:] = np.rot90(simmesh.mesh[4,:,:])

    # Group for photon data? 

    h5file.close()


