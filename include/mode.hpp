#pragma once
#ifndef FABRIC_MODE_DECL_HPP
#define FABRIC_MODE_DECL_HPP
#include <cstdint>

namespace fabric
{
    
    /*
        I apologize for the names. I like to think I'm a more clever writer than I am.
    */
    enum class MemoryMode : uint8_t
    {
        // Just a sentinel value for prohibiting invalid usage/behavior
        Invalid = 0,
        /*
            In "Fast" mode, a strong_handle is akin to a unique_ptr, and weak_handles
            + raw_handles are effectively just raw pointers. This will provide the 
            fastest behavior, but removes the ability for replays, safety checks,
            or the reallocation/defrag/compacting functionality.
        */
       Fast = 1,
       /*
            In "Tense" mode we mostly benefit from some mild safety. This mode does
            cause a performance decline, but can be worth it for allowing large
            amounts of easier scaling to multiple cores. The main change is that
            dangling pointers don't cause segfaults or memory corruption, but
            instead throw exceptions that can be caught by user systems.
       */
      Tense = 2,
      /*
            In "taut" mode, we get the above safety with additional memory relocation
            and compacting routines, which can be especially useful for games that have
            long runtimes / uptimes (e.g, dedicated servers benefit from such things, potentially).
            Defragmenting of memory can also be performed too, performed by memory
            "category" set by the user. This way memory categories can be moved closer together, 
            then using supplied comparator functions and type hashes to further sort items 
            into new in-memory locations.
      */
     Taut = 3
    };

}

#endif
