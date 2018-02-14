#pragma once

template<typename CLASS>
class GameSingleton
{
protected:
	GameSingleton() {}
	~GameSingleton(){}
public:
	static CLASS& instance() {
		static CLASS instance;
		return instance;
	}

};

class test : public GameSingleton<test>{
public:
	test() {
		
	}

	
};