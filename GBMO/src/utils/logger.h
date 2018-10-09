#pragma once

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <mutex>

#define LOG(cat, msg_format, ...)       Logger::instance().log( cat, Logger::LOG, msg_format, __VA_ARGS__ )
#define LOG_W(cat, msg_format, ...)     Logger::instance().log( cat, Logger::WARNING, msg_format, __VA_ARGS__ )
#define LOG_E(cat, msg_format, ...)     Logger::instance().log( cat, Logger::ERROR, msg_format, __VA_ARGS__ )
#define NO_CAT '\0'

// Non thread-safe logger.
class Logger
{
public:
    enum Level
    {
        LOG,
        WARNING,
        ERROR
    };

    static void create_instance( std::string const& filename );
    static void destroy_instance();
    static Logger& instance() { return *m_instance; }

    template<typename ...Args>
    void log( std::string const& category, Level level, std::string const& message_format, Args... args );
    template<typename ...Args>
    void log( char const* category, Level level, char const* message_format, Args... args );

    void flush();

private:

    Logger( std::string const& filename );
    ~Logger();
    Logger( Logger const& ) = delete;
    Logger( Logger const&& ) = delete;
    Logger& operator=( Logger const& ) = delete;
    Logger& operator=( Logger const&& ) = delete;

    typedef std::vector<std::string> TMessageQueue;

    const char* _get_level_string( Level level ) const;
    void _do_flush( TMessageQueue* queue );

    static Logger* m_instance;

    TMessageQueue m_log_queue_1;
    TMessageQueue m_log_queue_2;
    std::ofstream m_file;
    std::mutex m_mutex;

    bool m_use_first_queue;
};

template<typename ...Args>
inline void Logger::log( std::string const & category, Level level, std::string const & message_format, Args... args )
{
    log( category.c_str(), level, message_format.c_str(), args... );
}

template<typename ...Args>
inline void Logger::log( char const * category, Level level, char const * message_format, Args... args )
{
    using std::chrono::system_clock;

    std::chrono::time_point<system_clock> time_now;
    time_now = system_clock::now();
    std::time_t now_time_t = system_clock::to_time_t( time_now );
    std::stringstream stream;
    stream << std::put_time( std::localtime( &now_time_t ), "[%T]" );
    
    if( category && category != '\0' )
        stream << "[" << category << "]";

    stream << "[" << _get_level_string( level ) << "] - ";

    static unsigned int const MAX_LOG_LENGTH = 256;
    char buf[MAX_LOG_LENGTH];
    std::snprintf( buf, MAX_LOG_LENGTH, message_format, args... );
    stream << buf << std::endl;

    TMessageQueue* queue = nullptr;
    {
        std::lock_guard<std::mutex> lock( m_mutex );
        queue = m_use_first_queue ? &m_log_queue_1 : &m_log_queue_2;
    }
    queue->emplace_back( stream.str() );
}
