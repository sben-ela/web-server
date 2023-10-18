/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:22:08 by aybiouss          #+#    #+#             */
/*   Updated: 2023/09/24 14:39:41 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Webserv.hpp"

typedef std::vector<std::string>::iterator TokenVectsIter;

class Location
{
    private:
        std::string                        _pattern;
        std::map<int, std::string>         _error_pages;
        std::vector<std::string>           _limit_except;
        std::string                        _index;
        std::map<std::string, std::string> _cgi;
        std::string                        _upload;
        std::string                        _redirect;
        std::string                        _root;
        size_t                             _client_max_body_size;
        bool                               _AutoIndex;
        bool                               _root_exists;
        bool                               _pattern_exists;
    public:
        Location();
        Location(std::string path, TokenVectsIter& begin, TokenVectsIter& end);
        Location(const Location& other);
        Location& operator=(const Location& other);
        std::vector<std::string>            Tokenizations(std::string line);
        void                                InitClientBodySize(std::string value);
        void                                InitAutoIndex(std::string value);
        void                                InitIndex(std::string& value);
        void                                InitRoot(std::string value);
        void                                InitErrorPage(std::string& code, std::string& path);
        void                                InitPattern(std::string value);
        void                                InitLimitExcept(std::string value);
        void                                InitCgi(std::string path, std::string lang);
        void                                InitUpload(std::string value);
        void                                InitRedirect(std::string value);
        const std::string&                         getpattern() const;
        const std::string&                         getIndex() const;
        std::map<int, std::string>          getErrorPages() const;
        std::vector<std::string>            getLimit_except() const;
        std::map<std::string, std::string>  getCgi() const;
        const std::string&                         getUpload() const;
        const std::string&                         getRedirect() const;
        const std::string&                         getRoot() const;
        size_t                              getClientMaxBodySize() const;
        bool                                getAutoIndex() const;
        ~Location();
        friend std::ostream& operator<<(std::ostream& o, Location obj);
};