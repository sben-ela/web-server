/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:21 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 17:49:53 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Client.hpp"

Client::Client() : _status(0), _cgiTimer(0), _cgiPid(-1)
{
    _isFavicon = false;
}

void Client::set_server(Configuration p)
{
    _client_server = p;
}
void Client::set_socket(int socket)
{
    _socketId = socket;
}

const int &Client::GetSocketId(void) const
{
    return (_socketId);
}

Client::Client(const Client &other)
{
    if (this != &other)
    {
        this->_socketId = other._socketId;
        _readStatus = other._readStatus;
        this->_client_server = other._client_server;
        _status = other._status;
        this->response = other.response;
        _defaultErrorPages = other._defaultErrorPages;
        this->_cgiPid = other._cgiPid;
        this->_cgiTimer = other._cgiTimer;
    }
}

Client &Client::operator=(const Client &other)
{
    if (this != &other)
    {
        this->_socketId = other._socketId;
        _readStatus = other._readStatus;
        _status = other._status;
        this->_client_server = other._client_server;
        this->response = other.response;
        _defaultErrorPages = other._defaultErrorPages;
        this->_cgiPid = other._cgiPid;
        this->_cgiTimer = other._cgiTimer;
    }
    return *this;
}

const Configuration &Client::getServer(void) const
{
    return (_client_server);
}

void Client::fullMapEnv()
{
    struct stat statbuffer;
    std::stringstream ss;

    fstat(response.getFd(), &statbuffer);

    ss << statbuffer.st_size;
    _mapEnv["REDIRECT_STATUS"] = "200";
    _mapEnv["SCRIPT_FILENAME"] = _targetPath;
    _mapEnv["REQUEST_METHOD"] = response.getMethod();
    _mapEnv["QUERY_STRING"] = response.getQueryString();
    _mapEnv["HTTP_CONTENT_TYPE"] = "application/x-www-form-urlencoded";
    _mapEnv["CONTENT_TYPE"] = "application/x-www-form-urlencoded";

    for (std::map<std::string, std::string>::const_iterator it = response.getHeaders().begin(); it != response.getHeaders().end(); it++)
    {
        if (it->first == "Cookie")
            _mapEnv["HTTP_COOKIE"] = it->second;
        else if (it->first == "Content-Length")
        {
            _mapEnv["CONTENT_LENGTH"] = it->second;
            _mapEnv["HTTP_CONTENT_LENGTH"] = it->second;
        }
        else
            _mapEnv["HTTP_" + it->first] = it->second;
    }

    std::cout << "-------------------------------------------------------------------" << std::endl;
    int fd = open("txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    for (std::map<std::string, std::string>::const_iterator it = _mapEnv.begin(); it != _mapEnv.end(); it++)
    {
        write(fd, (it->first + "=" + it->second).c_str(), (it->first + "=" + it->second).size());
        write(fd, "\n", 1);
    }
}

void Client::initDefaultErrorPages(void)
{
    // std::cout << "inti error pages" << std::endl;
    _defaultErrorPages[MOVEDPERMANENTLY] = "Errors/301.html";
    _defaultErrorPages[NOTALLOWED] = "Errors/405.html";
    _defaultErrorPages[BADREQUEST] = "Errors/400.html";
    _defaultErrorPages[UNAUTHORIZED] = "Errors/401.html";
    _defaultErrorPages[FORBIDDEN] = "Errors/403.html";
    _defaultErrorPages[NOTFOUND] = "Errors/404.html";
    _defaultErrorPages[REQUESTTIMEOUT] = "Errors/408.html";
    _defaultErrorPages[CONFLICT] = "Errors/409.html";
    _defaultErrorPages[INTERNALSERVERERROR] = "Errors/500.html";
    _defaultErrorPages[NOTIMPLEMENTED] = "Errors/501.html";
    _defaultErrorPages[BADGATEWAY] = "Errors/502.html";
    _defaultErrorPages[SERVICEUNAVAILABLE] = "Errors/503.html";
    _defaultErrorPages[GATEWAYTIMEOUT] = "Errors/504.html";
    _defaultErrorPages[NOCONTENT] = "Errors/204.html";
}

std::string Client::findKey(const std::string &key)
{
    size_t start;
    size_t end;

    std::cout << "*************************CGI HEADER : "  << _CgiHeader << std::endl;
    // exit(127);
    start = _CgiHeader.find(key);
    if (start == std::string::npos)
    {
        return ("");
    }
    end = _CgiHeader.find("\r\n", start);
    return (_CgiHeader.substr(start, end - start));
}

std::string Client::getCookie(void)
{
    return ("\r\n" + findKey("Set-Cookie"));
}

void Client::fullEnv()
{
    fullMapEnv();
    _env = new char *[_mapEnv.size() + 1];
    size_t i = 0;
    for (std::map<std::string, std::string>::iterator it = _mapEnv.begin(); it != _mapEnv.end();)
    {
        _env[i] = strdup((char *)(it->first + "=" + it->second).c_str());
        it++;
        i++;
    }
    _env[i] = NULL;
}

void Client::deleteEnv()
{
    for (size_t i = 0; _env[i]; i++)
        free(_env[i]);
    delete[] _env;
}

std::string Client::get_content_type(void)
{
    std::string key;

    key = findKey("Content-Type");
    if (!key.empty())
        return (key);
    const char *last_dot = strrchr(response.getPath().c_str(), '.');
    if (last_dot)
    {
        if (strcmp(last_dot, ".css") == 0)
            return "Content-Type: text/css";
        if (strcmp(last_dot, ".gif") == 0)
            return "Content-Type: image/gif";
        if (strcmp(last_dot, ".html") == 0)
            return "Content-Type: text/html";
        if (strcmp(last_dot, ".ico") == 0)
            return "Content-Type: image/x-icon";
        if (strcmp(last_dot, ".jpeg") == 0)
            return "Content-Type: image/jpeg";
        if (strcmp(last_dot, ".mp4") == 0)
            return "Content-Type: video/mp4";
        if (strcmp(last_dot, ".jpg") == 0)
            return "Content-Type: image/jpeg";
        if (strcmp(last_dot, ".js") == 0)
            return "Content-Type: application/javascript";
        if (strcmp(last_dot, ".json") == 0)
            return "Content-Type: application/json";
        if (strcmp(last_dot, ".png") == 0)
            return "Content-Type: image/png";
        if (strcmp(last_dot, ".txt") == 0)
            return "Content-Type: text/plain";
    }
    return ("Content-Type: text/html");
}

Client::~Client() {}
// X-Powered-By: PHP/8.0.2
// Set-Cookie: user=test
// Content-type: text/html; charset=UTF-8