#pragma once

#include <logger/logger.h>
#include <types.h>

#include <memory>
#include <queue>
#include <semaphore>

namespace sealeo {

template <typename value_t>
class channel {
private:
    std::queue<value_t> buffer_;
    std::size_t buffer_capacity_;

    std::binary_semaphore sem_sender_ready_{0}, sem_receiver_ready_{0};
    bool closed_ = false;

    inline void
    set_value(const value_t& v)
    {
        buffer_.push(v);
    }

    inline value_t
    get_value()
    {
        auto front = buffer_.front();
        buffer_.pop();
        return front;
    }

public:
    // This channel's pointer type
    using pointer_t = std::shared_ptr<channel<value_t>>;

    channel() : buffer_capacity_(0) {}

    channel(std::size_t capacity) : buffer_capacity_(capacity) {}

    // Static constructors that create a shared pointer
    inline static pointer_t
    create_unbuffered_channel()
    {
        return std::make_shared<channel<value_t>>();
    }

    inline static pointer_t
    create_buffered_channel(std::size_t capacity)
    {
        return std::make_shared<channel<value_t>>(capacity);
    }

    // Returns true if channel is closed, false if open
    inline bool
    is_closed()
    {
        return closed_;
    }

    // Opens the channel. If already open, does nothing.
    inline void
    open()
    {
        closed_ = false;
    }

    // Closes the channel. If already closed, does nothing.
    inline void
    close()
    {
        closed_ = true;
    }

    // Reads a value from the channel. If there is no value, blocks until there is one.
    value_t
    recv()
    {
        if (buffer_.size() > 0) {
            return get_value();
        }

        sem_sender_ready_.release();
        sem_receiver_ready_.acquire();
        return get_value();
    }

    // Writes a value to the channel. Blocks until success.
    void
    send(const value_t& val)
    {
        if (buffer_.size() < buffer_capacity_) {
            set_value(val);
            return;
        }

        sem_sender_ready_.acquire();
        set_value(val);
        sem_receiver_ready_.release();
    }

    // Overload << operator for channel << value
    inline void
    operator<<(const value_t& val)
    {
        send(val);
    }

    // Overload << operator for channel >> value
    inline void
    operator>>(value_t& val)
    {
        val = recv();
    }
};

} // namespace sealeo
