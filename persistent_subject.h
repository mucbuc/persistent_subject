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

    private:


        typedef std::string string_type; 
        
        struct state
        {
            virtual ~state() = default;
            virtual void on_swap(context_type & lhs, context_type & rhs) const = 0; 
            virtual value_type value(persistent_subject & lhs) const = 0;
            void init(persistent_subject & lhs, string_type value) const; 
        protected: 
            static value_type get_value(const string_type &);
        };

        typedef std::shared_ptr<state> state_pointer;

        string_type & buffer_ref();
        const string_type & buffer_ref() const;

        state_pointer & state_ref();
        const state_pointer & state_ref() const; 

        struct named : state
        {   
            using state::get_value;
            virtual ~named() = default;
            virtual void on_swap(context_type & lhs, context_type & rhs) const; 
            virtual value_type value(persistent_subject & lhs) const; 
        };

        struct temporary : state
        {
            using state::get_value;
            virtual ~temporary() = default;
            virtual void on_swap(context_type & lhs, context_type & rhs) const;
            virtual value_type value(persistent_subject & lhs) const; 
        };

        typedef om636::persistent< std::map< string_type, string_type > > persistent_type;
        typedef singleton< persistent_type, default_lifetime< persistent_type >, create_new< persistent_type > > singleton_type;
        
        string_type m_buffer;
        std::shared_ptr<state> m_state;
    };
}   //om636

#include "persistent_subject.hxx"

#endif // persistent_subject_3lk34jtrljlkj344343