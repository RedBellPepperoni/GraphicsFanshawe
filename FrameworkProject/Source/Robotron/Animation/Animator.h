#pragma once
#include "GameEngine.h"
#include <unordered_map>


using namespace FanshaweGameEngine;

namespace Robotron
{



	struct AnimationClip
	{
		std::vector<SharedPtr<Mesh>> framelist;
		// The time between 2 frames ( in seconds)
		float playback = 1.0f;

	};

	typedef std::unordered_map<std::string, AnimationClip> ClipList;

	class Animator
	{
	public:

		Animator() = default;
		~Animator() = default;

		void SetMeshComponentRef(MeshComponent* comp);

		void AddAnimationClip(const std::string& name, AnimationClip clip);

		void PlayClip(const std::string& name);

		void Update(float deltatime);

	private:


		void NextFrame();

		ClipList m_clips;

		float animationcountdown = 0.0f;

		int animationframeIndex = 0;

		AnimationClip* currentClip = nullptr;
		
		MeshComponent* meshComponent = nullptr;
	};
}
