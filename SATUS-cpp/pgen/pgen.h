# include <vector>
# include "../src/Mesh.h"
# include "../src/Photon.h"

#ifndef PGEN_H_
#define PGEN_H_

void testProblemGen(Mesh &simmesh, std::vector< Photon > &photons, 
                int Nphotons, double dr, double w0) 
{
    
    std::mt19937 m_gen;
    std::normal_distribution< double > x1dist(0.0, w0/2);

    double RadL = 1.0;  // Large vessel radius mm
    double RadS = 0.75; // Small vessel radium mm

    std::vector<double> xcent = {-3.0, 3.0, 0.0};
    std::vector<double> ycent = {-3.0, 3.0, 0.0};

    for (int i=0; i<simmesh.nx2; ++i) {
        for (int j=0; j<simmesh.nx1; ++j) {

            simmesh.mesh[i][j].sct_coeff = 1.0;
            simmesh.mesh[i][j].abs_coeff = 0.0;
            simmesh.mesh[i][j].aniso_coeff = 0.8;
            
            // for (auto xc : xcent) {
            //     for (auto yc : ycent) {
            //         if (pow((simmesh.x1[j] - xc),2.0) + pow((simmesh.x2[i] - yc),2.0) <= RadS) {
            //             // std::cout << "HERE" << std::endl;
            //             simmesh.mesh[i][j].sct_coeff = 78.0;
            //             simmesh.mesh[i][j].abs_coeff = 0.0415;
            //             simmesh.mesh[i][j].aniso_coeff = 0.95;
            //         }
            //     }
            // }

            double i_x1 = simmesh.x1[j];
            double i_x2 = simmesh.x2[i];

            if (pow((i_x1),2.0) + pow(i_x2, 2.0) <= pow(RadL,2.0)) {
                simmesh.mesh[i][j].sct_coeff = 78.0;
                simmesh.mesh[i][j].abs_coeff = 0.0415;
                simmesh.mesh[i][j].aniso_coeff = 0.95;
            }

            if (pow((i_x1-2.5),2.0) + pow((i_x2-2.5), 2.0) <= pow(RadS,2.0)) {
                simmesh.mesh[i][j].sct_coeff = 78.0;
                simmesh.mesh[i][j].abs_coeff = 0.0415;
                simmesh.mesh[i][j].aniso_coeff = 0.95;
            }

            if (pow((i_x1+2.5),2.0) + pow((i_x2-2.5), 2.0) <= pow(RadS,2.0)) {
                simmesh.mesh[i][j].sct_coeff = 78.0;
                simmesh.mesh[i][j].abs_coeff = 0.0415;
                simmesh.mesh[i][j].aniso_coeff = 0.95;
            }

            if (pow((i_x1-2.5),2.0) + pow((i_x2+2.5), 2.0) <= pow(RadS,2.0)) {
                simmesh.mesh[i][j].sct_coeff = 78.0;
                simmesh.mesh[i][j].abs_coeff = 0.0415;
                simmesh.mesh[i][j].aniso_coeff = 0.95;
            }

            if (pow((i_x1+2.5),2.0) + pow((i_x2+2.5), 2.0) <= pow(RadS,2.0)) {
                simmesh.mesh[i][j].sct_coeff = 78.0;
                simmesh.mesh[i][j].abs_coeff = 0.0415;
                simmesh.mesh[i][j].aniso_coeff = 0.95;
            }

        }
    }

    for (int i=0; i<Nphotons; ++i) {
        double x20 = simmesh.x2min;
        double x10 = x1dist(m_gen);

        double phi0 = M_PI / 2.0;
        ind ind0 = simmesh.getSingMeshLoc(x10, x20);

        photons.push_back(Photon(x10, x20, ind0.indx1, ind0.indx2, phi0, dr));
    }

}

void ProblemGen(Mesh &simmesh, std::vector< Photon > &photons, 
                int Nphotons, double dr, double w0, int num_vessels) 
{
    std::mt19937 m_gen;
    std::normal_distribution< double > x1dist((simmesh.x1max + simmesh.x1min)/2, w0/2);
    std::normal_distribution< double > vessel_width(0.3,0.3);
    std::uniform_real_distribution< double > x1_cen(simmesh.x1min, simmesh.x1max);
    std::uniform_real_distribution< double > x2_cen(simmesh.x2min+2.0, simmesh.x2max-2.0);

    std::vector<double> vessel_x1_cen;
    std::vector<double> vessel_x2_cen;
    std::vector<double> vessel_radii;

    for (int n=0; n<num_vessels; ++n) {
        vessel_x1_cen.push_back(x1_cen(m_gen));
        vessel_x2_cen.push_back(x2_cen(m_gen));
        vessel_radii.push_back(vessel_width(m_gen));
    }


    for (int i=0; i<simmesh.nx2; ++i) {
        for (int j=0; j<simmesh.nx1; ++j) {

            simmesh.mesh[i][j].sct_coeff = 1.0;
            simmesh.mesh[i][j].abs_coeff = 0.0;
            simmesh.mesh[i][j].aniso_coeff = 0.8;
            
            // for (auto xc : xcent) {
            //     for (auto yc : ycent) {
            //         if (pow((simmesh.x1[j] - xc),2.0) + pow((simmesh.x2[i] - yc),2.0) <= RadS) {
            //             // std::cout << "HERE" << std::endl;
            //             simmesh.mesh[i][j].sct_coeff = 78.0;
            //             simmesh.mesh[i][j].abs_coeff = 0.0415;
            //             simmesh.mesh[i][j].aniso_coeff = 0.95;
            //         }
            //     }
            // }

            double i_x1 = simmesh.x1[j];
            double i_x2 = simmesh.x2[i];

            for (int n=0; n<num_vessels; ++n) {
                if (pow((i_x1-vessel_x1_cen[n]),2.0) + pow((i_x2-vessel_x2_cen[n]), 2.0) <= pow(vessel_radii[n],2.0)) {
                    
                    // std::cout << "Here!" << std::endl;
                    simmesh.mesh[i][j].sct_coeff = 78.0;
                    simmesh.mesh[i][j].abs_coeff = 0.0415;
                    simmesh.mesh[i][j].aniso_coeff = 0.95;
            }
            }
            


        }
    }

    for (int i=0; i<Nphotons; ++i) {
        double x20 = simmesh.x2min + simmesh.dx2;
        double x10 = x1dist(m_gen);

        double phi0 = M_PI / 2.0;
        ind ind0 = simmesh.getSingMeshLoc(x10, x20);

        photons.push_back(Photon(x10, x20, ind0.indx1, ind0.indx2, phi0, dr));
    }
}

#endif // PGEN_H_