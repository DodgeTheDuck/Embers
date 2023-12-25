#pragma once

namespace Core::Component {

	struct Base {
		std::string name;		
		entt::entity first{ entt::null };
		entt::entity prev{ entt::null };
		entt::entity next{ entt::null };
		entt::entity parent{ entt::null };
	};

}