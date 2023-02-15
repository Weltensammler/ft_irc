# pragma once

#ifndef IRC_CHANNEL_HPP
# define IRC_CHANNEL_HPP

#include <vector>

class Channel
{
    public:
        Channel(std::string const & newChannelName);
        ~Channel();
        Channel();

        std::string const  &    getName() const;
        void                    setName(std::string const & newName);

        std::vector<User *>     getUsers() const;
        void                    removeUser(User *);
        void                    addUser(User *);
        void                    setOperator(User *);

    protected:


    private:
        std::string             name;
        std::vector<User *>     users;

}

#endif
