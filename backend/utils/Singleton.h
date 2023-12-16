#pragma once
#include <cassert>

namespace Lithe
{
/// Utility to create singleton classes (based on Loki)
template <class T> class Singleton
{
public:
    static T& GetInstance()
    {
        if (!Singleton::s_Instance)
            Singleton::s_Instance = createInstance();
        return *Singleton::s_Instance;
    }

protected:
    explicit Singleton()
    {
        assert(("Singleton instance already exists", !Singleton::s_Instance));
        Singleton::s_Instance = static_cast<T*>(this);
    }

    ~Singleton() { Singleton::s_Instance = nullptr; }

    static T* createInstance() { return new T(); }

private:
    static T* s_Instance;

    explicit Singleton(const Singleton&){};
    Singleton& operator=(const Singleton&) { return *this; }
};

template <class T> T* Singleton<T>::s_Instance = 0;
} // namespace Lithe
