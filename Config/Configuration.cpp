/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:26:09 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 16:22:07 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Configuration.hpp"

Configuration::Configuration()
        : _host("localhost"), _client_max_body_size(0),  _AutoIndex(false), _root_exists(false),
        _port(0), _host_exists(false), _port_exists(false) {}
std::vector<std::string>    Configuration::Tokenization(std::string line)
{
    std::vector<std::string> result;
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token) {
        result.push_back(token);
    }
    return result;
}

bool Configuration::isStringAllDigits(const std::string& str) {
    // Find the first character that is not a digit
    size_t pos = str.find_first_not_of("0123456789");

    // If pos is equal to std::string::npos, it means there are no non-digit characters
    return (pos == std::string::npos);
}

Configuration::Configuration(std::vector<std::string> vecteur)
    : _host("127.0.0.1"), _client_max_body_size(0),  _AutoIndex(false), _root_exists(false),
    _port(0), _host_exists(false), _port_exists(false)
{
    TokenVectsIter begin = vecteur.begin();
    TokenVectsIter end = vecteur.end();
    while (begin != end)
    {
        std::string line = *begin;
        std::vector<std::string> token = Tokenization(line);
        // if (token.empty())
        // {
        //     // Skip empty lines.
        //     ++begin;
        //     continue;
        // }
        if (token[0] == "host" && token.size() == 2)
        {
            ++begin;
            if (begin != end && token.size() == 2)
                InitHost(token[1]);
            else
                throw std::string("Invalid host arguments");
        }
        else if (token[0] == "autoindex")
        {
            ++begin;
            if (begin != end && token.size() == 2)
                InitAutoIndex(token[1]);
            else
                throw std::string("Invalid autoindex arguments");
        }
        else if (token[0] == "index")
        {
            ++begin;
            if (begin != end && token.size() == 2)
                InitIndex(token[1]);
            else
                throw std::string("Invalid Index arguments");
        }
        else if (token[0] == "client_body_size")
        {
            ++begin;
            if (begin != end && token.size() == 2)
                InitClientBodySize(token[1]);
            else
                throw std::string("Invalid Client body size arguments");
        }
        else if (token[0] == "root")
        {
            ++begin;
            if (begin != end && token.size() == 2)
                InitRoot(token[1]);
            else
                throw std::string("Invalid root arguments");
        }
        else if (token[0] == "listen")
        {
            ++begin;
            if (isStringAllDigits(token[1]) && token.size() == 2 && atoi(token[1].c_str()) <= 65635)
                InitPort(token[1]);
            else
                throw std::string("Invalid port number arguments");
        }
        else if (token[0] == "server_name")
        {
            ++begin;
            if (token.size() == 2)
                InitServerName(token[1]);
            else
                throw std::string("Invalid server name arguments");
        }
        else if (token[0] == "upload_path")
        {
            // Extract and set upload
            ++begin;
            if (token.size() == 2 && begin != end)
                InitUpload(token[1]);
            else
                throw std::string("Invalid Upload path arguments");
        }
        else if (token[0] == "cgi")
        {
            // Extract and set CGI settings
            ++begin;
            if (token.size() == 3 && begin != end)
            {
                InitCgi(token[1], token[2]);
            }
            else
                throw std::string("Invalid cgi arguments");
        }
        else if (token[0] == "error_page")
        {
            ++begin;
            if (token.size() == 3)
                InitErrorPage(token[1], token[2]);
            else
                throw std::string("Invalid error page arguments");
        }
        else if (token[0] == "location")
        {
            ++begin;
            if (begin != end && token.size() == 2)
            {
                // Find the closing curly brace of the location block.
                TokenVectsIter endIt = std::find(begin, end, "	}");
                if (endIt != end)
                {
                // Create a Location object and add it to the vector.
                    Location location(token[1], begin, endIt);
                    // std::cout << location << std::endl;
                    // std::cout << "********************************" << std::endl;
                    _locations.push_back(location);
                    // ? hitax ma3amelx copy assignment
                    // Move the iterator to the next position after the location block.
                    begin = endIt + 1; // Advance by 1 to skip the closing brace.
                }
                else
                    throw std::string("Invalid location: Missing closing '}'");
            }
            else
                throw std::string("Invalid location: Missing location block");
        }
        else
            begin++;
    }
    if (getRoot().empty())
		throw std::string("No root found");
	if (getHost().empty())
		InitHost("localhost");
	if (getIndex().empty())
		InitIndex("");
    if (checkLocations())
        throw std::string("Location is duplicated");
    if (!getPort())
		throw std::string("Port not found");
    if (getServerNames().empty())
        throw std::string("No server name");
    std::vector<int> it = getCodes();
    std::map<int, std::string> pages = getErrorPages();
    for (std::vector<int>::iterator it2 = it.begin(); it2 != it.end(); it2++)
    {
        if (getTypePath(pages[*it2]) != 2)
        {
    	    if (getTypePath(this->_root + pages[*it2]) != 1)
    	    	throw std::string ("Incorrect path for error page file: " + this->_root + pages[*it2]);
    	    if (checkFile(this->_root + pages[*it2], 0) == -1 || checkFile(this->_root + pages[*it2], 4) == -1)
    	    	throw std::string ("Error page file :" + this->_root + pages[*it2] + " is not accessible");
        } // ! l3iba
    } // ! to be fixed !! 
    std::vector<Location> sortedLocations = _locations;
    int n = sortedLocations.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (compareLocations(sortedLocations[j], sortedLocations[j + 1]))
            {
                Location tmp = sortedLocations[j];
                sortedLocations[j] = sortedLocations[j + 1];
                sortedLocations[j + 1] = tmp;
            }
        }
    }
    _locations.clear();
    _locations = sortedLocations;
} //ila kant / katdir getcwd

bool    Configuration::compareLocations(const Location& loc1, const Location& loc2)
{
    return loc1.getpattern().length() > loc2.getpattern().length();   
}

std::vector<int>    Configuration::getCodes() const
{
    return _codes;
}

/* define is path is file(1), folder(2) or something else(3) */
int Configuration::getTypePath(std::string const path)
{
    // The stat structure is used to store information about a file, such as its size, permissions, and other attributes.
	struct stat	buffer;
	int			result;
	
	result = stat(path.c_str(), &buffer);
	if (result == 0)
	{
		if (S_ISREG(buffer.st_mode))
			return (1); // : This condition checks if the file is a regular file (a file that is not a directory or a special file). If true, it returns 1 to indicate that the path points to a regular file.
		else if (S_ISDIR(buffer.st_mode))
			return (2); // This condition checks if the file is a directory. If true, it returns 2 to indicate that the path points to a directory.
		else
			return (3); // If none of the above conditions match, it returns 3 to indicate that the path points to some other type of file.
	}
	else
		return (-1); // for error
}

/* checks is the file exists and accessable */
int	Configuration::checkFile(std::string const path, int mode)
{
	return (access(path.c_str(), mode));
}

/* check location for a dublicate */
bool Configuration::checkLocations() const
{
    std::vector<Location> locations = getLocations();
	std::vector<Location>::iterator it1;
	if (locations.size() < 2)
		return (false);
	std::vector<Location>::iterator it2;
	for (it1 = locations.begin(); it1 != locations.end() - 1; it1++)
    {
		for (it2 = it1 + 1; it2 != locations.end(); it2++)
        {
			if (it1->getpattern() == it2->getpattern())
				return (true);
		}
	}
	return (false);
}

Configuration::Configuration(const Configuration& other)
    : _root(other._root), _host(other._host), _index(other._index),
      _error_pages(other._error_pages), _codes(other._codes), _cgi(other._cgi), _client_max_body_size(other._client_max_body_size),
      _AutoIndex(other._AutoIndex), _root_exists(other._root_exists), _port(other._port),
      _host_exists(other._host_exists), _port_exists(other._port_exists), _upload(other._upload),
      _server_name(other._server_name), _locations(other._locations) {}

Configuration& Configuration::operator=(const Configuration& other)
{
    if (this != &other)
    {
        _root = other._root;
        _host = other._host;
        _index = other._index;
        _error_pages = other._error_pages;
        _codes = other._codes;
        _cgi = other._cgi;
        _client_max_body_size = other._client_max_body_size;
        _AutoIndex = other._AutoIndex;
        _root_exists = other._root_exists;
        _port = other._port;
        _host_exists = other._host_exists;
        _port_exists = other._port_exists;
        _upload = other._upload;
        _server_name = other._server_name;
        _locations = other._locations;
    }
    return *this;
}

void Configuration::InitCgi(std::string path, std::string lang)
{
    std::cout << "Print cgi  " << lang << "  " << path << std::endl;
    if (!lang.empty() && !path.empty())
    {
        // Store the CGI setting in the _cgi map.
        _cgi[lang] = path;
    }
    else
    {
        // Handle parsing error if needed.
        std::string str = "Error parsing CGI setting: " + path + " ";
        throw std::string(str.append(lang));
    }
}
void Configuration::InitHost(std::string value)
{
    _host = value;
    _host_exists = true;
}

void Configuration::InitPort(std::string value)
{
    _port = atoi(value.c_str());
    _port_exists = true;
}

void Configuration::InitServerName(std::string value)
{
    _server_name = value;
}

void Configuration::InitRoot(std::string value)
{
    _root = value;
    _root_exists = true;
}

void Configuration::InitIndex(std::string value)
{
    _index = value;
}

void Configuration::InitErrorPage(std::string code, std::string path)
{
    // Implement this method to initialize error pages.
    // You would need to parse and store error pages based on your needs.
    int error_code = atoi(code.c_str());
    if ((error_code >= 100 && error_code <= 599) && !path.empty())
    {
        // Store the parsed values in the _error_pages map
        _error_pages[error_code] = path;
        _codes.push_back(error_code);
    }
    else
    {
        // Handle parsing error if needed
        std::string str = "Error parsing error page: " + code + " ";
        throw std::string(str.append(path));
    }
}

void Configuration::InitClientBodySize(std::string value)
{
    // Use a stringstream to parse the input string as an integer
    std::istringstream iss(value);
    int client_max_body_size = 0;

    // Attempt to extract an integer from the string
    if (!(iss >> client_max_body_size))
    {
        // Handle parsing error if the extraction fails
        std::string error_msg = "Error parsing client max body size: " + value;
        throw std::string(error_msg);
    }

    // Check if the parsed value is valid (greater than zero)
    if (client_max_body_size < 0)
    {
        std::string error_msg = "Invalid client max body size: " + value;
        throw std::string(error_msg);
    }

    // Store the parsed value in the _client_max_body_size member
    _client_max_body_size = static_cast<size_t>(client_max_body_size);
}

void Configuration::InitAutoIndex(std::string value)
{
    // Implement this method to initialize the AutoIndex flag.
    // You would need to parse and store the flag based on your needs.

    // Convert the input string to lowercase for case-insensitive comparison
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    // Check if the value is "true" or "false"
    if (value == "on")
        _AutoIndex = true;
    else if (value == "off")
        _AutoIndex = false;
    else
    {
        // Handle parsing error if needed
        std::string error_msg = "Error parsing AutoIndex: " + value;
        throw std::string(error_msg);
    }
}

void Configuration::InitUpload(std::string value)
{
    _upload = value;
}

std::string Configuration::getUpload() const
{
    return _upload;
}

std::string Configuration::getRoot() const
{
    return _root;
}

std::string Configuration::getIndex() const
{
    return _index;
}

std::map<std::string, std::string> Configuration::getCgi() const
{
    return _cgi;
}

std::map<int, std::string> Configuration::getErrorPages() const
{
    return _error_pages;
}

size_t Configuration::getClientMaxBodySize() const
{
    return _client_max_body_size;
}

bool Configuration::getAutoIndex() const
{
    return _AutoIndex;
}

std::string Configuration::getHost() const
{
    return _host;
}

size_t Configuration::getPort() const
{
    return _port;
}

std::string Configuration::getServerNames() const
{
    return _server_name;
}

std::vector<Location> Configuration::getLocations() const
{
    return _locations;
}

// friend std::ostream& operator<<(std::ostream& o, const Configuration obj);

std::ostream& operator<<(std::ostream& o, Configuration obj)
{
    o << "Host: " << obj.getHost() << std::endl;
    o << "Port: " << obj.getPort() << std::endl;
    o << "Server Name: " << obj.getServerNames() << std::endl;
    std::map<int, std::string> p = obj.getErrorPages();
    for (std::map<int, std::string>::iterator it = p.begin(); it != p.end(); it++)
    {
        o << "Error pages: " << it->first << "  " << it->second << " " << std::endl;
    }
    // o << std::endl;
    // Output location blocks
    std::map<std::string, std::string> b = obj.getCgi();
    for (std::map<std::string, std::string>::iterator it = b.begin(); it != b.end(); it++)
    {
        o << "cgi: " << it->first << "  " << it->second << " " << std::endl;
    }
    o << std::endl;
    std::vector<Location> loca = obj.getLocations();
    for (std::vector<Location>::iterator it = loca.begin(); it != loca.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
    return o;
}
// This code defines the Configuration class with member functions for initialization and access to its attributes. It also handles parsing location blocks and uses the Location class to store and manage them.

Configuration::~Configuration() {}