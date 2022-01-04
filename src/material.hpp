#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>

#include"json.hpp"

#define MATERIAL_VERBOSE 1

// Author: Jérôme Dubois
// Date: 2022/01
// Version 1.0
//
// Comment: This librairy was created in order to manage material in simulation tool with the possibility to save materials in json format
// First used if for thermal conduction problem
// Depending on the need a class can be derived for other purpose (acoustic, electromagnetic, etc.)
// MATERIAL_VERBOSE is used for test/debug purpose

class material
{
public:
    material(int nID, std::string nName="unknowed");
    material(const material &other); //copy constructor
    material& operator=(const material &other); //copy assignement operator
    material(material &&other); //move constructor
    material& operator=(material &&other); //move assignement operator
    ~material();

    void edit_material(const int nID,  const std::string nName);
    void edit_material(const material OtherMaterial);
    void edit_from_json(const nlohmann::json input_json);
    void edit_ID(const int nID);
    void edit_name(const std::string nName);

    nlohmann::json get_json();

private:
    std::string Name;
    int ID;
};

class material_group
{
public:
    material_group();
    material_group(material first_material);
    material_group(std::vector<material> nMaterialVector);

private:
    std::vector<material> material_vector;
};

class heat_material : public material
{
public:
    heat_material(int nID, std::string nName="unknowed", float nDensity=1.f, float nSpecificHeat=1.f, float nThermalConductivity=1.f);
    heat_material(material nMaterial, float nDensity=1.f, float nSpecificHeat=1.f, float nThermalConductivity=1.f);
    heat_material(const heat_material &other); //copy constructor
    heat_material& operator=(const heat_material &other); //copy assignement operator
    heat_material(heat_material &&other); //move constructor
    heat_material& operator=(heat_material &&other); //move assignement operator
    ~heat_material();

    void edit_density(float nDensity);
    void edit_specific_heat(float nSpecificHeat);
    void edit_thermal_conductivity(float nThermalConductivity);
    void edit_from_json(nlohmann::json input_json);
    nlohmann::json get_json();

private:
    float Density;
    float SpecificHeat;
    float ThermalConductivity;
};

// TODO heat material group

#endif // MATERIAL_H
