# include <cmath>
# include <random>

#ifndef PHOTON_HPP_
#define PHOTON_HPP_

struct pos {
    double x1;
    double x2;
};

struct ind {
    int indx1;
    int indx2;
};

class Photon 
{
public:

    Photon(double x10, double x20, int indx1, int indx2, double phi0, double dr);
    double probAbsorb(double abs_coef_ij);
    double probScatter(double sct_coef_ij);
    void getNewDir(bool scatter, double g_ij);
    void Move();

    // Accessing private information
    pos getPhotonPos();
    ind getIndexPos();
    bool   isAlive();

    // Changing private info
    void setAlive(bool isalive);
    void setIndex(ind new_ind);
    void resetPhotonParams(double x10, double x20, int indx1, int indx2, double phi0, double dr);

private:
    double m_x1;
    double m_x2;
    double m_phi;

    int m_indx1;
    int m_indx2;

    double m_dr;

    bool alive;

    std::mt19937 m_gen{std::random_device{}()};

    std::uniform_real_distribution< double > phi_dist;

};

Photon::Photon(double x10, double x20, int indx1, int indx2, double phi0, double dr) {

    m_x1 = x10;
    m_x2 = x20;

    m_indx1 = indx1;
    m_indx2 = indx2;

    m_phi = phi0;
    m_dr = dr;

    alive = true;

    phi_dist = std::uniform_real_distribution< double >(-1.0, 1.0);

}

double Photon::probAbsorb(double abs_coef_ij) {
    return (1 - exp(-abs_coef_ij * m_dr));
}

double Photon::probScatter(double sct_coef_ij){
    return (1 - exp(-sct_coef_ij * m_dr));
}

void Photon::getNewDir(bool scatter, double g_ij) {

    if (scatter == true) {
        double s2 = phi_dist(m_gen);
        m_phi += s2 * g_ij;
    } else {
        m_phi += 0.0;
    }
}

void Photon::Move() {
    m_x1 += m_dr * cos(m_phi);
    m_x2 += m_dr * sin(m_phi);
}

void Photon::setAlive(bool isalive) {
    alive = isalive;
}

void Photon::setIndex(ind new_ind) {
    m_indx1 = new_ind.indx1;
    m_indx2 = new_ind.indx2;
}

pos Photon::getPhotonPos() {
    pos new_pos;
    new_pos.x1 = m_x1;
    new_pos.x2 = m_x2;
    return new_pos;
}

ind Photon::getIndexPos() {
    ind new_ind;
    new_ind.indx1 = m_indx1;
    new_ind.indx2 = m_indx2;
    return new_ind;
}

bool Photon::isAlive() {
    return alive;
}

void Photon::resetPhotonParams(double x10, double x20, int indx1, int indx2, double phi0, double dr) {

    m_x1 = x10;
    m_x2 = x20;

    m_indx1 = indx1;
    m_indx2 = indx2;

    m_phi = phi0;
    m_dr = dr;

    alive = true;

}

#endif // PHOTON_HPP_