//////////////////////////////////////////////////////////////////////////////
//
//   P h a m 
//
// copyright 2005-2021 Marc Hernandez
#pragma once






template<typename TimeT = std::chrono::microseconds>
struct Timer
{
    template<typename F, typename ...TParms>
    static typename TimeT::rep execution( const F &func, TParms... parms )
    {
        auto start = std::chrono::system_clock::now();
        func( parms... );
        auto duration = std::chrono::duration_cast<TimeT>(
            std::chrono::system_clock::now() - start );
        return duration.count();
    }
};

