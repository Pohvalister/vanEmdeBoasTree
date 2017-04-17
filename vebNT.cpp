#include "vebNT.h"
#include "my_math.h"
#include <vector>
#include <unordered_map>


#define valType unsigned long long int

enum activation {
    deactivated,
    minOnly,
    activated
};


class VEBTree : AbstractVEBTree {
    //conatins

    const unsigned int bytesVal;
    const unsigned int count;//сколько надо чанков чтобы поместить 2^поддеревья
    const unsigned long long int curSize;
    const unsigned long long int nextSize;//размер поддеревьев

    mutable std::unordered_map<unsigned long long, VEBTree *> clusters;
    VEBTree *summary;
    valType min;
    valType max;
    //\contains

public:
    activation status;

    VEBTree(unsigned int size) : status(deactivated), summary(nullptr),curSize(my_2_pow(size)),bytesVal(size),nextSize(my_2_pow(bytesVal / 2)),count(bytesVal-(bytesVal/2)) {
    };

    ~VEBTree(){
        for (auto pair : clusters)
            delete pair.second;
        if (summary!= nullptr)
            delete summary;
    }

    void add(unsigned long long x) {
        if (x >= curSize)
            return;
        if (status == deactivated) {
            min = max = x;
            status = minOnly;
        } else {
            if (min == x)return;

            if (min > x) std::swap(min, x);

            if (max < x) max = x;

            if (status == minOnly && summary == nullptr) {
                summary = new VEBTree(count);
            }
            status = activated;

            unsigned long long point = high(bytesVal, x);

            if (clusters.find(point) == clusters.end()) {
                clusters[point] = new VEBTree(bytesVal/2);
            }

            if (clusters[point]->status == deactivated)
                summary->add(point);

            clusters[point]->add(low(bytesVal, x));

        }
    }

    void remove(unsigned long long x) {
        if (x >= curSize)
            return;
        if (status == deactivated || status == minOnly) {
            if (status == minOnly && x == min)
                status = deactivated;
            return;
        }
        if (x == min) {
            x = clusters[summary->getMin()]->getMin() + summary->getMin() * nextSize;
            min = x;
        }
        unsigned long long point = high(bytesVal, x);
        if (clusters.find(point) == clusters.end())
            return;
        clusters[point]->remove(low(bytesVal, x));
        if (clusters[point]->status == deactivated)
            summary->remove(point);
        if (max == x)
            if (summary->status != deactivated)
                max = clusters[summary->getMax()]->getMax() + summary->getMax() * nextSize;
            else {
                max = min;
                status = minOnly;
            }
    }

    unsigned long long next(unsigned long long x) const {
        if (x >= curSize || status == deactivated)
            return NO;

        if (x < min)
            return min;
        if (status == minOnly)
            return NO;

#define maxInside clusters[high(bytesVal, x)]->getMax()
        if (clusters.find(high(bytesVal, x)) != clusters.end() && maxInside != NO && maxInside > low(bytesVal, x)) {
            return (x - low(bytesVal, x))/*firstPart*/+
                   clusters[high(bytesVal, x)]->next(low(bytesVal, x))/*secondPart*/;
        } else {
            unsigned long long firstPart = summary->next(high(bytesVal, x));
            if (firstPart == NO)
                return NO;
            return firstPart * nextSize + clusters[firstPart]->getMin();
        }
#undef maxInside

    }

    unsigned long long prev(unsigned long long x) const {
        if (status == deactivated)
            return NO;

        if (x > max)
            return max;
        if (status == minOnly)
            return NO;

#define minInside clusters[high(bytesVal, x)]->getMin()
        if (clusters.find(high(bytesVal, x)) != clusters.end() && minInside != NO && minInside < low(bytesVal, x)) {
            return (x - low(bytesVal, x))/*firstPart*/+
                   clusters[high(bytesVal, x)]->prev(low(bytesVal, x))/*secondPart*/;
        } else {
            unsigned long long firstPart = summary->prev(high(bytesVal, x));
            if (firstPart == NO)
                if (min < x)
                    return min;//cause min is not inside
                else
                    return NO;
            return firstPart * nextSize + clusters[firstPart]->getMax();
        }
#undef minInside

    }

    unsigned long long getMin() const {
        return (status == deactivated ? NO : min);
    }

    unsigned long long getMax() const {
        return (status == deactivated ? NO : max);
    }

};
