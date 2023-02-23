#include "user.hpp"
#include "server.hpp"
#include "channel.hpp"

#include "CommanHandler.hpp"

// -----------------------
/* Currently only returns the nickname, because other data has to be added/checked still */
std::string User::getPrefix() {
/* 	std::string return_msg; // = (*this->getNick());
	char* buf = this->_host;
	std::string hostname;
	hostname.assign(buf);
	std::string buffer = this->getNick(); */

	char* buf = this->_host;
	std::string hostname;
	hostname.assign(buf);

	std::string return_msg = this->getNick();

	/* :<nickname>!<username>@host CMD <target> \r\n */

	if (/* this->getUsername().empty() */this->getNick().empty() == false) {
		return_msg += "!" + /* this->getUsername() */ this->getNick();
		if (/* *this->getHost().empty() */ hostname.empty() == false)
		{
			return_msg += "@" + hostname;
		}
	}
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
void User::reply(/*const std::string& reply_msg*/ const char* reply_msg)
{
	std::string str_reply;
	str_reply.assign(reply_msg);

	std::cout << "reached this checkpoint" << std::endl;
	std::string sendMessage = ":" + getPrefix() + " " + str_reply;
	// write(":" + getPrefix() + " " + reply_msg);
	send(_fd, sendMessage.c_str(), sendMessage.size(), 0);
}

/*
* format: JOIN <channel>{,<channel>} [<key>{,<key>}]
*/
void User::execute_join_cmd(User* user, std::string& cmd_name, std::vector<std::string> args)
{
	std::cout<<"it reached the Join Command" << std::endl;


	if(this->_server->findChannel(args[0]) == NULL)
	{
		Channel* newChannel = new Channel(args[0]);
		this->_server->addChannel(newChannel);
		newChannel->addUser(this);
		std::string nickName = "nicktest";
		std::string channelName = "test";
		this->reply(this->RPL_JOIN(nickName, channelName));

		this->_channelList.push_back(newChannel);

		newChannel->addCreator(this);
		// newChannel->findAllUsers();
		// this->reply(RPL_NAMREPLY(args[0], foundChannel->findAllUsers()));
	}
	else
	{
		Channel* foundChannel = this->_server->findChannel(args[0]);
		if (foundChannel->ifBanned(this) == true)
		{
			this->reply(ERR_BANNEDFROMCHAN(args[0]));
		}
		else
		{
			// maximum of 20 channels per connection
			if (foundChannel->getClientCount() >= foundChannel->getMaxClients())
			{
				this->reply(ERR_CHANNELISFULL(this->getNick(), args[0]));
				return ;
			}
			if (this->_channelList.size() >= 20)
			{
				this->reply(ERR_TOOMANYCHANNELS(this->getNick(), args[0]));
				return ;
			}
			if (foundChannel->ifJoined(this->getNick()) != 1)
				this->reply(ERR_USERONCHANNEL(user, channel));
				return ;
			foundChannel->addUser(this);
			this->_channelList.push_back(foundChannel);
			// this->reply(RPL_NAMREPLY(args[0], foundChannel->findAllUsers()));
			foundChannel->_countClients++;
		}
	}
}

// format: KICK <channel> <user> [<comment>]
// void User::execute_kick_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
// {
// 	if(this->_channelList.ifOperator(args[1]) == NULL)
// 	{
		
// 	}

// }



/* void User::write_msg(const std::string& msg) const
{
	std::string new_msg = msg + "\r\n"; // per documentation definition line in irc end with \r
	if (send(_fd, new_msg.c_str(), new_msg.length(), 0) < 0) // c_str =copy of the string is sent
	{
		std::cerr << "error when notifying memebers of channell about someone joining\n";
	}
} */

// format: KICK <channel> <user> [<comment>] // COMMENTED OUT BY MADIS FOR DEBUGGING 23.02.
/* void User::execute_kick_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() < 2 )
	{
		user->reply(ERR_NEEDMOREPARAMS(user->getNick(), cmd_name));
		return;
	}

	const std::string channel_name = args[0];
	std::string target = args[1];
	std::string reason = "";

	// fill in reasons - commented out by Madis during debugging 
	if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() >= 1))
	{
		std::vector<std::string>::iterator start = args.begin() + 2;
		std::vector<std::string>::iterator end = args.end();

		while (start != end)
		{
			reason.append((*start) + " ");
			start++;
		}
	}

	// check if user that wants to kick someone is in same channel
	Channel* foundChannel = user->get_channel_if_in(channel_name);
	if (foundChannel == NULL)
	{
		user->reply(ERR_NOTONCHANNEL(user->getNick(), foundChannel._channelName));
		return;
	}

	// check if user is admin
	if (foundChannel->ifOperator(*_nick) == false) // overload or via getName()
	{
		user->reply(ERR_CHANOPRIVSNEEDED(user->getNick(), foundChannel));
		return;
	}

	// check if target-user is in channel
	User* target_user = foundChannel->get_user_if_in(target);
	if (target_user == NULL)
	{
		user->reply(ERR_NOSUCHNICK(target, channel_name));
		user->reply(ERR_USERNOTINCHANNEL(target, channel_name));
		return;
	}

	// actual kicking

	foundChannel->notify_others(RPL_KICK(user, channel_name, target, reason), this);

	target_user->deleteChannel(*(target_user->get_channel_if_in(channel_name))->getName());

	foundChannel->deleteUser(target);

	
	std::cout << target << " has been kicked from channel " << channel_name << ".\n";
} */

// format: QUIT (:)[<quitmsg>] // COmmanted out by Madsi for debugging on 23.02.
/* void User::execute_quit_cmd(const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.empty() == true)
	{
		reason = "no reason";
	}
	else
	{
		reason = args[0];
		if (reason[0] == ':')
		{
			reason = reason.substr(1);
		}	
	}
	this->reply(RPL_QUIT(this->getPrefix(), reason));


 // ---------------------------------------------------------------------

	//send quit msg
	std::vector<Channel *> channel = getChannels();
	for(int i = 0;  i < getChannels().size(); i++)
	{
		if (args.size() == 0)
		{
			channel[i]->notify_others("QUIT", this);
			channel[i]->delete_user(this);
			
		}
		else if (args.size() > 0)
		{
			std::string quitmsg = args[0];
			if (quitmsg.at(0) == ':')
			{
				quitmsg = quitmsg.substr(1);
			}
			channel[i]->notify_others("QUIT :" + args[0], this);
			channel[i]->delete_user(this);
		}
	}
	setFd(-1);
	_isRegistered = false;
	//killUser(this, "User hast quit"); //When command is implemented, we only need to call it
} */


// format: PING <server1> [<server2>]
/* void User::execute_ping_cmd(const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() == 1)
	{
		if (!strcmp((const char *)args[0][0], (const char *)_host)) //comparing args[0] to servername, is _host the servername? ANswer: no, it is not, the server name is _name unders the server, and the _host is the IP/host of a connected client
		{
			reply(("PONG " + args[0]).c_str());
		}
		else
		 reply(ERR_NOSUCHSERVER(args[0]));
	}
} */

// format: INVITE <nickname> <channel>
// void User::execute_invite_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
// {
// 	// check if user is operator operator rights of the channel
// 	if (args.size() < 2)
// 		reply(ERR_NEEDMOREPARAMS(_nick, cmd_name));
// 	else if (args.size() == 2)
// 	{
// 		//is nickname existing
// 			//using the server function to find the nickname

// 		//is channel existing
// 			//using the server function to find the channel

// 		//is the inviter channel operator
// 	}
// }

// std::string convert_to_string(char* string)
// {
// 	std::string str; // = (*this->getNick());
// 	str.assign(string);

// 	return (str);
// }

// format: NICK <nickname>
void User::execute_nick_cmd(User* user, const std::string& cmd_name, std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		user->reply(ERR_NONICKNAMEGIVEN((*user->getNick()).c_str())); // c_str returns c version of the std::string
		return;
	}

	std::string nickname = args[0];

	if (user->_server->findByNick(nickname) != NULL)
	{
		user->reply(ERR_NICKNAMEINUSE(/*convert_to_string*/(user->getNick())));
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
	user->reply(ERR_ALREADYREGISTRED(user->getNick()));
	return;
 }

 if (args.size() < 4)
 {
	user->reply(ERR_NEEDMOREPARAMS(user->getNick(), "USER"));
	return;
 }

 user->setUsername(args[0]);
 user->setRealname(args[3]);
 user->reply(RPL_WELCOME(user->getNick()));

}
