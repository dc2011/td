#include "stream.h"

namespace td
{

Stream::Stream() : position_(0) { }

Stream::Stream(const QByteArray& data) : position_(0), data_(data) { }

unsigned char Stream::readByte() {
    if (eof()) {
        throw new EOFException();
    }

    return data_.constData()[position_++];
}

short Stream::readShort() {
    if (eof()) {
        throw new EOFException();
    }

    short ret = *(short*)&data_.constData()[position_];
    position_ += sizeof(short);

    return ret;
}

int Stream::readInt() {
    if (eof()) {
        throw new EOFException();
    }

    int ret = *(int*)&data_.constData()[position_];
    position_ += sizeof(int);

    return ret;
}

float Stream::readFloat() {
    if (eof()) {
        throw new EOFException();
    }

    float ret = *(float*)&data_.constData()[position_];
    position_ += sizeof(float);

    return ret;
}

double Stream::readDouble() {
    if (eof()) {
        throw new EOFException();
    }

    double ret = *(double*)&data_.constData()[position_];
    position_ += sizeof(double);

    return ret;
}

QByteArray& Stream::read(const int length) {
    if (eof()) {
        throw new EOFException();
    }

    QByteArray ret = data_.mid(position_, length);
    position_ += ret.size();

    return ret;
}

void Stream::writeByte(const unsigned char value) {
    data_ += value;
    position_++;
}

void Stream::writeShort(const short value) {
    data_ += QByteArray::fromRawData((const char*)&value, sizeof(short));
    position_ += sizeof(short);
}

void Stream::writeInt(const int value) {
    data_ += QByteArray::fromRawData((const char*)&value, sizeof(int));
    position_ += sizeof(int);
}

void Stream::writeFloat(const float value) {
    data_ += QByteArray::fromRawData((const char*)&value, sizeof(float));
    position_ += sizeof(float);
}

void Stream::writeDouble(const double value) {
    data_ += QByteArray::fromRawData((const char*)&value, sizeof(double));
    position_ += sizeof(double);
}

void Stream::write(const QByteArray& value) {
    data_ += value;
    position_ += value.size();
}

} /* end namespace td */
