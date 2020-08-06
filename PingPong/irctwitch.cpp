#include "irctwitch.h"

Irctwitch::Irctwitch(std::string oauth, std::string nickname) {
	sf::IpAddress ip("irc.chat.twitch.tv");
	sf::Socket::Status status = socket.connect(ip, 6667);

	if (status != sf::Socket::Done) {
		std::cout << "Error on connection!" << std::endl;
	}
	else {
		login = oauthPhrase + oauth + "\r\n";
		name = nicknamePhrase + nickname + "\r\n";
		channel = joinChannelPhrase + nickname + "\r\n";

		std::thread first([this] {this->run();});
		first.detach();
	}
}

void Irctwitch::run() {
	std::string temp("");
	std::string token("");
	authenticate();
	while (true) {
		memset(&data[0], 0, sizeof(data));
		socket.receive(data, 1024, received);

		int pos = 0;

		std::string read(data);

		token += temp + "";
		std::string temp("");

		while (pos != std::string::npos) {
			pos = read.find("\r\n");
			if (pos == std::string::npos) {
				break;
			}
			if (token == "PING :tmi.twitch.tv") {
				socket.send(response.c_str(), response.length());
			}
			token += std::string(read.substr(0, pos));
			
			lines.push(token);
			read = read.substr(pos+2, read.length()-1);
			token = "";
		}
		temp = std::string(read.substr(0, read.length()-1));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// std::cout << "OK" << std::endl;
	}
	
}

void Irctwitch::authenticate() {
	// login
	socket.send(login.c_str(), login.length());
	socket.send(name.c_str(), name.length());
	socket.send(channel.c_str(), channel.length());

	// socket.send("PRIVMSG #ksk_nico :HEYO\r\n", 25);
}