#pragma once
#include "Engine/Core/Physics/Collision/Bounds/AABB.h"
#include "Engine/Utils/Logging/Log.h"
#include <unordered_map>

namespace FanshaweGameEngine
{
	namespace Physics
	{

		struct pair_hash 
		{
			template<typename T1, typename T2>
			size_t operator() (const std::pair<T1, T2>& pair) const {
				return (std::hash<T1>()(pair.first) * 0x1f1f1f1f)
					^ std::hash<T2>()(pair.second);
			}
		};


		template< typename _t>

		class grid
		{

		public:

			std::unordered_map<std::pair<int, int>, std::vector<_t>, pair_hash> m_grid;
		private:

			Vector3 m_cellSize;

		public:
			grid(const AABB& cellBounds)
				: m_cellSize(glm::compAdd(cellBounds.Max, -cellBounds.Min))
			{}

			grid(const Vector3& cellSize)
				: m_cellSize(cellSize)
			{
				if (cellSize.x < 0 || cellSize.y < 0)
				{
					LOG_ERROR("Negative Cell Size");
				}
			}

			grid(int cellSize)
				: m_cellSize(cellSize)
			{
				if (cellSize < 0)
				{
					LOG_ERROR("Negative Cell Size");
				}
			}


			grid() = default;
			grid(const grid& other) = default;
			~grid() = default;

			

			void foreach(const AABB& bounds,std::function<void(std::pair<int, int>, std::vector<_t>&)> func)
			{
				

				Vector3Int minPos = glm::floor(bounds.Min / m_cellSize);
				Vector3Int maxPos = glm::floor(bounds.Max / m_cellSize);

				for (int x = minPos.x; x <= maxPos.x; x++)
					for (int y = minPos.y; y <= maxPos.y; y++)
					{
						auto p = std::make_pair(x, y);
						func(p, m_grid[p]);
					}
			}

			void emplace(
				const _t& item,
				const AABB& bounds)
			{
				foreach(bounds, [&](auto p, auto& items) {
					items.push_back(item);
					});
			}

			void erase(
				const _t& item,
				const AABB& hint = AABB())
			{
				foreach(hint, [&](auto p, auto& items) {
					items.erase(std::find(items.begin(), items.end(), item));
					});
			}

			void clear() {
				m_grid.clear();
			}
		};


	}
}
