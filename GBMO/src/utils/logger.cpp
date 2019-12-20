
#include "logger.h"

#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>

#define LOG_FLUSHER_SLEEP_WHILE_WAITING

Logger* Logger::m_instance = nullptr;

Logger::Logger( std::string const& filename )
{
    m_file.open( filename, std::ios_base::out | std::ios_base::trunc );

    //ASSERT(m_file.is_open());
    if( m_file.is_open() )
    {
        std::chrono::time_point<std::chrono::system_clock> time_now;
        time_now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t( time_now );

        m_file << "[System]["
            << _get_level_string( Level::LOG )
            << "] Log started: "
            << std::put_time( std::localtime( &now_time_t ), "%A %d %B %Y [%T]" )
            << " - " << sizeof( m_log_buffer )
            << std::endl;
    }

    static_assert( ( BUFFER_SIZE & ( BUFFER_SIZE - 1u ) ) == 0, "Ring buffer size is not power of 2!" );

    m_worker_thread = std::thread( &Logger::_flusher, this );
}

Logger::~Logger()
{
    if( m_worker_thread.joinable() )
    {
        m_join_flusher = true;
        m_worker_thread.join();
    }

    if( m_file.is_open() )
    {
        std::chrono::time_point<std::chrono::system_clock> time_now;
        time_now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t( time_now );

        m_file << "[System]["
            << _get_level_string( Level::LOG )
            << "] Log ended: "
            << std::put_time( std::localtime( &now_time_t ), "%A %d %B %Y [%T]" )
            << std::endl;

        m_file.close();
    }
}

const char* Logger::_get_level_string( Level level ) const
{
    switch( level )
    {
    case LOG:       return "LOG";       break;
    case WARNING:   return "WARNING";   break;
    case ERROR:     return "ERROR";     break;
    }

    return "";
}

void Logger::create_instance( std::string const& filename )
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

void Logger::_flusher()
{
    size_t next_idx_flushed_to_file = 0u;
    bool work_done = false;
    bool join_requested = m_join_flusher;
    while( !join_requested || !work_done )
    {
        {
            size_t const logger_idx = m_logger_idx;
            if( logger_idx != m_flusher_idx )
            {
                work_done = false;
                size_t const f_idx = m_flusher_idx & ( BUFFER_SIZE - 1u );
                _flusher_do_work( f_idx );
                ++m_flusher_idx;
            }
        }

        {
            size_t const logger_idx = m_logger_idx;
            if( logger_idx == m_flusher_idx )
            {
                work_done = true;
#ifdef LOG_FLUSHER_SLEEP_WHILE_WAITING
                //std::this_thread::sleep_for(5ms); // C++ 14
                std::this_thread::sleep_for( std::chrono::duration<float, std::milli>( 5 ) );
#endif

                if( next_idx_flushed_to_file != m_flusher_idx )
                {
                    m_file.flush();
                    next_idx_flushed_to_file = m_flusher_idx;
                }
            }
        }

        join_requested = m_join_flusher;
    }
}

void Logger::_flusher_do_work( size_t const idx )
{
    using namespace std::chrono;
    auto const& log = m_log_buffer[idx];

    std::time_t now_time_t = system_clock::to_time_t( log.time );
    std::stringstream stream;
    stream << std::put_time( std::localtime( &now_time_t ), "[%T]" );

    if( log.cat && log.cat != '\0' )
        stream << "[" << log.cat << "]";

    stream << "[" << _get_level_string( log.level ) << "] - ";
    stream << log.message << std::endl;

    m_file << stream.str();
}
