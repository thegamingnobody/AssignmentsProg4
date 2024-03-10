#ifndef TRASHTHECACHE
#define TRASHTHECACHE

#include <vector>

namespace Trash
{
    struct transform
    {
        float matrix[16] = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        };
    };

    class GameObject
    {
    public:
        transform* local{};
        int id{};
    };

    struct Graph
    {
        std::vector<float> StepSizes{};
        std::vector<float> Timings{};
    };

    Graph CalculateTrashInt(int const samples);
    void DisplayIntWindow();
}

#endif