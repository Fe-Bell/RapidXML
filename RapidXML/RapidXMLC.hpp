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
	/**Creates a new XML file*/
	__declspec(dllexport) rapidxml::xml_document<>* CreateXML(const uint8_t& version, const std::string& encoding);
	/**Writes the header of an xml file
	* @param doc - A xml document object
	* @param version - the version of the XML format
	* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
	* @returns True if success*/
	__declspec(dllexport) const bool SetHeader(rapidxml::xml_document<>** doc, const uint8_t& version, const std::string& encoding);
	__declspec(dllexport) const bool SetNodeDefaultNamespaces(rapidxml::xml_document<>** doc, rapidxml::xml_node<>** node);
	__declspec(dllexport) const bool SetNodeNamespaces(rapidxml::xml_document<>** doc, rapidxml::xml_node<>** node, const std::string& xsi, const std::string& xsd);
	/**Disposes resources.
	* @param doc - A xml document object
	* @returns True if success*/
	__declspec(dllexport) const bool FreeXML(rapidxml::xml_document<>** doc);
	/**Saves and XML object to a file
	* @param doc - A xml document object
	* @param filePath - The path to an xml file
	* @returns True if success*/
	__declspec(dllexport) const bool SaveXML(rapidxml::xml_document<>** doc, const std::string& filePath);

	__declspec(dllexport) rapidxml::xml_attribute<>* CreateAttribute(rapidxml::xml_document<>** doc, const std::string& attributeName, const std::string& attributeValue);
	__declspec(dllexport) rapidxml::xml_node<>* CreateNode(rapidxml::xml_document<>** doc, const std::string& nodeName, const std::string& nodeValue);
}