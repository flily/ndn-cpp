// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_ALL_EXTENT_HOLT_2004_0827
#define NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_ALL_EXTENT_HOLT_2004_0827

#include <ndnboost/type_traits/msvc/typeof.hpp>
#include <ndnboost/type_traits/is_array.hpp>

namespace ndnboost {
    template<typename T>
    struct remove_all_extents;

    namespace detail {
        template<bool IsArray>
        struct remove_all_extents_impl_typeof {
            template<typename T,typename ID>
            struct inner {
                typedef T type;
            };
        };
        template<>
        struct remove_all_extents_impl_typeof<true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U[]);
                static msvc_register_type<T,ID> test(...);
                NDNBOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( *((T*)NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type reduced_type;
                typedef typename remove_all_extents<reduced_type>::type type;
            };
        };
    } //namespace detail

    template<typename T>
    struct remove_all_extents {
        typedef typename ndnboost::detail::remove_all_extents_impl_typeof<
            ndnboost::is_array<T>::value                
        >::template inner<T,remove_all_extents<T> >::type type;
        NDNBOOST_MPL_AUX_LAMBDA_SUPPORT(1,remove_all_extents,T)
    };
} //namespace ndnboost

#endif //NDNBOOST_TYPE_TRAITS_MSVC_REMOVE_BOUNDS_HOLT_2004_0827

