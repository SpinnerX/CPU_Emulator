#pragma once
#include <gtest/gtest.h>
#include "TestCase1.h"

int InitializeGoogletest(){
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}