#include <iostream>
#include "../RapidXML/rapidxml.hpp"
#include "../RapidXML/rapidxml_utils.hpp"
#include "../RapidXML/RapidXMLSTD.hpp"

void ReadXML();
void WriteXML();

int main()
{
    std::cout << "Hello Example!\n";

    ReadXML();
    WriteXML();

	int ret = getchar();
}

void ReadXML()
{
	std::string error;

	//load file
	XMLFile* file = ::OpenXMLFile("ReadExample.xml", error);
	if (!file)
	{
		std::cout << error << std::endl;
		return;
	}

	XMLDocument* xml = ::CreateXMLFromFile(file, error);
	if (!xml)
	{
		std::cout << error << std::endl;
		::DisposeXMLFile(file);
		return;
	}

	//find root
	XMLElement* root = ::FirstOrDefaultElement(xml, "RootElement", error);
	if (!root)
	{
		std::cout << error << std::endl;
		::DisposeXMLObject(xml);
		::DisposeXMLFile(file);
		return;
	}

	//Reading an attribute
	auto xml_RootAttrib = root->first_attribute("Attribute");
	if (!xml_RootAttrib)
	{
		std::cout << "Could not find attribute in root." << std::endl;
		::DisposeXMLObject(xml);
		::DisposeXMLFile(file);
		return;
	}

	char* valueAsStr = xml_RootAttrib->value();
	int valueAsNumber = atoi(valueAsStr);

	//Reading an array of elements
	XMLElement* xml_ElmentArray = root->first_node("ElementArray");
	if (!xml_ElmentArray)
	{
		std::cout << "Could not find ElmentArray xml element." << std::endl;
		::DisposeXMLObject(xml);
		::DisposeXMLFile(file);
		return;
	}
	
	//Loops through all the elements with the name "Element"
	for (XMLElement* xml_Element = xml_ElmentArray->first_node("Element"); xml_Element; xml_Element = xml_Element->next_sibling())
	{
		if (!xml_Element)
		{
			printf("Element is not valid.\n");
			continue;
		}

		std::cout << xml_Element->value() << std::endl;
	}

	::DisposeXMLObject(xml);
	::DisposeXMLFile(file);
}

void WriteXML()
{
	std::string error;
	auto doc = ::CreateXML(1, "utf-8", error);
	if (!doc)
	{
		std::cout << error << std::endl;
		return;
	}

	auto root = ::CreateElement(doc, "ROOT", "", error);
	if (!root)
	{
		std::cout << error << std::endl;
		::DisposeXMLObject(doc);
		return;
	}

	if (!::AddElementToDocument(doc, root, error))
	{
		std::cout << error << std::endl;
		::DisposeXMLObject(doc);
		return;
	}

	if (!SetElementDefaultNamespaces(doc, root, error))
	{
		std::cout << error << std::endl;
		::DisposeXMLObject(doc);
		return;
	}

	for (size_t i = 0; i < 5; i++)
	{
		auto x = ::CreateElement(doc, "Node", "", error);
		if (!x)
		{
			std::cout << error << std::endl;
			continue;
		}

		auto a = ::CreateAttribute(doc, "ID", std::to_string(i), error);
		if (!a)
		{
			std::cout << error << std::endl;
			continue;
		}

		if (!::AddAttributeToElement(x, a, error))
		{
			std::cout << error << std::endl;
			continue;
		}

		if (!::AddElementToElement(root, x, error))
		{
			std::cout << error << std::endl;
			continue;
		}
	}	

	if (!::SaveXML(*doc, "test.xml"))
	{
		std::cout << "Could not create file" << std::endl;
	}
	::DisposeXMLObject(doc);
}