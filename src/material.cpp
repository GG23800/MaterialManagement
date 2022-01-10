#include "material.hpp"

Material::Material(int nID, std::string nName)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material constructor" << std::endl;
    #endif
    edit_material(nID, nName);
}

Material::Material(const Material &other) // copy constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material copy constructor" << std::endl;
    #endif
    ID = other.ID;
    Name = other.Name;
}

Material& Material::operator=(const Material &other) //copy assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material copy assignement operator" << std::endl;
    #endif
    if (this != &other)
    {
        ID = other.ID;
        Name = other.Name;
    }
    return *this;
}

Material::Material(Material &&other) //move constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material move constructor" << std::endl;
    #endif
    ID = other.ID;
    Name = other.Name;
    //release other ressource (optinal here)
    other.ID = 0;
    other.Name = "";
}

Material& Material::operator=(Material &&other) //move assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material move assignement operator" << std::endl;
    #endif
    if (this != &other)
    {
        ID = other.ID;
        Name = other.Name;
        //release other ressource (optinal here)
        other.ID = 0;
        other.Name = "";    
    }
    return *this;
}

Material::~Material()
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material destructor" << std::endl;
    #endif
}


void Material::edit_material(const int nID, const std::string nName)
{
    ID = nID;
    Name = nName;
}

void Material::edit_material(const Material OtherMaterial)
{
    ID = OtherMaterial.ID;
    Name = OtherMaterial.Name;
}

int Material::edit_from_json(const nlohmann::json input_json)
{
    int lerror = 0;
    int lID = 0;
    std::string lName = "unknow";
    if (input_json.find("ID") != input_json.end())
    {
        lID = input_json["ID"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, Material::edit_material_from_json(), ID not found in input json" << std::endl;
    }
    if (input_json.find("Name") != input_json.end())
    {
        lName = input_json["Name"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, Material::edit_material_from_json(), Name not found in input json" << std::endl;
    }
    if (!lerror)
    {
        ID = lID;
        Name = lName;
    }
    else
    {
        std::cout << "Problem with input json, material not edited" << std::endl;
    }
    return lerror;
}

void Material::edit_ID(const int nID)
{
    ID = nID;
}

void Material::edit_name(const std::string nName)
{
    Name = nName;
}

nlohmann::json Material::get_json()
{
    nlohmann::json ljson = nlohmann::json{};
    ljson["ID"] = ID;
    ljson["Name"] = Name;

    return ljson;
}





HeatMaterial::HeatMaterial(int nID, std::string nName, float nDensity, float nSpecificHeat, float nThermalConductivity) : Material(nID, nName)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material constructor" << std::endl;
    #endif
    Density = nDensity;
    SpecificHeat = nSpecificHeat;
    ThermalConductivity = nThermalConductivity;
}

HeatMaterial::HeatMaterial(Material nMaterial, float nDensity, float nSpecificHeat, float nThermalConductivity) : Material(nMaterial)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material constructor with material parameter" << std::endl;
    #endif
    Density = nDensity;
    SpecificHeat = nSpecificHeat;
    ThermalConductivity = nThermalConductivity;
}

HeatMaterial::HeatMaterial(const HeatMaterial &other) : Material(other) // copy constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material copy constructor" << std::endl;
    #endif
    Density = other.Density;
    SpecificHeat = other.SpecificHeat;
    ThermalConductivity = other.ThermalConductivity;
}

HeatMaterial& HeatMaterial::operator=(const HeatMaterial &other) //copy assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material copy assignement operator" << std::endl;
    #endif
    if (this != &other)
    {
        Material::operator=(other);
        Density = other.Density;
        SpecificHeat = other.SpecificHeat;
        ThermalConductivity = other.ThermalConductivity;
    }
    return *this;
}

HeatMaterial::HeatMaterial(HeatMaterial &&other) : Material(other) //move constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material move constructor" << std::endl;
    #endif
    Density = other.Density;
    SpecificHeat = other.SpecificHeat;
    ThermalConductivity = other.ThermalConductivity;
    //release other ressource (optional here)
    other.Density = 0.f;
    other.SpecificHeat = 0.f;
    other.ThermalConductivity = 0.f;
}

HeatMaterial& HeatMaterial::operator=(HeatMaterial &&other) //move assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material move assignement operator" << std::endl;
    #endif
   if (this != &other)
    {
        Material::operator=(other);
        Density = other.Density;
        SpecificHeat = other.SpecificHeat;
        ThermalConductivity = other.ThermalConductivity;
        //release other ressource (optional here)
        other.Density = 0.f;
        other.SpecificHeat = 0.f;
        other.ThermalConductivity = 0.f;
    }
    return *this;
}

HeatMaterial::~HeatMaterial()
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material destructor" << std::endl;
    #endif
}

void HeatMaterial::edit_density(float nDensity)
{
    Density = nDensity;
}
void HeatMaterial::edit_specific_heat(float nSpecificHeat)
{
    SpecificHeat = nSpecificHeat;
}
void HeatMaterial::edit_thermal_conductivity(float nThermalConductivity)
{
    ThermalConductivity = nThermalConductivity;
}

int HeatMaterial::edit_from_json(nlohmann::json input_json)
{
    int lerror = 0;
    Material test_material(Material::get_ID(), Material::get_name());
    float lDensity=0.f, lSpecificHeat=0.f, lThermalConductivity=0.f;
    if (input_json.find("Density") != input_json.end())
    {
        lDensity = input_json["Density"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, HeatMaterial::edit_from_json(), Density not found in input json" << std::endl;
    }
    if (input_json.find("SpecificHeat") != input_json.end())
    {
        lSpecificHeat = input_json["SpecificHeat"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, HeatMaterial::edit_from_json(), SpecificHeat not found in input json" << std::endl;
    }
    if (input_json.find("ThermalConductivity") != input_json.end())
    {
        lThermalConductivity = input_json["ThermalConductivity"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, HeatMaterial::edit_from_json(), ThermalConductivity not found in input json" << std::endl;
    }
    if (!lerror)
    {
        lerror = test_material.edit_from_json(input_json);
    }

    if (!lerror)
    {
        Material::edit_material(test_material);
        Density = lDensity;
        SpecificHeat = lSpecificHeat;
        ThermalConductivity = lThermalConductivity;
    }
    else
    {
        std::cout << "Problem with input json, heat material not edited" << std::endl;
    }
    return lerror;
}

nlohmann::json HeatMaterial::get_json()
{
    nlohmann::json ljson = nlohmann::json{};
    ljson = Material::get_json();
    ljson["Density"] = Density;
    ljson["SpecificHeat"] = SpecificHeat;
    ljson["ThermalConductivity"] = ThermalConductivity;
    return ljson;
}

MaterialList::MaterialList() : MaterialVector{Material(0,"Void")}
{
    FileName = "MaterialList.json"; //default file name
}

void MaterialList::add_material(Material new_material)
{
    new_material.edit_ID(MaterialVector.size());
    MaterialVector.push_back(new_material);
}

void MaterialList::edit_material(unsigned int ID, Material new_material)
{
    if (ID < MaterialVector.size())
    {
        if (ID != 0) // ID 0 is reserved for void material, can't be modify nor destroyed
        {
            new_material.edit_ID(ID);
            MaterialVector[ID] = new_material;
        }
        else
        {
            std::clog << "Warning, can't modify material at ID 0, it is reserved for void material" << std::endl;
        }
    }
    else
    {
        std::clog << "Warning, trying to edit an out of bound material, nothing is edited" << std::endl;
    }
}

void MaterialList::delete_material(unsigned int ID)
{
    if (MaterialVector.size() == 1)
    {
        std::clog << "Warning, MaterialList contained only one element (the void material), can't delete it" << std::endl;
    }
    else
    {
        if (ID < MaterialVector.size())
        {
            if (ID != 0) // ID 0 is reserved for void material, can't be modify nor destroyed
            {
                MaterialVector.erase(MaterialVector.begin()+ID);
                for (unsigned int k=0 ; k<MaterialVector.size() ; k++)
                {
                    MaterialVector[k].edit_ID(k);
                }
            }
            else
            {
                std::clog << "Warning, can't delete material at ID 0, it is reserved for void material" << std::endl;
            }
        }
        else
        {
            std::clog << "Warning, trying to delete an out of bound material, nothing is deleted" << std::endl;
        }
    }
}

void MaterialList::reset()
{
    MaterialVector.erase(MaterialVector.begin()+1,MaterialVector.end());
}

void MaterialList::load()
{
    std::ifstream InputJsonFile;
    InputJsonFile.open(FileName);
    if (!InputJsonFile)
    {
        std::clog << "Warning, can't open " << FileName << ", file doesn't exist or corrupted. New Material list file with only void material will be created" << std::endl;
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

void MaterialList::save()
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

nlohmann::json MaterialList::get_json()
{
    nlohmann::json ljson = nlohmann::json{};
    nlohmann::json OutputJson = nlohmann::json{};
    for (unsigned int k=0 ; k<MaterialVector.size() ; k++)
    {
        ljson = MaterialVector[k].get_json();
        OutputJson[k] = ljson;
    }
    return OutputJson;
}

void MaterialList::edit_from_json(nlohmann::json InputJson)
{
    int NumberOfMaterial = InputJson.size();
    Material lMaterial(0,"void");
    if (NumberOfMaterial < 1)
    {
        std::clog << "Warning, json size is too small... Is it a list of material? Material list is reset" << std::endl;
        reset();
    }
    else
    {
        std::vector<Material> lv(NumberOfMaterial, lMaterial);
        for (int k=1 ; k<NumberOfMaterial ; k++)
        {
            lMaterial.edit_from_json(InputJson[k]);
            lv[k] = lMaterial;
        }
        MaterialVector = lv;
    }
}
