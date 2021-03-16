#include "SOOGL/Tests/speed_test.hpp"
#include "SOOGL/Tests/shader_creater.hpp"
#include "SOOGL/Tests/mesh_test.hpp"

int main()
{
	//sgl::tests::shader_creater_test();
	sgl::tests::mesh_test();
	return sgl::tests::speed_test_soogl_and_sfml();
}