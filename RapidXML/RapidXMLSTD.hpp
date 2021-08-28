#ifndef RAPIDXMLSTD
#define RAPIDXMLSTD

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_ext.hpp"
#include <string>

#define XML_XSI_TYPE	"xsi:type"
#define XML_XMLNS_XSI	"xmlns:xsi"
#define XML_XMLNS_XSD	"xmlns:xsd"

/**Defines basic RapidXML types with friendly names**/

typedef rapidxml::xml_document<> XMLDocument;
typedef rapidxml::xml_node<> XMLElement;
typedef rapidxml::xml_attribute<> XMLAttributte;
typedef rapidxml::file<> XMLFile;

extern "C"
{
	/**Opens a new XML file
	* @param filePath - The path to a file
	* @returns A xml file object*/
	__declspec(dllexport) XMLFile* OpenXMLFile(const std::string& filePath);
	/**Disposes resources.
	* @param doc - A xml object file
	* @returns True if success*/
	__declspec(dllexport) const bool FreeXMLFile(XMLFile* file);
	/**Creates a new XML file
	* @param file - The xml object file
	* @returns A xml document*/
	__declspec(dllexport) XMLDocument* CreateXMLFromFile(XMLFile* file);
	/**Creates a new XML file
	* @param version - the version of the XML format
	* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
	* @returns A xml document*/
	__declspec(dllexport) XMLDocument* CreateXML(const uint8_t& version, const std::string& encoding);
	/**Disposes resources.
	* @param doc - A xml document object
	* @returns True if success*/
	__declspec(dllexport) const bool FreeXMLObject(XMLDocument* doc);
	/**Saves and XML object to a file
	* @param doc - A xml document object
	* @param filePath - The path to an xml file
	* @returns True if success*/
	__declspec(dllexport) const bool SaveXML(const XMLDocument& doc, const std::string& filePath);
	/**Writes the header of an xml file
	* @param doc - A xml document object
	* @param version - the version of the XML format
	* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
	* @returns True if success*/
	__declspec(dllexport) const bool SetHeader(XMLDocument* doc, const uint8_t& version, const std::string& encoding);
	/**Sets the default xsi and xsd namespaces
	* @param doc - A xml document object
	* @param node - The element to set the namespace
	* @returns True if success*/
	__declspec(dllexport) const bool SetNodeDefaultNamespaces(XMLDocument* doc, XMLElement* node);
	/**Sets the xmlns:xsi and xmlns:xsd namespaces
	* @param doc - A xml document object
	* @param node - The element to set the namespace
	* @param xsi - The xsi address
	* @param xsd - The xds address
	* @returns True if success*/
	__declspec(dllexport) const bool SetNodeNamespaces(XMLDocument* doc, XMLElement* node, const std::string& xsi, const std::string& xsd);
	/**Adds a node to a xml document
	* @param doc - A xml document object
	* @param node - The element add
	* @returns True if success*/
	__declspec(dllexport) const bool AddNodeToDocument(XMLDocument* doc, XMLElement* node);
	/**Adds a node to another node
	* @param parent - The parent element
	* @param child - The child element
	* @returns True if success*/
	__declspec(dllexport) const bool AddNodeToNode(XMLElement* parent, XMLElement* child);
	/**Adds an attribute to a node
	* @param parent - The parent element
	* @param child - The child element
	* @returns True if success*/
	__declspec(dllexport) const bool AddAttributeToNode(XMLElement* parent, XMLAttributte* child);
	/**Creates an attribute
	* @param doc - A xml document object
	* @param attributeName - The name of the attribute
	* @param attributeValue - The value of the attribute
	* @returns True if success*/
	__declspec(dllexport) XMLAttributte* CreateAttribute(XMLDocument* doc, const std::string& attributeName, const std::string& attributeValue = "");
	/**Creates a node
	* @param doc - A xml document object
	* @param nodeName - The name of the node
	* @param nodeValue - The value of the node
	* @returns True if success*/
	__declspec(dllexport) XMLElement* CreateNode(XMLDocument* doc, const std::string& nodeName, const std::string& nodeValue = "");
	/**Creates a node
	* @param doc - A xml document object
	* @param nodeName - The name of the node
	* @param subNodes - An array of nodes
	* @param subNodesCount - The number of nodes to add
	* @returns True if success*/
	__declspec(dllexport) XMLElement* CreateNodeA(XMLDocument* doc, const std::string& nodeName, XMLElement** subNodes, const size_t& subNodesCount);
	/**Creates a node
	* @param doc - A xml document object
	* @param nodeName - The name of the node
	* @returns True if success*/
	__declspec(dllexport) XMLElement* FindNodeInRoot(XMLDocument* doc, const std::string& nodeName);
};

#endif