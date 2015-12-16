/** \file Message.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Message.
 * \todo Andrzej napisze, a na razie zaślepki.
 */

#include "Message.hpp"

using namespace message;

unsigned char Message::getCode() const
{
	return code;
}

unsigned char Message::getCategory() const
{
	return 0;
}

unsigned char Message::getState() const
{
	return 0;
}

unsigned char Message::getSubcategory() const
{
	return 0;
}

hostMessage::hostMessage( HostSub sub, State state, const std::vector<Ip> & addresses )
{

}

hostMessage::hostMessage( State state )
{

}

unsigned short hostMessage::getAgentCount() const
{
	return 0;
}

std::vector<Ip> & hostMessage::getAddresses() const
{
	std::vector<Ip> v;
	return v;
}

taskMessage::taskMessage( TaskSub sub,
						State state,
						bool respectPriority,
						unsigned short priority,
						unsigned long taskId,
						const std::chrono::steady_clock::time_point & timestamp )
{

}

taskMessage::taskMessage( State state )
{

}

bool taskMessage::getRespectPriority()
{
	return 0;
}

unsigned short taskMessage::getPriority() const
{
	return 0;
}

unsigned long taskMessage::getTaskId() const
{
	return 0;
}

std::chrono::steady_clock::time_point & taskMessage::getTimestamp() const
{
	std::chrono::steady_clock::time_point t;
	return t;
}

depMessage::depMessage ( State state, std::vector<unsigned long> & tasks )
{

}

depMessage::depMessage ( State state )
{

}

unsigned short depMessage::getTaskCount()
{
	return 0;
}

std::vector<unsigned long> & depMessage::getTasks()
{
	std::vector<unsigned long> v;
	return v;
}

fileMessage::fileMessage(State state,
						bool isMainFile,
						unsigned long taskId,
						std::string filename,
						const std::ifstream & file )
{

}

fileMessage::fileMessage ( State state )
{

}

bool fileMessage::getIsMainFile()
{
	return 0;
}

unsigned long fileMessage::getTaskId()
{
	return 0;
}

std::string fileMessage::getFilename()
{
	return std::string();
}

std::ofstream & fileMessage::getFile()
{
	std::ofstream o("file",std::ofstream::out);
	return o;
}

retMessage::retMessage( State state,
					unsigned char exitStatus,
					unsigned long taskId,
					std::string filename,
					const std::ifstream & file )
{

}

retMessage::retMessage ( State state )
{

}

unsigned char retMessage::getExitStatus()
{
	return 0;
}

unsigned long retMessage::getTaskId()
{

}

std::string retMessage::getFilename()
{
	return std::string();
}

std::ofstream & retMessage::getFile()
{
	std::ofstream o("file",std::ofstream::out);
	return o;
}

synMessage::synMessage ( State state )
{

}

pingMessage::pingMessage ( State state )
{

}

errMessage::errMessage ( ErrSub sub, State state, unsigned char errCode )
{

}

errMessage::errMessage ( State state )
{

}

unsigned char errMessage::getErrCode () const
{

}
























