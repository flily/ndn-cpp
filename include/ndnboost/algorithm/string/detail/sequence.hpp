//  Boost string_algo library sequence.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef NDNBOOST_STRING_DETAIL_SEQUENCE_HPP
#define NDNBOOST_STRING_DETAIL_SEQUENCE_HPP

#include <ndnboost/algorithm/string/config.hpp>
#include <ndnboost/mpl/bool.hpp>
#include <ndnboost/mpl/logical.hpp>
#include <ndnboost/range/begin.hpp>
#include <ndnboost/range/end.hpp>

#include <ndnboost/algorithm/string/sequence_traits.hpp>

namespace ndnboost {
    namespace algorithm {
        namespace detail {

//  insert helpers  -------------------------------------------------//
        
            template< typename InputT, typename ForwardIteratorT >
            inline void insert(
                InputT& Input,
                NDNBOOST_STRING_TYPENAME InputT::iterator At,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                Input.insert( At, Begin, End );
            }

            template< typename InputT, typename InsertT >
            inline void insert(
                InputT& Input,
                NDNBOOST_STRING_TYPENAME InputT::iterator At,
                const InsertT& Insert )
            {
                ::ndnboost::algorithm::detail::insert( Input, At, ::ndnboost::begin(Insert), ::ndnboost::end(Insert) );
            }
           
//  erase helper  ---------------------------------------------------//

            // Erase a range in the sequence
            /*
                Returns the iterator pointing just after the erase subrange
            */
            template< typename InputT >
            inline typename InputT::iterator erase(
                InputT& Input,
                NDNBOOST_STRING_TYPENAME InputT::iterator From,
                NDNBOOST_STRING_TYPENAME InputT::iterator To )
            {
                return Input.erase( From, To );
            }

//  replace helper implementation  ----------------------------------//

            // Optimized version of replace for generic sequence containers
            // Assumption: insert and erase are expensive
            template< bool HasConstTimeOperations >
            struct replace_const_time_helper
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    NDNBOOST_STRING_TYPENAME InputT::iterator From,
                    NDNBOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    // Copy data to the container ( as much as possible )
                    ForwardIteratorT InsertIt=Begin;
                    NDNBOOST_STRING_TYPENAME InputT::iterator InputIt=From;
                    for(; InsertIt!=End && InputIt!=To; InsertIt++, InputIt++ )
                    {
                        *InputIt=*InsertIt;
                    }

                    if ( InsertIt!=End )
                    {
                        // Replace sequence is longer, insert it
                        Input.insert( InputIt, InsertIt, End );
                    }
                    else
                    {
                        if ( InputIt!=To )
                        {
                            // Replace sequence is shorter, erase the rest
                            Input.erase( InputIt, To );
                        }
                    }
                }
            };

            template<>
            struct replace_const_time_helper< true >
            {
                // Const-time erase and insert methods -> use them
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    NDNBOOST_STRING_TYPENAME InputT::iterator From,
                    NDNBOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    NDNBOOST_STRING_TYPENAME InputT::iterator At=Input.erase( From, To );
                    if ( Begin!=End )
                    {
                        if(!Input.empty())
                        {
                            Input.insert( At, Begin, End );
                        }
                        else
                        {
                            Input.insert( Input.begin(), Begin, End );
                        }
                    }
                }
            };

            // No native replace method
            template< bool HasNative >
            struct replace_native_helper
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    NDNBOOST_STRING_TYPENAME InputT::iterator From,
                    NDNBOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    replace_const_time_helper< 
                        ndnboost::mpl::and_<
                            has_const_time_insert<InputT>,
                            has_const_time_erase<InputT> >::value >()(
                        Input, From, To, Begin, End );
                }
            };

            // Container has native replace method
            template<>
            struct replace_native_helper< true >
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    NDNBOOST_STRING_TYPENAME InputT::iterator From,
                    NDNBOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    Input.replace( From, To, Begin, End );
                }
            };

//  replace helper  -------------------------------------------------//
        
            template< typename InputT, typename ForwardIteratorT >
            inline void replace(
                InputT& Input,
                NDNBOOST_STRING_TYPENAME InputT::iterator From,
                NDNBOOST_STRING_TYPENAME InputT::iterator To,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                replace_native_helper< has_native_replace<InputT>::value >()(
                    Input, From, To, Begin, End );
            }

            template< typename InputT, typename InsertT >
            inline void replace(
                InputT& Input,
                NDNBOOST_STRING_TYPENAME InputT::iterator From,
                NDNBOOST_STRING_TYPENAME InputT::iterator To,
                const InsertT& Insert )
            {
                if(From!=To)
                {
                    ::ndnboost::algorithm::detail::replace( Input, From, To, ::ndnboost::begin(Insert), ::ndnboost::end(Insert) );
                }
                else
                {
                    ::ndnboost::algorithm::detail::insert( Input, From, ::ndnboost::begin(Insert), ::ndnboost::end(Insert) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace ndnboost


#endif  // NDNBOOST_STRING_DETAIL_SEQUENCE_HPP
