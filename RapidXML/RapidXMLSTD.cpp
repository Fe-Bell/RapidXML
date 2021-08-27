#include "RapidXMLSTD.hpp"

/**Creates a new XML file
* @param filePath - Reads a xml file
* @returns A xml document*/
XMLDocument* CreateXMLFromFile(const std::string& filePath)
{
	if (filePath.empty())
		return nullptr;

	XMLFile xmlFile(filePath.c_str());

	XMLDocument* doc = new XMLDocument();;
	doc->parse<0>(xmlFile.data());

	return doc;
}
/**Creates a new XML file
* @param version - the version of the XML format
* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
* @returns A xml document*/
XMLDocument* CreateXML(const uint8_t& version, const std::string& encoding)
{
	XMLDocument* doc = new XMLDocument();
	SetHeader(doc, version, encoding);

	return doc;
}
/**Writes the header of an xml file
* @param doc - A xml document object
* @param version - the version of the XML format
* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
* @returns True if success*/
const bool SetHeader(XMLDocument* doc, const uint8_t& version, const std::string& encoding)
{
	if (!doc)
		return false;

	XMLElement* decl = doc->allocate_node(rapidxml::node_type::node_declaration);

	char buf[10];
	sprintf_s(buf, 10, "%d.0", version);

	const char* _versionVal = doc->allocate_string(buf);
	decl->append_attribute(doc->allocate_attribute("version", _versionVal));

	const char* _encodingVal = doc->allocate_string(encoding.c_str());
	decl->append_attribute(doc->allocate_attribute("encoding", _encodingVal));

	doc->append_node(decl);
	return true;
}
/**Sets the default xsi and xsd namespaces
* @param doc - A xml document object
* @param node - The element to set the namespace
* @returns True if success*/
const bool SetNodeDefaultNamespaces(XMLDocument* doc, XMLElement* node)
{
	return SetNodeNamespaces(doc, node, "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/2001/XMLSchema");
}
/**Sets the xmlns:xsi and xmlns:xsd namespaces
* @param doc - A xml document object
* @param node - The element to set the namespace
* @param xsi - The xsi address
* @param xsd - The xds address
* @returns True if success*/
const bool SetNodeNamespaces(XMLDocument* doc, XMLElement* node, const std::string& xsi, const std::string& xsd)
{
	if (!node)
		return false;

	node->append_attribute(CreateAttribute(doc, XML_XMLNS_XSI, xsi));
	node->append_attribute(CreateAttribute(doc, XML_XMLNS_XSD, xsd));
	return true;
}
/**Disposes resources.
* @param doc - A xml document object
* @returns True if success*/
const bool FreeXML(XMLDocument* doc)
{
	if (!doc)
		return false;

	doc->clear();
	delete (doc);
	return true;
}
/**Saves and XML object to a file
* @param doc - A xml document object
* @param filePath - The path to an xml file
* @returns True if success*/
const bool SaveXML(const XMLDocument& doc, const std::string& filePath)
{
	// Save to file
	std::ofstream file_stored(filePath);
	file_stored << doc;
	file_stored.close();

	return true;
}
/**Creates an attribute
* @param doc - A xml document object
* @param attributeName - The name of the attribute
* @param attributeValue - The value of the attribute
* @returns True if success*/
XMLAttributte* CreateAttribute(XMLDocument* doc, const std::string& attributeName, const std::string& attributeValue)
{
	if (!doc || attributeName.empty())
		return nullptr;

	const char* name = doc->allocate_string(attributeName.c_str());
	const char* value = doc->allocate_string(attributeValue.c_str());
	return doc->allocate_attribute(name, value);
}
/**Creates a node
* @param doc - A xml document object
* @param nodeName - The name of the node
* @param nodeValue - The value of the node
* @returns True if success*/
XMLElement* CreateNode(XMLDocument* doc, const std::string& nodeName, const std::string& nodeValue)
{
	if (!doc || nodeName.empty())
		return nullptr;

	const char* name = doc->allocate_string(nodeName.c_str());
	if (!nodeValue.empty())
	{
		const char* value = doc->allocate_string(nodeValue.c_str());
		return doc->allocate_node(rapidxml::node_type::node_element, name, value);
	}
	else
	{
		return doc->allocate_node(rapidxml::node_type::node_element, name);
	}
}
/**Creates a node
* @param doc - A xml document object
* @param nodeName - The name of the node
* @param subNodes - An array of nodes
* @param subNodesCount - The number of nodes to add
* @returns True if success*/
XMLElement* CreateNodeA(XMLDocument* doc, const std::string& nodeName, XMLElement** subNodes, const size_t& subNodesCount)
{
	if (!doc || nodeName.empty() || !subNodes || subNodesCount <= 0)
		return nullptr;

	const char* name = doc->allocate_string(nodeName.c_str());
	XMLElement* n = doc->allocate_node(rapidxml::node_type::node_element, name);
	for (size_t i = 0; i < subNodesCount; i++)
	{
		auto sn = subNodes[i];
		if (sn)
		{
			n->append_node(sn);
		}
	}
	
	return n;
}
/**Creates a node
* @param doc - A xml document object
* @param nodeName - The name of the node
* @returns True if success*/
XMLElement* FindNodeInRoot(XMLDocument* doc, const std::string& nodeName)
{
	if (!doc || nodeName.empty())
		return nullptr;

	for (XMLElement* x = doc->first_node(); x; x = x->next_sibling())
	{
		if (x && std::string(x->name()) == nodeName)
		{
			return x;
		}
	}
	return nullptr;
}
/**Adds a node to a xml document
* @param doc - A xml document object
* @param node - The element add
* @returns True if success*/
const bool AddNodeToDocument(XMLDocument* doc, XMLElement* node)
{
	if (!doc || !node)
	{
		return false;
	}

	doc->append_node(node);
	return true;
}
/**Adds a node to another node
* @param parent - The parent element
* @param child - The child element
* @returns True if success*/
const bool AddNodeToNode(XMLElement* parent, XMLElement* child)
{
	if (!parent || !child)
	{
		return false;
	}

	parent->append_node(child);
	return true;
}
/**Adds an attribute to a node
* @param parent - The parent element
* @param child - The child element
* @returns True if success*/
const bool AddAttributeToNode(XMLElement* parent, XMLAttributte* child)
{
	if (!parent || !child)
	{
		return false;
	}

	parent->append_attribute(child);
	return true;
}