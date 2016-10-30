#ifndef BUFFERDATA_H
#define BUFFERDATA_H

// Буффер данных о поверхностях
// Данный буфер содержит три элемента данных о изображенииях

#include <QtWidgets>
#include <exception>
#include <QVector>
#include "Components/Main/header.h"
#include "Components/Data/array.h"

//namespace bad_buffer_data
//{
//    class bad_buffer_data : public std::exception
//    {
//    public:
//        bad_buffer_data()
//            : std::exception()
//        {}
//        bad_buffer_data(const QString & message = "")
//            : std::exception(message.toStdString().c_str())
//        {
//        }
//        QString message() const
//        {
//            return QString(std::exception::what());
//        }
//    };
//}

class BufferData
{
public:
    using tData = setting_global::tArray;
public:
    BufferData(std::size_t countElements);
    void pushData(const tData & data);
    const tData & readyData() const;
    bool isEmpty() const;
private:
    int                 m_positionBuffer;
    std::size_t         m_countElements;
    QVector<tData>      m_buffer;
};

#endif // BUFFERDATA_H
