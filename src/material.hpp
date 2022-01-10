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

class Material
{
public:
    Material(int nID, std::string nName="unknowed");
    Material(const Material &other); //copy constructor
    Material& operator=(const Material &other); //copy assignement operator
    Material(Material &&other); //move constructor
    Material& operator=(Material &&other); //move assignement operator
    ~Material();

    // edit functions
    void edit_material(const int nID,  const std::string nName);
    void edit_material(const Material OtherMaterial);
    virtual int edit_from_json(const nlohmann::json input_json);
    void edit_ID(const int nID);
    void edit_name(const std::string nName);

    // get functions
    int get_ID() {return ID;}
    std::string get_name() {return Name;}
    virtual nlohmann::json get_json();

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
    void add_material(Material new_material);
    void edit_material(unsigned int ID, Material new_material);
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
    std::vector<Material> MaterialVector;
    std::string FileName; // file name where MaterialList can be saved or loaded
};

class HeatMaterial : public Material
{
public:
    HeatMaterial(int nID, std::string nName="unknowed", float nDensity=1.f, float nSpecificHeat=1.f, float nThermalConductivity=1.f);
    HeatMaterial(Material nMaterial, float nDensity=1.f, float nSpecificHeat=1.f, float nThermalConductivity=1.f);
    HeatMaterial(const HeatMaterial &other); //copy constructor
    HeatMaterial& operator=(const HeatMaterial &other); //copy assignement operator
    HeatMaterial(HeatMaterial &&other); //move constructor
    HeatMaterial& operator=(HeatMaterial &&other); //move assignement operator
    ~HeatMaterial();

    // edit functions
    void edit_density(float nDensity);
    void edit_specific_heat(float nSpecificHeat);
    void edit_thermal_conductivity(float nThermalConductivity);
    int edit_from_json(nlohmann::json input_json);

    // get functions
    float get_density() {return Density;}
    float get_specific_heat() {return SpecificHeat;}
    float get_thermal_conductivity() {return ThermalConductivity;}
    nlohmann::json get_json();

private:
    float Density;
    float SpecificHeat;
    float ThermalConductivity;
};

// TODO heat material group

#endif // MATERIAL_H
