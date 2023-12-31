#include "pugixml.hpp"

#include <iostream>

int main()
{
    pugi::xml_document doc;

    //[code_modify_add
    // add node with some name
    pugi::xml_node node = doc.append_child();
    node.set_name("node");

    // add description node with text child
    pugi::xml_node descr = node.append_child();
    descr.set_name("description");
    descr.append_child(pugi::node_pcdata).set_value("Simple node");

    // add param node before the description
    pugi::xml_node param = node.insert_child_before(pugi::node_element, descr);
    param.set_name("param");

    // add attributes to param node
    param.append_attribute("name") = "version";
    param.append_attribute("value") = 1.1;
    param.insert_attribute_after("type", param.attribute("name")) = "float";
    //]

    doc.print(std::cout);
}

// vim:et
