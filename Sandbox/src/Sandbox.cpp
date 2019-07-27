
#include <Engine.h>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

void TestQuat();

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		EG_TRACE("Sandbox.exe\n");
		TestQuat();
	}

	~Sandbox()
	{

	}

};

Engine::Application* Engine::CreateApplication()
{

		
	return new Sandbox();
}
//------------------------------------------------------------------------------------------------------------------------
void TestQuat()
{
	// Creates an identity quaternion (no rotation)
	glm::quat MyQuaternion;

	// Direct specification of the 4 components
	// You almost never use this directly
	MyQuaternion = glm::quat(1, 0.1, 0.1, 0.1);

	// Conversion from Euler angles (in radians) to Quaternion
	glm::vec3 EulerAngles(90, 45, 0);
	MyQuaternion = glm::quat(EulerAngles);

	// Conversion from axis-angle
	// In GLM the angle must be in degrees here, so convert it.

	EG_INFO("Quaternion: |x: {0}| |y: {1}| |z: {2}| |w: {3}| |length: {4}|", MyQuaternion.x, MyQuaternion.y, MyQuaternion.z, MyQuaternion.w, MyQuaternion.length());

}