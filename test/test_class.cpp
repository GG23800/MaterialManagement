#include<iostream>

#include"material.hpp"

int main (int argc, char *argv[])
{
    std::cout << "Bazinga!" << std::endl;

    // Material
    material ma(0), mb(3,"lulu"), mc(51);
    mc = mb;
    nlohmann::json ja,jb,jc;
    ja = ma.get_json();
    jb = mb.get_json();
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mb.edit_ID(23);
    mb.edit_name("toto");
    jb = mb.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    mc.edit_from_json(jb);
    jc = mc.get_json();

    std::cout << "material a json: " << ja << std::endl;
    std::cout << "material b json: " << jb << std::endl;
    std::cout << "material c json: " << jc << std::endl;

    // heat material
    heat_material hm1(42);
    std::cout << "hm1 json: " << hm1.get_json() << std::endl;
    heat_material hm2(2,"lala",2.f,1.5f,6.f);
    std::cout << "hm2 json: " << hm2.get_json() << std::endl;
    heat_material hm3(mc,4.6f,0.23f,9.87f);
    std::cout << "hm3 json: " << hm3.get_json() << std::endl;
    heat_material cchm(hm2);
    std::cout << "copy constructor from hm2: " << cchm.get_json() << std::endl;
    cchm = hm3;
    std::cout << "copy assignement from hm3: " << cchm.get_json() << std::endl;

    hm3.edit_ID(199);
    hm3.edit_name("tralala");
    hm3.edit_from_json(hm2.get_json());
    std::cout << "copy from json hm2: " << hm3.get_json() << std::endl;

    // Material list
    MaterialList nml;
    std::cout << "new material list: " << nml.get_json() << std::endl;
    nml.add_material(ma);
    nml.add_material(mb);
    nml.add_material(mc);
    std::cout << "adding material a, b and c: " << nml.get_json() << std::endl;
    nml.delete_material(2);
    std::cout << "delete material 2: " << nml.get_json() << std::endl;
    nml.reset();
    std::cout << "reset list: " << nml.get_json() << std::endl;

    return 0;
}
