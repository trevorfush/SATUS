// C and C++ includes
# include <cstdlib>
# include <iostream>
# include <cassert>
# include <cmath>
# include <vector>
# include <random>
# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>

// SATUS includes
# include "src/Mesh.h"
# include "src/Photon.h"
# include "pgen/pgen.h"

std::string ZeroPadNumber(int num)
{
    std::ostringstream ss;
    ss << std::setw(4) << std::setfill('0') << num;
    std::string result = ss.str();
    if (result.length() > 7)
    {
        result.erase(0, result.length() - 7);
    }
    return result;
}

std::string getFname(int iter, std::string fname_prefix) {

    std::string fname;
    std::stringstream ss;
    std::stringstream ssfname;
    std::string newnum = ZeroPadNumber(iter);

    ss << fname_prefix << newnum << ".csv";

    ss >> fname;

    return fname;

}

void saveCSV(Mesh &simmesh, std::string fname, int saveiter) {

    std::ofstream out(fname);

    for (int j=0; j<simmesh.nx2; ++j) {
        for (int i=0; i<simmesh.nx1; ++i) {
            out << simmesh.mesh[j][i].phot_count << ",";
        }
        out << '\n';
    }

    if (saveiter == 0) {
        std::ofstream out("ABSORPTION_COEFF.csv");

        for (int j=0; j<simmesh.nx2; ++j) {
            for (int i=0; i<simmesh.nx1; ++i) {
                out << simmesh.mesh[j][i].abs_coeff << ",";
            }
            out << '\n';
    }
    }
}

void generateNewPhotons(double x20, int Nphotons, double dr, Mesh &simmesh, std::vector<Photon> &photonArray, std::mt19937 gen, std::normal_distribution<double> x10_dist) {

    ind new_ind;

    for (int i=0; i<Nphotons; ++i) {

        double x10 = x10_dist(gen);

        double phi0 = M_PI / 2;

        ind ind0 = simmesh.getSingMeshLoc(x10, x20);

        photonArray.push_back(Photon(x10, x20, ind0.indx1, ind0.indx2, phi0, dr));
    }

}

int main() {

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution< double > prob(0.0, 1.0);
    std::uniform_real_distribution< double > s2_dist(-1.0, 1.0);

    //------------------------------------------------------------//

    // Grid info
    int nx1 = 1000;
    int nx2 = 400;

    double x1min = 0; // mm
    double x1max = 50;
    double x2min = 0;
    double x2max = 20;

    // Photon info
    int Nphotons = 10000;
    double dr = 0.08; //mm step length
    double w0 = 2.5;  //mm initial waist of beam

    // Time info
    int maxIter = 300;
    int savefreq = 3;
    int pulselength = 150;

    // Vessel info
    int num_vessel = 200;

    // Save info
    std::string fname_prefix = "OUTPUT_";

    //------------------------------------------------------------//


    // std::cout << "TESTING RNG:" <<std::endl;
    // for (int i=0; i<100; ++i) {
    //     std::cout << prob(gen) << std::endl;
    // }

    // Making mesh and photon array
    Mesh simmesh(nx1, nx2, x1min, x1max, x2min, x2max);
    std::vector<Photon> photonArray;

    std::normal_distribution< double > x10_dist((simmesh.x1max + simmesh.x1min)/2, w0/2);

    // Fill grid and generate problem
    ProblemGen(simmesh, photonArray, Nphotons, dr, w0, num_vessel);

    // Main simulation Loop -->
    int saveiter = 0;

    for (int iter=0; iter<=maxIter; ++iter) {

        simmesh.clearPhotonCounts();
        
        if (iter <= pulselength) {
            generateNewPhotons(x2min, Nphotons, dr, simmesh, photonArray, gen, x10_dist);
        }
        
        simmesh.SnapToMesh(photonArray);
        
        // Looping through each photon, 
        // probably could slap a pramga on here with OMP
        for (int p=0; p<photonArray.size(); p++) {
            bool is_photon_alive = photonArray[p].isAlive();

            if (is_photon_alive == true) {
                ind phot_ind = photonArray[p].getIndexPos();

                double p_abs = photonArray[p].probAbsorb(simmesh.mesh[phot_ind.indx2][phot_ind.indx1].abs_coeff);

                if (prob(gen) < p_abs) {
                    photonArray[p].setAlive(false);
                } else {

                    double p_scat = photonArray[p].probScatter(simmesh.mesh[phot_ind.indx2][phot_ind.indx1].sct_coeff);

                    // std::cout << p_scat << std::endl;

                    bool scatter;
                    if (prob(gen) < p_scat){
                        scatter = true;
                    } else {
                        scatter = false;
                    }

                    photonArray[p].getNewDir(scatter, simmesh.mesh[phot_ind.indx2][phot_ind.indx1].aniso_coeff);
                    photonArray[p].Move();

                }

            }

        }

        if (iter % savefreq == 0) {
            std::string fname = getFname(saveiter, fname_prefix);
            saveCSV(simmesh, fname, saveiter);
            std::cout << "[UPDATE] Saving to " << fname << " for iteration " << iter << std::endl;
            saveiter += 1;
        }

    }


    return 0;
}