#include <iostream>
#include "include/fengod_compare.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc <= 1)  // 在命令后面没参数时argc为1
    {
        std::cout << "Please input the file name."  << std::endl;
        return -1;       
    }
    // GauBlurCmp(cv::String(argv[1]));
    // CannyCmp(cv::String(argv[1]));
    // GauBlurVideoCmp(cv::String(argv[1]));
    CannyVideoCmp(cv::String(argv[1]));
    // BilFiltCmp(cv::String(argv[1]));
    // BilFiltVideoCmp(cv::String(argv[1]));
    // BilFiltVideoSav(cv::String(argv[1]));
    // CannyVideoSav(cv::String(argv[1]));
    return 0;
}

