#pragma warning(push)
#pragma warning(disable: 6495)   // Conditional expression is constant
#include "gtest/gtest.h"
#pragma warning(pop)
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "RapidXMLSTD.hpp"

TEST(BasicTests, BasicReadXML) 
{
	std::string error;

	//load file
	XMLFile* file = ::OpenXMLFile("./Assets/ReadExample.xml", error);
	EXPECT_TRUE(file) << error;

	XMLDocument* xml = ::CreateXMLFromFile(file, error);
	EXPECT_TRUE(xml) << [file, error]()->std::string 
		{ 
			::DisposeXMLFile(file);
			return error; 
		}();

	//find root
	XMLElement* root = ::FirstOrDefaultElement(xml, "RootElement", error);
	EXPECT_TRUE(root) << [xml, file, error]()->std::string
		{
			::DisposeXMLObject(xml);
			::DisposeXMLFile(file);
			return error;
		}();

	//Reading an attribute
	XMLAttributte* xml_RootAttrib = root->first_attribute("Attribute");
	EXPECT_TRUE(xml_RootAttrib) << [xml, file, error]()->std::string
		{
			::DisposeXMLObject(xml);
			::DisposeXMLFile(file);
			return "Could not find attribute in root.";
		}();

	char* valueAsStr = xml_RootAttrib->value();
	int valueAsNumber = atoi(valueAsStr);

	//Reading an array of elements
	XMLElement* xml_ElmentArray = root->first_node("ElementArray");
	EXPECT_TRUE(xml_ElmentArray) << [xml, file, error]()->std::string
		{
			::DisposeXMLObject(xml);
			::DisposeXMLFile(file);
			return "Could not find ElmentArray xml element.";
		}();

	//Loops through all the elements with the name "Element"
	for (XMLElement* xml_Element = xml_ElmentArray->first_node("Element"); xml_Element; xml_Element = xml_Element->next_sibling())
	{
		EXPECT_TRUE(xml_Element) << [xml, file, error]()->std::string
			{
				::DisposeXMLObject(xml);
				::DisposeXMLFile(file);
				return "Element is not valid.";
			}();

		std::cout << xml_Element->value() << std::endl;
	}

	::DisposeXMLObject(xml);
	::DisposeXMLFile(file);
}

TEST(BasicTests, BasicWriteXML)
{
	std::string error;
	XMLDocument* doc = ::CreateXML(1, "utf-8", error);
	EXPECT_TRUE(doc) << error;

	auto root = ::CreateElement(doc, "ROOT", "", error);
	EXPECT_TRUE(root) << [doc, error]()->std::string
		{
			::DisposeXMLObject(doc);
			return error;
		}();

	bool result = ::AddElementToDocument(doc, root, error);
	EXPECT_TRUE(result) << [doc, error]()->std::string
		{
			::DisposeXMLObject(doc);
			return error;
		}();

	result = ::SetElementDefaultNamespaces(doc, root, error);
	EXPECT_TRUE(result) << [doc, error]()->std::string
		{
			::DisposeXMLObject(doc);
			return error;
		}();

	for (size_t i = 0; i < 5; i++)
	{
		XMLElement* x = ::CreateElement(doc, "Node", "", error);
		EXPECT_TRUE(x) << [doc, error]()->std::string
			{
				::DisposeXMLObject(doc);
				return error;
			}();

		XMLAttributte* a = ::CreateAttribute(doc, "ID", std::to_string(i), error);
		EXPECT_TRUE(x) << [doc, error]()->std::string
			{
				::DisposeXMLObject(doc);
				return error;
			}();

		result = ::AddAttributeToElement(x, a, error);
		EXPECT_TRUE(result) << [doc, error]()->std::string
			{
				::DisposeXMLObject(doc);
				return error;
			}();

		result = ::AddElementToElement(root, x, error);
		EXPECT_TRUE(result) << [doc, error]()->std::string
		{
			::DisposeXMLObject(doc);
			return error;
		}();
	}

	result = ::SaveXML(*doc, "BasicWriteXML.xml");
	EXPECT_TRUE(result) << [doc, error]()->std::string
		{
			::DisposeXMLObject(doc);
			return "Could not create file";
		}();

	::DisposeXMLObject(doc);
}