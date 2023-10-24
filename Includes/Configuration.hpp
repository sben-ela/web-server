/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:22:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 13:56:44 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Location.hpp"

typedef std::vector<std::string>::iterator TokenVectsIter;


class Configuration
{
    private:
        std::string                                      _root;
        std::string                                      _host;
        std::string                                      _index;
        std::map<int, std::string>                       _error_pages;
        std::vector<int>                                 _codes;
        std::map<std::string, std::string>               _cgi;
        size_t                                           _client_max_body_size;
        bool                                             _AutoIndex;
        bool                                             _root_exists;
        size_t                                           _port;
        bool                                             _host_exists;
        bool                                             _port_exists;
        std::string                                      _upload;
        std::string                                      _server_name;                                   
        std::vector<Location>                            _locations;
    public:
        int                                              _socketfd; //
        Configuration();
        // Configuration operator()(std::string host, std::string  port);
        Configuration(std::vector<std::string> vecteur);
        std::vector<std::string>    Tokenization(std::string line);
        Configuration(const Configuration& other);
        Configuration& operator=(const Configuration& other);
        bool isStringAllDigits(const std::string& str);
        void InitHost(std::string value);
        void InitPort(std::string value);
        void InitServerName(std::string value);
        void                         InitRoot(std::string value);
        void                         InitIndex(std::string value);
        void                         InitErrorPage(std::string code, std::string path);
        void                         InitClientBodySize(std::string value);
        void                         InitAutoIndex(std::string value);
        void                         InitUpload(std::string value);
        std::map<std::string, std::string>  getCgi() const;
        void                                InitCgi(std::string path, std::string lang);
        std::string                  getUpload() const;
        std::string                  getRoot() const;
        std::string                  getIndex() const;
        std::map<int, std::string>   getErrorPages() const;
        std::vector<int>             getCodes() const;
        size_t                       getClientMaxBodySize() const;
        bool                         getAutoIndex() const;
        // static    void check_dup(std::string host, std::string port);
        std::string                 getHost() const;
        size_t                      getPort() const;
        std::string                 getServerNames() const;
        std::vector<Location>       getLocations() const;
        bool                        checkLocations() const;
        int	                        checkFile(std::string const path, int mode);
        int                         getTypePath(std::string const path);
        friend std::ostream& operator<<(std::ostream& o, Configuration obj);
        bool    compareLocations(const Location& loc1, const Location& loc2);
        ~Configuration();
};

/*
The friend keyword is used to declare a function or class as a friend of the class in which it is declared. A friend function is not a member of the class but is allowed to access its private and protected members.
*/