#include "Sequencer.h"

namespace FanshaweGameEngine
{
	namespace Animation
	{


		void Sequencer::AddSequence(Sequence data)
		{

			m_SequenceList.push_back(data);
			//totalDuration += (data.duration);

		}

		void Sequencer::SetSeek(float seek)
		{
			 currentSeek = seek;
		}

		void Sequencer::Update(float deltaTime)
		{

			currentSeek = currentSeek + deltaTime;

			for (int index = 0; index < m_SequenceList.size(); index++)
			{
				m_SequenceList[index].Update(currentSeek,deltaTime);
			}


		}
		void Sequencer::SetTotalDuration(float duration)
		{
			totalDuration = duration;
		}
	}
}