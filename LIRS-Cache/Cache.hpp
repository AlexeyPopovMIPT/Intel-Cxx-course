#ifndef __CACHE_HPP__
#define __CACHE_HPP__

#include <iostream>
#include <deque>
#include <cassert>


/*
 * Кэш с алгоритмом кэширования LIRS
 * http://web.cse.ohio-state.edu/hpcs/WWW/HTML/publications/papers/TR-02-6.pdf
 * 
 */
class Cache
{
    enum State
    {
        LIR = 0,
        HIR_RESIDENT = 1,
        HIR_NON_RESIDENT = 2
    };
    const char* STATES [3] = { "LIR   ", "HIR r ", "HIR nr" };

    struct Block
    {
        int value;
        State state;
    };

    std::deque<Block> lirs_;
    std::deque<int> hirs_;
    int l_lirs_;
    int l_hirs_;

    void pruning ();

    void makeResident (int value);

    void makeNonResident (int value);

    inline void removeFromHirs (std::deque<int>::const_iterator &&position);

    inline void removeFromHirs (std::deque<int>::const_iterator &position);


    inline void addToHirsFront (int value);

    void addToHirsBack (int value);

    void addToLirsFront (Block &&block);


    bool isLir (int that, std::deque<int>::const_iterator *hirs_iter, std::deque<Block>::const_iterator *lirs_iter) const;

    inline bool isLirsFull () const;
    inline bool isHirsFull () const;

public:

    Cache (int l_lirs, int l_hirs);

    bool hit (int &&that);

    void printState (FILE* out);

};


#endif // !__CACHE_HPP__
