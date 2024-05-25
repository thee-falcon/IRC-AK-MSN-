/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakran <omakran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:45:48 by omakran           #+#    #+#             */
/*   Updated: 2024/05/26 00:45:56 by omakran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"

Client::Client(int _fd) : fd(_fd), authenticated(false) {
    std::cout << "Client created with fd: " << fd << std::endl;
}

Client::~Client() {}

std::vector<std::string> Client::splitMessage(const std::string& message) {
    std::vector<std::string>    result;
    std::istringstream stream(message);
    std::string                 token;

    // split the message by whitespace and store each part in the `result` vector.
    while (stream >> token) {
        //  if there's data to read from the stream
        result.push_back(token);
    } 
    return result;
}

void    Client::handleMessage(const std::string& message) {
    std::cout << "Handling message: " << message << std::endl;
    std::vector<std::string>    parts = splitMessage(message);

    if (parts.empty())
        return ; // ignore empty messages.

    //                          extract the command from the message
    std::string                 command = parts[0];
    if (command == "NICK") {
        if (parts.size() > 1)
            handleNick(parts[1]);
    } else if (command == "USER") {
        if (parts.size() > 1)
            handleUser(parts[1]);
    } else if (command == "JOIN") {
        if (parts.size() > 1)
            handleJoin(parts[1]);
    } else if (command == "PRIVMSG") {
        if (parts.size() > 2)
            handlePrivmsg(parts[1], message.substr(message.find(parts[2])));
    } 
    // else if (command == "KICK") {
    //     if (parts.size() > 1)
    //         handleKick(parts[1]);
    // }
    // else if(commaand == "TOPIC"){
    //     if(parts.size() > 1)
    //         handleTopic(parts[1]);
    // }
    // else if(command == " INVITE"){
    //     if(parts.size() > 1)
    //         handleInvite(parts[1]);
    // }
    // else if (command == "MODE") {
    //     if (parts.size() > 1)
    //         handleMode(parts[1]);
    // }

    else {
        std::cerr << "Uknowon command: " << command << std::endl;
    }
}

void    Client::handleNick(const std::string& nick) {
    nickname = nick; // set the client's nickname.
    std::cout << "Nickname set to : " << nickname <<std::endl;
}

void    Client::handleUser(const std::string& user) {
    username = user;
    std::cout << "Username set to: " << username << std::endl;
}

void    Client::handleJoin(const std::string& channel) {
    channels.push_back(channel); // add the client to the channel
    std::cout << "Joined channel: " << channel << std::endl;
}

void    Client::handlePrivmsg(const std::string& target, const std::string& message) {
    // print the private message to the target.
    std::cout << "Private messge to " << target << ": " << message << std::endl; 
}

std::string Client::getUserName() const {
    return username;
}

int Client::getFd() const {
    return fd;
}

bool    Client::isAuthenticated(void) const {
    return authenticated;
}

void    Client::setAuthenticated(bool authenticated) {
    authenticated = authenticated;
}

void    Client::newMessage(const std::string &message) {
    messageQueue.push_back(message);
}