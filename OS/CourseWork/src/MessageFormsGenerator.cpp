#include "MessageFormsGenerator.hpp"

pt::ptree ClientAuth::getForm()
{
	pt::ptree data;

	data.put<std::string>("Message.type", "Auth");
	data.put<std::string>("Auth.login", login);

	return data;
}

pt::ptree ServerAuthSucceed::getForm()
{
	pt::ptree authData;

	authData.put<std::string>("Message.type", "Auth");
	authData.put<bool>("Auth.status", true);
	authData.put<long long>("Auth.givenId", id);
	authData.put<unsigned short>("Auth.portToSend", portToSend);
	authData.put<unsigned short>("Auth.portToRecv", portToRecv);

	return authData;
}

pt::ptree ServerAuthFailed::getForm()
{
	pt::ptree authData;

	authData.put<std::string>("Message.type", "Auth");
	authData.put<bool>("Auth.status", false);
	authData.put<std::string>("Auth.errorMessage", message);

	return authData;
}

pt::ptree ServerPing::getForm()
{
	pt::ptree data;
	data.put<std::string>("Message.type", "Ping");
	data.put<long long>("Message.clientId", id);

	return data;
}

pt::ptree ClientPing::getForm()
{
	pt::ptree data;

	data.put<std::string>("Message.type", "Ping");
	data.put<long long>("Message.clientId", id);
	data.put<bool>("Message.ping.status", true);

	return data;
}

void MessageForAll::setMessage(std::string _message)
{
	message = _message;
}

pt::ptree MessageForAll::getForm()
{
	pt::ptree data;
	data.put<std::string>("Message.type", "ForAll");
	data.put<std::string>("Message.message", message);

	return data;
}

void GameActionRequest::setAction(GameClientAction _action)
{
	action = _action;
}

pt::ptree GameActionRequest::getForm()
{
	pt::ptree data;
	data.put<std::string>("Message.type", "GameAction");
	data.put<GameAction>("Game.action.type", action);
}

void GameActionRequest::setWord(std::string _word)
{
	word = _word;
}

void GameActionReply::setAction(GameAction _action)
{
	action = _action;
}

void GameActionReply::setWord(std::string _word)
{
	word = _word;
}

pt::ptree GameActionReply::getForm()
{
	pt::ptree data;
	
	data.put<std::string>("Message.type", "GameAction");
	data.put<long long>("Message.id", id);
	data.put<std::string>("Game.login", login);
	data.put<GameAction>("Game.action.type", action);
	data.put<std::string>("Game.action.word", word);

	if (action == GameAction::guessWord && !guessed.has_value()) {
		throw std::logic_error("Guessed not specified. Please set guessed login");
	}

	data.put<std::string>("Game.action.guessed", guessed);

	return data;
}

void GameActionReply::setGuessed(std::string guessedLogin)
{
	guessed = guessedLogin
}
