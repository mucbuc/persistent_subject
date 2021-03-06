namespace om636 {
namespace can_do {
    /////////////////////////////////////////////////////////////////////////////////////////////
    // arithmetic<T, U>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    void arithmetic<T, U>::constraints(T lhs, U rhs)
    {
        T temp(lhs + rhs);
        temp += lhs + rhs;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    arithmetic<T, U>::arithmetic()
    {
        void (*dummy)(T, U) = constraints;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // read_stream<T, U>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    void read_stream<T, U>::constraints(T lhs, U rhs)
    {
        lhs >> rhs;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    read_stream<T, U>::read_stream()
    {
        void (*dummy)(T, U) = constraints;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // write_stream<T, U>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    void write_stream<T, U>::constraints(T lhs, U rhs)
    {
        lhs << rhs;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, class U>
    write_stream<T, U>::write_stream()
    {
        void (*dummy)(T, U) = constraints;
    }
}
}