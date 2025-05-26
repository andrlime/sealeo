#include <channel/channel.h>
#include <logger/logger.h>

#include <iostream>
#include <thread>
#include <vector>

template <typename T>
void
sender(std::vector<T> numbers, typename sealeo::channel<T>::pointer_t channel)
{
    for (T elem : numbers) {
        *channel << elem;
    }

    channel->close();
    return;
}

template <typename T>
void
receiver(typename sealeo::channel<T>::pointer_t channel, std::size_t count)
{
    sealeo::logger logger(sealeo::LoggerLevel::INFO);

    T val;
    while (!channel->is_closed()) {
        *channel >> val;
        logger.info(std::to_string(val));
    }

    return;
}

int
main()
{
    sealeo::logger logger(sealeo::LoggerLevel::DEBUG);
    auto c = sealeo::channel<int>::create_buffered_channel(3);

    std::vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::thread thread1(sender<int>, values, c);
    std::thread thread2(receiver<int>, c, values.size());

    thread1.join();
    thread2.join();
    return 0;
}
