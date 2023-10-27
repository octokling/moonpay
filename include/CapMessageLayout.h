#pragma once

class CapMessageLayout
{
public:
    CapMessageLayout(char const*, char const*, al::LayoutInitInfo const&, char const*, bool);
    void startCore(CapMessageShowInfo const*, bool);

    char* field_0x32;
};