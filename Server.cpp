/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:28:39 by mravily           #+#    #+#             */
/*   Updated: 2022/07/08 18:38:09 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"
#include <iostream>

void irc::Server::setDatatime()
{
	time_t tmm = time(0); 
	this->_datatime = asctime(gmtime(&tmm));
	this->_datatime.erase(--_datatime.end());
};

void irc::Server::setPassword(std::string pass) {this->_password = pass;};
std::string irc::Server::getPassword() {return (_password);};
std::string irc::Server::getVersion() {return (_version);};
std::string irc::Server::getDatatime() {return (_datatime);};
std::map<int, irc::User *> irc::Server::getUsers() {return (_users);};
std::string irc::Server::getUsrMode() {return (_usrMode);};
std::string irc::Server::getChanMode() {return (_chanMode);};

/*
** @brief Créer un point de communication 
** @param domain cette constante désigne les protocoles internet IPv4 
** @param type le type indique le style de communication désiré entre les deux participants
** @param protocol le protocole est souvent mis à zéro car l'association de la famille de protocole et du type de communication définit explicitement le protocole de transport.
*/
void	irc::Server::setSocketServer(int domain, int type, int protocol)
{
	if ((this->_socketServer = socket(domain, type, protocol)) < 0)
		DisplayError("Socket: ");
}

/*
** @brief Ajoute socket à la list des sockets surveiller par poll
** @param socket socket to add
*/
void	irc::Server::addSocket(int socket)
{
	this->_pollFds.push_back(pollfd());
	this->_pollFds.back().fd = socket;
	this->_pollFds.back().events = POLLIN;
}

/*
** @brief Manipulation du socket afin qu'il soit non bloquant
** @param F_SETFL Positionner les nouveaux attributs d'état pour le fichier à la valeur indiquée par arg.
** @param O_NONBLOCK Cela évite de bloquer "longtemps" l'ouverture du fichier.
*/
void	irc::Server::manipSocket(int fd, int cmd, int arg)
{
	if (fcntl(fd, cmd, arg) < 0)
		DisplayError("Fcntl: ");
}

/*
** @brief Configure les options du socket
** @param fd Socket à modifier les options
** @param level lvl approprier au protocol TCP 
** @param optname Indique les règles permettant la validation des adresses fournies dans un appel bind doivent autoriser la réutilisation des adresses locales
** @param optval un paramètre non nul valide une option booléenne, et zéro l'invalide
** @param optlen taille du param optval
*/
void	irc::Server::configSocketServer()
{
	int opt = 1;
	if (setsockopt(this->_pollFds[0].fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		DisplayError("SetSockOpt: ");
	manipSocket(this->_pollFds[0].fd, F_SETFL, O_NONBLOCK);
}


/*
** @brief Structure contenant les informations relatives au socket
** @param sin_family famille d'adresses
** @param sin_addr.s_addr INADDR_ANY (0.0.0.0) signifie un attachement à n'importe quelle adresse
** @param sin_port indique sur quel port le serveur se met en attente de connexion
*/
void irc::Server::setAddressServer(char *port)
{	
	(this->_addrServer.sin_family) = AF_INET;
	(this->_addrServer.sin_addr.s_addr) = htonl(INADDR_ANY);
	(this->_addrServer.sin_port) = htons(atoi(port));
}

/*
** @brief Affecte l'adresse spécifiée dans addr à la socket référencée par le descripteur de fichier sockfd.
** @param sockfd descripteur de fichier du socket
** @param addr structure d'adresse
** @param addrlen indique la taille, en octets de la struct d'address
*/
void irc::Server::bindAddress()
{
	if (bind(this->_pollFds[0].fd, (const struct sockaddr *)&this->_addrServer, sizeof(this->_addrServer)) < 0)
		DisplayError("Bind: ");
}

/*
** @brief Ecoute des connexions sur une socketServer
** @param sockfd est un descripteur de fichier qui fait référence à une socket
** @param backlog définit une longueur maximale jusqu'à laquelle la file des connexions en attente pour sockfd peut croître
*/
void irc::Server::listenAddress()
{
	if (listen(this->_pollFds[0].fd, (this->_addrServer.sin_port)) < 0)
		DisplayError("Bind: ");
}

/*
** @brief Attends un évenement sur le socketServer
** @param fd fd sur lequel on attend un évenement
** @param nfds Nombres de FD
** @param delai L'argument délai définit une limite supérieure, en millisecondes, sur le temps pendant lequel poll() bloquera.
*/
void irc::Server::monitoring()
{
	if (poll(&(this->_pollFds[0]), (this->_pollFds.size()), (60 * 1000) / 10) < 0)
		DisplayError("Poll: ");
}

/*
** Si le socketServer est en attente de donnée de lecture
** Ajout du client a la list des socket surveiler par poll
*/	
void irc::Server::acceptClient()
{
	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	int socketClient;
	if ((socketClient = accept(this->_pollFds[0].fd, (struct sockaddr *)&addrClient, &csize)) < 0)
		DisplayError("Accept: ");

	this->_users[socketClient] = new User(this, socketClient, addrClient);
	std::cout << "[SERVER] Nouvelle connexion client sur le server\n"
	<< "[SERVER] Socket [" << socketClient << "] | IP [" <<  _users[socketClient]->getHostaddr().c_str() << "]\n"
	<< "[SERVER] Authentification en cours..." << std::endl;
	
	addSocket(socketClient);
}

void irc::Server::runtime()
{
	monitoring();
	if (this->_pollFds[0].revents == POLLIN)
		acceptClient();
	else
	{
		for (std::vector<pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it)
			if ((*it).revents == POLLIN)
				this->_users[(*it).fd]->getMessages();
	}
}

bool getType(std::string name) {return (name[0] == '&');};

void irc::Server::createChan(std::vector<std::string> infos, irc::User* usr)
{
	std::vector<std::string> names = split(infos[0], ",");
	std::vector<std::string> keys;
	//Check la validité des names
	std::vector<std::string>::iterator itp;
	if (infos.size() > 1)
	{
		std::vector<std::string> keys = split(infos[1], ",");
		itp = keys.begin();
	}	
	std::vector<std::string>::iterator itn(names.begin());
	for (; itn != names.end(); itn++)
	{
		if (infos.size() > 1 && itp != keys.end())
			_channels.push_back(Channel(getType((*itn)), (*itn), usr, (*itp++)));
		else
			_channels.push_back(Channel(getType((*itn)), (*itn), usr));
		
		usr->addWaitingSend(":" + usr->getClient() + " JOIN " + (*itn) + CRLF);
		usr->reply(331, &_channels.back());
		usr->addWaitingSend(":" + usr->getClient() + " MODE " + (*itn) + " +" + _channels.back().getModes() + CRLF);
		usr->reply(353, &_channels.back());
		usr->reply(366, &_channels.back());
	}
}

irc::Server::Server(char *port, char *pass) : _version("1.42"), _password(pass), _usrMode("iswo"), _chanMode("opsitnmlbvk")
{
   	setDatatime();
	setSocketServer(AF_INET, SOCK_STREAM, 0);
	addSocket(this->_socketServer);
	configSocketServer();
	setAddressServer(port);
	bindAddress();
	listenAddress();
}

irc::Server::~Server()
{
	close(this->_socketServer);
	for (std::vector<pollfd>::iterator it(_pollFds.begin()); it != _pollFds.end(); it++)
		close((*it).fd);
}
