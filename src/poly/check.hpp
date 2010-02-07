
//! Check for nonnull pointer.
template <typename T>
inline T* check(T* ptr)
{
    if (0 == ptr)
        throw std::logic_error("attempting to dereferece a null pointer");

    return ptr;
}
