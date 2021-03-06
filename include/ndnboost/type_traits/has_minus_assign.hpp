//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef NDNBOOST_TT_HAS_MINUS_ASSIGN_HPP_INCLUDED
#define NDNBOOST_TT_HAS_MINUS_ASSIGN_HPP_INCLUDED

#define NDNBOOST_TT_TRAIT_NAME has_minus_assign
#define NDNBOOST_TT_TRAIT_OP -=
#define NDNBOOST_TT_FORBIDDEN_IF\
   ::ndnboost::type_traits::ice_or<\
      /* Lhs==pointer and Rhs==fundamental and Rhs!=integral */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Lhs_noref >::value,\
         ::ndnboost::is_fundamental< Rhs_nocv >::value,\
         ::ndnboost::type_traits::ice_not< ::ndnboost::is_integral< Rhs_noref >::value >::value\
      >::value,\
      /* Lhs==void* and Rhs==fundamental */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Lhs_noref >::value,\
         ::ndnboost::is_void< Lhs_noptr >::value,\
         ::ndnboost::is_fundamental< Rhs_nocv >::value\
      >::value,\
      /* Rhs==void* and Lhs==fundamental */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Rhs_noref >::value,\
         ::ndnboost::is_void< Rhs_noptr >::value,\
         ::ndnboost::is_fundamental< Lhs_nocv >::value\
      >::value,\
      /* Lhs=fundamental and Rhs=pointer */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_fundamental< Lhs_nocv >::value,\
         ::ndnboost::is_pointer< Rhs_noref >::value\
      >::value,\
      /* Lhs==pointer and Rhs==pointer */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::is_pointer< Lhs_noref >::value,\
         ::ndnboost::is_pointer< Rhs_noref >::value\
      >::value,\
      /* (Lhs==fundamental or Lhs==pointer) and (Rhs==fundamental or Rhs==pointer) and (Lhs==const) */\
      ::ndnboost::type_traits::ice_and<\
         ::ndnboost::type_traits::ice_or<\
            ::ndnboost::is_fundamental< Lhs_nocv >::value,\
            ::ndnboost::is_pointer< Lhs_noref >::value\
         >::value,\
         ::ndnboost::type_traits::ice_or<\
            ::ndnboost::is_fundamental< Rhs_nocv >::value,\
            ::ndnboost::is_pointer< Rhs_noref >::value\
         >::value,\
         ::ndnboost::is_const< Lhs_noref >::value\
      >::value\
   >::value


#include <ndnboost/type_traits/detail/has_binary_operator.hpp>

#undef NDNBOOST_TT_TRAIT_NAME
#undef NDNBOOST_TT_TRAIT_OP
#undef NDNBOOST_TT_FORBIDDEN_IF

#endif
