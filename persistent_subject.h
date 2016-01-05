#ifndef persistent_subject_3lk34jtrljlkj344343 
#define persistent_subject_3lk34jtrljlkj344343

#include <map>
#include <memory>

#include <lib/om636/src/core/persistent.h>
#include <lib/om636/src/create/singleton.h>

#include <lib/context/src/interface.h>
#include <lib/context/src/default_subject.h>

namespace om636
{
    template<class T>
    struct persistent_subject
    : public T
    {
        typedef T base_type;
        using typename base_type::context_type;
        using typename base_type::value_type;
        using base_type::on_init;

        persistent_subject();
        persistent_subject(const char *);
        virtual ~persistent_subject();
        
        template<class U, class V>
        static value_type on_init(U &, const V &);

        virtual void on_swap(context_type &, context_type &);

        std::string & name();
        std::string name() const;

    private:
    
        typedef std::string string_type; 

        struct state
        {
            virtual ~state() = default;
            virtual void on_swap(context_type & lhs, context_type & rhs) = 0; 
        };

        struct named : state
        {
            virtual ~named() = default;
            
            named(const string_type &); 
            virtual void on_swap(context_type & lhs, context_type & rhs);
            string_type & name();
            string_type name() const;
        private: 
            string_type m_name;
        };

        struct temporary : state
        {
            virtual ~temporary() = default;
            
            temporary(const value_type &); 
            virtual void on_swap(context_type & lhs, context_type & rhs); 
            value_type & value();
            value_type value() const;
        private: 
            value_type m_value;
        };

        typedef om636::persistent< std::map< string_type, string_type > > persistent_type;
        typedef singleton< persistent_type, default_lifetime< persistent_type >, create_new< persistent_type > > singleton_type;
        
        std::string m_name;
        std::shared_ptr<value_type> m_local;
    };
}   //om636

#include "persistent_subject.hxx"

#endif // persistent_subject_3lk34jtrljlkj344343