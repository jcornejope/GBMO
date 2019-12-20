#pragma once

#include <chrono>
#include <fstream>
#include <thread>
#include <vector>

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

private:
    Logger( std::string const& filename );
    ~Logger();
    Logger( Logger const& ) = delete;
    Logger( Logger const&& ) = delete;
    Logger& operator=( Logger const& ) = delete;
    Logger& operator=( Logger const&& ) = delete;

    const char* _get_level_string( Level level ) const;

    static Logger* m_instance;
    std::ofstream m_file;

    static unsigned int const MAX_LOG_LENGTH = 256u;
    struct MessageData
    {
        const char* cat;
        Level level;
        std::chrono::time_point<std::chrono::system_clock> time;
        char message[MAX_LOG_LENGTH];
    };

    void _flusher();
    void _flusher_do_work( size_t const idx );

    static unsigned int const BUFFER_SIZE = 16u;
    typedef MessageData TMessageRing[BUFFER_SIZE];
    TMessageRing m_log_buffer;

    std::thread m_worker_thread;
    size_t m_logger_idx = 0;
    size_t m_flusher_idx = 0;

    bool m_join_flusher = false;
};

template<typename ...Args>
inline void Logger::log( std::string const& category, Level level, std::string const& message_format, Args... args )
{
    log( category.c_str(), level, message_format.c_str(), args... );
}

template<typename ...Args>
inline void Logger::log( char const* category, Level level, char const* message_format, Args... args )
{
    {
        size_t flusher_idx = m_flusher_idx;
        size_t const l_idx = m_logger_idx & ( BUFFER_SIZE - 1u );
        size_t f_idx = flusher_idx & ( BUFFER_SIZE - 1u );
        while( ( l_idx == f_idx ) && ( m_logger_idx != flusher_idx ) )
        {
            //ASSERT(m_logger_idx & (size - 1u) == m_flusher_idx & (size - 1u), "Stall logging!!! Main thread spinning! Consider making log buffer bigger!");
            flusher_idx = m_flusher_idx;
            f_idx = flusher_idx & ( BUFFER_SIZE - 1u );
        }
    }

    MessageData& msg = m_log_buffer[m_logger_idx & ( BUFFER_SIZE - 1u )];
    msg.time = std::chrono::system_clock::now();
    msg.cat = category;
    msg.level = level;
    std::snprintf( msg.message, MAX_LOG_LENGTH, message_format, args... );

    ++m_logger_idx;
}
