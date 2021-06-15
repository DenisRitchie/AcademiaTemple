#include <iostream>
#include "tools.h"
//#include "rlutil.h"
//using namespace rlutil;
int32_t main(int argc, char const *argv[])
{

    int32_t i = 0;
    std::string mario =
#include "mario.txt"
        ;
    //12100
    for (; i < 12100; i++)
    {
        resetColor();
        // ************************************************************
        // OJOS
        if (i == 2463)
        {
            setColor(4);
            for (; i < 2478; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2623)
        {
            setColor(4);
            for (; i < 2629; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2638)
        {
            setColor(4);
            for (; i < 2641; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2783)
        {
            setColor(4);
            for (; i < 2789; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2819)
        {
            setColor(4);
            for (; i < 2831; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2943)
        {
            setColor(4);
            for (; i < 2946; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 2988)
        {
            setColor(4);
            for (; i < 2991; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 3150)
        {
            setColor(4);
            for (; i < 3153; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 3307)
        {
            setColor(4);
            for (; i < 3310; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        // ************************************************************************
        // BOTONES
        if (i == 5217)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5224; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 5381)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5390; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 5531)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5540; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 5694)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5698; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 5758)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5762; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 5935)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 5942; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 6101)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 6108; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }
        if (i == 6275)
        {
            setBackgroundColor(3);
            setColor(3);
            for (; i < 6280; ++i)
                std::cout << mario[i];
            --i;
            continue;
        }

        // ************************************************************************
        // zapatos
        if (i == 8788)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 8821; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 8957)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9002; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9125)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9179; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9294)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9351; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9458)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9518; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9620)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9680; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9794)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9836; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9935)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9950; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 9974)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 9983; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 10080)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 10119; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 10220)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 10265; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 10355)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 10391; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 10911)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 10914; ++i)
                std::cout << mario[i];
            resetColor();
        }
        if (i == 10985)
        {
            setBackgroundColor(1);
            setColor(0);
            for (; i < 10997; ++i)
                std::cout << mario[i];
            resetColor();
        }

        // ************************************************************************
        //cara
        if (mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -111)
        {
            if (i < 6280)
            {
                setBackgroundColor(7);
                setColor(3);
                std::cout << mario[i];
                std::cout << mario[i + 1];
                std::cout << mario[i + 2];
                i += 2;
            }
            else
            {
                setBackgroundColor(1);
                setColor(2);
                std::cout << mario[i];
                std::cout << mario[i + 1];
                std::cout << mario[i + 2];
                i += 2;
            }
            continue;
        }
        // ************************************************************************
        // contorno
        if (mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -124 ||
            mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -128 ||
            mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -120 ||
            mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -116 ||
            mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -112)
        {
            setBackgroundColor(7);
            setColor(0);
            std::cout << mario[i];
            std::cout << mario[i + 1];
            std::cout << mario[i + 2];
            i += 2;
            continue;
        }
        // ************************************************************************
        // brazo y cabeza
        if (mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -109)
        {
            setBackgroundColor(1);
            setColor(1);
            std::cout << mario[i];
            std::cout << mario[i + 1];
            std::cout << mario[i + 2];
            i += 2;
            continue;
        }
        // **************************************************************************
        // cuerpo
        if (mario[i] == -30 && mario[i + 1] == -106 && mario[i + 2] == -110)
        {
            if (i < 11045)
            {
                setBackgroundColor(4);
                setColor(0);
                std::cout << mario[i];
                std::cout << mario[i + 1];
                std::cout << mario[i + 2];
                i += 2;
            }
            else
            {
                setBackgroundColor(1);
                setColor(0);
                std::cout << mario[i];
                std::cout << mario[i + 1];
                std::cout << mario[i + 2];
                i += 2;
            }
            continue;
        }
        setBackgroundColor(7);
        setColor(7);
        std::cout << mario[i];
    }

    std::cout << std::endl;
    resetColor();
    return 0;
}