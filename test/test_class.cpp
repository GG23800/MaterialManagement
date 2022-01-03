#include<iostream>

#include"material.hpp"

int main (int argc, char *argv[])
{
    std::cout << "Bazinga!" << std::endl;

    material ma, mb, mc;
    nlohmann::json ja,jb,jc;
    ja = ma.get_json();
    jb = mb.get_json();
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mb.edit_material_ID(23);
    mb.edit_material_name("toto");
    jb = mb.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mc.edit_material_from_json(jb);
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    return 0;
}
