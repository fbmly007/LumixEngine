#include "unit_tests/suite/lumix_unit_tests.h"
#include "engine/universe/universe.h"


namespace
{
	void UT_universe(const char* params)
	{
		Lumix::DefaultAllocator allocator;
		Lumix::PathManager path_manager(allocator);
		Lumix::Universe universe(allocator);
		LUMIX_EXPECT(!universe.hasEntity(Lumix::INVALID_ENTITY));
		LUMIX_EXPECT(!universe.hasEntity({0}));
		LUMIX_EXPECT(!universe.hasEntity({1}));
		LUMIX_EXPECT(!universe.hasEntity({100}));

		static const int ENTITY_COUNT = 5;

		Lumix::Vec3 p(0, 0, 0);
		Lumix::Quat r(0, 0, 0, 1);
		Lumix::Entity entities[ENTITY_COUNT];
		for (int i = 0; i < ENTITY_COUNT; ++i)
		{
			entities[i] = universe.createEntity(p, r);
		}
		universe.destroyEntity(entities[4]);
		entities[4] = universe.createEntity(p, r);

		universe.destroyEntity(entities[3]);
		entities[3] = universe.createEntity(p, r);

		universe.destroyEntity(entities[3]);
		universe.destroyEntity(entities[4]);
		entities[3] = universe.createEntity(p, r);
		entities[4] = universe.createEntity(p, r);

		universe.destroyEntity(entities[4]);
		universe.destroyEntity(entities[3]);
		entities[3] = universe.createEntity(p, r);
		entities[4] = universe.createEntity(p, r);

		universe.destroyEntity(entities[0]);
		universe.destroyEntity(entities[0]);
		entities[0] = universe.createEntity(p, r);

		for (int i = 0; i < ENTITY_COUNT; ++i)
		{
			universe.setPosition(entities[i], float(i), float(i), float(i));
			Lumix::Vec3 pos = universe.getPosition(entities[i]);
			LUMIX_EXPECT_CLOSE_EQ(pos.x, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.y, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.z, float(i), 0.00001f);
		}
		universe.destroyEntity(entities[1]);
		for (int i = 0; i < ENTITY_COUNT; ++i)
		{
			if (i == 1) continue;
			universe.setPosition(entities[i], float(i), float(i), float(i));
			Lumix::Vec3 pos = universe.getPosition(entities[i]);
			LUMIX_EXPECT_CLOSE_EQ(pos.x, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.y, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.z, float(i), 0.00001f);
		}
		entities[1] = universe.createEntity(p, r);
		for (int i = 0; i < ENTITY_COUNT; ++i)
		{
			universe.setPosition(entities[i], float(i), float(i), float(i));
			Lumix::Vec3 pos = universe.getPosition(entities[i]);
			LUMIX_EXPECT_CLOSE_EQ(pos.x, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.y, float(i), 0.00001f);
			LUMIX_EXPECT_CLOSE_EQ(pos.z, float(i), 0.00001f);
		}
	}
} // anonymous namespace

REGISTER_TEST("unit_tests/engine/universe", UT_universe, "");
