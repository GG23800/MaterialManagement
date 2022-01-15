#ifndef MATERIAL_H
#define MATERIAL_H

#include<iostream>
#include<fstream>
#include<typeinfo>

#include"json.hpp"

#define MATERIAL_VERBOSE 0

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
    void edit_material(const HeatMaterial OtherMaterial);
    void edit_density(float nDensity);
    void edit_specific_heat(float nSpecificHeat);
    void edit_thermal_conductivity(float nThermalConductivity);
    virtual int edit_from_json(nlohmann::json input_json);

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


// Material ID is automatically manage by MaterialList
// ID 0 is reserved for void material
// to take benefit of polymorphisme we use only material class and subclass
/*
 * use of templace class that only accept material and subclass material
 * static_assert is a compil time assertion
 * is_base_of return true if sMaterial is a Material or a subclass of Material
 */

template<class SubMaterial> 
class MaterialList
{
public:
    MaterialList();
    ~MaterialList();

    void add_material(const SubMaterial nMaterial);
    void edit_material(const unsigned int ID, const SubMaterial nMaterial);
    void delete_material(const unsigned int ID);
    void reset();
    SubMaterial get_material(unsigned int ID);
    void edit_save_file_name(std::string nName) {FileName = nName;}
    std::string get_save_file_name() {return FileName;}
    unsigned int size() {return MaterialVector.size();}

    void save();
    void load();

private:
    void edit_from_json(nlohmann::json InputJson);
    nlohmann::json get_json();

    std::vector<SubMaterial> MaterialVector;
    std::string FileName;
};

template <class SubMaterial>
MaterialList<SubMaterial>::MaterialList() : MaterialVector{}
{
    static_assert( std::is_base_of< Material, SubMaterial >::value, "Class insterted in MaterialList is not Material or subclass Material" );
    std::cout << "Constructor" << std::endl;
    SubMaterial nMaterial(0, "Void");
    MaterialVector.push_back(nMaterial);
    FileName = "MaterialList.json";
}

template <class SubMaterial>
MaterialList<SubMaterial>::~MaterialList()
{

}

template <class SubMaterial>
void MaterialList<SubMaterial>::add_material(const SubMaterial nMaterial)
{
    std::cout << "add material ID " << MaterialVector.size() << std::endl;
    int ID = MaterialVector.size();
    MaterialVector.push_back(nMaterial);
    MaterialVector[ID].edit_ID(ID);
}

template <class SubMaterial>
void MaterialList<SubMaterial>::edit_material(const unsigned int ID, const SubMaterial nMaterial)
{
    if (ID == 0)
    {
        std::clog << "Warning, can't edit material 0, it is reserved for void material" << std::endl;
    }
    else if (ID >= MaterialVector.size())
    {
        std::clog << "Warning, trying to edit an out of bound Material, nothing is done" << std::endl;
    }
    else
    {
        MaterialVector[ID] = nMaterial;
        MaterialVector[ID].edit_ID(ID);
    }
}

template <class SubMaterial>
void MaterialList<SubMaterial>::delete_material(unsigned const int ID)
{
    if (ID == 0)
    {
        std::clog << "Warning, can't delete material 0, it is reserved for void material" << std::endl;
    }
    else if (ID >= MaterialVector.size())
    {
        std::clog << "Warning, trying to delete an out of bound Material, nothing is done" << std::endl;
    }
    else
    {
        MaterialVector.erase(MaterialVector.begin()+ID);
        for (unsigned int k=ID ; k<MaterialVector.size() ; k++) {MaterialVector[k].edit_ID(k);}
    }   
}

template <class SubMaterial>
void MaterialList<SubMaterial>::reset()
{
    MaterialVector.erase(MaterialVector.begin()+1, MaterialVector.end());
}

template <class SubMaterial>
SubMaterial MaterialList<SubMaterial>::get_material(unsigned int ID)
{
    if ( ID >= MaterialVector.size() )
    {
        std::clog << "Warning, trying to access an out of bound material, returning the last one of the list" << std::endl;
        ID = MaterialVector.size() - 1;
    }
    return MaterialVector[ID];
}

template <class SubMaterial>
void MaterialList<SubMaterial>::load()
{
    std::ifstream InputJsonFile;
    InputJsonFile.open(FileName);
    if (!InputJsonFile)
    {
        std::clog << "Warning, can't open " << FileName << ", file doesn't exist or corrupted. New Material     list file with only void material will be created" << std::endl;
        std::ofstream OutputJsonFile;
        OutputJsonFile.open(FileName);
        if (!OutputJsonFile)
        {
            std::clog << "Error, can't create new material list file" << std::endl; // TODO stop program?
        }
        else
        {
            reset();
            OutputJsonFile << get_json();
            OutputJsonFile.close();
        }
    }
    else
    {
        edit_from_json(nlohmann::json::parse(InputJsonFile));
        InputJsonFile.close();
    }
}

template <class SubMaterial>
void MaterialList<SubMaterial>::save()
{
    std::ofstream OutputJsonFile;
    OutputJsonFile.open(FileName);
    if (!OutputJsonFile)
    {
        std::clog << "Error, can't open/create material list file" << std::endl; // TODO stop?
    }
    else
    {
        OutputJsonFile << get_json();
        OutputJsonFile.close();
    }
}

template <class SubMaterial>
void MaterialList<SubMaterial>::edit_from_json( nlohmann::json InputJson )
{
    int NumberOfMaterial = InputJson.size();
    reset();
    if (NumberOfMaterial < 1)
    {
        std::clog << "Warning, json size is too small... Is it a list of material? Material list is reset" << std::endl;
    }
    else
    {
        SubMaterial lm(0);
        for (int k=1 ; k<NumberOfMaterial ; k++)
        {
            lm.edit_from_json(InputJson[k]);
            MaterialVector.emplace_back(lm);
        }
    }
}

template <class SubMaterial>
nlohmann::json MaterialList<SubMaterial>::get_json()
{
    nlohmann::json OutputJson{};
    for (unsigned int k=0 ; k<MaterialVector.size() ; k++)
    {
        OutputJson[k] = MaterialVector[k].get_json();
    }
    return OutputJson;
}

#endif // MATERIAL_H
