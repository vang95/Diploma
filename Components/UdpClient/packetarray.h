#ifndef PACKETARRAY_H
#define PACKETARRAY_H

#include <QVector>
#include <QDataStream>

#include "Components/Main/header.h"
#include "Components/Data/array.h"

class PacketArray;
QDataStream & operator << (QDataStream & outStream, const PacketArray & packet);
QDataStream & operator >> (QDataStream & inStream, PacketArray & packet);

class PacketArray
{
public:
    using tData = QVector<int>;
public:
    PacketArray();
    PacketArray(const PacketArray::tData & data, std::size_t indexPacket);
public:
    void set_data(const PacketArray::tData & data);
    void set_index_packet(std::size_t index);
    const PacketArray::tData & get_data() const;
    std::size_t index_packet() const;

    friend QDataStream & operator << (QDataStream & outStream, const PacketArray & packet);
    friend QDataStream & operator >> (QDataStream & inStream, PacketArray & packet);
private:
    std::size_t     m_indexPacket;
    tData           m_data;
};

#endif // PACKETARRAY_H
