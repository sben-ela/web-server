/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:22:49 by sben-ela          #+#    #+#             */
/*   Updated: 2023/10/15 13:21:01 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#define PORT 7070 // Where the clients can reach at
#define MAX_CLIENTS 10 // Maximum number of clients to handle
#include <csignal>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <sstream>
#include <netdb.h>
// #include "./Includes/Location.hpp"
// #include "./Includes/Socket.hpp"
// #include "./Includes/Configuration.hpp"ƒ
// #include "./Includes/Servers.hpp"
// #ifndef REQUEST_HPP
// #define REQUEST_HPP
// #include "./Includes/Request.hpp"
// #endif
// #ifndef RESPONSE_HPP
// #define RESPONSE_HPP
// #include "./Includes/Response.hpp"
// #endif
 #include <signal.h>
#include <sys/stat.h>
#include <stack>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>      // For input and output
#include <cstring>       // For string manipulation and error handling
#include <cstdlib>       // For standard library functions
#include <cerrno>        // For error numbers and error handling
#include <sys/socket.h>  // For socket functions
#include <netinet/in.h>  // For IP address structures and constants
#include <unistd.h>      // For read, write, and close functions
#include <fcntl.h>       // For file control options and non-blocking sockets
#include <sys/select.h>  // For the select function
#include <algorithm>
#include <string>        // For string manipulation
#include <exception>
#include <climits>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
// #include "Response/Response.hpp"

bool isOpen(int fd);
void signalHandler(int signal);
class Client;
typedef std::vector<std::string>::iterator TokenVectsIter;
void     sigintHandler(int signal);
void    Delete_dir(const std::string& folderPath);
void    ft_send(Client& client);
void sig_handler(int sig);
// ! new 
// ? status Code
#define HEADER_SIZE 67
#define FILESIZE 10
#define EXFIALE 13 
#define BUFFER_SIZE 1024
#define CONTINUE 100
#define SWITCHINGPROTOCOLS 101

#define OK 200
#define CREATED 201
#define ACCEPTED 202
#define NONAUTHORITATIVEINFORMATION 203
#define NOCONTENT 204
#define RESETCONTENT 205
#define PARTIALCONTENT 206

#define MULTIPLECHOICES 300
#define MOVEDPERMANENTLY 301
#define MOVEDTEMPORARILY 302
#define SEEOTHER 303
#define NOTMODIFIED 304
#define USEPROXY 305
#define TEMPORARYREDIRECT 307

#define BADREQUEST 400
#define UNAUTHORIZED 401
#define PAYMENTREQUIRED 402
#define FORBIDDEN 403
#define NOTFOUND 404
#define NOTALLOWED 405
#define NOTACCEPTABLE 406
#define PROXYAUTHENTICATIONREQUIRED 407
#define REQUESTTIMEOUT 408
#define CONFLICT 409
#define GONE 410
#define LENGTHREQUIRED 411
#define PRECONDITIONFAILED 412
#define CONTENTTOLARGE 413
#define URLTOOLONGE 414
#define UNSUPPORTEDMEDIATYPE 415
#define REQUESTEDRANGENOTSATISFIABLE 416
#define EXPECTATIONFAILED 417

#define INTERNALSERVERERROR 500
#define NOTIMPLEMENTED 501
#define BADGATEWAY 502
#define SERVICEUNAVAILABLE 503
#define GATEWAYTIMEOUT 504
#define HTTPVERSIONNOTSUPPORTED 505
#define CGI 19

void ft_close(int fd);