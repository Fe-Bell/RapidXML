#include "rapidxml_factory.hpp"
#include <filesystem> //C++17's file/directory management library

// Copyright (C) 2020 Felipe Bellini
// Version 1.14
// Revision $DateTime: 2020/07/23 12:57:00 $
//! \file rapidxml_factory.hpp This file contains a safe C++ factory for rapid xml file.

/// <summary>
/// Safe rapidxml::file loader.
/// </summary>
/// <param name="filePath">A path for an XML file</param>
/// <param name="xmlFile">A reference for a rapidxml::file object.</param>
/// <param name="error">An error string. Will contain data only in case of UnknownError, otherwise it will be empty.</param>
/// <returns>An error code or zero case successful.</returns>
rapidxml_factory::Result_e rapidxml_factory::open_file(const std::string& filePath, rapidxml::file<>& xmlFile, std::string& error)
{
    rapidxml_factory::Result_e rc = rapidxml_factory::Result_e::Success;

    //Checks if the specified path is a directory
    if (!std::filesystem::is_directory(filePath))
    {
        //Make sure the path to the file exists
        if (std::filesystem::exists(filePath))
        {
            try 
            {
                xmlFile = rapidxml::file<>(filePath.c_str());
            }
            catch (std::runtime_error err)
            {
                std::string errstr = err.what();
                if (errstr.rfind("cannot open file"))
                {
                    rc = rapidxml_factory::Result_e::CannotOpenFile;
                }
                else
                {
                    rc = rapidxml_factory::Result_e::UnknownError;
                    error = errstr;
                }
            }
        }
        else
        {
            rc = rapidxml_factory::Result_e::FileNotFound;
        }
    }
    else
    {
        rc = rapidxml_factory::Result_e::PathIsDirectory;
    }

    return rc;
}
