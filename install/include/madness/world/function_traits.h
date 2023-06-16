#ifndef MADNESS_FUNCTION_TRAITS
#define MADNESS_FUNCTION_TRAITS

#include <type_traits>

namespace madness {
    namespace detail {
        // helps to implement other metafunctions
        template<typename> struct is_type : public std::true_type { };

        /// Function traits in the spirit of boost function traits
        template <typename functionT, typename enablerT = void>
        struct function_traits : public std::false_type {};

        /// Function traits in the spirit of boost function traits
        template <typename functionT, typename enablerT = void>
        struct callable_traits : public std::false_type {};

        /// Member function traits in the spirit of boost function traits
        template <typename memfuncT>
        struct memfunc_traits : public std::false_type { };

        /// Function trait specialization for a free function pointer
        template <typename resultT, typename... argTs>
        struct function_traits<resultT(*)(argTs...), void> {
          static const bool value = true;
          static const int arity = sizeof...(argTs);
          using result_type = resultT;
        };

        /// Function trait specialization for a *reference* to a free function pointer
        template <typename resultT, typename... argTs>
        struct function_traits<resultT(*&)(argTs...), void> {
          static const bool value = true;
          static const int arity = sizeof...(argTs);
          using result_type = resultT;
        };

        /// Function trait specialization for a callable (can be a function, a (generic) lambda, etc.)
        template <typename fnT, typename... argTs>
        struct function_traits<fnT(argTs...), std::enable_if_t<is_type<std::invoke_result_t<fnT, argTs...>>::value>> {
            static const bool value = true;
            static const int arity = sizeof...(argTs);
            using result_type = std::invoke_result_t<fnT, argTs...>;
        };

        /// Function traits in the spirit of boost function traits
        template <typename fnT, typename... argTs>
        struct callable_traits<fnT(argTs...), std::enable_if_t<is_type<std::invoke_result_t<fnT, argTs...>>::value>> {
            static const bool value = true;
            static const int arity = sizeof...(argTs);
            using result_type = std::invoke_result_t<fnT, argTs...>;
        };

        /// Member function traits in the spirit of boost function traits
        template <typename objT, typename returnT, typename... argTs>
        struct memfunc_traits<returnT(objT::*)(argTs...)> {
            static const bool value = true;
            static const int arity = sizeof...(argTs);
            static const bool constness = false;
            typedef objT obj_type;
            typedef returnT result_type;
        };

        /// Member function traits in the spirit of boost function traits
        template <typename objT, typename returnT, typename... argTs>
        struct memfunc_traits<returnT(objT::*)(argTs...) const> {
            static const bool value = true;
            static const int arity = sizeof...(argTs);
            static const bool constness = true;
            typedef objT obj_type;
            typedef returnT result_type;
        };


        template <typename fnT, typename Enabler = void>
        struct is_functor {
            typedef char (& yes)[1];
            typedef char (& no)[2];

            // we need a template here to enable SFINAE
            template <typename U>
            static yes deduce(char (*)[sizeof(&U::operator())]);
            // fallback
            template <typename> static no deduce(...);

            static const bool value = sizeof(deduce<fnT>(0)) == sizeof(yes);
        };

        template <typename fnT>
        struct is_functor<fnT, typename std::enable_if<is_type<typename fnT::result_type>::value >::type> :
                public std::true_type
        { };

        template <typename fnT, typename Enabler = void>
        struct result_of {
            typedef typename fnT::result_type type;
        };

        template <typename fnT>
        struct result_of<fnT, typename std::enable_if<is_type<decltype(&fnT::operator())>::value >::type> :
                public result_of<decltype(&fnT::operator())>
        { };

        template <typename fnT>
        struct result_of<fnT, typename std::enable_if<function_traits<fnT>::value>::type> {
            typedef typename function_traits<fnT>::result_type type;
        };

        template <typename fnT>
        struct result_of<fnT, typename std::enable_if<memfunc_traits<fnT>::value>::type> {
            typedef typename memfunc_traits<fnT>::result_type type;
        };
    }
}
#endif
