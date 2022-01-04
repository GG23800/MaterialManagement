#include "material.hpp"

material::material(int nID, std::string nName)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material constructor" << std::endl;
    #endif
    edit_material(nID, nName);
}

material::material(const material &other) // copy constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material copy constructor" << std::endl;
    #endif
    ID = other.ID;
    Name = other.Name;
}

material& material::operator=(const material &other) //copy assignement operator
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

material::material(material &&other) //move constructor
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

material& material::operator=(material &&other) //move assignement operator
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

material::~material()
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Material destructor" << std::endl;
    #endif
}


void material::edit_material(const int nID, const std::string nName)
{
    ID = nID;
    Name = nName;
}

void material::edit_material(const material OtherMaterial)
{
    ID = OtherMaterial.ID;
    Name = OtherMaterial.Name;
}

void material::edit_from_json(const nlohmann::json input_json)
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
        std::cout << "Warning, material::edit_material_from_json(), ID not found in input json" << std::endl;
    }
    if (input_json.find("Name") != input_json.end())
    {
        lName = input_json["Name"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, material::edit_material_from_json(), Name not found in input json" << std::endl;
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
}

void material::edit_ID(const int nID)
{
    ID = nID;
}

void material::edit_name(const std::string nName)
{
    Name = nName;
}

nlohmann::json material::get_json()
{
    nlohmann::json ljson = nlohmann::json{};
    ljson["ID"] = ID;
    ljson["Name"] = Name;

    return ljson;
}





heat_material::heat_material(int nID, std::string nName, float nDensity, float nSpecificHeat, float nThermalConductivity) : material(nID, nName)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material constructor" << std::endl;
    #endif
    Density = nDensity;
    SpecificHeat = nSpecificHeat;
    ThermalConductivity = nThermalConductivity;
}

heat_material::heat_material(material nMaterial, float nDensity, float nSpecificHeat, float nThermalConductivity) : material(nMaterial)
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material constructor with material parameter" << std::endl;
    #endif
    Density = nDensity;
    SpecificHeat = nSpecificHeat;
    ThermalConductivity = nThermalConductivity;
}

heat_material::heat_material(const heat_material &other) : material(other) // copy constructor
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material copy constructor" << std::endl;
    #endif
    Density = other.Density;
    SpecificHeat = other.SpecificHeat;
    ThermalConductivity = other.ThermalConductivity;
}

heat_material& heat_material::operator=(const heat_material &other) //copy assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material copy assignement operator" << std::endl;
    #endif
    if (this != &other)
    {
        material::operator=(other);
        // or
        //using material::operator=;
        Density = other.Density;
        SpecificHeat = other.SpecificHeat;
        ThermalConductivity = other.ThermalConductivity;
    }
    return *this;
}

heat_material::heat_material(heat_material &&other) : material(other) //move constructor
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

heat_material& heat_material::operator=(heat_material &&other) //move assignement operator
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material move assignement operator" << std::endl;
    #endif
   if (this != &other)
    {
        material::operator=(other);
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

heat_material::~heat_material()
{
    #if MATERIAL_VERBOSE == 1
        std::cout << "Heat Material destructor" << std::endl;
    #endif
}

void heat_material::edit_density(float nDensity)
{
    Density = nDensity;
}
void heat_material::edit_specific_heat(float nSpecificHeat)
{
    SpecificHeat = nSpecificHeat;
}
void heat_material::edit_thermal_conductivity(float nThermalConductivity)
{
    ThermalConductivity = nThermalConductivity;
}

void heat_material::edit_from_json(nlohmann::json input_json)
{
    int lerror = 0;
    float lDensity=0.f, lSpecificHeat=0.f, lThermalConductivity=0.f;
    if (input_json.find("ID") != input_json.end())
    {
        lDensity = input_json["Density"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, heat_material::edit_from_json(), Density not found in input json" << std::endl;
    }
    if (input_json.find("SpecificHeat") != input_json.end())
    {
        lSpecificHeat = input_json["SpecificHeat"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, heat_material::edit_from_json(), SpecificHeat not found in input json" << std::endl;
    }
    if (input_json.find("ThermalConductivity") != input_json.end())
    {
        lThermalConductivity = input_json["ThermalConductivity"];
    }
    else 
    {
        lerror = 1;
        std::cout << "Warning, heat_material::edit_from_json(), ThermalConductivity not found in input json" << std::endl;
    }

    if (!lerror)
    {
        material::edit_from_json(input_json);
        Density = lDensity;
        SpecificHeat = lSpecificHeat;
        ThermalConductivity = lThermalConductivity;
    }
    else
    {
        std::cout << "Problem with input json, heat material not edited" << std::endl;
    }
}
