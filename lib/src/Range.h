#ifndef WERNICKE_RANGE_H
#define WERNICKE_RANGE_H

#include <cstddef>

class Range {

    std::size_t start_, end_;
    bool invert_;
public:
    Range(std::size_t start, std::size_t length, bool invert = false)
            : start_(start), end_(start + length), invert_(invert)
    {

    }

    /**
     * Covers all possible ranges
     */
    Range() : start_(0), end_(0), invert_(true){
    }

    bool contains(std::size_t i) {
        if (invert_) {
            return i < start_ || i >= end_;
        } else {
            return i >= start_ && i < end_;
        }
    }

};


#endif //WERNICKE_RANGE_H
