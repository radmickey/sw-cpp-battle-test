#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace sw
{
	class TypeRegistry
	{
	private:
		std::unordered_map<std::type_index, std::shared_ptr<void>> _instances;

	public:
		TypeRegistry() = default;

		TypeRegistry(const TypeRegistry&) = delete;
		TypeRegistry& operator=(const TypeRegistry&) = delete;

		TypeRegistry(TypeRegistry&&) = default;
		TypeRegistry& operator=(TypeRegistry&&) = default;

		template <typename T, typename... Interfaces, typename... Args>
		std::shared_ptr<T> emplace(Args&&... args)
		{
			static_assert((std::is_base_of_v<Interfaces, T> && ...), "T must inherit from all specified interfaces");

			auto instance = std::make_shared<T>(std::forward<Args>(args)...);
			_instances[std::type_index(typeid(T))] = instance;
			((_instances[std::type_index(typeid(Interfaces))] = instance), ...);
			return instance;
		}

		template <typename T, typename... Interfaces>
		void add(std::shared_ptr<T> instance)
		{
			static_assert((std::is_base_of_v<Interfaces, T> && ...), "T must inherit from all specified interfaces");

			_instances[std::type_index(typeid(T))] = instance;
			((_instances[std::type_index(typeid(Interfaces))] = instance), ...);
		}

		template <typename T>
		std::shared_ptr<T> get() const
		{
			auto it = _instances.find(std::type_index(typeid(T)));
			if (it != _instances.end())
			{
				return std::static_pointer_cast<T>(it->second);
			}
			return nullptr;
		}
	};
}
