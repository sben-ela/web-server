/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:27:48 by aybiouss          #+#    #+#             */
/*   Updated: 2023/09/14 16:09:43 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Response.hpp"

void    Response::Function()
{
    // // ! the structure of it
    // if (_method == "GET")
    // {
    //     if (_path) {
    //         if () { /*Im gonna search if the path is on the configfile*/
    //             ;
    //         } else {
    //             return setResponseStatus("404 Not Found Response.");
    //         }
    //     } else {
    //         return setResponseStatus("400 Bad Request Response.");
    //     }
    // }
    // else if (_method == "POST")
    // {
    //     ;
    // }
    // else if (_method == "DELETE")
    // {
    //     ;
    // }
    // else
    // {
    //     ;
    // }

    // // for (std::map<std::string, std::string>::iterator it = _header.begin(); it != _header.end(); it++)
    // // {
    // //     std::cout << it->first << it->second << std::endl;
    // // }
}

Response::Response() {}

Response::Response(const Response& other) : Request(other) {}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
        Request::operator=(other);
    return *this;
}

Response::~Response() {}