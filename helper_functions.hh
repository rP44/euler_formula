#pragma once
#ifndef HELPER_FUNCTIONS_HH
#define HELPER_FUNCTIONS_HH

#include <iostream> //cout, endl
#include <iomanip>  //setw
#include <chrono>   //duration_cast

template < class T >
void print_time( const T& duration )
{
  using namespace std::chrono;
  const size_t ALIGN_SIZE = 4; //-V112

  std::cout
    << "HOS" << std::setw( ALIGN_SIZE )
    << duration_cast< hours >( duration ).count()   % 24 << std::endl

    << "MIN" << std::setw( ALIGN_SIZE )
    << duration_cast< minutes >( duration ).count() % 60 << std::endl

    << "SEC" << std::setw( ALIGN_SIZE )
    << duration_cast< seconds >( duration ).count() % 60 << std::endl

    << "MIL" << std::setw( ALIGN_SIZE )
    << duration_cast< milliseconds >( duration ).count() % 1000 << std::endl

    << "MIC" << std::setw( ALIGN_SIZE )
    << duration_cast< microseconds >( duration ).count() % 1000 << std::endl

    << "NAN" << std::setw( ALIGN_SIZE )
    << duration_cast< nanoseconds >( duration ).count()  % 1000 << std::endl;
}

#endif
