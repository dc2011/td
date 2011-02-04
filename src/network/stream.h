#ifndef _stream_
#define _stream_

#include <QByteArray>
#include <exception>

namespace td
{

/**
 * Access class for data in a network buffer.
 * This class allows reading and writing standard data types to a byte array
 * buffer intended for use with network packets. You can you this class to
 * parse the data in a packet that has been received; or use it to write to
 * a buffer for sending.
 * Internally, this class is implemented as a wrapper over the QByteArray
 * class, which is the common data type for Qt's socket buffers.
 *
 * @author Darryl Pogue
 */
class Stream
{
public:
    /**
     * Exception thrown when trying to read beyond the buffer of a stream.
     * Any calls to read functions can throw this exception and it MUST be
     * handled by the caller.
     *
     * @author Darryl Pogue
     */
    class EOFException : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "EOF reached on buffer read";
        }
    };

private:
    /**
     * The current position within the buffer.
     */
    int position_;

    /**
     * The array of bytes representing the buffer.
     */
    QByteArray data_;

public:
    /**
     * Constructor for a stream with a empty data (for writing).
     */
    Stream();

    /**
     * Constructor for a stream to read existing data (for reading).
     */
    Stream(const QByteArray& data);

    /**
     * Gets the total size of the stream buffer.
     * For reading, this is the total amount of available data.
     * For writing, this is the amount of data already written.
     *
     * @author Darryl Pogue
     * @return The total buffer size.
     */
    int size() const {
        return data_.size();
    }

    /**
     * Gets the current position in the stream buffer.
     * For reading, this is the progress through the buffer.
     * For writing, this is the amount of data already written.
     *
     * @author Darryl Pogue
     * @return The current position in the buffer.
     */
    int position() const {
        return position_;
    }

    /**
     * Returns whether the end of the buffer has been reached.
     * For reading, this is a valid check.
     * For writing, this will always be true.
     *
     * @author Darryl Pogue
     * @return true if the end of buffer is reached, false otherwise.
     */
    bool eof() const {
        return position_ >= data_.size();
    }


    /**
     * Returns the Stream buffer as a constant QByteArray reference.
     * This is needed when writing the buffer data to a file or socket.
     *
     * @author Darryl Pogue
     * @return The buffer data as a QByteArray reference.
     */
    const QByteArray& data() const {
        return data_;
    }

    /**
     * Reads a byte (unsigned char) from the buffer.
     *
     * @author Darryl Pogue
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return A byte read from the buffer.
     */
    unsigned char readByte();

    /**
     * Reads a (unsigned) short from the buffer.
     *
     * @author Darryl Pogue
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return A short read from the buffer.
     */
    short readShort();

    /**
     * Reads an (unsigned) int from the buffer.
     *
     * @author Darryl Pogue
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return An int read from the buffer.
     */
    int readInt();

    /**
     * Reads a float from the buffer.
     *
     * @author Darryl Pogue
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return A float read from the buffer.
     */
    float readFloat();

    /**
     * Reads a double from the buffer.
     *
     * @author Darryl Pogue
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return A double read from the buffer.
     */
    double readDouble();

    /**
     * Reads a QByteArray with the specified length from the buffer.
     * If the length is greater than the remaining buffer size, the
     * returned array contains up to the end of the buffer.
     *
     * @author Darryl Pogue
     * @param length The number of bytes to read.
     * @throw EOFException if the end of buffer has been reached.
     *        The caller must safely handle this exception!
     * @return An array of data read from the buffer.
     */
    QByteArray& read(const int length);

    /**
     * Writes a byte to the buffer.
     *
     * @author Darryl Pogue
     * @param value The byte value to be written.
     */
    void writeByte(const unsigned char value);

    /**
     * Writes a short to the buffer.
     *
     * @author Darryl Pogue
     * @param value The short value to be written.
     */
    void writeShort(const short value);

    /**
     * Writes an int to the buffer.
     *
     * @author Darryl Pogue
     * @param value The int value to be written.
     */
    void writeInt(const int value);

    /**
     * Writes a float to the buffer.
     *
     * @author Darryl Pogue
     * @param value The float value to be written.
     */
    void writeFloat(const float value);

    /**
     * Writes a double to the buffer.
     *
     * @author Darryl Pogue
     * @param value The double value to be written.
     */
    void writeDouble(const double value);

    /**
     * Writes an existing QByteArray to the buffer.
     *
     * @author Darryl Pogue
     * @param value The byte array to be written.
     */
    void write(const QByteArray& value);
};

} /* end namespace td */

#endif /* _stream_ */
