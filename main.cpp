#include "test.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

