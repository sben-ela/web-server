/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:34:48 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 17:47:32 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Request.hpp"

class Response : public Request
{
    public:
        Response();
        Response(const Response& other);
        Response& operator=(const Response& other);
        void    Function();
        const char* get_content_type(const char* path);
        ~Response();
};
