#ifndef __CHANNEL_HPP_INCLUDED__
#define __CHANNEL_HPP_INCLUDED__

// class bad_any_cast : public std::bad_cast
// {
//  public:
//     const char* what() const noexcept override
//     {
//         return "bad any cast";
//     }
// };


// https://www.youtube.com/watch?v=CIg6eyJv4dk
template <typename T>
class channel
{
 public:
    void send(const T& to_send)
    {
        std::lock_guard<std::mutex> guard(key);
        fifo.push(to_send);
        non_empty.notify_all();
    }
    
    void receive(T& to_receive)
    {
        std::lock_guard<std::mutex> guard(key);
        non_empty.wait(
            key,
            [this] {
                return !fifo.empty();
            });
        to_receive = fifo.front();
        fifo.pop();
    }
  
    bool try_recieve(T& to_receive)
    {
        bool received = false;
        if (key.try_lock()) {
            // http://en.cppreference.com/w/cpp/thread/lock_tag
            std::lock_guard<std::mutex> guard(key, std::adopt_lock); 
            if (!fifo.empty()) {
                to_receive = fifo.front();
                fifo.pop();
                received = true;
            }
        }

        return received;
    }

 private:
    std::mutex key;
    std::condition_variable_any non_empty; // http://en.cppreference.com/w/cpp/thread/condition_variable_any
    std::queue<T> fifo;

};

#endif // !__CHANNEL_HPP_INCLUDED__
