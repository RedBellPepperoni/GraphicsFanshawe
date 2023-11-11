#include "Animator.h"

namespace Robotron
{
	void Animator::SetMeshComponentRef(MeshComponent* comp)
	{
		meshComponent = comp;
	}

	void Animator::AddAnimationClip(const std::string& name, AnimationClip clip)
	{
		m_clips.emplace(name, clip);
	}

	void Animator::PlayClip(const std::string& name)
	{
		if(!meshComponent)
		{
			return;
		}
		 
		// find the clip with the given name
		ClipList::iterator itr = m_clips.find(name);

		if (itr != m_clips.end())
		{
			// if the clip is found set the current clip to point to the found clip
			currentClip = &itr->second;
		}

	}

	void Animator::Update(float deltatime)
	{
		// one of the refernces is null, so we skip animating
		if(!meshComponent || !currentClip)
		{
			return;
		}

		// Increase the animation time counter
		animationcountdown += deltatime;

		if (animationcountdown >= currentClip->playback)
		{
			
			// if enough time has pass according to the plat=yback time, we play the next frame of the animation
			NextFrame();
			animationcountdown = 0.0f;
		}
	}


	void Animator::NextFrame()
	{
		if (!meshComponent)
		{
			return;
		}

		if (animationframeIndex >= currentClip->framelist.size())
		{
			animationframeIndex = 0;
		}
		

		SharedPtr<Mesh> newmesh = currentClip->framelist[animationframeIndex];

		meshComponent->SetMesh(newmesh);

		animationframeIndex++;

	}
}