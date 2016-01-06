namespace om636
{
#pragma mark peristent_subject 
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent_subject<T>::state
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>  
    void persistent_subject<T>::state::init(persistent_subject & lhs, string_type value) const
    {
        lhs.buffer_ref() = value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>  
    auto persistent_subject<T>::state::get_value(const string_type & str) -> value_type 
    {
        value_type result;
        std::stringstream( str ) >> result;
        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent_subject<T>::named
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::named::value(persistent_subject & lhs) const -> value_type
    {
        return get_value( singleton_type::instance().storage()[ lhs.buffer_ref() ] );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::named::on_swap(persistent_subject & lhs, persistent_subject & rhs) const 
    {
        std::swap( lhs.buffer_ref(), rhs.buffer_ref() );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent_subject<T>::temporary
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::temporary::value(persistent_subject & lhs) const -> value_type
    {
        return get_value( lhs.buffer_ref() );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::temporary::on_swap(persistent_subject & lhs, persistent_subject & rhs) const 
    {
        ASSERT( dynamic_cast<named *>( lhs.state_ref().get() ) );

        string_type & value ( singleton_type::instance().storage()[ lhs.buffer_ref() ] );
        value = rhs.buffer_ref();

        rhs.state_ref() = lhs.state_ref();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent_subject<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject()
    : base_type()
    , m_buffer()
    , m_state(new temporary())
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject( const char * path )
    : base_type()
    , m_buffer( path )
    , m_state(new named())
    {
        singleton_type::instance().open( path );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::~persistent_subject()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U, class V> 
    auto persistent_subject<T>::on_init(U & lhs, const V & init) -> value_type
    {
        std::stringstream tmp;
        tmp << init;

        lhs.state_ref()->init(lhs, tmp.str());

        return lhs.state_ref()->value(lhs); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        rhs.state_ref()->on_swap(lhs,rhs);
        base_type::on_swap( lhs, rhs );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::buffer_ref() -> string_type &
    {
        return m_buffer;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::buffer_ref() const -> const string_type &
    {
        return m_buffer;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::state_ref() -> state_pointer &
    {
        return m_state;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::state_ref() const -> const state_pointer &
    {
        return m_state;
    }
        

}   // om636