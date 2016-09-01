namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
	// sub_scope
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	sub_scope<T>::sub_scope( context_type & c )
		: m_context( c )
	{
        context().attach( * this );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    sub_scope<T>::sub_scope(sub_scope && other)
        : m_context( other.context() )
    {
        context().replace(other, * this);
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	sub_scope<T>::~sub_scope()
	{	
		context().detach( * this );	
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	auto sub_scope<T>::context() const -> context_type &
	{	
		return m_context;	
	} 
	
} // om636