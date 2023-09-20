#include "RapidXMLSTD.hpp"
#include "rapidxml_print.hpp"

/**Opens a new XML file
* @param filePath - The path to a file
* @returns A xml file object*/
XMLFile* OpenXMLFile(const std::string& filePath, std::string& error)
{
	if (filePath.empty())
		return nullptr;

	return new XMLFile(filePath.c_str());
}
/**Disposes resources.
* @param doc - A xml object file
* @returns True if success*/
const bool DisposeXMLFile(XMLFile* file)
{
	if (!file)
	{
		return false;
	}

	delete (file);
	return true;
}
/**Creates a new XML file
* @param file - The xml object file
* @returns A xml document*/
XMLDocument* CreateXMLFromFile(XMLFile* file, std::string& error)
{
	if (!file)
	{
		error = "XMLFile cannot be null";
		return nullptr;
	}

	XMLDocument* doc = new XMLDocument();
	doc->parse<0>(file->data());

	return doc;
}
/**Creates a new XML file
* @param version - the version of the XML format
* @param encoding - The Encoding of the XML file (eg: utf-8, utf-16)
* @returns A xml document*/
XMLDocument* CreateXML(const uint8_t& version, const std::string& encoding, std::string& error)
{
	XMLDocument* doc = new XMLDocument();
	if (!::SetHeader(doc, version, encoding, error))
	{
		::DisposeXMLObject(doc);
		return nullptr;
	}

	return doc;
}
/**Writes the header of an xml file
* @param doc - A xml document object
* @param version - the version of the XML format
* @param encoding = The Encoding of the XML file (eg: utf-8, utf-16)
* @returns True if success*/
const bool SetHeader(XMLDocument* doc, const uint8_t& version, const std::string& encoding, std::string& error)
{
	if (!doc)
	{
		error = "XDocument cannot be null";
		return false;
	}

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
* @param element - The element to set the namespace
* @returns True if success*/
const bool SetElementDefaultNamespaces(XMLDocument* doc, XMLElement* node, std::string& error)
{
	return SetElementNamespaces(doc, node, "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/2001/XMLSchema", error);
}
/**Sets the xmlns:xsi and xmlns:xsd namespaces
* @param doc - A xml document object
* @param element - The element to set the namespace
* @param xsi - The xsi address
* @param xsd - The xds address
* @returns True if success*/
const bool SetElementNamespaces(XMLDocument* doc, XMLElement* element, const std::string& xsi, const std::string& xsd, std::string& error)
{
	if (!doc)
	{
		error = "XMLDocument cannot be null";
		return false;
	}

	if (!element)
	{
		error = "Element cannot be null";
		return false;
	}		

	element->append_attribute(CreateAttribute(doc, XML_XMLNS_XSI, xsi, error));
	element->append_attribute(CreateAttribute(doc, XML_XMLNS_XSD, xsd, error));
	return true;
}
/**Disposes resources.
* @param doc - A xml document object
* @returns True if success*/
const bool DisposeXMLObject(XMLDocument* doc)
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
XMLAttributte* CreateAttribute(XMLDocument* doc, const std::string& attributeName, const std::string& attributeValue, std::string& error)
{
	if (!doc)
	{
		error = "XDocument cannot be null";
		return nullptr;
	}

	if (attributeName.empty())
	{
		error = "Attribute name cannot be null";
		return nullptr;
	}

	const char* name = doc->allocate_string(attributeName.c_str());
	const char* value = doc->allocate_string(attributeValue.c_str());
	return doc->allocate_attribute(name, value);
}
/**Creates a element
* @param doc - A xml document object
* @param elementName - The name of the element
* @param elementValue - The value of the element
* @returns True if success*/
XMLElement* CreateElement(XMLDocument* doc, const std::string& elementName, const std::string& elementValue, std::string& error)
{
	if (!doc)
	{
		error = "XDocument cannot be null";
		return nullptr;
	}

	if (elementName.empty())
	{
		error = "Element name cannot be null";
		return nullptr;
	}

	const char* name = doc->allocate_string(elementName.c_str());
	if (!elementValue.empty())
	{
		const char* value = doc->allocate_string(elementValue.c_str());
		return doc->allocate_node(rapidxml::node_type::node_element, name, value);
	}
	else
	{
		return doc->allocate_node(rapidxml::node_type::node_element, name);
	}
}
/**Creates a element
* @param doc - A xml document object
* @param elementName - The name of the element
* @param subElements - An array of elements
* @param subElementCount - The number of elements to add
* @returns True if success*/
XMLElement* CreateElementA(XMLDocument* doc, const std::string& elementName, XMLElement** innerElements, const size_t& innerElementsCount, std::string& error)
{
	if (!doc)
	{
		error = "XDocument cannot be null";
		return nullptr;
	}

	if (elementName.empty())
	{
		error = "Element name cannot be null";
		return nullptr;
	}

	if (!innerElements)
	{
		error = "Inner elements array cannot be null";
		return nullptr;
	}

	if (innerElementsCount <= 0)
	{
		error = "Inner elements count must be larger than zero";
		return nullptr;
	}		

	const char* name = doc->allocate_string(elementName.c_str());
	XMLElement* n = doc->allocate_node(rapidxml::node_type::node_element, name);
	for (size_t i = 0; i < innerElementsCount; i++)
	{
		auto sn = innerElements[i];
		if (sn)
		{
			n->append_node(sn);
		}
	}
	
	return n;
}
/**Searches for a named element
* @param parent - A xml element object
* @param elementName - The name of the element
* @returns The element, if success*/
XMLElement* FirstOrDefaultElement(XMLElement* parent, const std::string& elementName, std::string& error)
{
	if (!parent)
	{
		error = "Parent cannot be null";
		return nullptr;
	}

	if (elementName.empty())
	{
		error = "Element name cannot be null";
		return nullptr;
	}
		
	for (XMLElement* x = parent->first_node(); x != nullptr; x = x->next_sibling())
	{
		if (x && std::string(x->name()) == elementName)
		{
			return x;
		}
	}

	return nullptr;
}
/**Searches for a named element
* @param parent - A xml document object
* @param elementName - The name of the element
* @returns The element, if success*/
XMLElement* FirstOrDefaultElementA(XMLDocument* parent, const std::string& elementName, std::string& error)
{
	if (!parent)
	{
		error = "Parent cannot be null";
		return nullptr;
	}

	if (elementName.empty())
	{
		error = "Element name cannot be null";
		return nullptr;
	}

	return parent->first_node(elementName.c_str());
}

XMLAttributte* FirstOrDefaultAttribute(XMLElement* parent, const std::string& attributeName, std::string& error)
{
	if (!parent)
	{
		error = "Parent cannot be null";
		return nullptr;
	}

	if (attributeName.empty())
	{
		error = "Element name cannot be null";
		return nullptr;
	}
		
	return parent->first_attribute(attributeName.c_str());
}

const bool SetAttributeValue(XMLAttributte* attribute, const std::string& attributeValue, std::string& error)
{
	if (!attribute)
	{
		error = "Attribute cannot be null";
		return false;
	}

	XMLDocument* doc = attribute->document();
	if (!doc)
	{
		error = "Parent document cannot be null";
		return false;
	}

	const char* value = doc->allocate_string(attributeValue.c_str());
	attribute->value(value);
	return true;
}
const bool SetAttributeValueA(XMLElement* element, const std::string& attributeName, const std::string& attributeValue, std::string& error)
{
	if (!element)
	{
		error = "Element cannot be null";
		return false;
	}

	if (attributeName.empty())
	{
		error = "Attribute name cannot be null";
		return false;
	}

	XMLAttributte* attribute = ::FirstOrDefaultAttribute(element, attributeName, error);
	if (!attribute)
	{
		return false;
	}

	return ::SetAttributeValue(attribute, attributeValue, error);
}
const bool SetElementValue(XMLElement* parent, XMLElement* child, std::string& error)
{
	if (!parent)
	{
		error = "Parent cannot be null";
		return false;
	}

	if (!child)
	{
		error = "Child cannot be null";
		return false;
	}

	parent->append_node(child);
	return true;
}
const bool SetElementValueA(XMLElement* element, const std::string& elementValue, std::string& error)
{
	if (!element)
	{
		error = "Element cannot be null";
		return false;
	}

	XMLDocument* doc = element->document();
	if (!doc)
	{
		error = "Parent document cannot be null";
		return false;
	}

	const char* value = doc->allocate_string(elementValue.c_str());
	element->value(value);
	return true;
}
/**Adds a node to a xml document
* @param doc - A xml document object
* @param node - The element add
* @returns True if success*/
const bool AddElementToDocument(XMLDocument* doc, XMLElement* element, std::string& error)
{
	if (!doc)
	{
		error = "XMLDocument cannot be null";
		return false;
	}

	if (!element)
	{
		error = "XMLElement cannot be null";
		return false;
	}

	doc->append_node(element);
	return true;
}
/**Adds a node to another node
* @param parent - The parent element
* @param child - The child element
* @returns True if success*/
const bool AddElementToElement(XMLElement* parent, XMLElement* child, std::string& error)
{
	if (!parent)
	{
		error = "PArent cannot be null";
		return false;
	}

	if (!child)
	{
		error = "Child cannot be null";
		return false;
	}

	parent->append_node(child);
	return true;
}
/**Adds an attribute to a node
* @param parent - The parent element
* @param child - The child element
* @returns True if success*/
const bool AddAttributeToElement(XMLElement* parent, XMLAttributte* child, std::string& error)
{
	if (!parent)
	{
		error = "PArent cannot be null";
		return false;
	}

	if (!child)
	{
		error = "Child cannot be null";
		return false;
	}

	parent->append_attribute(child);
	return true;
}