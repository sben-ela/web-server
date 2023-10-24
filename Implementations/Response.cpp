/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:27:48 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 17:45:42 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Response.hpp"

Response::Response() {}

Response::Response(const Response& other) : Request(other) {}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
        Request::operator=(other);
    return *this;
}

Response::~Response() {}