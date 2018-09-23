#pragma once

#ifdef NDEBUG

#define ASSERT( exp ) ((void)0)
#define ASSERT_MSG( exp, msg, ... ) ((void)0)
#define ERROR_MSG( msg, ... ) ((void)0)

#else

#include <iostream>

#define MAX_ASSERT_MSG_LENGTH 256

#define ASSERT( exp )               assert_msg_impl( "Assert failed", false, #exp, exp, __FILE__, __LINE__, #exp )
#define ASSERT_MSG( exp, msg, ... ) assert_msg_impl( "Assert failed", false, #exp, (exp), __FILE__, __LINE__, msg, __VA_ARGS__ )
#define ERROR_MSG( msg, ... )       assert_msg_impl( "ERROR\t", true, "ERROR", false, __FILE__, __LINE__, msg, __VA_ARGS__ )

namespace
{
    template <typename... Args>
    void assert_msg_impl( char const* assert_type, bool const fatal, char const* exp_str, bool exp, char const* file, int line, char const* msg, Args... args )
    {
        if( !exp )
        {
            std::cerr << "===========================================================" << std::endl;
            std::cerr << assert_type << ":\t";
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
            std::cerr << "===========================================================" << std::endl;

            fatal ? abort() : __debugbreak();
        }
    }
}

#undef MAX_ASSERT_MSG_LENGTH

#endif
