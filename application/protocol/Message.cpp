/** \file Message.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Message.
 * \todo Andrzej napisze, a na razie zaślepki.
 */

#include <iostream>
#include <fstream>
#include <boost/crc.hpp>

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

	
	DBG_M( "Message code = " << std::hex << ( (unsigned)code & 0xE0 ) << " + " << ( (unsigned)code & 0x1C ) << " + " << ( (unsigned)code & 0x03 ) );
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
	addresses(addr)
{
	DBG_M( "hostMessage() REQ" );

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
	Message::Message( Category::HOST, s )
{
	DBG_M("hostMessage() ACK/OK/NOK")

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
	respectPriority(rPriority),
	taskId(tId),
	time(timestamp)
{
	DBG_M( "taskMessage() REQ" );
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
	Message::Message( Category::TASK, s )
{
	DBG_M( "taskMessage() ACK/OK/NOK" );
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

std::chrono::steady_clock::time_point taskMessage::getTimestamp() const
{
	return time;
}

//------------------------------
// depMessage
//------------------------------
depMessage::depMessage ( State state, std::vector<unsigned long> & tasks ) : Message::Message( Category::DEP ), tasks(tasks)
{
	DBG_M( "depMessage() REQ" );
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
	DBG_M( "depMessage() ACK/OK/NOK" );
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
	isMainFile(isMainF),
	taskId(tId),
	name(filename)
{
	DBG_M( "fileMessage() REQ" );
	code += (unsigned char)s;

	unsigned short fnameSize = filename.size();

	unsigned long fileSize = 0;

	unsigned short checkSum;

	std::ifstream in ( filename );
	
	in.ignore( std::numeric_limits<std::streamsize>::max() );
	std::streamsize length = in.gcount();
	in.clear();   //  Since ignore will have set eof.
	in.seekg( 0, std::ios_base::beg );

	fileSize = length;

	bufferSize = 12 + fnameSize + fileSize;

	buffer = new char [bufferSize];

	buffer[0] = code;

	unsigned char second = fnameSize & 0x7F;

	if( !isMainF )
		second | 0x80;	

	buffer[1] = second;
	buffer[2] = 0;
	buffer[3] = 0;

	buffer[4] =   tId         & 0x00FF;
	buffer[5] = ( tId >> 8 )  & 0x00FF;
	buffer[6] = ( tId >> 16 ) & 0x00FF;
	buffer[7] = ( tId >> 24 ) & 0x00FF;

	buffer[8]  =   fileSize          & 0x00FF;
	buffer[9]  = ( fileSize  >> 8 )  & 0x00FF;
	buffer[10] = ( fileSize  >> 16 ) & 0x00FF;
	buffer[11] = ( fileSize  >> 24 ) & 0x00FF;

	for(unsigned short i = 0; i < fnameSize; ++i )
		buffer[ 12 + i ] = filename[i];

	unsigned long currIndex = 12 + fnameSize; 

	char c;

	boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false>  crc;

	for(unsigned long i = 0; i < fileSize; ++i )
	{
		in.get(c);
		DBG(c)
		crc.process_byte (c);
		buffer[ currIndex + i ] = c;
	}

	in.close();

	checkSum = crc();

	buffer[2] = checkSum & 0x00FF;
	buffer[3] = ( checkSum >> 8 ) & 0x00FF;
}

fileMessage::fileMessage ( State s ) :
	Message::Message( Category::FILE, s )
{

	DBG_M( "fileMessage() ACK/OK/NOK" );
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


//------------------------------
// retMessage
//------------------------------
retMessage::retMessage( State s,
                        unsigned char exitStatus,
                        unsigned long tId,
                        std::string filename) :
	Message::Message( Category::RET ),
	taskId(tId),
	name(filename)
{
	DBG_M( "retMessage() REQ" );
	code += (unsigned char)s;

	unsigned short fnameSize = filename.size();

	unsigned long fileSize = 0;

	std::ifstream in ( filename );
	
	in.ignore( std::numeric_limits<std::streamsize>::max() );
	std::streamsize length = in.gcount();
	in.clear();
	in.seekg( 0, std::ios_base::beg );

	fileSize = length;

	bufferSize = 12 + fnameSize + fileSize;

	buffer = new char [bufferSize];

	buffer[0] = code;

	buffer[1] = exitStatus;
	buffer[2] = fnameSize & 0xFF;
	buffer[3] = 0;

	buffer[4] =   tId         & 0x00FF;
	buffer[5] = ( tId >> 8 )  & 0x00FF;
	buffer[6] = ( tId >> 16 ) & 0x00FF;
	buffer[7] = ( tId >> 24 ) & 0x00FF;

	buffer[8]  =   fileSize          & 0x00FF;
	buffer[9]  = ( fileSize  >> 8 )  & 0x00FF;
	buffer[10] = ( fileSize  >> 16 ) & 0x00FF;
	buffer[11] = ( fileSize  >> 24 ) & 0x00FF;

	for(unsigned short i = 0; i < fnameSize; ++i )
		buffer[ 12 + i ] = filename[i];

	unsigned long currIndex = 12 + fnameSize; 

	char c;

	for(unsigned long i = 0; i < fileSize; ++i )
	{
		in.get(c);
		buffer[ currIndex + i ] = c;
	}

	in.close();
}

retMessage::retMessage ( State s ) :
	Message::Message( Category::RET, s )
{

	DBG_M( "retMessage() ACK/OK/NOK" );
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


//---------------
// synMessage
//---------------
synMessage::synMessage ( State state ) : Message::Message( Category::SYN, state )
{
	DBG_M( "synMessage() ACK/OK/NOK" );
}


//---------------
// pingMessage
//---------------
pingMessage::pingMessage ( State state ) : Message::Message( Category::PING, state )
{
	DBG_M( "taskMessage() ACK/OK/NOK" );
}


//------------------------------
// errMessage
//------------------------------
errMessage::errMessage ( ErrSub sub, State state, unsigned char errCode ) : Message::Message( Category::ERR ), errCode(errCode)
{
	DBG_M( "errMessage() REQ" );
	code += (unsigned char)state;
	code += (unsigned char)sub;

	bufferSize = 2;

	buffer = new char [ bufferSize ];

	buffer[0] = code;
	buffer[1] = errCode;
}

errMessage::errMessage ( State state ) : Message::Message( Category::ERR, state )
{
	DBG_M( "errMessage() ACK/OK/NOK" );
}

unsigned char errMessage::getErrCode () const
{
	return errCode;
}
























