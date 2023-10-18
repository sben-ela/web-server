/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:54:36 by aybiouss          #+#    #+#             */
/*   Updated: 2023/09/30 18:13:50 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Configuration.hpp"
#include "Socket.hpp"
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