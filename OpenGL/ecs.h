#pragma once
#include<iostream>
#include<vector>

struct Entities
{
	size_t id;
};

struct Transform
{

};

struct Health
{
};
struct Imge
{
};

class World {
	private:
		std::vector<Entities> entities;
		static unsigned int idCounter;
		static World* instance;
		World() = default;

	public :
		static World* GetInstance() {
				if (instance == nullptr) {
					instance = new World();
				}
				return instance;
		}
		Entities CreateEntity();
		void PrintEntities();
		template<typename ComponentType>
		void AddComponent(Entities entity , ComponentType);
		template<>
		void AddComponent<Transform>(Entities entity, Transform transform) {};

		void RemoveComponent(Entities entity);
};