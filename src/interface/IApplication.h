#pragma once

class IApplication {
public:
	virtual ~IApplication() {};
	virtual void OnUpdate() = 0;
};
