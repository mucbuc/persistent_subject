namespace om636
{
#pragma mark peristent_subject 
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::named::named(const string_type & name)
    : m_name( name )
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::named::on_swap(context_type & lhs, context_type & rhs)
    {

    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::named::name() -> string_type & 
    {
        return m_name;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::named::name() const -> string_type
    {
        return m_name;
    }
     
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::temporary::temporary(const value_type & v)
    : m_value(v)
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::temporary::on_swap(context_type & lhs, context_type & rhs)
    {
        
    }
            
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::temporary::value() -> value_type & 
    {
        return m_value; 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::temporary::value() const -> value_type
    {
        return m_value; 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject()
    : base_type()
    , m_name()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_subject<T>::persistent_subject( const char * path )
    : base_type()
    , m_name( path )
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
    auto persistent_subject<T>::on_init(U & lhs, const V & init)->value_type
    {
        using std::stringstream;

        if (lhs.m_name.empty()) 
        {
            lhs.m_local.reset( new value_type() );
            
            stringstream tmp;
            tmp << init;
            tmp >> * lhs.m_local;
            return * lhs.m_local;
        }

        string_type & value ( singleton_type::instance().storage()[ lhs.name() = init ] );
        
        value_type result;
        stringstream( value ) >> result;
        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_subject<T>::on_swap(context_type & lhs, context_type & rhs)
    {
        using namespace std;

        if (rhs.m_local)
        {
            ASSERT( !lhs.name().empty() ); 

            stringstream tmp; 
            tmp << * rhs.m_local;

            string & value ( singleton_type::instance().storage()[ lhs.name() ] );
            value = tmp.str(); 

            rhs.m_local.reset();
            rhs.name() = lhs.name();
        }
        else 
        {
            std::swap(lhs.name(), rhs.name() );
        }

        base_type::on_swap( lhs, rhs );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::name() -> string_type &
    {
        return m_name;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    auto persistent_subject<T>::name() const -> string_type
    {
        return m_name;
    }

}   // om636