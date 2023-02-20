#include "user.hpp"

// -----------------------
/* Currently only returns the nickname, because other data has to be added/checked still */
std::string User::getPrefix() const
 {
	std::string return_msg = this->getNick();

	/* if (this->_nick.size() != 0)
	{
		return_msg += "!" + this->getUsername()
		if (this->_hostname.size() != 0)
		{
			return_msg += "@" + this->getHostname(); // no hostname func yet
		}
	} */
	return(return_msg);
 }

/*
*	Use of the extended prefix (['!' <user> ] ['@' <host> ]) must
	not be used in server to server communications and is only
	intended for server to client messages in order to provide
	clients with more useful information about who a message is
	from without the need for additional queries.
	-> calling start in server leading to here.
*/
void User::reply(const std::string& reply_msg)
{
	std::cout << "This message from reply function under User object\n";
	/* write(":" + getPrefix() + " " + reply_msg); */
}

/*
* format: JOIN <channel>{,<channel>} [<key>{,<key>}]
*/
void User::execute_join_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.empty() == true)
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNick(), cmd_name ))
		return ;
	}
	
	std::string channel_name = args[0];
	if (args.size() > 1)
	{
		std::string password = args[1];
	}

	// maximum of 20 channels per conenction
	if (user->_channels.size() >= 20)
	{
		user->reply(ERR_TOOMANYCHANNELS(user->getNick(), channel_name));
		return ;
	}

	Channel* channel = _server->getChannel(channel_name); // still needs _server in user
	if (!channel)
	{
		_server->createChannel(some params) // need create channel in server
	}

	if (channel->getClientsCount() >= channel->getMaxClients())
	{
		user->reply(ERR_CHANNELISFULL(user->getNick(), channel_name));
		return ;
	}

	if (channel->getPWD().compare(password) != 0)
	{
		user->reply(ERR_BADCHANNELKEY(user->getNick(), channel_name));
		return ;
	}
	// actual joining
	channel->addUser(user);
	_channels.push_back(channel);

	std::string user_list;
	std::vector<User*>::iterator start = channel->_userLogList.begin();
	std::vector<User*>::iterator end = channel->_userLogList.end();

	while (start != end)
	{
		user_list.append((*start)->getNick());
		start++;
	}

	reply(RPL_NAMEREPLY(user->getNick(), channel->getName(), user_list));
	reply(RPL_ENDOFNAMES(user->getNick(), channel->getName()));

	channel->notify_others(RPL_JOIN(getPrefix(), channel->getName()));
	std::cout << user->getNick() << " has joined channel " << channel->getName() << std::endl;
}

void User::write_msg(const std::string& msg) const
{
	std::string new_msg = msg + "\r\n"; // per documentation definition line in irc end with \r
	if (send(_fd, new_msg.c_str(), new_msg.length(), 0) < 0) // c_str =copy of the string is sent
	{
		std::cerr << "error when notifying memebers of channell about someone joining\n";
	}
}

// format: KICK <channel> <user> [<comment>]
void User::execute_kick_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() < 2 )
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNick(), cmd_name));
		return;
	}

	std::string channel_name = args[0];
	std::string target = args[1];
	std::string reason = "";

	// fill in reasons
	if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() >= 1))
	{
		std::vector<std::string>::iterator start = args.begin() + 2;
		std::vector<std::string>::iterator start = args.end();

		while (start != end)
		{
			reason.append((*start) + " ");
			start++;
		}
	}

	// check if user that wants to kick someone is in same channel
	Channel* channel = user->get_if_in_channel(const std::string& channel_name);
	if (channel == NULL)
	{
		user->reply(ERR_NOTONCHANNEL(user->getNick(), channel_name));
		return;
	}

	// check if user is admin
	if (user != channel->getAdmin()) // overload or via getName()
	{
		user->reply(ERR_CHANOPRIVSNEEDED(user->getNick(), channel_name));
		return;
	}

	// check if target-user is in channel
	User* target_user = channel->get_user_if_in(target);
	if (target_user == NULL)
	{
		user->reply(ERR_NOSUCHNICK(target, channel_name));
		user->reply(ERR_USERNOTINCHANNEL(target, channel_name));
		return;
	}

	// actual kicking

	channel->notify_others(RPL_KICK(user, channel_name, target, reason));

	channel->delete_user(target_user);

	std::cout << target << " has been kicked from channel " << channel_name << ".\n";
}


// format: QUIT (:)[<quitmsg>]
void User::execute_quit_cmd(const std::string& cmd_name, std::vector<std::string> args)
{
	//send quit msg
	std::vector<Channel *> cha = getChannels();
	for(int i = 0;  i < getChannels().size(); i++)
	{
		if (args.size() == 1) // args.size() == 0 -> the cmmd-name is not in args
		{
			cha[i]->notify_others("QUIT", this);
		}
		else if (args.size() == 2) // args.size() > 0
		{
			std::string quitmsg = args[0];
			if (quitmsg.at(0) == ':')
			{
				quitmsg = quitmsg.substr(1);
			}
			cha[i]->notify_others("QUIT :" + args[1], this); // args[0]
			
		}
	}

	//quit session
	// what actually does the client do to quit?

}


// format: PING <server1> [<server2>]
void User::execute_ping_cmd(const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() == 1)
	{
		if (!strcmp((const char *)args[0][0], (const char *)_host))
		{
			reply("PONG " + args[0]);
		}
		else
		 reply(ERR_NOSUCHSERVER(args[0]));
	}
	// else if (args.size() == 2)
	// {
	// 	if (!strcmp((const char *)args[0][0], (const char *)_nick[0]))
	// 	{
	// 		if (!strcmp((const char *)args[1][0], (const char *)_host))
	// 		{
	// 			reply("PONG " + args[1]);
	// 		}
	// 		else
	// 			reply(ERR_NOSUCHSERVER(args[0]))
	// 	}
	// 	else
	// 		reply(ERR_NOORIGIN())
	// }
}

// format: INVITE <nickname> <channel>
void User::execute_invite_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{

}

// format: NICK <nickname>
void User::execute_nick_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		user->reply(ERR_NONICKNAMEGIVEN(user->getNick()));
		return;
	}

	std::string nickname = args[0];

	if (user->_server->findByNick(nickname) != NULL)
	{
		user->reply(ERR_NICKNAMEINUSE(user->getNick()));
		return;
	}

	user->setNick(nickname);
	user->reply(RPL_WELCOME(nickname));
}

/*
* format: USER <username> <hostname> <servername> <realname>
* ***********************************************************
* used in communication between servers to indicate new user
* arriving on IRC, since only after both USER and NICK have been
* received from a client does a user become registered.
*/
void User::execute_user_cmd(User* user, std::vector<std::string> args)
{
 if (user->isRegistered())
 {
	user->reply(ERR_ALREADYREGISTERED(user->getNick()));
	return;
 }

 if (args.size() < 4)
 {
	user->reply(ERR_NEEDMOREPARAMS(user->getNick()), "USER");
	return;
 }

 user->setUsername(args[0]);
 user->setRealname(args[3]);
 user->reply(RPL_WELCOME(user->getNick()));

}