#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>

#include"json.hpp"

// Author: Jérôme Dubois
// Date: 2022/01
// Version 1.0
//
// Comment: This librairy was created in order to manage material in simulation tool with the possibility to save materials in json format
// First used if for thermal conduction problem
// Depending on the need a class can be derived for other purpose (acoustic, electromagnetic, etc.)

class material
{
public:
    material(int nID=0, std::string nName="unknowed");
    material(const material &other); //copy constructor
    material& operator=(const material &other); //copy assignement operator
    material(material &&other); //move constructor
    material& operator=(material &&other); //move assignement operator
    ~material();

    void edit_material(const int nID,  const std::string nName);
    void edit_material(const material OtherMaterial);
    void edit_material_from_json(const nlohmann::json input_json);
    void edit_material_ID(const int nID);
    void edit_material_name(const std::string nName);

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
    //TODO only double? <T>?
    // big 5
    heat_material(int nID=0, std::string nName="unknowed", float nDensity=1.f, float nSpecificHeat=1.f, float ThermalConductivity=1.f);
    heat_material(material = material(), float nDensity=1.f, float nSpecificHeat=1.f, float ThermalConductivity=1.f);

    // Other function
    // edit global
    // edit material part ; full, ID and name must be herited => TODO
    // edit density
    // edit specific heat
    // edit thermal conductivity
private:
    float Density;
    float SpecificHeat;
    float ThermalConductivity;
};

// TODO material group

#endif // MATERIAL_H
