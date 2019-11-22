#include "std/String.h"

#include <std/mem.h>
#include <std/err.h>
#include <std/Array.h>

namespace std
{
    // String //
    String::String()
        : _size(0)
    {
        _allocData();
    }

    String::String(const sz SIZE)
        : _size(SIZE)
    {
        _allocData();
    }

    String::String(cstr data)
        : _size(strSize(data))
    {
        _allocData(data);
    }

    String::String(cstr data, const sz SIZE)
        : _size(SIZE)
    {
        _allocData(data);
    }

    String::String(const String &OTHER)
        : _size(OTHER._size)
    {
        // Copy data
        _allocData(OTHER._data);
    }

    String::~String()
    {
        // Free
        _dallocData();
    }

    sz String::count(const char c) const
    {
        sz count = 0;
        for (sz i = 0; i < _size; ++i)
            // Found
            if (_data[i] == c)
                ++count;
        
        return count;
    }

    Array<String> String::split(const char SEP) const
    {
        const sz WORD_COUNT = count(SEP) + 1;

        if (WORD_COUNT == 1)
        {
            Array<String> array(1);
            array[0] = String(*this);
            return array;
        }

        // One word for each separator
        Array<String> words(WORD_COUNT);

        sz wordStart = 0,
            wordId = 0;
        for (sz i = 0; i < _size; ++i)
            if (_data[i] == SEP)
            {
                // Add the word (without space)
                words[wordId] = String(_data + wordStart, i - wordStart);

                // Update id
                ++wordId;

                // Update word start
                wordStart = i + 1;
            }

        // Append last word
        words[wordId] = String(_data + wordStart, _size - wordStart);

        // Remove empty words
        Array<String> parsed(WORD_COUNT);
        sz parsedWordCount = 0;

        for (sz i = 0; i < words.size(); ++i)
            // If not empty
            if (words[i]._size != 0)
            {
                parsed[parsedWordCount] = String(words[i]);
                ++parsedWordCount;
            }

        // Remove unitialized tail
        parsed.resize(parsedWordCount);

        return parsed;
    }

    String &String::operator=(const String &OTHER)
    {
        // Free
        _dallocData();

        // Copy
        _size = OTHER._size;
        _allocData(OTHER._data);

        return *this;
    }

    String String::operator+(const String &OTHER) const
    {
        String s(_size + OTHER._size);

        // Add this data (begin)
        cpy(_data, s._data, _size);

        // Add OTHER data (end)
        cpy(OTHER._data, s._data + _size, OTHER._size);

        return s;
    }

    String &String::operator+=(const String &OTHER)
    {
        const sz NEW_SIZE = _size + OTHER._size;

        // Allocates
        str const NEW_DATA = (str)alloc(NEW_SIZE + 1);

        // Add this data (begin)
        cpy(_data, NEW_DATA, _size);

        // Add OTHER data (end)
        cpy(OTHER._data, NEW_DATA + _size, OTHER._size);

        // Set end
        NEW_DATA[NEW_SIZE] = '\0';

        // Free old data
        _dallocData();

        // Update attributes
        _size = NEW_SIZE;
        _data = NEW_DATA;

        return *this;
    }

    String &String::operator+=(const char c)
    {
        const sz NEW_SIZE = _size + 1;

        // Allocates
        str const NEW_DATA = (str)alloc(NEW_SIZE + 1);

        // Add this data (begin)
        cpy(_data, NEW_DATA, _size);

        // Add char
        NEW_DATA[_size] = c;

        // Set end
        NEW_DATA[NEW_SIZE] = '\0';

        // Free old data
        _dallocData();

        // Update attributes
        _size = NEW_SIZE;
        _data = NEW_DATA;

        return *this;
    }

    String::operator cstr() const
    {
        return _data;
    }

    char String::operator[](const sz i) const
    {
        // Buffer overflow
        if (i >= _size)
            fatalError(error::MEM_OVERFLOW);

        return _data[i];
    }

    char &String::operator[](const sz i)
    {
        // Buffer overflow
        if (i >= _size)
            fatalError(error::MEM_OVERFLOW);

        return _data[i];
    }

    bool String::operator==(const String &OTHER) const
    {
        // Check size
        if (_size != OTHER._size)
            return false;

        // Check content
        for (sz i = 0; i < _size; ++i)
            if (_data[i] != OTHER._data[i])
                return false;

        // Same strings
        return true;
    }

    bool String::operator==(cstr OTHER) const
    {
        // Check content
        for (sz i = 0; i < _size; ++i)
            if (_data[i] != OTHER[i])
                return false;

        // Same strings
        return true;
    }

    void String::_allocData(cstr data)
    {
        // Allocates
        _data = (str)alloc(_size + 1);

        // Copy
        cpy(data, _data, _size);

        // Set end
        _data[_size] = '\0';
    }

    void String::_allocData()
    {
        // Allocates
        _data = (str)alloc(_size + 1);

        // Set end
        _data[_size] = '\0';
    }

    void String::_dallocData()
    {
        dalloc(_data);
        _data = nullptr;
    }

    // StringStream //
    StringStream::StringStream()
        : Stream(StringStream::printWrapper, StringStream::putCharWrapper)
    {}

    StringStream::StringStream(const String &s)
        : Stream(StringStream::printWrapper, StringStream::putCharWrapper),
        _data(s)
    {}

    StringStream::StringStream(const cstr s)
        : Stream(StringStream::printWrapper, StringStream::putCharWrapper),
        _data(s)
    {}

    void StringStream::printWrapper(Stream &t, const String &s)
    {
        reinterpret_cast<StringStream*>(&t)->_data += s;
    }

    void StringStream::putCharWrapper(Stream &t, const char c)
    {
        reinterpret_cast<StringStream*>(&t)->_data += c;
    }

    Stream& operator<<(Stream& stream, const StringStream& STR)
    {
        return stream << STR._data;
    }
}
