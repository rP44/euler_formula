#include <iostream>
#include <string>
#include <chrono>
#include <tbb/task_scheduler_init.h>
#include "euler.hh"
#include "format.hh"
#include "helper_functions.hh"

int main( int argc, char** argv )
{
  if ( argc < 4 ) //-V112
  {
    const auto msg = format(
      "%1%: error: too few program arguments\n"
      "Syntax:\n"
      "\t%1% <NUMBER_OF_MEMBER> <NUMBER_OF_FUNCTION> <COUNT_OF_THREADS>", argv[ 0 ] );

    std::cerr << msg << std::endl;

    return EXIT_FAILURE;
  }

  const size_t NUMBER_OF_MEMBER  { ( size_t )std::stoul( argv[ 1 ] ) };
  const size_t NUMBER_OF_FUNCTION{ ( size_t )std::stoul( argv[ 2 ] ) };
  /// используется только если выбрана фукция #3
  const size_t COUNT_OF_THREADS  { ( size_t )std::stoul( argv[ 3 ] ) };

  tbb::task_scheduler_init init{ static_cast< int >( COUNT_OF_THREADS ) };
  Euler euler;

  const auto start  = std::chrono::high_resolution_clock::now();
  const auto ANSWER = euler.get_member( NUMBER_OF_MEMBER, NUMBER_OF_FUNCTION );
  const auto stop   = std::chrono::high_resolution_clock::now();

  std::cout << format( "N == %1%\n%2%\n", NUMBER_OF_MEMBER, ANSWER ) << std::endl;
  print_time( stop - start );

  return EXIT_SUCCESS;
}
