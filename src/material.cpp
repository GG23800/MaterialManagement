#include "material.hpp"

material::material(int nID, std::string nName)
{
    edit_material(nID, nName);
}

material& material::operator=(const material &other) //copy assignement operator
{
    if (this != &other)
    {
        ID = other.ID;
        Name = other.Name;
    }
    return *this;
}

material::material(material &&other) //move constructor
{
    ID = other.ID;
    Name = other.Name;
    //release other ressource (optinal here)
    other.ID = 0;
    other.Name = "";
}

material& material::operator=(material &&other) //move assignement operator
{
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

void material::edit_material_from_json(const nlohmann::json input_json)
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

void material::edit_material_ID(const int nID)
{
    ID = nID;
}

void material::edit_material_name(const std::string nName)
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
