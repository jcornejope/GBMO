
#include "logger.h"
#include <thread>

Logger* Logger::m_instance = nullptr;

Logger::Logger( std::string const & filename )
    : m_use_first_queue( true )
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

    m_log_queue_1.reserve( 100 );
    m_log_queue_2.reserve( 100 );
}

Logger::~Logger()
{
    if( m_file.is_open() )
    {
        while( !m_log_queue_1.empty() || !m_log_queue_2.empty() )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
        }

        _do_flush( &m_log_queue_1 );
        _do_flush( &m_log_queue_2 );

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
    TMessageQueue* queue = nullptr;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        queue = m_use_first_queue ? &m_log_queue_1 : &m_log_queue_2;
        m_use_first_queue = false;
    }

    std::thread flush_thread( &Logger::_do_flush, this, queue );
    flush_thread.detach();
}

void Logger::_do_flush( TMessageQueue* queue )
{
    if( m_file.is_open() )
    {
        for( auto const& msg : *queue )
        {
            m_file << msg;
        }

        m_file.flush();
    }

    queue->clear();
}
