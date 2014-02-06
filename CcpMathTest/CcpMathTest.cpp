#include "gtest/gtest.h"

struct D3DVIEWPORT9
{
};


int main( int argc, char **argv ) 
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}