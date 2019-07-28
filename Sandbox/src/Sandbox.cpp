#include <egpch.h>
#include <Engine.h>

void TestQuat();

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		EG_TRACE("Sandbox.exe\n");
		PushLayer(new Engine::ImGuiLayer());
		

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
	
	glm::quat Quaternion;


	// Direct specification of the 4 components
	// You almost never use this directly	


	// Conversion from Euler angles (in radians) to Quaternion
	glm::vec3 EulerAngles(90, 45, 0);
	Quaternion = glm::quat(EulerAngles);
	
	// Conversion from axis-angle
	// In GLM the angle must be in degrees here, so convert it.
	//Quaternion = gtx::quat::angleAxis(glm::degrees(RotationAngle), RotationAxis);

	glm::mat4 RotationMatrix = glm::toMat4(Quaternion);

	EG_TRACE("Quaternion: |x: {0}| |y: {1}| |z: {2}| |w: {3}| |length: {4}|", Quaternion.x, Quaternion.y, Quaternion.z, Quaternion.w, Quaternion.length());
	EG_TRACE("RotationMatrix: |{0}		 {1}		 {2}		 {3}		| ", RotationMatrix[0][0], RotationMatrix[0][1], RotationMatrix[0][2], RotationMatrix[0][3]);
	EG_TRACE("		   : |{0}		 {1}		 {2}		 {3}		| ", RotationMatrix[1][0], RotationMatrix[1][1], RotationMatrix[1][2], RotationMatrix[1][3]);
	EG_TRACE("		   : |{0}		 {1}		 {2}		 {3}		| ", RotationMatrix[2][0], RotationMatrix[2][1], RotationMatrix[2][2], RotationMatrix[2][3]);
	EG_TRACE("		   : |{0}.0000	  	  {1}.0000		  {2}.0000		 {3}.0000		| ", RotationMatrix[3][0], RotationMatrix[3][1], RotationMatrix[3][2], RotationMatrix[3][3]);

	

}