#pragma once
#include <vector>

template <typename T>
class DepozitSpecial {
private:
    std::vector<T> colectie;
public:
    void adauga(T obiect) { colectie.push_back(obiect); }
    int getTotal() { return (int)colectie.size(); }
};