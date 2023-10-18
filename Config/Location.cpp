/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:26:06 by aybiouss          #+#    #+#             */
/*   Updated: 2023/09/24 14:46:52 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Location.hpp"

Location::Location() : _pattern_exists(false) {
    _pattern_exists = false;
    _error_pages.clear();
    _limit_except.clear();
    _index.clear();
    _cgi.clear();
    _upload.clear();
    _redirect.clear();
    _root.clear();
    _client_max_body_size = 0;
    _AutoIndex = false;
    _root_exists = false;
}

std::vector<std::string>    Location::Tokenizations(std::string line)
{
    std::vector<std::string> result;
    std::istringstream iss(line);
    std::string token;
    
    while (iss >> token) {
        result.push_back(token);
    }
    return result;
}

Location::Location(std::string path, TokenVectsIter& begin, TokenVectsIter& end)
    :   _upload(""),
        _redirect(""),
        _root(""),
        _client_max_body_size(0),
        _AutoIndex(false),
        _root_exists(false)
{
    // Initialize the Location object using the provided iterators (assuming they point to strings).
    if (!path.empty())
        InitPattern(path);
    while (begin != end)
    {
        std::string line = *begin;
        std::vector<std::string> token = Tokenizations(line);
        if (token[0] == "allow_methods")
        {
            // Extract and set limit_except values
            size_t i = 1;
            if (begin == end)
                throw std::string("Invalid allow_methods arguments");
            while (i < token.size())
            {
                InitLimitExcept(token[i]);
                i++;
            } // ! ba9i aykhssni nsre3ha (BASFA)
            ++begin;
        }
        else if (token[0] == "autoindex")
        {
            if (begin != end && token.size() == 2)
                InitAutoIndex(token[1]);
            else
                throw std::string("Invalid autoindex");
            ++begin;
        }
        else if (token[0] == "client_body_size")
        {
            if (begin != end && token.size() == 2)
                InitClientBodySize(token[1]);
            else
                throw std::string("Invalid Client body size");
            ++begin;
        }
        else if (token[0] == "root")
        {
            if (begin != end && token.size() == 2)
                InitRoot(token[1]);
            else
                throw std::string("Invalid root");
            ++begin;
        }
        else if (token[0] == "index")
        {
            if (begin != end && token.size() == 2)
            {
                InitIndex(token[1]);
            }
            else
                throw std::string("Invalid Index " + token[0] + token[1]);
            ++begin;
        }
        else if (token[0] == "cgi")
        {
            // Extract and set CGI settings
            if (token.size() == 3 && begin != end)
                InitCgi(token[1], token[2]);
            else
                throw std::string("Invalid cgi arguments");
            ++begin;
        }
        else if (token[0] == "upload_path")
        {
            // Extract and set upload
            if (begin != end && token.size() == 2)
                InitUpload(token[1]);
            else
                throw std::string("Invalid upload_path arguments");
            ++begin;
        }
        else if (token[0] == "error_page")
        {
            if (token.size() == 3)
                InitErrorPage(token[1], token[2]);
            else
                throw std::string("Invalid error page arguments");
            ++begin;
        }
        else if (token[0] == "redirect")
        {
            // Extract and set redirect
            if (begin != end && token.size() == 2)
                InitRedirect(token[1]);
            else
                throw std::string("Invalid redirect arguments");
            ++begin;
        }
        else
            ++begin;
        // Handle other tokens as needed
    }
    // std::cout << "#############################33" << std::endl;
    // std::cout << this->getRoot() << std::endl;
    // std::cout << "#############################33" << std::endl;
    // std::cout << *this << std::endl;
    // std::cout << "#############################33" << std::endl;
}

Location::Location(const Location& other)
    : _pattern(other._pattern), _error_pages(other._error_pages),
      _limit_except(other._limit_except), _index(other._index),
      _cgi(other._cgi), _upload(other._upload),
      _redirect(other._redirect), _root(other._root),
      _client_max_body_size(other._client_max_body_size), _AutoIndex(other._AutoIndex),
      _root_exists(other._root_exists), _pattern_exists(other._pattern_exists) {}

Location& Location::operator=(const Location& other)
{
    if (this != &other)
    {
        _pattern = other._pattern;
        _error_pages = other._error_pages;
        _limit_except = other._limit_except;
        _index = other._index;
        _cgi = other._cgi;
        _upload = other._upload;
        _redirect = other._redirect;
        _root = other._root;
        _client_max_body_size = other._client_max_body_size;
        _AutoIndex = other._AutoIndex;
        _root_exists = other._root_exists;
        _pattern_exists = other._pattern_exists;
    }
    return *this;
}

void Location::InitIndex(std::string& value)
{
    _index = value;
}

void Location::InitPattern(std::string value)
{
    _pattern = value;
    _pattern_exists = true;
}

void Location::InitLimitExcept(std::string value)
{
    _limit_except.push_back(value);
}

void Location::InitErrorPage(std::string& code, std::string& path)
{
    // Implement this method to initialize error pages.
    // You would need to parse and store error pages based on your needs.
    int error_code = atoi(code.c_str());
    std::string error_page_path = path;
    if ((error_code >= 100 && error_code <= 599) && !path.empty())
    {
        // Store the parsed values in the _error_pages map
        _error_pages[error_code] = error_page_path;
    }
    else
    {
        // Handle parsing error if needed
        std::string str = "Error parsing error page: " + code + " ";
        throw std::string(str.append(path));
    }
}

void Location::InitCgi(std::string path, std::string lang)
{
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

void Location::InitRoot(std::string value)
{
    _root = value;
    _root_exists = true;
}

void Location::InitClientBodySize(std::string value)
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

void Location::InitAutoIndex(std::string value)
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

void Location::InitUpload(std::string value)
{
    _upload = value;
}

void Location::InitRedirect(std::string value)
{
    _redirect = value;
}

const std::string& Location::getpattern() const
{
    return _pattern;
}

const std::string& Location::getRoot() const
{
    return _root;
}

size_t Location::getClientMaxBodySize() const
{
    return _client_max_body_size;
}

bool Location::getAutoIndex() const
{
    return _AutoIndex;
}

std::vector<std::string> Location::getLimit_except() const
{
    return _limit_except;
}

const std::string& Location::getIndex() const
{
    return _index;
}

std::map<std::string, std::string> Location::getCgi() const
{
    return _cgi;
}

std::map<int, std::string> Location::getErrorPages() const
{
    return _error_pages;
}

const std::string& Location::getUpload() const
{
    return _upload;
}

const std::string& Location::getRedirect() const
{
    return _redirect;
}

Location::~Location() {}

// friend std::ostream& operator<<(std::ostream& o, const Location obj);

std::ostream& operator<<(std::ostream& o, Location obj)
{
    o << "Pattern: " << obj._pattern << std::endl;
    o << "Uploads: " << obj.getUpload() << std::endl;
    o << "Index: " << obj.getIndex() << std::endl;
    o << "Root : " << obj._root << std::endl;
    o << "AutoIndex :" << obj.getAutoIndex() << std::endl;
    std::map<int, std::string> p = obj.getErrorPages();
    for (std::map<int, std::string>::iterator it = p.begin(); it != p.end(); it++)
    {
        o << "Error pages: " << it->first << "  " << it->second << " " << std::endl;
    }
    o << std::endl;
    std::map<std::string, std::string> nn = obj.getCgi();
    for (std::map<std::string, std::string>::iterator it = nn.begin(); it != nn.end(); it++)
    {
        o << "Cgi: " << it->first << "  " << it->second << " " << std::endl;
    }
    o << std::endl;
    // std::copy(obj.getIndex().begin(), obj.getIndex().end(), std::ostream_iterator<std::string>(o, ", "));
    // Output other members as needed
    return o;
}