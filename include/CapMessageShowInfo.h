#pragma once

class CapMessageShowInfo
{
public:
    CapMessageShowInfo(const char* String1, const char* String2, int, int, bool, bool);
    CapMessageShowInfo();

    const char* getMstxtName() const;
    const char* getLabelName() const;
};