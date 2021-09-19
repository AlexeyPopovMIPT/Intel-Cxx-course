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

    void pruning ()
    {
        while (lirs_.size() > 0 && lirs_.back().state != LIR)
            lirs_.pop_back();
    }

    void makeResident (int value)
    {
        for (auto j = lirs_.begin(); j < lirs_.end(); j++)
            if (j->value == value)
                j->state = HIR_RESIDENT;
    }

    void makeNonResident (int value)
    {
        for (auto j = lirs_.begin(); j < lirs_.end(); j++)
            if (j->value == value)
                j->state = HIR_NON_RESIDENT;
    }


    bool isLir (int that, std::deque<int>::const_iterator *hirs_iter, std::deque<Block>::const_iterator *lirs_iter) const
    {
        for (auto j = lirs_.begin(); j < lirs_.end(); j++)
        {
            if (j->value == that)
            {
                *lirs_iter = j;
                switch (j->state)
                {
                case LIR:
                    return true;

                case HIR_RESIDENT:
                    for (auto i = hirs_.begin(); i < hirs_.end(); i++)
                    {
                        if (*i == that)
                        {
                            *hirs_iter = i;
                            return false;
                        }
                    }
                    assert (0);
                    break;

                case HIR_NON_RESIDENT:
                    *hirs_iter = hirs_.end();
                    return false;

                }
            }
        }

        *lirs_iter = lirs_.end();
        for (auto i = hirs_.begin(); i < hirs_.end(); i++)
        {
            if (*i == that)
            {
                *hirs_iter = i;
                return false;
            }
        }

        *hirs_iter = hirs_.end();
        return false;

    }

    inline bool isLirsFull () { return lirs_.size() == l_lirs_; }
    inline bool isHirsFull () { return hirs_.size() == h_lirs_; }

public:

    Cache (int l_lirs, int l_hirs):
        l_lirs_(l_lirs),
        l_hirs_(l_hirs),
        hirs_(),
        lirs_()
    {}

    /*
     * top means front, bottom means back
     *                     end means back
     */
    bool hit (int &&that)
    {

        std::deque<Block>::const_iterator lirs_iter;
        std::deque<int>::const_iterator hirs_iter;

        bool isThatLirBlock = isLir (that, &hirs_iter, &lirs_iter);

        if (!isLirsFull())
        {
            // move \that to the front of \lirs_

            if (isThatLirBlock)
                lirs_.erase (lirs_iter);
            lirs_.push_front ({ that, LIR });

            return isThatLirBlock;
        }

        if (isThatLirBlock)
        {
            lirs_.erase (lirs_iter);
            lirs_.push_front ({ that, LIR });

            // if entry was originally at the bottom, pruning
            if (lirs_.end() - lirs_iter == 1)
                pruning ();
                
            return true;
        }

        if (hirs_iter != hirs_.end())
        {
            if (lirs_iter != lirs_.end())
            {
                // turn \that to LIR
                lirs_[lirs_iter - lirs_.begin()].state = LIR;

                // remove \that from \hirs_
                hirs_.erase (hirs_iter);

                // load bottom of \lirs_ to the end of \hirs_
                hirs_.push_back (lirs_.back().value);
                lirs_.pop_back();

                pruning ();

                return true;
            }

            // move \that to the top of \lirs_
            lirs_.push_front ({ that, HIR_RESIDENT });

            // move \that to the end of \hirs_
            hirs_.erase (hirs_iter);
            hirs_.push_back (that);

            return true;
        }

        // here we come if \that is HIR non resident 
        // or if it's absent in cache

        if (lirs_iter != lirs_.end())
        {
            lirs_.erase (lirs_iter);
            lirs_.push_front ({ that, LIR });

            // replace end of \hirs_ by the bottom of \lirs_

            if (isHirsFull())
            {
                makeNonResident (hirs_.front());
                hirs_.pop_front();
            }
            hirs_.push_back (lirs_.back().value);
            makeResident (lirs_.back().value);
            lirs_.pop_back();

            pruning ();
            return false;
        }

        lirs_.push_front ({ that, HIR_RESIDENT });

        if (isHirsFull())
        {
            makeNonResident (hirs_.front());
            hirs_.pop_front();
        }
        hirs_.push_back (that);

        return false;
    }

    void printState (FILE* out)
    {
        fprintf (out, "   LIRS    HIRS\n");
        for (int i = 0; i < hirs_.size() || i < lirs_.size(); i++)
        {
            if (i < lirs_.size())
                fprintf (out, "|%2d %s| ", lirs_[i].value, STATES[lirs_[i].state]);
            else
                fprintf (out, "            ");

            if (i < hirs_.size())
                fprintf (out, "|%2d|\n", hirs_[i]);
            else
                fprintf (out, "\n");
            
        }
        fprintf (out, "----------------------------------------\n");
    }

};


void testFromPaper (Cache *cache)
{
    FILE *dump = fopen ("dump.txt", "w");
    if (dump == nullptr)
        return;

    cache->hit (1);
    cache->printState (dump);
    cache->hit (4);
    cache->printState (dump);
    cache->hit (2);
    cache->printState (dump);
    cache->hit (3);
    cache->printState (dump);
    cache->hit (2);
    cache->printState (dump); 
    cache->hit (1);
    cache->printState (dump);
    cache->hit (4);
    cache->printState (dump);
    cache->hit (1);
    cache->printState (dump);
    cache->hit (5);
    cache->printState (stdout);
    
}

int main ()
{
    Cache cache (2, 1);
    testFromPaper (&cache);

}
