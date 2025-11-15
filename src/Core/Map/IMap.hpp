#pragma once

#include "Core/Units/UnitId.hpp"

namespace sw::core
{
	class IPosition;
	class IMap
	{
	public:
		virtual ~IMap() = default;

		virtual uint32_t getDimensionSize(int index) const = 0;
		virtual int getDimensionCount() const = 0;
		virtual bool isValid(const IPosition& pos) const = 0;
		virtual bool isOccupied(const IPosition& pos) const = 0;
		virtual void occupy(const IPosition& pos, UnitId id) = 0;
		virtual void free(const IPosition& pos, UnitId id) = 0;
	};
}
