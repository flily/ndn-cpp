//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef NDNBOOST_TT_HAS_GREATER_EQUAL_HPP_INCLUDED
#define NDNBOOST_TT_HAS_GREATER_EQUAL_HPP_INCLUDED

#define NDNBOOST_TT_TRAIT_NAME has_greater_equal
#define NDNBOOST_TT_TRAIT_OP >=
#define NDNBOOST_TT_FORBIDDEN_IF\
   ::ndnboost::type_traits::ice_or<\
      /* Lhs==pointer and Rhs==fundamental */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Lhs_noref >::value,\
         ::ndnboost::is_fundamental< Rhs_nocv >::value\
      >::value,\
      /* Rhs==pointer and Lhs==fundamental */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Rhs_noref >::value,\
         ::ndnboost::is_fundamental< Lhs_nocv >::value\
      >::value,\
      /* Lhs==pointer and Rhs==pointer and Lhs!=base(Rhs) and Rhs!=base(Lhs) and Lhs!=void* and Rhs!=void* */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Lhs_noref >::value,\
         ::ndnboost::is_pointer< Rhs_noref >::value,\
         ::ndnboost::type_traits::ice_not<\
            ::ndnboost::type_traits::ice_or<\
               ::ndnboost::is_base_of< Lhs_noptr, Rhs_noptr >::value,\
               ::ndnboost::is_base_of< Rhs_noptr, Lhs_noptr >::value,\
               ::ndnboost::is_same< Lhs_noptr, Rhs_noptr >::value,\
               ::ndnboost::is_void< Lhs_noptr >::value,\
               ::ndnboost::is_void< Rhs_noptr >::value\
            >::value\
         >::value\
      >::value\
   >::value


#include <ndnboost/type_traits/detail/has_binary_operator.hpp>

#undef NDNBOOST_TT_TRAIT_NAME
#undef NDNBOOST_TT_TRAIT_OP
#undef NDNBOOST_TT_FORBIDDEN_IF

#endif
