
#include "memory_span.h"
#include "memory_system.h"

#include "utils/assert.h"

MemorySpan::MemorySpan( MemorySystem& memory, u16 address, u16 size )
{
    ASSERT_MSG( address + size < 0x10000, "Trying to create a MemorySpan out of the GB address space!" );

    auto const remapped_address = memory._remap_address( address );
    m_span_base = &memory.m_memory[remapped_address];
    m_size = size;
}

u8& MemorySpan::operator[]( u16 index )
{
    ASSERT( m_span_base );
    ASSERT( index < m_size );

    return m_span_base[index];
}

u8 const& MemorySpan::operator[]( u16 index ) const
{
    ASSERT( m_span_base );
    ASSERT( index < m_size );

    return m_span_base[index];
}
