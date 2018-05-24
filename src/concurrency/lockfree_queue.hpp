#ifndef __LOCKFREE_QUEUE_HPP_INCLUDED__
#define __LOCKFREE_QUEUE_HPP_INCLUDED__

#include <cassert>
#include <array>
#include <atomic>

// url: https://www.youtube.com/watch?v=qdrp6k4rcP4
template <typename T, size_t N>
class lockfree_queue
{
 public:
    bool push(const T& new_element)
    {
        auto old_write_pos = write_pos.load();
        auto new_write_pos = position_after(old_write_pos);

        if (new_write_pos == read_pos.load()) {
            return false;
        }

        return true;
    }

    //  bool push(T&& new_element);

    bool pop(T& returned_element)
    {
        auto old_write_pos = write_pos.load();
        auto old_read_pos = read_pos.load();

        if (old_write_pos == old_read_pos) {
            return false;
        }

        returned_element = std::move(ring_buffer_[old_read_pos]);
        read_pos.store(++old_read_pos);
  
        return true;
    }

    // TODO
    // size_t size() const noexcept;
    // void clear();

    // void push_range(InputIterator first, InputIterator* last);
    // void push_elements(InputIterator first, size_t num_elements);
    // size_t pop_all(OutputIterator it);
    // size_t pop_elements(OutputIterator it, size_t num_elements);
  

 private:
    static constexpr size_t position_after(size_t pos) noexcept
    {
        return ++pos == ring_buffer_size ? 0 : pos;
    }
  
    static constexpr size_t ring_buffer_size = N + 1;
    std::array<T, ring_buffer_size> ring_buffer_;
    std::atomic<size_t> read_pos = {0};
    std::atomic<size_t> write_pos = {0};
};

#endif // !__LOCKFREE_QUEUE_HPP_INCLUDED__
