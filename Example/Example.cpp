#include <iostream>
#include "../RapidXML/rapidxml.hpp"
#include "../RapidXML/rapidxml_utils.hpp"
#include "../RapidXML/rapidxml_ext.hpp"
#include "../RapidXML/RapidXMLC.hpp"

void ReadXML();
void WriteXML();

int main()
{
    std::cout << "Hello Example!\n";

    //int ret = getchar();

    //ReadXML();

    //ret = getchar();

    WriteXML();

	int ret = getchar();
}

void ReadXML()
{
	//load file
	rapidxml::file<> xmlFile("ReadExample.xml");
	rapidxml::xml_document<>* xml = new rapidxml::xml_document<>();
	if (xml)
	{
		char* xmlData = xmlFile.data();
		if (xmlData)
		{
			xml->parse<0>(xmlData);

			//find root
			rapidxml::xml_node<>* root = xml->first_node();
			if (root)
			{
				//Reading an attribute
				auto xml_RootAttrib = root->first_attribute("Attribute");
				if (xml_RootAttrib)
				{
					char* valueAsStr = xml_RootAttrib->value();
					int valueAsNumber = atoi(valueAsStr);
				}
				else
				{
					printf("Could not find attribute in root.\n");
				}

				//Reading an array of elements
				rapidxml::xml_node<char>* xml_ElmentArray = root->first_node("ElementArray");
				if (xml_ElmentArray)
				{
					//Loops through all the elements with the name "Element"
					for (rapidxml::xml_node<>* xml_Element = xml_ElmentArray->first_node("Element"); xml_Element; xml_Element = xml_Element->next_sibling())
					{ 
						if (xml_Element)
						{
							char* valueAsStr = xml_Element->value();
						}
						else
						{
							printf("Element is not valid.\n");
						}
					}
				}
				else
				{
					printf("Could not find ElmentArray xml element.\n");
				}
			}
			else
			{
				printf("Could not find root.\n");
			}
		}
		else
		{
			printf("No xml data.\n");
		}

		delete(xml);
	}
	else
	{
		//XML object not created
	}
}

void WriteXML()
{
	auto doc = ::CreateXML(1, "utf-8");

	auto root = ::CreateNode(doc, "ROOT", "");
	if (!::AddNodeToDocument(doc, root))
	{
		std::cout << "Could not add root" << std::endl;
		::FreeXML(doc);
		return;
	}

	if (!SetNodeDefaultNamespaces(doc, root))
	{
		std::cout << "Could not set namespaces" << std::endl;
		::FreeXML(doc);
		return;
	}

	for (size_t i = 0; i < 5; i++)
	{
		auto x = ::CreateNode(doc, "Node", "");
		auto a = ::CreateAttribute(doc, "ID", std::to_string(i));		
		::AddAttributeToNode(x, a);
		::AddNodeToNode(root, x);
	}	

	if (!::SaveXML(*doc, "test.xml"))
	{
		std::cout << "Could not create file" << std::endl;
	}
	::FreeXML(doc);
}