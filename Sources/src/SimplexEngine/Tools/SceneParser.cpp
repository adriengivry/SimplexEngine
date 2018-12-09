/**
* Project SimplexEngine
* @author Adrien Givry
* @version 1.0
*/

#include "SimplexEngine/Tools/SceneParser.h"

SimplexEngine::Components::CameraComponent const * SimplexEngine::Tools::SceneParser::GetMainCamera(const Scenes::AScene& p_scene)
{
	for (auto actor : p_scene.GetActors())
		if (auto camera = actor->GetComponent<Components::CameraComponent>(); camera != nullptr)
			return camera.get();

	return nullptr;
}

std::vector<std::reference_wrapper<const SimplexEngine::Components::CameraComponent>> SimplexEngine::Tools::SceneParser::FindCameras(const Scenes::AScene& p_scene)
{
	std::vector<std::reference_wrapper<const Components::CameraComponent>> result;

	for (auto actor : p_scene.GetActors())
		if (auto camera = actor->GetComponent<Components::CameraComponent>(); camera != nullptr)
			result.push_back(std::cref(*camera));

	return result;
}

std::vector<std::reference_wrapper<const SimplexEngine::Components::MeshComponent>> SimplexEngine::Tools::SceneParser::FindMeshes(const Scenes::AScene& p_scene)
{
	std::vector<std::reference_wrapper<const Components::MeshComponent>> result;

	for (auto actor : p_scene.GetActors())
		if (auto mesh = actor->GetComponent<Components::MeshComponent>(); mesh != nullptr)
			result.push_back(std::cref(*mesh));

	return result;
}
