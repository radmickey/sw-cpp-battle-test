#pragma once

#include "Core/Units/UnitId.hpp"
#include "Position.hpp"

namespace sw::core
{
	class IMap
	{
	public:
		virtual ~IMap() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual bool isValid(const Position& pos) const = 0;
		virtual bool isOccupied(const Position& pos) const = 0;
		virtual void occupy(const Position& pos, UnitId id) = 0;
		virtual void free(const Position& pos, UnitId id) = 0;
	};
}
