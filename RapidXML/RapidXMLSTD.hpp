#ifndef RAPIDXMLSTD
#define RAPIDXMLSTD

// Copyright (C) 2019 https://github.com/Fe-Bell/RapidXML
// Version 1.17
// Revision $DateTime: 2023/09/19 23:27:00 $

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string>

#define XML_XSI_TYPE	"xsi:type"
#define XML_XMLNS_XSI	"xmlns:xsi"
#define XML_XMLNS_XSD	"xmlns:xsd"

/**Defines basic RapidXML types with friendly names**/

typedef rapidxml::xml_document<> XMLDocument;
typedef rapidxml::xml_node<> XMLElement;
typedef rapidxml::xml_attribute<> XMLAttributte;
typedef rapidxml::file<> XMLFile;

#if defined _WIN32 || defined _WIN64

/*If windows based*/
#define  DLL_EX __declspec(dllexport)
extern "C"
{
	/**Searches for a named element
	* @param parent - A xml element object
	* @param elementName - The name of the element
	* @param error - An error message
	* @returns The element, if success*/
	DLL_EX XMLElement* FirstOrDefaultElement(XMLElement* parent, const std::string& elementName, std::string& error);
	/**Searches for a named element
	* @param parent - A xml document object
	* @param elementName - The name of the element
	* @param error - An error message
	* @returns The element, if success*/
	DLL_EX XMLElement* FirstOrDefaultElementA(XMLDocument* parent, const std::string& elementName, std::string& error);
	/**Searches for a named attribute
	* @param parent - A xml document object
	* @param attributeName - The name of the attribute
	* @param error - An error message
	* @returns The attribute, if success*/
	DLL_EX XMLAttributte* FirstOrDefaultAttribute(XMLElement* parent, const std::string& attributeName, std::string& error);
	/**Sets the value of an attribute
	* @param attribute - The attribute
	* @param attributeValue - The value of the attribute
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetAttributeValue(XMLAttributte* attribute, const std::string& attributeValue, std::string& error);
	/**Sets the value of an attribute
	* @param element - The attribute parent
	* @param attributeName - The attribute name
	* @param attributeValue - The value of the attribute
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetAttributeValueA(XMLElement* element, const std::string& attributeName, const std::string& attributeValue, std::string& error);
	/**Sets the value of an attribute
	* @param parent - The element's parent
	* @param child - The element
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetElementValue(XMLElement* parent, XMLElement* child, std::string& error);
	/**Sets the value of an attribute
	* @param element - The element
	* @param elementValue - The element value
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetElementValueA(XMLElement* element, const std::string& elementValue, std::string& error);
	/**Opens a new XML file
	* @param filePath - The path to a file
	* @param error - An error message
	* @returns A xml file object*/
	DLL_EX XMLFile* OpenXMLFile(const std::string& filePath, std::string& error);
	/**Disposes resources.
	* @param doc - A xml object file
	* @returns True if success*/
	DLL_EX const bool DisposeXMLFile(XMLFile* file);
	/**Creates a new XML file
	* @param file - The xml object file
	* @param error - An error message
	* @returns A xml document*/
	DLL_EX XMLDocument* CreateXMLFromFile(XMLFile* file, std::string& error);
	/**Creates a new XML file
	* @param version - the version of the XML format
	* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
	* @param error - An error message
	* @returns A xml document*/
	DLL_EX XMLDocument* CreateXML(const uint8_t& version, const std::string& encoding, std::string& error);
	/**Disposes resources.
	* @param doc - A xml document object
	* @returns True if success*/
	DLL_EX const bool DisposeXMLObject(XMLDocument* doc);
	/**Saves and XML object to a file
	* @param doc - A xml document object
	* @param filePath - The path to an xml file
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SaveXML(const XMLDocument& doc, const std::string& filePath);
	/**Writes the header of an xml file
	* @param doc - A xml document object
	* @param version - the version of the XML format
	* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetHeader(XMLDocument* doc, const uint8_t& version, const std::string& encoding, std::string& error);
	/**Sets the default xsi and xsd namespaces
	* @param doc - A xml document object
	* @param element - The element to set the namespace
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetElementDefaultNamespaces(XMLDocument* doc, XMLElement* element, std::string& error);
	/**Sets the xmlns:xsi and xmlns:xsd namespaces
	* @param doc - A xml document object
	* @param element - The element to set the namespace
	* @param xsi - The xsi address
	* @param xsd - The xds address
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool SetElementNamespaces(XMLDocument* doc, XMLElement* element, const std::string& xsi, const std::string& xsd, std::string& error);
	/**Adds an element to a xml document
	* @param doc - A xml document object
	* @param element - The element add
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool AddElementToDocument(XMLDocument* doc, XMLElement* element, std::string& error);
	/**Adds a element to another element
	* @param parent - The parent element
	* @param child - The child element
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool AddElementToElement(XMLElement* parent, XMLElement* child, std::string& error);
	/**Adds an attribute to a element
	* @param parent - The parent element
	* @param child - The child element
	* @param error - An error message
	* @returns True if success*/
	DLL_EX const bool AddAttributeToElement(XMLElement* parent, XMLAttributte* child, std::string& error);
	/**Creates an attribute
	* @param doc - A xml document object
	* @param attributeName - The name of the attribute
	* @param attributeValue - The value of the attribute
	* @param error - An error message
	* @returns True if success*/
	DLL_EX XMLAttributte* CreateAttribute(XMLDocument* doc, const std::string& attributeName, const std::string& attributeValue, std::string& error);
	/**Creates a element
	* @param doc - A xml document object
	* @param elementName - The name of the element
	* @param elementValue - The value of the element
	* @param error - An error message
	* @returns True if success*/
	DLL_EX XMLElement* CreateElement(XMLDocument* doc, const std::string& elementName, const std::string& elementValue, std::string& error);
	/**Creates a element
	* @param doc - A xml document object
	* @param elementName - The name of the element
	* @param subElements - An array of elements
	* @param subElementCount - The number of elements to add
	* @param error - An error message
	* @returns True if success*/
	DLL_EX XMLElement* CreateElementA(XMLDocument* doc, const std::string& elementName, XMLElement** subElements, const size_t& subElementCount, std::string& error);
};

/*If unix based*/
#else
/**Searches for a named element
	* @param parent - A xml element object
	* @param elementName - The name of the element
	* @param error - An error message
	* @returns The element, if success*/
XMLElement* FirstOrDefaultElement(XMLElement* parent, const std::string& elementName, std::string& error);
/**Searches for a named element
* @param parent - A xml document object
* @param elementName - The name of the element
* @param error - An error message
* @returns The element, if success*/
XMLElement* FirstOrDefaultElementA(XMLDocument* parent, const std::string& elementName, std::string& error);
/**Searches for a named attribute
* @param parent - A xml document object
* @param attributeName - The name of the attribute
* @param error - An error message
* @returns The attribute, if success*/
XMLAttributte* FirstOrDefaultAttribute(XMLElement* parent, const std::string& attributeName, std::string& error);
/**Sets the value of an attribute
* @param attribute - The attribute
* @param attributeValue - The value of the attribute
* @param error - An error message
* @returns True if success*/
const bool SetAttributeValue(XMLAttributte* attribute, const std::string& attributeValue, std::string& error);
/**Sets the value of an attribute
* @param element - The attribute parent
* @param attributeName - The attribute name
* @param attributeValue - The value of the attribute
* @param error - An error message
* @returns True if success*/
const bool SetAttributeValueA(XMLElement* element, const std::string& attributeName, const std::string& attributeValue, std::string& error);
/**Sets the value of an attribute
* @param parent - The element's parent
* @param child - The element
* @param error - An error message
* @returns True if success*/
const bool SetElementValue(XMLElement* parent, XMLElement* child, std::string& error);
/**Sets the value of an attribute
* @param element - The element
* @param elementValue - The element value
* @param error - An error message
* @returns True if success*/
const bool SetElementValueA(XMLElement* element, const std::string& elementValue, std::string& error);
/**Opens a new XML file
* @param filePath - The path to a file
* @param error - An error message
* @returns A xml file object*/
XMLFile* OpenXMLFile(const std::string& filePath, std::string& error);
/**Disposes resources.
* @param doc - A xml object file
* @returns True if success*/
const bool DisposeXMLFile(XMLFile* file);
/**Creates a new XML file
* @param file - The xml object file
* @param error - An error message
* @returns A xml document*/
XMLDocument* CreateXMLFromFile(XMLFile* file, std::string& error);
/**Creates a new XML file
* @param version - the version of the XML format
* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
* @param error - An error message
* @returns A xml document*/
XMLDocument* CreateXML(const uint8_t& version, const std::string& encoding, std::string& error);
/**Disposes resources.
* @param doc - A xml document object
* @returns True if success*/
const bool DisposeXMLObject(XMLDocument* doc);
/**Saves and XML object to a file
* @param doc - A xml document object
* @param filePath - The path to an xml file
* @param error - An error message
* @returns True if success*/
const bool SaveXML(const XMLDocument& doc, const std::string& filePath);
/**Writes the header of an xml file
* @param doc - A xml document object
* @param version - the version of the XML format
* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
* @param error - An error message
* @returns True if success*/
const bool SetHeader(XMLDocument* doc, const uint8_t& version, const std::string& encoding, std::string& error);
/**Sets the default xsi and xsd namespaces
* @param doc - A xml document object
* @param element - The element to set the namespace
* @param error - An error message
* @returns True if success*/
const bool SetElementDefaultNamespaces(XMLDocument* doc, XMLElement* element, std::string& error);
/**Sets the xmlns:xsi and xmlns:xsd namespaces
* @param doc - A xml document object
* @param element - The element to set the namespace
* @param xsi - The xsi address
* @param xsd - The xds address
* @param error - An error message
* @returns True if success*/
const bool SetElementNamespaces(XMLDocument* doc, XMLElement* element, const std::string& xsi, const std::string& xsd, std::string& error);
/**Adds an element to a xml document
* @param doc - A xml document object
* @param element - The element add
* @param error - An error message
* @returns True if success*/
const bool AddElementToDocument(XMLDocument* doc, XMLElement* element, std::string& error);
/**Adds a element to another element
* @param parent - The parent element
* @param child - The child element
* @param error - An error message
* @returns True if success*/
const bool AddElementToElement(XMLElement* parent, XMLElement* child, std::string& error);
/**Adds an attribute to a element
* @param parent - The parent element
* @param child - The child element
* @param error - An error message
* @returns True if success*/
const bool AddAttributeToElement(XMLElement* parent, XMLAttributte* child, std::string& error);
/**Creates an attribute
* @param doc - A xml document object
* @param attributeName - The name of the attribute
* @param attributeValue - The value of the attribute
* @param error - An error message
* @returns True if success*/
XMLAttributte* CreateAttribute(XMLDocument* doc, const std::string& attributeName, const std::string& attributeValue, std::string& error);
/**Creates a element
* @param doc - A xml document object
* @param elementName - The name of the element
* @param elementValue - The value of the element
* @param error - An error message
* @returns True if success*/
XMLElement* CreateElement(XMLDocument* doc, const std::string& elementName, const std::string& elementValue, std::string& error);
/**Creates a element
* @param doc - A xml document object
* @param elementName - The name of the element
* @param subElements - An array of elements
* @param subElementCount - The number of elements to add
* @param error - An error message
* @returns True if success*/
XMLElement* CreateElementA(XMLDocument* doc, const std::string& elementName, XMLElement** subElements, const size_t& subElementCount, std::string& error);
#endif


#endif