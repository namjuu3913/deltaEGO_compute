#include "VAD.hpp"

struct O1_Tasks_Result 
{
    VADPoint delta;
    double instant_stress;
    double affective_lability;
    double dopamine;
};

struct Cumulative_Result
{
    double stress_raw;
    double reward_raw;
    double ratio_total;
    double stress_ratio;
    double reward_ratio;
};