#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <chrono>
#include <iostream>
#include <tuple>
class Irctwitch {
private:
	const std::string oauthPhrase = "PASS oauth:";
	const std::string nicknamePhrase = "NICK ";
	const std::string response = "PONG :tmi.twitch.tv";
	const std::string joinChannelPhrase = "JOIN #";
	std::string login;
	std::string name;
	std::string channel;
	void authenticate();
	void run();
	std::tuple<std::string, std::string> slice(std::string s);

public:
	char data[1024];
	std::size_t received;
	sf::TcpSocket socket;
	std::queue<std::tuple<std::string, std::string>> lines;
	Irctwitch(std::string oauth, std::string nickname);
};