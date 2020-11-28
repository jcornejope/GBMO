#pragma once

#include "utils/types.h"

class MemorySystem;

class MemorySpan
{
public:
    MemorySpan( MemorySystem& memory, u16 address, u16 size );

    u8& operator[]( u16 index );
    u8 const& operator[]( u16 index ) const;

private:
    u8* m_span_base;
    u16 m_size;
};
