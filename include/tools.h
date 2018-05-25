#pragma once

#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <iostream>

class Tools
{
    public:
        Tools();
        virtual ~Tools();
        static void debug(const std::string &str);
        static void err(const std::string &str);
};

#endif // TOOLS_H
