#ifndef JOB_COMPARATOR_HPP
#define JOB_COMPARATOR_HPP

#include "Job.hpp"

// Custom comparator for the priority queue (based on job priority)
class JobComparator {
public:
    bool operator()(const Job& a, const Job& b) const {
        return a.getPriority() < b.getPriority(); // Higher priority comes first (lower priority value)
    }
};

#endif // JOB_COMPARATOR_HPP