#include <iostream>
#include <app_skeleton.h>
#include <thread>

class Driver : public vkapp::Skeleton
{
public:
    void run()
    {
        update();
        render();
    }
    int analyze()
    {
        return 0;
    }
    int initialize() override
    {
        // Initialize framework
        {
            vkapp::Skeleton::Options initOpt;
            initOpt.m_gfxHeapSize = 4llu * 1024llu * 1024llu * 1024llu;
            const int res = initializeUtil(&initOpt);
            if (res != 0) return res;
        }
        return 0;
    }
    int update() override
    {
        return 0;
    }
    void render() override
    {
        // TODO
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    int finalize() override
    {
        return finalizeUtil();
    }
};

int main(int argc, const char* argv[])
{
    Driver driver;
    {
        const int res = driver.initialize();
        if (res != 0) return res;
    }
    driver.run();
    const int ret = driver.analyze();
    driver.finalize();
    return ret;
}