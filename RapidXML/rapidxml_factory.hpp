#ifndef RAPIDXML_FACTORY_HPP_INCLUDED
#define RAPIDXML_FACTORY_HPP_INCLUDED

#include "../RapidXML/rapidxml.hpp"
#include "../RapidXML/rapidxml_utils.hpp"
#include "../RapidXML/rapidxml_ext.hpp"

// Copyright (C) 2020 Felipe Bellini
// Version 1.14
// Revision $DateTime: 2020/07/23 12:57:00 $
//! \file rapidxml_factory.hpp This file contains a safe C++ factory for rapid xml file.

class rapidxml_factory
{
public:
	enum class Result_e
	{
		Success = 0,
		UnknownError = -1,
		FileNotFound = -2,
		PathIsDirectory = -3,
		CannotOpenFile = -4,
	};

	/// <summary>
	/// Safe rapidxml::file loader.
	/// </summary>
	/// <param name="filePath">A path for an XML file</param>
	/// <param name="xmlFile">A reference for a rapidxml::file object.</param>
	/// <param name="error">An error string. Will contain data only in case of UnknownError, otherwise it will be empty.</param>
	/// <returns>An error code or zero case successful.</returns>
	rapidxml_factory::Result_e open_file(const std::string& filePath, rapidxml::file<>& xmlFile, std::string& error);
};

#endif /* RAPIDXML_FACTORY_HPP_INCLUDED */