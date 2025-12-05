#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool schedHelp (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t day, size_t col
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size();
    size_t k = avail[0].size();
    if (dailyNeed > k) {
        return false;
    }
    sched.resize(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<int> shifts(k, 0);
    return schedHelp(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);

}

bool schedHelp (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t day, size_t col
) {
    size_t n = avail.size();
    size_t k = avail[0].size();
    if (day == n) {
        return true;
    }

    size_t dayNext = day;
    size_t colNext = col + 1;

    if (colNext == dailyNeed) {
        dayNext = day + 1;
        colNext = 0;
    }

    for (Worker_T w = 0; w < k; w++) {
        if (avail[day][w]) {
            if (shifts[w] < (int) maxShifts) {
                bool working = false;
                if (find(sched[day].begin(), sched[day].begin() + col, w) != (sched[day].begin() + col)) {
                    working = true;
                }
                if (!working) {
                    sched[day][col] = w;
                    shifts[w]++;

                    if (schedHelp(avail, dailyNeed, maxShifts, sched, shifts, dayNext, colNext)) {
                        return true;
                    }
                    shifts[w]--;
                    sched[day][col] = INVALID_ID;
                }
            }
        }
    }
    return false;
}