#pragma once
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_ext.hpp"
#include <string>

#define XML_XSI_TYPE						"xsi:type"
#define XML_XMLNS_XSI						"xmlns:xsi"
#define XML_XMLNS_XSD						"xmlns:xsd"

extern "C"
{
	/**Creates a new XML file
	* @param version - the version of the XML format
	* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
	* @returns A xml document*/
	__declspec(dllexport) rapidxml::xml_document<>* CreateXML(const uint8_t& version, const std::string& encoding);
	/**Disposes resources.
	* @param doc - A xml document object
	* @returns True if success*/
	__declspec(dllexport) const bool FreeXML(rapidxml::xml_document<>* doc);
	/**Saves and XML object to a file
	* @param doc - A xml document object
	* @param filePath - The path to an xml file
	* @returns True if success*/
	__declspec(dllexport) const bool SaveXML(const rapidxml::xml_document<>& doc, const std::string& filePath);
	/**Writes the header of an xml file
	* @param doc - A xml document object
	* @param version - the version of the XML format
	* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
	* @returns True if success*/
	__declspec(dllexport) const bool SetHeader(rapidxml::xml_document<>* doc, const uint8_t& version, const std::string& encoding);
	/**Sets the default xsi and xsd namespaces
	* @param doc - A xml document object
	* @param node - The element to set the namespace
	* @returns True if success*/
	__declspec(dllexport) const bool SetNodeDefaultNamespaces(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* node);
	/**Sets the xmlns:xsi and xmlns:xsd namespaces
	* @param doc - A xml document object
	* @param node - The element to set the namespace
	* @param xsi - The xsi address
	* @param xsd - The xds address
	* @returns True if success*/
	__declspec(dllexport) const bool SetNodeNamespaces(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* node, const std::string& xsi, const std::string& xsd);
	/**Adds a node to a xml document
	* @param doc - A xml document object
	* @param node - The element add
	* @returns True if success*/
	__declspec(dllexport) const bool AddNodeToDocument(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* node);
	/**Adds a node to another node
	* @param parent - The parent element
	* @param child - The child element
	* @returns True if success*/
	__declspec(dllexport) const bool AddNodeToNode(rapidxml::xml_node<>* parent, rapidxml::xml_node<>* child);
	/**Adds an attribute to a node
	* @param parent - The parent element
	* @param child - The child element
	* @returns True if success*/
	__declspec(dllexport) const bool AddAttributeToNode(rapidxml::xml_node<>* parent, rapidxml::xml_attribute<>* child);
	/**Creates an attribute
	* @param doc - A xml document object
	* @param attributeName - The name of the attribute
	* @param attributeValue - The value of the attribute
	* @returns True if success*/
	__declspec(dllexport) rapidxml::xml_attribute<>* CreateAttribute(rapidxml::xml_document<>* doc, const std::string& attributeName, const std::string& attributeValue = "");
	/**Creates a node
	* @param doc - A xml document object
	* @param nodeName - The name of the node
	* @param nodeValue - The value of the node
	* @returns True if success*/
	__declspec(dllexport) rapidxml::xml_node<>* CreateNode(rapidxml::xml_document<>* doc, const std::string& nodeName, const std::string& nodeValue = "");
	/**Creates a node
	* @param doc - A xml document object
	* @param nodeName - The name of the node
	* @param subNodes - An array of nodes
	* @param subNodesCount - The number of nodes to add
	* @returns True if success*/
	__declspec(dllexport) rapidxml::xml_node<>* CreateNodeA(rapidxml::xml_document<>* doc, const std::string& nodeName, rapidxml::xml_node<>** subNodes, const size_t& subNodesCount);
}