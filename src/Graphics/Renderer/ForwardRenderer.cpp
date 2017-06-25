#include "ForwardRenderer.h"

void ce::graphics::ForwardRenderer::init()
{
	m_commandQueue.reserve(1000);
}

void ce::graphics::ForwardRenderer::begin()
{
	glViewport(0, 0, m_screenBufferWidth, m_screenBufferHeight);

	m_commandQueue.clear();
	m_camera = nullptr;
}

void ce::graphics::ForwardRenderer::beginScene(Camera* camera)
{
	m_camera = camera;
}

void ce::graphics::ForwardRenderer::submit(const RenderCommand& command)
{
	m_commandQueue.push_back(command);
}

void ce::graphics::ForwardRenderer::submitMesh(Mesh* mesh, const glm::mat4 & transform)
{
	RenderCommand command;
	command.mesh = mesh;
	command.transform = transform;
	command.shader = mesh->material.shader;
	submit(command);
}

void ce::graphics::ForwardRenderer::submitLightSetup(const LightSetup& lightSetup)
{
	m_lightSetup = lightSetup;
}

void ce::graphics::ForwardRenderer::endScene()
{
}

void ce::graphics::ForwardRenderer::end()
{
	// TODO: Batching and sorting etc
}

void ce::graphics::ForwardRenderer::present()
{
	// TODO: Shader binding, texture sorting, visibility testing
	for (unsigned int i = 0; i < m_commandQueue.size(); i++)
	{
		RenderCommand& command = m_commandQueue[i];
		command.shader->use();

		if (command.mesh->material.hasProperty(MAT_BLEND))
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}

		// Temp: submit camera
		command.shader->setMat4("view", m_camera->getViewMatrix());
		command.shader->setMat4("projection", m_camera->getProjectionMatrix());

		// Temp: submit lights (later sort by shader making us only submit this once per shader per cycle)
		for (unsigned int x = 0; x < m_lightSetup.dirLights.size(); x++)
		{
			std::string xs = std::to_string(x);
			command.shader->setVec3("dirLights[" + xs + "].ambient", m_lightSetup.dirLights[x].ambient);
			command.shader->setVec3("dirLights[" + xs + "].diffuse", m_lightSetup.dirLights[x].diffuse);
			command.shader->setVec3("dirLights[" + xs + "].specular", m_lightSetup.dirLights[x].specular);
			command.shader->setVec3("dirLights[" + xs + "].direction", m_lightSetup.dirLights[x].direction);
		}

		for (unsigned int x = 0; x < m_lightSetup.dirLights.size(); x++)
		{
			std::string xs = std::to_string(x);
			command.shader->setVec3("pointLights[" + xs + "].ambient", m_lightSetup.pointLights[x].ambient);
			command.shader->setVec3("pointLights[" + xs + "].diffuse", m_lightSetup.pointLights[x].diffuse);
			command.shader->setVec3("pointLights[" + xs + "].specular", m_lightSetup.pointLights[x].specular);
			command.shader->setVec3("pointLights[" + xs + "].position", m_lightSetup.pointLights[x].position);

			command.shader->setFloat("pointLights[" + xs + "].constant", m_lightSetup.pointLights[x].constant);
			command.shader->setFloat("pointLights[" + xs + "].linear", m_lightSetup.pointLights[x].linear);
			command.shader->setFloat("pointLights[" + xs + "].quadratic", m_lightSetup.pointLights[x].quadratic);
		}

		for (unsigned int x = 0; x < m_lightSetup.dirLights.size(); x++)
		{
			std::string xs = std::to_string(x);
			command.shader->setVec3("spotLights[" + xs + "].ambient", m_lightSetup.spotLights[x].ambient);
			command.shader->setVec3("spotLights[" + xs + "].diffuse", m_lightSetup.spotLights[x].diffuse);
			command.shader->setVec3("spotLights[" + xs + "].specular", m_lightSetup.spotLights[x].specular);
			command.shader->setVec3("spotLights[" + xs + "].position", m_lightSetup.spotLights[x].position);
			command.shader->setVec3("spotLights[" + xs + "].direction", m_lightSetup.spotLights[x].direction);

			command.shader->setFloat("spotLights[" + xs + "].constant", m_lightSetup.spotLights[x].constant);
			command.shader->setFloat("spotLights[" + xs + "].linear", m_lightSetup.spotLights[x].linear);
			command.shader->setFloat("spotLights[" + xs + "].quadratic", m_lightSetup.spotLights[x].quadratic);

			command.shader->setFloat("spotLights[" + xs + "].cutOff", m_lightSetup.spotLights[x].cutOff);
			command.shader->setFloat("spotLights[" + xs + "].outerCutOff", m_lightSetup.spotLights[x].outerCutOff);
		}

		// Submit model matrix
		command.shader->setMat4("model", command.transform);

		// render
		command.mesh->draw();
	} // Next command
}