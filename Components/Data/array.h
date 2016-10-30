#ifndef DATA_H
#define DATA_H

#include <QDataStream>

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
class Array
{
public:
    Array();
    Array(const Array & array);
    const Array & operator = (const Array & array);

    const T * operator [] (std::size_t index) const;
    const T & operator () (std::size_t index_x, std::size_t index_y) const;
    T * operator [] (std::size_t index);
    T & operator () (std::size_t index_x, std::size_t index_y);

    std::size_t size_row() const;
    std::size_t size_column() const;

//private:
//    void copyArray(const T ** array_data);
private:
    bool                m_flagEmpty;
    const std::size_t   m_size_row;
    const std::size_t   m_size_column;
    T                   m_array[SizeRow][SizeColumn];
};

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
Array<T, SizeRow, SizeColumn>::Array()
    : m_size_row(SizeRow), m_size_column(SizeColumn)
{
}

//template<class T, std::size_t SizeRow, std::size_t SizeColumn>
//void Array<T, SizeRow, SizeColumn>::copyArray(const T ** array_data)
//{
//   for(std::size_t i = 0; i < m_size_row; ++i){
//       for(std::size_t j = 0; j < m_size_column; ++j)
//           m_array[i][j] = array_data[i][j];
//   }
//}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
Array<T, SizeRow, SizeColumn>::Array(const Array & array)
    : m_size_row(array.m_size_row), m_size_column(array.m_size_column)
{
    for(std::size_t i = 0; i < m_size_row; ++i){
        for(std::size_t j = 0; j < m_size_column; ++j)
            m_array[i][j] = array.m_array[i][j];
    }
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
const Array<T, SizeRow, SizeColumn> & Array<T, SizeRow, SizeColumn>::operator = (const Array<T, SizeRow, SizeColumn> & array)
{
    if(this == &array)
        return *this;

    for(std::size_t i = 0; i < m_size_row; ++i){
        for(std::size_t j = 0; j < m_size_column; ++j)
            m_array[i][j] = array.m_array[i][j];
    }

    return *this;
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
const T * Array<T, SizeRow, SizeColumn>::operator [](std::size_t index) const
{
    return m_array[index];
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
const T & Array<T, SizeRow, SizeColumn>::operator () (std::size_t index_x, std::size_t index_y) const
{
    return m_array[index_x][index_y];
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
T * Array<T, SizeRow, SizeColumn>::operator [](std::size_t index)
{
    return m_array[index];
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
T & Array<T, SizeRow, SizeColumn>::operator () (std::size_t index_x, std::size_t index_y)
{
    return m_array[index_x][index_y];
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
std::size_t Array<T, SizeRow, SizeColumn>::size_row() const
{
    return m_size_row;
}

template<class T, std::size_t SizeRow, std::size_t SizeColumn>
std::size_t Array<T, SizeRow, SizeColumn>::size_column() const
{
    return m_size_column;
}

#endif // DATA_H
