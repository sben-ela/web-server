/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:07:10 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/17 13:46:25 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../Webserv.hpp"

class Request
{
    protected:
        std::string     _method;
        std::string     _path;
        std::string     _httpVersion;
        int             _responseStatus;
        std::string    _header_before;
        std::vector<char>     _body;
        std::map<std::string, std::string>  _headers;
        std::map<int, std::string>          _statusCode;
        std::string     _contentType;
        const char*     _bodyFile;
        std::string     _ofile;
        int             _chunksize;
        std::string     _bodies;
        std::string     _all;
        std::string     _queryString;
        bool        _transferEncodingChunked;
        bool        _transferEncoding;
        bool        _contentLength;
        bool        _headers_done;
        int         _fd;
        std::string _contentTypeValue;
        bool        _condition;
        unsigned long         _length;
        unsigned long         _total;
        bool                  _chunked;
    public:
        std::string           _name;
        Request();
        Request(const Request& other);
        Request& operator=(const Request& other);
        int                        processAllBody();
        int                        parseHttpRequest(std::string requestBuffer);
        const std::string&         getPath() const;
        const std::string&         getMethod() const;
        const std::string&         getHttpVersion() const;
        int                        getResponseStatus() const;
        std::string                GetFileExtention( void ) const;
        std::string                getContentType( void ) const;
        void                       setPath(std::string newPath);
        void                       setResponseStatus(int status);
        int                        processChunk(std::string buffer);
        int                        parseRequest();
        int                        processBody();
        size_t                     customFind(const std::vector<char>& vec, const std::string& str, size_t start);
        int                        parseHeaders();
        std::string                GenerateFile();
        std::string                getQueryString() const;
        const int&                 getFd() const;
        int                        countNumbersInString(const std::string& inputString);
        std::string                vectorCharToString(const std::vector<char>& vec);
        std::vector<char>          customSubstr(const std::vector<char>& vec, size_t start, size_t length);
        std::map<int, std::string> getStatusCode( void ) const;
        void                       CreateStatusCode( void );
        void                       processMultiPart(std::string content);
        std::string                ft_temp( void ) const;
        const std::map<std::string, std::string>& getHeaders( void ) const;
        ~Request();
};