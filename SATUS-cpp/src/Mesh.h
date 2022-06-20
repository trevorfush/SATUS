# include <vector>
# include "Photon.h"

#ifndef MESH_HPP_
#define MESH_HPP_

struct Grid {
    double sct_coeff=0.0;
    double abs_coeff=0.0;
    double aniso_coeff=0.0;
    int    phot_count=0;
};

class Mesh
{
public:

    // Important values that other stuff needs to know too
    int nx1;
    int nx2;

    double x1max;
    double x2max;
    double x1min;
    double x2min;

    double dx1;
    double dx2;

    std::vector< std::vector< Grid > > mesh;
    std::vector< double >              x1;
    std::vector< double >              x2;

    // Methods
    Mesh(int i_nx1, int i_nx2, double i_x1min, double i_x1max, double i_x2min, double i_x2max);
    void SnapToMesh(std::vector< Photon > &photons);
    ind  getSingMeshLoc(double x1, double x2);
    void clearPhotonCounts();

private:

};

Mesh::Mesh(int i_nx1, int i_nx2, double i_x1min, double i_x1max, double i_x2min, double i_x2max): mesh(i_nx2, std::vector< Grid > (i_nx1, Grid())), x1(i_nx1), x2(i_nx2) {

    nx1 = i_nx1;
    nx2 = i_nx2;

    x1max = i_x1max;
    x1min = i_x1min;
    x2max = i_x2max;
    x2min = i_x2min;

    dx1 = (x1max - x1min) / nx1;
    dx2 = (x2max - x2min) / nx2;

    for (int i=0; i<nx1; ++i) {
        x1[i] = x1min + i * dx1;
    }

    for (int i=0; i<nx2; ++i) {
        x2[i] = x2min + i * dx2;
    }

}

void Mesh::SnapToMesh(std::vector< Photon > &photons) {

    double phot_x1, phot_x2;
    int ind_x1, ind_x2;

    for (int i=0; i<photons.size(); ++i) {
        bool isalive = photons[i].isAlive();
        if (isalive == true) {
            pos photonpos = photons[i].getPhotonPos();

            phot_x1 = photonpos.x1;
            phot_x2 = photonpos.x2;

            ind_x1  = int((phot_x1 - x1min) / dx1);
            ind_x2  = int((phot_x2 - x2min) / dx2);

            if (ind_x1 > nx1-1 || ind_x1 < 0 || ind_x2 > nx2-1 || ind_x2 < 0) {
                photons[i].setAlive(false);
            } else {
                mesh[ind_x2][ind_x1].phot_count += 1;

                ind new_ind;
                new_ind.indx1 = ind_x1;
                new_ind.indx2 = ind_x2;

                photons[i].setIndex(new_ind);
            }

        } 
    }

}

ind Mesh::getSingMeshLoc(double x1, double x2) {

    ind new_ind;
    new_ind.indx1 = int((x1 - x1min) / dx1);
    new_ind.indx2 = int((x2 - x2min) / dx1);

    return new_ind;
}

void Mesh::clearPhotonCounts() {

    for (int i=0; i<nx2; ++i) {
        for (int j=0; j<nx1; ++j) {
            mesh[i][j].phot_count = 0.0;
        }
    }
 
}
#endif // MESH_HPP_