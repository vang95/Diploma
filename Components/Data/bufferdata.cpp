#include "bufferdata.h"

BufferData::BufferData(std::size_t countElements)
    : m_countElements(countElements), m_positionBuffer(-1), m_buffer(countElements)
{
}

void BufferData::pushData(const tData &array)
{
    int newPos = m_positionBuffer + 1;
    if(newPos == m_buffer.size())
        newPos = 0;
    m_buffer[newPos] = array;
    m_positionBuffer = newPos;
}

const BufferData::tData & BufferData::readyData() const
{
//    if(isEmpty()){
//        QString message("Буффер пуст!");
//        throw bad_buffer_data::bad_buffer_data(message);
//    }
    return m_buffer[m_positionBuffer];
}

bool BufferData::isEmpty() const
{
    return m_positionBuffer == -1;
}

