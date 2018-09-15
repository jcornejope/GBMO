#pragma once

#ifdef NDEBUG
#define ASSERT_MSG(exp, msg, ...) ((void)0)
#else
#include <cassert>
#include <cstdio>
#define MAX_ASSERT_MSG_LENGTH 256
#define ASSERT_MSG(exp, msg, ...) assert_msg_impl(#exp, (exp), __FILE__, __LINE__, msg, __VA_ARGS__)

template <typename... Args>
void assert_msg_impl( const char* exp_str, bool exp, const char* file, int line, const char* msg, Args... args )
{
    if( !exp )
    {
        std::cerr << "=========================================" << std::endl;
        std::cerr << "Assert failed:\t";
        constexpr bool zero_args = sizeof...( args ) == 0;
        if( zero_args )
        {
            std::cerr << msg << std::endl;
        }
        else
        {
            char buf[MAX_ASSERT_MSG_LENGTH];
            std::snprintf( buf, MAX_ASSERT_MSG_LENGTH, msg, args... );
            std::cerr << buf << std::endl;
        }
        std::cerr << "Expected:\t" << exp_str << std::endl
            << "Source:\t\t" << file << ", line " << line << std::endl;
        std::cerr << "=========================================" << std::endl;

        abort();
    }
}
#undef MAX_ASSERT_MSG_LENGTH
#endif
