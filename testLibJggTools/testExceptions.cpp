/**
 * @file exceptionsValuesTest.cpp
 * @author Grandez
 * @date   09/2021
 * @brief Test invalid data passed in command line
 *
 * Type of parameter is defined in design time
 */

#include "pch.h"
#include <iostream>

#include "../libjggtools/code/include/exceptions.hpp"

using namespace std;

using namespace jggtools;

TEST(Exceptions, general) {
const char *data;
try {
   throw new ToolsException("exception");
} catch (ToolsException *ex) {
   data = ex->what();
}
EXPECT_EQ(strcmp(data, "exception"), 0);
}
