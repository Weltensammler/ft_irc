
user.cpp/hpp:
added execute_join_cmd();
added getchannel();
added reply();
getPrefix();
write_msg(const std::string& msg) const

channel.hpp/cpp:
added getName();
added getmaxclients();
added getClientCount();
addUser(User* user);
notify_others(const std::string& msg, User* skip);

server hpp/cpp.
added getchannel(const std::stirng channelname);

added errormsgs

added responses.hpp, commandhandler.hpp/cpp, join.cpp, readme.txt