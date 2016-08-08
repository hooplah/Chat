#ifndef CHANNEL_H
#define CHANNEL_H

// TAKEN FROM
// https://st.xorian.net/blog/2012/08/go-style-channel-in-c/

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

template<class item>
class Channel
{
    public:
        Channel() : closed(false) {}

        void close()
        {
            std::unique_lock<std::mutex> lock(m);
            closed = true;
            cv.notify_all();
        }

        bool is_closed()
        {
            std::unique_lock<std::mutex> lock(m);
            return closed;
        }

        void send(const item &i)
        {
            std::unique_lock<std::mutex> lock(m);
            if(closed)
                throw std::logic_error("put to closed channel");
            queue.push_back(i);
            cv.notify_one();
        }

        bool receive(item &out, bool wait = true)
        {
            std::unique_lock<std::mutex> lock(m);
            if(wait)
                cv.wait(lock, [&]()
            {
                return closed || !queue.empty();
            });
            if(queue.empty())
                return false;
            out = queue.front();
            queue.pop_front();
            return true;
        }

    private:
        std::list<item> queue;
        std::mutex m;
        std::condition_variable cv;
        bool closed;
};

#endif // CHANNEL_H
