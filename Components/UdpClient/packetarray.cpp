#include "packetarray.h"

QDataStream & operator << (QDataStream & outStream, const PacketArray & packet)
{
    outStream << packet.m_indexPacket << packet.m_data;
    return outStream;
}

QDataStream & operator >> (QDataStream & inStream, PacketArray & packet)
{
    inStream >> packet.m_indexPacket >> packet.m_data;
    return inStream;
}

PacketArray::PacketArray()
    : m_indexPacket(0)
{}

PacketArray::PacketArray(const PacketArray::tData & data, std::size_t indexPacket)
    : m_data(data), m_indexPacket(indexPacket)
{
}

void PacketArray::set_data(const PacketArray::tData &data)
{
    m_data = data;
}

void PacketArray::set_index_packet(size_t index)
{
    m_indexPacket = index;
}

const PacketArray::tData & PacketArray::get_data() const
{
    return m_data;
}

std::size_t PacketArray::index_packet() const
{
    return m_indexPacket;
}
