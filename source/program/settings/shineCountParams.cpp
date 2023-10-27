#include "shineCountParams.hpp"

#include "logger/Logger.hpp"

SEAD_SINGLETON_DISPOSER_IMPL(shineCountParams)

shineCountParams::shineCountParams(){
    Logger::log("Params called !");
}

void shineCountParams::init(){
    
}