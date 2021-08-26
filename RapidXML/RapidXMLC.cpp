#include "RapidXMLC.hpp"

/**Creates a new XML file*/
rapidxml::xml_document<>* CreateXML(const uint8_t& version, const std::string& encoding)
{
	rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
	SetHeader(&doc, version, encoding);

	return doc;
}
/**Writes the header of an xml file*/
const bool SetHeader(rapidxml::xml_document<>** doc, const uint8_t& version, const std::string& encoding)
{
	if (!doc || !(*doc))
		return false;

	rapidxml::xml_node<>* decl = (*doc)->allocate_node(rapidxml::node_type::node_declaration);

	char buf[10];
	sprintf_s(buf, 10, "%d.0", version);

	const char* _versionVal = (*doc)->allocate_string(buf);
	decl->append_attribute((*doc)->allocate_attribute("version", _versionVal));

	const char* _encodingVal = (*doc)->allocate_string(encoding.c_str());
	decl->append_attribute((*doc)->allocate_attribute("encoding", _encodingVal));

	(*doc)->append_node(decl);
	return true;
}
const bool SetNodeDefaultNamespaces(rapidxml::xml_document<>** doc, rapidxml::xml_node<>** node)
{
	return SetNodeNamespaces(doc, node, "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/2001/XMLSchema");
}
const bool SetNodeNamespaces(rapidxml::xml_document<>** doc, rapidxml::xml_node<>** node, const std::string& xsi, const std::string& xsd)
{
	if (!node || !(*node))
		return false;

	(*node)->append_attribute(CreateAttribute(doc, XML_XMLNS_XSI, xsi));
	(*node)->append_attribute(CreateAttribute(doc, XML_XMLNS_XSD, xsd));
	return true;
}
/**Disposes resources.*/
const bool FreeXML(rapidxml::xml_document<>** doc)
{
	if (!doc || !(*doc))
		return false;

	(*doc)->clear();
	delete (*doc);
	return true;
}

const bool SaveXML(rapidxml::xml_document<>** doc, const std::string& filePath)
{
	if (!doc || !(*doc))
		return false;

	// Save to file
	std::ofstream file_stored(filePath);
	file_stored << *doc;
	file_stored.close();

	return true;
}

rapidxml::xml_attribute<>* CreateAttribute(rapidxml::xml_document<>** doc, const std::string& attributeName, const std::string& attributeValue)
{
	if (!doc || !(*doc))
		return nullptr;

	const char* value = (*doc)->allocate_string(attributeValue.c_str());
	return (*doc)->allocate_attribute(attributeName.c_str(), value);
}

rapidxml::xml_node<>* CreateNode(rapidxml::xml_document<>** doc, const std::string& nodeName, const std::string& nodeValue)
{
	if (!doc || !(*doc))
		return nullptr;

	if (!nodeValue.empty())
	{
		const char* value = (*doc)->allocate_string(nodeValue.c_str());
		return (*doc)->allocate_node(rapidxml::node_type::node_element, nodeName.c_str(), value);
	}
	else
	{
		return (*doc)->allocate_node(rapidxml::node_type::node_element, nodeName.c_str());
	}
}
