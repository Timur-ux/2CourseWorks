#include "Messages/MessageFormsGenerator.hpp"
#include "print.hpp"

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

pt::ptree game::GameActionForm::getForm()
{
	pt::ptree data;
	data.put<std::string>("Message.type", "GameAction");
	data.put<int>("Game.action.type", static_cast<int>(action));

	return data;
}

pt::ptree game::reply::Form::getForm() {
	pt::ptree data = GameActionForm::getForm();

	data.put<long long>("Message.id", id);
	data.put<std::string>("Game.login", login);

	return data;
}

pt::ptree game::reply::SelectWordForm::getForm() {
	pt::ptree data = Form::getForm();

	data.put<std::string>("Game.action.word", word);

	return data;
}

pt::ptree game::reply::GuessWordForm::getForm() {
	pt::ptree data = Form::getForm();

	data.put<std::string>("Game.action.word", word);
	data.put<std::string>("Game.action.opponent", opponent);

	return data;
}

pt::ptree game::request::RequestToServerForm::getForm() {
	pt::ptree data;
	data.put<std::string>("Message.type", "RequestToServer");
	data.put<int>("Request.type", static_cast<int>(type));
	data.put<std::string>("Request.sender.login", senderLogin);

	return data;
}

pt::ptree game::request::GetLoginsListForm::getForm() {
	pt::ptree data = RequestToServerForm::getForm();

	return data;
}

pt::ptree game::request::CreateNewGameForm::getForm() {
	pt::ptree data = RequestToServerForm::getForm();

	pt::ptree loginsData;
	for (std::string& login : logins) {
		pt::ptree child;
		child.put<std::string>("", login);
		loginsData.push_back(std::make_pair("", child));
	}

	data.add_child("Request.logins", loginsData);

	print() << data << std::endl;

	return data;
}

pt::ptree game::request::CreateNewGameForm::getForm() {
	pt::ptree data;

	data.put<std::string>("Message.type", "CreateNewGame");
	data.put<std::list<std::string>>("Game.init.logins", players);

	return data;
}

pt::ptree game::reply::ReplyFromServerForm::getForm() {
	pt::ptree data;

	data.put<std::string>("Message.type", "ReplyFromServer");
	data.put<int>("Reply.type", static_cast<int>(type));

	return data;
}

pt::ptree game::reply::GetLoginsListForm::getForm() {
	pt::ptree data = 
}