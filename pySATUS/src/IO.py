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
    aniscoef = h5group.create_dataset("AnisoCoeff", simmesh.mesh[2,:,:].shape, type(simmesh.mesh[2,0,0]))
    aniscoef[:,:] = simmesh.mesh[2,:,:]

    # Photon count data
    photcount = h5group.create_dataset("PhotCnt", simmesh.mesh[3,:,:].shape, type(simmesh.mesh[3,0,0]))
    photcount[:,:] = np.rot90(simmesh.mesh[3,:,:])

    # x1 array
    x1arr = h5group.create_dataset("x1", simmesh.x1[:].shape, type(simmesh.x1[0]))
    x1arr[:] = simmesh.x1[:]

    # x2 array
    x2arr = h5group.create_dataset("x2", simmesh.x2[:].shape, type(simmesh.x2[0]))
    x2arr[:] = simmesh.x2[:]

    # Group for photon data? 

    h5file.close()


