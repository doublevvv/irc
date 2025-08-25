#include "../../include/Part.hpp"

Part::Part()
{
	;
}

Part::Part(Part const &obj) : ACommand()
{
	(void)obj;
}

Part& Part::operator=(Part const &obj)
{
	(void)obj;
	return (*this);
}

Part::~Part()
{
	;
}

void Part::execute(Server &server, std::string const &command, std::vector<Client*>::iterator it, std::string const &args)
{
    std::cout << "Entering " << command << " command" << std::endl;

    std::stringstream ss(args);
    std::string channelsStr;
    ss >> channelsStr;
	std::set<int> fds;
	fds.insert((*it)->getFd());
	std::map<std::string, std::set<int> > &output = server.getOutput();

    if (channelsStr.empty())
    {
		output.insert(std::pair<std::string, std::set<int> >(ERR_NEEDMOREPARAMS((*it)->getNick()), fds));
        return;
    }

    // Recuperer le message optionnel (commentaire)
    std::string comment;
    std::getline(ss, comment);
    std::cout << "comment: " << comment << std::endl;

    // Split channels par virgule et nettoyer les espaces
    std::vector<std::string> channels;
    size_t start = 0;
    while (true)
    {
        size_t pos = channelsStr.find(',', start);
        std::string token;
        if (pos == std::string::npos)
            token = channelsStr.substr(start);
        else
            token = channelsStr.substr(start, pos - start);

        // Supprimer espaces début/fin
        size_t first = 0;
        while (first < token.size() && token[first] == ' ')
            first++;
        size_t last = token.size();
        while (last > first && token[last - 1] == ' ')
            last--;
        token = token.substr(first, last - first);

        if (!token.empty())
            channels.push_back(token);

        if (pos == std::string::npos)
            break;
        start = pos + 1;
    }

    // Boucle sur chaque channel
    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string &channelName = channels[i];

        // Verifier que le channel commence par # ou &
        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
        {
			output.insert(std::pair<std::string, std::set<int> >(ERR_BADCHANMASK((*it)->getNick(), channelName), fds));
            continue;
        }

        // Verifier que le channel existe
        std::map<std::string, Channel*> &serverChannels = server.getChannels();
        std::map<std::string, Channel*>::iterator ite = serverChannels.find(channelName);
        if (ite == serverChannels.end())
        {
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOSUCHCHANNEL((*it)->getNick(), channelName), fds));
            continue;
        }

        Channel *chan = ite->second;

        // Verifier que le client est dans le channel
        if (!chan->isClientInChannel((*it)->getNick()))
        {
			output.insert(std::pair<std::string, std::set<int> >(ERR_NOTONCHANNEL((*it)->getNick(), channelName), fds));
            continue;
        }

        // Supprimer le client du channel
        chan->removeClientFromChannel((*it)->getNick());
        std::cout << (*it)->getNick() << " left " << channelName;
        if (!comment.empty())
        {
            std::cout << " (" << comment << ")" << std::endl;
        }

        // Envoyer message PART au client
		output.insert(std::pair<std::string, std::set<int> >(RPL_PART((*it)->getNick(), (*it)->getReal(), command, channelName, comment), fds));
    }
}
