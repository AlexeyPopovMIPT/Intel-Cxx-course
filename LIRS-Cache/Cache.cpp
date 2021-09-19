#include "Cache.hpp"

void Cache::pruning()
{
    while (lirs_.size() > 0 && lirs_.back().state != LIR)
        lirs_.pop_back();
}

void Cache::makeResident(int value)
{
    for (auto j = lirs_.begin(); j < lirs_.end(); j++)
        if (j->value == value)
            j->state = HIR_RESIDENT;
}

void Cache::makeNonResident(int value)
{
    for (auto j = lirs_.begin(); j < lirs_.end(); j++)
        if (j->value == value)
            j->state = HIR_NON_RESIDENT;
}

inline void Cache::removeFromHirs(std::deque<int>::const_iterator &&position)
{
    makeNonResident(*position);
    hirs_.erase(position);
}

inline void Cache::removeFromHirs(std::deque<int>::const_iterator &position)
{
    makeNonResident(*position);
    hirs_.erase(position);
}

inline void Cache::addToHirsFront(int value)
{
    if (!isHirsFull())
    {
        makeResident(value);
        hirs_.push_front(value);
    }
}

/*
 * @Issue: what should we do if there's not enough space?
 *         (assuming remove from \hirs_.front)
 */
void Cache::addToHirsBack(int value)
{
    makeResident(value);
    if (isHirsFull())
    {
        makeNonResident(hirs_.front());
        removeFromHirs(hirs_.begin());
    }
    hirs_.push_back(value);
}

/*
 * @Issue: what should we do if there's not enough space?
 *         (assuming move \lirs_.back to \hirs_.back)
 */
void Cache::addToLirsFront(Block &&block)
{
    bool lirsfull = isLirsFull();
    lirs_.push_front(block);
    if (lirsfull)
    {
        if (isHirsFull())
            removeFromHirs(hirs_.begin());
        hirs_.push_back(lirs_.back().value);
        lirs_.pop_back();
    }
}

bool Cache::isLir(int that, std::deque<int>::const_iterator *hirs_iter, std::deque<Block>::const_iterator *lirs_iter) const
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
                assert(0);
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

inline bool Cache::isLirsFull() const { return lirs_.size() == l_lirs_; }
inline bool Cache::isHirsFull() const { return hirs_.size() == l_hirs_; }

Cache::Cache(int l_lirs, int l_hirs) : l_lirs_(l_lirs),
                                       l_hirs_(l_hirs),
                                       hirs_(),
                                       lirs_()
{}

bool Cache::hit(int that)
{

    std::deque<Block>::const_iterator lirs_iter;
    std::deque<int>::const_iterator hirs_iter;

    bool isThatLirBlock = isLir(that, &hirs_iter, &lirs_iter);

    if (isThatLirBlock)
    {
        lirs_.erase(lirs_iter);
        lirs_.push_front({that, LIR});

        // if entry was originally at the bottom, pruning is needed
        pruning();

        return true;
    }

    if (hirs_iter != hirs_.end()) // if \that in \hirs_
    {
        // Here we come if \that is HIR resident

        if (lirs_iter != lirs_.end()) // if \that in \lirs_
        {
            // Move \that to the top of \lirs_ with status of LIR

            lirs_.erase(lirs_iter);
            lirs_.push_front({that, LIR});

            // remove \that from \hirs_

            hirs_.erase(hirs_iter);

            // load bottom of \lirs_ to the end of \hirs_

            addToHirsBack(lirs_.back().value);
            lirs_.pop_back();

            pruning();

            return true;
        }

        // move \that to the end of \hirs_

        hirs_.erase(hirs_iter); // Not "removeFromHirs (hirs_iter)", because we don't need to change status of \that
        hirs_.push_back(that);

        // move \that to the top of \lirs_

        addToLirsFront({that, HIR_RESIDENT});

        pruning();

        return true;
    }

    // here we come if \that is HIR non resident
    // or if it's absent in cache

    if (lirs_iter != lirs_.end())
    {
        // \that is HIR non resident

        // @Issue: is it a hit on cache?
        //         (assuming it isn't)
        // According to Wikipedia, we have to move the back of \lirs_ to
        // the back of \hirs_ only if \that has status of HIR non resident

        lirs_.erase(lirs_iter);
        lirs_.push_front({that, LIR});

        // replace back of \hirs_ by the back of \lirs_

        addToHirsBack(lirs_.back().value);
        lirs_.pop_back();

        pruning();
        return false;
    }

    // \that is absent on both \lirs_ and \hirs_

    // @Issue: according to the article, this snippet seemed to be at the beginning of function
    // (When LIR block set is not full, all the referenced blocks are given an LIR status).
    // But in this case snippet executes even if \that is HIR resident, ignoring required interaction
    // moving of \that in \hirs_.
    // @Assuming snippet should be there

    if (!isLirsFull())
    {
        // move \that to the front of \lirs_

        if (isThatLirBlock)
            lirs_.erase(lirs_iter);
        lirs_.push_front({that, LIR});

        pruning();

        return isThatLirBlock;
    }




    addToLirsFront({that, HIR_RESIDENT});

    // @Issue: should we trust Wikipedia (check line 197)?
    //         (assuming we should)

    addToHirsBack(that);

    pruning();

    return false;
}

void Cache::printState(FILE *out)
{
    fprintf(out, "   LIRS        HIRS\n");
    for (int i = 0; i < hirs_.size() || i < lirs_.size(); i++)
    {
        if (i < lirs_.size())
            fprintf(out, "|%2d %s|    ", lirs_[i].value, STATES[lirs_[i].state]);
        else
            fprintf(out, "               ");

        if (i < hirs_.size())
            fprintf(out, "|%2d|\n", hirs_[i]);
        else
            fprintf(out, "\n");
    }
    fprintf(out, "----------------------------------------\n");
}
