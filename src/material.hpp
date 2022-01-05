#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>
#include<fstream>

#include"json.hpp"

#define MATERIAL_VERBOSE 1

// Author: Jérôme Dubois
// Date: 2022/01
// Version 1.0
//
// Comment: This librairy was created in order to manage material in simulation tool with the possibility to save material list in json format
// First used is for thermal conduction problem
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

    int get_ID() {return ID;}
    std::string get_name() {return Name;}
    nlohmann::json get_json();

private:
    std::string Name;
    int ID;
};

// Material ID is automatically manage by MaterialList
// ID 0 is reserved for void material
class MaterialList
{
public:
    MaterialList();
    void add_material(material new_material);
    void edit_material(unsigned int ID, material new_material);
    void delete_material(unsigned int ID);
    void reset();
    std::string get_save_file_name() {return FileName;}
    void set_save_file_name(std::string nFileName) {FileName = nFileName;}
    void load();
    void save();

//private:
    nlohmann::json get_json();
    void edit_from_json(nlohmann::json input_json);
private:
    std::vector<material> MaterialVector;
    std::string FileName; // file name where MaterialList can be saved or loaded
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
