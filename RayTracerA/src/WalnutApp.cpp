#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"
#include "Walnut/Timer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

#include <iostream>
#include <string>
#include <limits>
#include <memory>

#include "../Sphere.h"
#include "../HittableObjectList.h"
#include "../Camera.h"
#include "../Utility.h"

using namespace Walnut;

class Ray;

uint32_t CreateRGBA(float red, float green, float blue, float alpha)
{
	int r = (int)(Utility::Clamp(red, 0.0, 0.999) * 256);
	int g = (int)(Utility::Clamp(green, 0.0, 0.999) * 256);
	int b = (int)(Utility::Clamp(blue, 0.0, 0.999) * 256);
	int a = (int)(Utility::Clamp(alpha, 0.0, 0.999) * 256);

	return ((a & 0xff) << 24)  +((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);
}

glm::vec4 RayColor(const Ray& ray, const HittableObject& world) {
	HitEvent evt;
	if (world.Hit(ray, evt, 0, std::numeric_limits<double>::infinity())) {
		glm::vec3 col = (float)0.5 * (evt.normal + glm::vec3(1, 1, 1));
		return glm::vec4(col.x, col.y, col.z, 1.0);
	}

	float p = 0.5 * (glm::normalize(ray.dir).y + 1.0);
	glm::vec3 back_color = (1.0 - p) * glm::vec3(1.0, 1.0, 1.0) + p * glm::vec3(0.5, 0.7, 1.0);
	return glm::vec4(back_color.x, back_color.y, back_color.z, 1.0);
}

class ExampleLayer : public Walnut::Layer
{
public:	
	const int samples_per_pixel = 10;

	HittableObjectList world;

	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last render %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render")) {
			Render();
		}
		ImGui::Checkbox("Real time on CPU", &m_RealTimeOptionCPU);
		//ImGui::SliderFloat3("Sphere position", &sphere_pos.x, 0, 10);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		if(m_Image)
			ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_Image->GetWidth(), (float)m_Image->GetHeight() });

		ImGui::End();
		ImGui::PopStyleVar();

		if (m_RealTimeOptionCPU) {
			Render();
		}
	}

	

	void Render() {
		Timer timer;

		Camera camera{ (int)m_ViewportWidth, (int)m_ViewportHeight };

		world.Add(std::make_shared<Sphere>(0.5, glm::vec3(0, 0, -1)));
		world.Add(std::make_shared<Sphere>(100, glm::vec3(0, -100.5, -1)));

		if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight()) {
			m_Image = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight * 4];
		}

		for (uint32_t j = 0; j < m_ViewportHeight; j++) {
			for (uint32_t i = 0; i < m_ViewportWidth; i++) {			
				uint32_t color;

				glm::vec4 pixelColor = glm::vec4(0, 0, 0, 0);

				for (uint32_t s = 0; s < samples_per_pixel; s++) {
					float u = (i + Utility::RandomFloat()) / (m_ViewportWidth - 1);
					float v = (j + Utility::RandomFloat()) / (m_ViewportHeight - 1);
					Ray ray = camera.GetRay(u, v);
					pixelColor += RayColor(ray, world);
				}

				float scale = 1.0 / samples_per_pixel;
				glm::vec4 finalColor = glm::vec4(pixelColor.x * scale, pixelColor.y * scale, pixelColor.z * scale, 1.0);

				color = CreateRGBA(finalColor.x, finalColor.y, finalColor.z, 1);

				// Fill up array on reverse order
				m_ImageData[(m_ViewportWidth * m_ViewportHeight) - ( (j * m_ViewportWidth) + i)] = color;
			}
		}

		m_Image->SetData(m_ImageData);

		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = nullptr;
	uint32_t m_ViewportWidth, m_ViewportHeight;

	float m_LastRenderTime = 0;

	bool m_RealTimeOptionCPU;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "RayTracer - A";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}
