/** \file Message.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Message.
 * \todo Andrzej napisze, a na razie zaślepki.
 */

#include <iostream>

#include "Message.hpp"
#include "debug.h"

using namespace message;
using namespace std;

//------------------------------
// Message
//------------------------------
Message::Message( Category category ) : code( (unsigned char) category )
{

}

Message::Message( Category category, unsigned long bufferSize ) : code( (unsigned char) category ), bufferSize( bufferSize )
{

}

Message::Message( Category category, State state ) : code( (unsigned char) category + (unsigned char) state )
{
	buffer = new char [1];

	buffer[0] = code;

	bufferSize = 1;

	
	std::cout << "CODE" << std::hex << (unsigned)code << std::endl;
	std::cout << std::dec;
}

Message::~Message()
{
	if( buffer )
		delete [] buffer;
}


bool Message::checkMessage() const
{
	if(getCategory()<=7 && getSubcategory()<=7 && getState()<=3)
	{
		if(getCategory()>(unsigned char)message::Category::HOST)
		{
			if(getSubcategory()>2)
				return false;
		}
	}
	/**< \todo uzupełnić sprawdzanie kodów, ale to mało ważne */
	return (getCategory()<=7 && getSubcategory()<=7 && getState()<=3)?true:false;
}


unsigned char Message::getCode() const
{
	return code;
}

unsigned char Message::getCategory() const
{
	return code&0xE0;
}

unsigned char Message::getState() const
{
	return code&0x03;
}

unsigned char Message::getSubcategory() const
{
	return code&0x1C;
}

char * Message::getBuffer() const
{
	return buffer;
}

unsigned long Message::getBufferSize() const
{
	return bufferSize;
}

void Message::print() const
{
	if( buffer )
		for( unsigned long i = 0; i < bufferSize; ++i )
			std::cout << std::hex << ( (unsigned)buffer[i] & 0xFF );
	else
		std::cout << "buffer == nullptr";
	std::cout << std::endl;
	std::cout << std::dec;
}


//------------------------------
// hostMessage
//------------------------------
hostMessage::hostMessage( HostSub sub, State state, const std::vector<Ipv4> & addr ) :
	Message::Message( Category::HOST ),
	sub(sub),
	state(state),
	addresses(addr)
{
	code += (unsigned char)state;

	unsigned addrSize = addr.size();

	bufferSize = 4 * ( addrSize + 1);

	buffer = new char [addrSize];

	buffer[0] = code;
	buffer[1] = 0x00;
	buffer[2] = addrSize & 0x00FF;
	buffer[3] = ( addrSize >> 8 ) & 0x00FF;

	unsigned long a;

	for( unsigned i = 0; i < addrSize; ++i )
	{
		a = addr[i].getAddressNum();
		buffer[ (i + 1) * 4     ] =   a         & 0x00FF;
		buffer[ (i + 1) * 4 + 1 ] = ( a >> 8  ) & 0x00FF;
		buffer[ (i + 1) * 4 + 2 ] = ( a >> 16 ) & 0x00FF;
		buffer[ (i + 1) * 4 + 3 ] = ( a >> 24 ) & 0x00FF;
	}
}

hostMessage::hostMessage( State s ) :
	Message::Message( Category::HOST, s ),
	state(s)
{

}

unsigned short hostMessage::getAgentCount() const
{
	return addresses.size();
}

std::vector<Ipv4> & hostMessage::getAddresses()
{
	return addresses;
}

//------------------------------
// taskMessage
//------------------------------
taskMessage::taskMessage( TaskSub sub,
                          State s,
                          bool rPriority,
			  unsigned short priority,
			  unsigned long tId,
			  const std::chrono::steady_clock::time_point & timestamp ) :
			
	Message::Message( Category::TASK ),
	taskSub(sub),
	state(s),
	respectPriority(rPriority),
	taskId(tId),
	time(timestamp)
{
	code += (unsigned char)s;
	code += (unsigned char)sub;

	std::cout << "CODE" << std::hex << (unsigned)code << std::endl;
	std::cout << std::dec;

	bufferSize = 12;

	buffer = new char [ 12 ];

	buffer[0] = code;

	if( rPriority )
		buffer[1] = 0x80;
	else
		buffer[1] = 0x00;

	buffer[2] =   priority        & 0x00FF;
	buffer[3] = ( priority >> 8 ) & 0x00FF;

	buffer[4] =   tId         & 0x00FF;
	buffer[5] = ( tId >> 8 )  & 0x00FF;
	buffer[6] = ( tId >> 16 ) & 0x00FF;
	buffer[7] = ( tId >> 24 ) & 0x00FF;

	std::chrono::steady_clock::duration d = timestamp.time_since_epoch();

	unsigned long l = d.count();

	buffer[8]  =   l         & 0x00FF;
	buffer[9]  = ( l >> 8 )  & 0x00FF;
	buffer[10] = ( l >> 16 ) & 0x00FF;
	buffer[11] = ( l >> 24 ) & 0x00FF;
}

taskMessage::taskMessage( State s ) :
	Message::Message( Category::TASK, s ),
	state(s)
{

	std::cout << "CODE" << std::hex << (unsigned)code << std::endl;
	std::cout << std::dec;
}

bool taskMessage::getRespectPriority()
{
	return respectPriority;
}

unsigned short taskMessage::getPriority() const
{
	return priority;
}

unsigned long taskMessage::getTaskId() const
{
	return taskId;
}

std::chrono::steady_clock::time_point & taskMessage::getTimestamp() const
{
	std::chrono::steady_clock::time_point t(time);
	return t;
}

//------------------------------
// depMessage
//------------------------------
depMessage::depMessage ( State state, std::vector<unsigned long> & tasks ) : Message::Message( Category::DEP ), tasks(tasks)
{
	code += (unsigned char)state;

	unsigned tasksSize = tasks.size();

	bufferSize = 4 * (tasksSize + 1);

	buffer = new char [tasksSize];

	buffer[0] = code;
	buffer[1] = 0;
	buffer[2] = tasksSize & 0x00FF;
	buffer[3] = ( tasksSize >> 8 ) & 0x00FF;

	for( unsigned i = 0; i < tasksSize; ++i )
	{
		buffer[ (i + 1) * 4     ] =   tasks[i]         & 0x00FF;
		buffer[ (i + 1) * 4 + 1 ] = ( tasks[i] >> 8  ) & 0x00FF;
		buffer[ (i + 1) * 4 + 2 ] = ( tasks[i] >> 16 ) & 0x00FF;
		buffer[ (i + 1) * 4 + 3 ] = ( tasks[i] >> 24 ) & 0x00FF;
	}
}

depMessage::depMessage ( State state ) : Message::Message( Category::DEP, state )
{
}

depMessage::depMessage ( char * buff, unsigned long bufferSize ) : Message::Message( Category::DEP, bufferSize )
{
	buffer = new char [bufferSize];

	this->bufferSize = bufferSize;

	for( unsigned long i = 0; i < bufferSize; i++ )
		buffer[i] = buff[i];

	code = buffer[0];

	unsigned tasksSize = 0;
	
	tasksSize += (unsigned)buffer[3];

	tasksSize += (unsigned)buffer[4] << 8;

	tasks = std::vector<unsigned long> (tasksSize, 0);

	for( unsigned i = 0; i < tasksSize; ++i )
	{
		tasks[i] += (unsigned long)buffer[ (i + 1) * 4     ];
		tasks[i] += (unsigned long)buffer[ (i + 1) * 4 + 1 ] << 8;
		tasks[i] += (unsigned long)buffer[ (i + 1) * 4 + 2 ] << 16;
		tasks[i] += (unsigned long)buffer[ (i + 1) * 4 + 3 ] << 24;
	}
}

unsigned short depMessage::getTaskCount()
{
	return tasks.size();
}

std::vector<unsigned long> & depMessage::getTasks()
{
	return tasks;
}

//------------------------------
// fileMessage
//------------------------------
fileMessage::fileMessage(State s,
                         bool isMainF,
                         unsigned long tId,
                         std::string filename ) :
	Message::Message( Category::FILE ),
	state(s),
	isMainFile(isMainF),
	taskId(tId),
	name(filename)
{
	//taskId=tId;
	//name=filename;
	/** \author Tomasz Jakubczyk
	 * \todo Jeśli jest to wiadomość wysyłana, to powinna otworzyć plik
	 * o podanej nazwie wczytać i wysłać, a jeśli odebran, to ze swojego
	 * magicznego bufora zapisać plik pod podana nazwą.
	 * Może być to rozwiązane prze zsprawdzenie, czy istnieje plik o
	 * podanej nazwie. */
}

fileMessage::fileMessage ( State s ) :
	Message::Message( Category::FILE, s ),
	state(s)
{

}

bool fileMessage::getIsMainFile()
{
	return isMainFile;
}

unsigned long fileMessage::getTaskId()
{
	return taskId;
}

std::string fileMessage::getFilename()
{
	return name;
}

std::fstream & fileMessage::getFile()
{
	file.open(name.c_str(),std::fstream::out);
	return file;
}

//------------------------------
// retMessage
//------------------------------
retMessage::retMessage( State s,
                        unsigned char exitStatus,
                        unsigned long tId,
                        std::string filename) :
	Message::Message( Category::RET ),
	state(s),
	taskId(tId),
	name(filename)
{

}

retMessage::retMessage ( State s ) :
	Message::Message( Category::RET, s ),
	state(s)
{

}

unsigned char retMessage::getExitStatus()
{
	return exitStatus;
}

unsigned long retMessage::getTaskId()
{
	return taskId;
}

std::string retMessage::getFilename()
{
	return name;
}

std::fstream & retMessage::getFile()
{
	file.open(name.c_str(),std::fstream::out);
	return file;
}




//---------------
// synMessage
//---------------
synMessage::synMessage ( State state ) : Message::Message( Category::SYN, state )
{
}

synMessage::synMessage ( char * buffer, unsigned long bufferSize ) : Message::Message( Category::SYN, bufferSize )
{
	this->buffer = new char [ bufferSize ];

	for( unsigned long i = 0; i < bufferSize; ++i )
		this->buffer[i] = buffer[i];

	code = buffer[0];
}


//---------------
// pingMessage
//---------------
pingMessage::pingMessage ( State state ) : Message::Message( Category::PING, state )
{
}

pingMessage::pingMessage ( char * buffer, unsigned long bufferSize ) : Message::Message( Category::PING, bufferSize )
{
	this->buffer = new char [ bufferSize ];

	for( unsigned long i = 0; i < bufferSize; ++i )
		this->buffer[i] = buffer[i];

	code = buffer[0];
}


//------------------------------
// errMessage
//------------------------------
errMessage::errMessage ( ErrSub sub, State state, unsigned char errCode ) : Message::Message( Category::ERR )
{
	code += (unsigned char)state;
	code += (unsigned char)sub;

	bufferSize = 2;

	buffer = new char [ bufferSize ];

	buffer[0] = code;
	buffer[1] = errCode;
}

errMessage::errMessage ( State state ) : Message::Message( Category::ERR, state )
{

}

unsigned char errMessage::getErrCode () const
{

}
























