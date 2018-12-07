/**
* Project Rasterizer
* @author Adrien Givry
* @version 1.0
*/

#include "Rasterizer/Tools/SceneParser.h"

Rasterizer::Components::CameraComponent const * Rasterizer::Tools::SceneParser::GetMainCamera(const Scenes::AScene& p_scene)
{
	for (const std::unique_ptr<Rasterizer::Actors::Actor>& actor : p_scene.GetActors())
		if (auto camera = actor->GetComponent<Components::CameraComponent>(); camera != nullptr)
			return camera.get();

	return nullptr;
}

std::vector<std::reference_wrapper<const Rasterizer::Components::CameraComponent>> Rasterizer::Tools::SceneParser::FindCameras(const Scenes::AScene& p_scene)
{
	std::vector<std::reference_wrapper<const Components::CameraComponent>> result;

	for (const std::unique_ptr<Rasterizer::Actors::Actor>& actor : p_scene.GetActors())
		if (auto camera = actor->GetComponent<Components::CameraComponent>(); camera != nullptr)
			result.push_back(std::cref(*camera));

	return result;
}

std::vector<std::reference_wrapper<const Rasterizer::Components::MeshComponent>> Rasterizer::Tools::SceneParser::FindMeshes(const Scenes::AScene& p_scene)
{
	std::vector<std::reference_wrapper<const Components::MeshComponent>> result;

	for (const std::unique_ptr<Rasterizer::Actors::Actor>& actor : p_scene.GetActors())
		if (auto mesh = actor->GetComponent<Components::MeshComponent>(); mesh != nullptr)
			result.push_back(std::cref(*mesh));

	return result;
}
