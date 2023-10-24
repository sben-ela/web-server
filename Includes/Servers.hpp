/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:54:36 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 18:16:04 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Configuration.hpp"
#include "Client.hpp"

class Servers
{
    private:
        std::vector<Configuration>   _servers;
        std::vector<Client>          _client;
    public:
        Servers();
        Servers(const Servers& other);
        Servers& operator=(const Servers& other);
        int    ConfigFileParse(std::string file);
        void printServerData() const;
        int AllServers();
        void checkServers();
        ~Servers() {};
};