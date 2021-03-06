#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include "euler.hh"

class Euler::Multiplyer
{
public:
  explicit Multiplyer( Euler* parent ) :
    parent_{ parent }
  {}

  Multiplyer( const Multiplyer& other, tbb::split ) :
    parent_{ other.parent_ }
  {}

  void join( const Multiplyer& other )
  {
    sum_ += other.sum_;
  }

  LongNumber get() { return std::move( sum_ ); }

  void operator()( const tbb::blocked_range< size_t >& range )
  {
    const size_t CACHE_SIZE = parent_->cache_.size();

    for ( size_t i = range.begin(); i != range.end(); ++i )
      sum_ += parent_->cache_[ i ] * parent_->cache_[ CACHE_SIZE - i - 1 ];
  }

private:
  Euler* const parent_; ///< указатель для доступа к кешу
  LongNumber      sum_; ///< сумма произведений подинтервала
};

Euler::Euler()
{
  cache_.push_back( 1 ); ///< 0-ой элемент последовательности
  cache_.push_back( 1 ); ///< 1-ый элемент последовательности
}

LongNumber Euler::get_member( size_t number_of_member,
                          size_t number_of_function )
{
  switch ( number_of_function )
  {
  case  1: return get_member1( number_of_member );
  case  2: return get_member2( number_of_member );
  case  3: return get_member3( number_of_member );
  default: return {};
  }
}

LongNumber Euler::get_member1( size_t number_of_member )
{
  size_t size = 0;

  while ( cache_.size() <= number_of_member )
  {
    sum_ = 0;

    size = cache_.size();

    for ( size_t i = 0; i < size; ++i )
      sum_ += cache_[ i ] * cache_[ size - i - 1 ];

    cache_.push_back( sum_ );
  }

  return cache_[ number_of_member ];
}

LongNumber Euler::get_member2( size_t number_of_member )
{
  size_t size = 0;

  while ( cache_.size() <= number_of_member )
  {
    sum_ = 0;

    size = cache_.size();

    for ( size_t i = 0; i < size / 2; ++i )
      sum_ += cache_[ i ] * cache_[ size - i - 1 ];

    sum_ <<= 1;

    if ( size % 2 )
      sum_ += pow( cache_[ size / 2 ], 2 );

    cache_.push_back( sum_ );
  }

  return cache_[ number_of_member ];
}

LongNumber Euler::get_member3( size_t number_of_member )
{
  size_t size = cache_.size();

  while ( size <= number_of_member )
  {
    Multiplyer multiplyer( this );

    tbb::parallel_reduce( tbb::blocked_range< size_t >( 0, size / 2 ),
                          multiplyer );

    sum_ = multiplyer.get();
    sum_ <<= 1;

    if ( size % 2 )
      sum_ += pow( cache_[ size / 2 ], 2 );

    cache_.push_back( sum_ );
    size = cache_.size();
  }

  return cache_[ number_of_member ];
}
