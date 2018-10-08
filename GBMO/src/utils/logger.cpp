
#include "logger.h"

Logger* Logger::m_instance = nullptr;

Logger::Logger( std::string const & filename )
{
    m_file.open( filename, std::ios_base::out | std::ios_base::trunc );
    if( m_file.is_open() )
    {
        std::chrono::time_point<std::chrono::system_clock> time_now;
        time_now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t( time_now );

        m_file << "[System][" 
               << _get_level_string( Level::LOG ) 
               << "] Log started: " 
               << std::put_time( std::localtime( &now_time_t ), "%A%e %B %Y [%T]" )
               << std::endl;
    }

    m_log_queue.reserve( 100 );
}

Logger::~Logger()
{
    if( m_file.is_open() )
    {
        flush();

        std::chrono::time_point<std::chrono::system_clock> time_now;
        time_now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t( time_now );

        m_file << "[System]["
               << _get_level_string( Level::LOG )
               << "] Log ended: "
               << std::put_time( std::localtime( &now_time_t ), "%A%e %B %Y [%T]" )
               << std::endl;

        m_file.close();
    }
}

const char * Logger::_get_level_string( Level level ) const
{
    switch( level )
    {
    case LOG:       return "LOG";       break;
    case WARNING:   return "WARNING";   break;
    case ERROR:     return "ERROR";     break;
    }

    return "";
}

void Logger::create_instance( std::string const & filename )
{
    if( m_instance != nullptr )
    {
        destroy_instance();
    }

    m_instance = new Logger( filename );
}

void Logger::destroy_instance()
{
    if( m_instance != nullptr )
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

void Logger::flush()
{
    if( m_file.is_open() )
    {
        for( auto const& msg : m_log_queue )
        {
            m_file << msg;
        }

        m_file.flush();
    }

    m_log_queue.clear();
}
